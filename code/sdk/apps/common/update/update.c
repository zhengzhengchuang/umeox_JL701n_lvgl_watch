#include "update.h"
#include "update_loader_download.h"
#include "asm/crc16.h"
#include "asm/wdt.h"
#include "os/os_api.h"
#include "app_config.h"
#include "cpu.h"
#include "syscfg_id.h"
#include "btcontroller_modules.h"
#include "system/includes.h"
#include "uart_update.h"
#include "dual_bank_updata_api.h"
#include "btstack/avctp_user.h"

#if TCFG_UI_ENABLE
#include "ui/ui_api.h"
#endif

#if RCSP_BTMATE_EN
#include "rcsp_user_update.h"
#elif RCSP_ADV_EN
#include "rcsp_adv_user_update.h"
#endif

#ifdef UPDATE_VOICE_REMIND
#include "tone_player.h"
#include "audio_config.h"
#endif

#ifdef UPDATE_LED_REMIND
#include "asm/pwm_led.h"
#endif

#include "custom_cfg.h"

#define LOG_TAG "[APP-UPDATE]"
#define LOG_INFO_ENABLE
#define LOG_ERROR_ENABLE
#include "system/debug.h"

#define LOADER_NAME		"LOADER.BIN"
#define DEVICE_UPDATE_KEY_ERR  BIT(30)
#define DEVICE_FIRST_START     BIT(31)

extern void update_module_init(void (*cbk)(update_mode_info_t *, u32, void *));
extern void testbox_update_init(void);
extern void ll_hci_destory(void);
extern void hci_controller_destory(void);
extern const int support_norflash_update_en;
extern void ram_protect_close(void);
extern void hwi_all_close(void);
extern void wifi_det_close();

__attribute__((weak))
void wifi_det_close()
{
    printf("tmp weak func wifi_det_close\n");
}
extern void *dev_update_get_parm(int type);
extern u8 get_ota_status();
extern int get_nor_update_param(void *buf);
extern bool get_tws_phone_connect_state(void);
extern void tws_sniff_controle_check_disable(void);
extern void tws_tx_unsniff_req(void);
extern void sys_auto_sniff_controle(u8 enable, u8 *addr);
extern void app_audio_set_wt_volume(s16 volume);
extern u8 get_max_sys_vol(void);
extern u8 get_ldo_trim_res(u8 *res);


#ifdef DEV_UPDATE_SUPPORT_JUMP
extern void __JUMP_TO_MASKROM();
extern void save_spi_port();
extern s32 sd1_unmount(void);
extern void usb_sie_close_all(void);
#endif      //endif DEV_UPDATE_SUPPORT_JUMP

extern const int support_update_backup_btif_addr;
extern const int support_norflash_update_en;
const u8 loader_file_path[] = "mnt/norflash/C/"LOADER_NAME"";
//升级文件路径必须是短文件名（8+3）结构，仅支持２层目录
/* const char updata_file_name[] = "/UPDATA/JL_692X.BFU"; */
const char updata_file_name[] = "/*.UFW";
static u32 g_updata_flag = 0;
static volatile u8 ota_status = 0;
static succ_report_t succ_report;
static bool g_write_vm_flag = true;
static u32 g_cur_update_type = 0;

bool is_testbox_ble_update_type(void)
{
    return (BLE_TEST_UPDATA == g_cur_update_type);
}

int syscfg_write_update_check(u16 item_id, void *buf, u16 len)
{
    return g_write_vm_flag;
}

bool vm_need_recover(void)
{
    if (support_update_backup_btif_addr) {
        // 在这里面进行btif的还原，不然在vm初始哈后还原，对于的flash内容会被擦掉
        after_update_btif_resume(g_updata_flag & 0xffff);
    }
    return (((g_updata_flag & 0xffff) == UPDATA_SUCC) ? true : false
            || ((g_updata_flag & 0xffff) == UPDATA_DEV_ERR) ? true : false);
}

u16 update_result_get(void)
{
    u16 ret = UPDATA_NON;

    if (!UPDATE_SUPPORT_DEV_IS_NULL()) {
        UPDATA_PARM *p = UPDATA_FLAG_ADDR;
        u16 crc_cal;
        crc_cal = CRC16(((u8 *)p) + 2, sizeof(UPDATA_PARM) - 2);	//2 : crc_val
        if (crc_cal && crc_cal == p->parm_crc) {
            ret =  p->parm_result;
        }
        g_updata_flag = ret;
        g_updata_flag |= ((u32)(p->magic)) << 16;

        memset(p, 0x00, sizeof(UPDATA_PARM));
    }

    return ret;
}

void update_result_set(u16 result)
{
    if (!UPDATE_SUPPORT_DEV_IS_NULL()) {
        UPDATA_PARM *p = UPDATA_FLAG_ADDR;

        memset(p, 0x00, sizeof(UPDATA_PARM));
        p->parm_result = result;
        p->parm_crc = CRC16(((u8 *)p) + 2, sizeof(UPDATA_PARM) - 2);
    }
}
void update_clear_result()
{
    g_updata_flag = 0;
}

bool update_success_boot_check(void)
{
    if (!UPDATE_SUPPORT_DEV_IS_NULL()) {
        u16 result = g_updata_flag & 0xffff;
        u16 up_tpye = g_updata_flag >> 16;
        /* if ((UPDATA_SUCC == result) && ((SD0_UPDATA == up_tpye) || (SD1_UPDATA == up_tpye) || (USB_UPDATA == up_tpye))) { */
        if (UPDATA_SUCC == result) {
            if (support_dual_bank_update_en) {
                return true;
            } else {
                switch (up_tpye) {
                case SD0_UPDATA:
                case SD1_UPDATA:
                case USB_UPDATA:
                case UART_UPDATA:
                case BT_UPDATA:
                case BLE_APP_UPDATA:
                case BLE_TEST_UPDATA:
                case DUAL_BANK_UPDATA:
                    return true;
                }
            }
        }
    }
    return false;
}

bool device_is_first_start()
{
    log_info("g_updata_flag=0x%x\n", g_updata_flag);
    if ((g_updata_flag & DEVICE_FIRST_START) || (g_updata_flag & DEVICE_UPDATE_KEY_ERR) || (g_updata_flag == UPDATA_SUCC)) {
        puts("\n=================device_is_first_start=========================\n");
        return true;
    }
    return false;
}

void led_update_start(void)
{
#ifdef UPDATE_LED_REMIND
    puts("led_update_start\n");
    pwm_led_mode_set(PWM_LED_ALL_OFF);
#endif
}

void led_update_finish(void)
{
#ifdef UPDATE_LED_REMIND
    puts("led_update_finish\n");
    pwm_led_mode_set(PWM_LED0_LED1_FAST_FLASH);
#endif
}

static inline void dev_update_close_ui()
{

#if (TCFG_UI_ENABLE&&(CONFIG_UI_STYLE == STYLE_JL_LED7))
    u8 count = 0;
    UI_SHOW_WINDOW(ID_WINDOW_POWER_OFF);
__retry:
    if (UI_GET_WINDOW_ID() != ID_WINDOW_POWER_OFF) {
        /* os_time_dly(10);//增加延时防止没有关显示，由于此处关了中断，不能用os接口 */
        delay_2ms(50);//增加延时防止没有关显示
        count++;
        if (count < 3) {
            goto __retry;
        }
    }
#endif
}
#ifdef UPDATE_VOICE_REMIND
void update_tone_event_clear()
{
    struct sys_event e = {0};
    e.type = SYS_DEVICE_EVENT;
    e.arg  = (void *)DEVICE_EVENT_FROM_TONE;
    sys_event_clear(&e);
}
#endif

int update_result_deal()
{
#ifdef CONFIG_FPGA_ENABLE
    return 0;
#endif

    u8 key_voice_cnt = 0;
    u16 result = 0;
    result = (g_updata_flag & 0xffff);
    log_info("<--------update_result_deal=0x%x %x--------->\n", result, g_updata_flag >> 16);
#ifdef  CONFIG_DEBUG_ENABLE
#if TCFG_APP_BT_EN
    /* u8 check_update_param_len(void); */
    /* ASSERT(check_update_param_len(), "UPDATE_PARAM_LEN ERROR"); */
#endif
#endif
    if (result == UPDATA_NON || 0 == result) {
        return 0;
    }
#ifdef UPDATE_VOICE_REMIND
#endif
    if (result == UPDATA_SUCC) {
#if(JL_EARPHONE_APP_EN && RCSP_UPDATE_EN)
        u8 clear_update_flag = 0;
        syscfg_write(VM_UPDATE_FLAG, &clear_update_flag, 1);
#endif
#ifdef UPDATE_LED_REMIND
        led_update_finish();
#endif
    }

    int voice_max_cnt = 5;
    while (1) {
        wdt_clear();
        key_voice_cnt++;
#ifdef UPDATE_VOICE_REMIND
        if (result == UPDATA_SUCC) {
            puts("<<<<<<UPDATA_SUCC");
            app_audio_set_volume(APP_AUDIO_STATE_WTONE, get_max_sys_vol() / 2, 1);
            tone_play(TONE_SIN_NORMAL, 1);
            os_time_dly(25);
            puts(">>>>>>>>>>>\n");
            update_tone_event_clear();
        } else {
            voice_max_cnt = 20; //区分下升级失败提示音
            log_info("!!!!!!!!!!!!!!!updata waring !!!!!!!!!!!=0x%x\n", result);
            app_audio_set_volume(APP_AUDIO_STATE_WTONE, get_max_sys_vol(), 1);
            tone_play(TONE_SIN_NORMAL, 1);
            os_time_dly(10);
            update_tone_event_clear();
        }
#endif
        if (key_voice_cnt > voice_max_cnt) {
            key_voice_cnt = 0;
            puts("enter_sys_soft_poweroff\n");
            break;
            //注:关机要慎重,要设置开机键
            //enter_sys_soft_poweroff();
        }
    }

    return 1;
}

void clr_update_ram_info(void)
{
    UPDATA_PARM *p = UPDATA_FLAG_ADDR;
    memset(p, 0x00, sizeof(UPDATA_PARM));
}

void update_close_hw(void *filter_name)
{
    const struct update_target *p;
    list_for_each_update_target(p) {
        if (memcmp(filter_name, p->name, strlen(filter_name)) != 0) {
            printf("close Hw Name : %s\n", p->name);
            p->driver_close();
        }
    }
}

static void update_before_jump_common_handle(UPDATA_TYPE up_type)
{
    dev_update_close_ui();

#if TCFG_AUDIO_ANC_ENABLE
    extern void audio_anc_hw_close();
    audio_anc_hw_close();
#endif

#if (CPU_CORE_NUM == 1)         //双核在跳转前关中断lock_set后会和maskrom 初始化中断冲突导致ilock err
    local_irq_disable();
#endif

    hwi_all_close();

#ifdef CONFIG_SUPPORT_WIFI_DETECT
    wifi_det_close();
#endif
    /*跳转的时候遇到死掉的情况很可能是硬件模块没关导致，加上保护可以判断哪个异常，保护的地址根据不同SDK而定*/
    /* u8 inv = 0; */
    /* mpu_set(1, (u32)&test_pro_addr, (u32)test_pro_addr, inv, "0r", DBG_FM); */

}

//ota.bin 放到exflash升级的方式，parm_priv存放了norflash的参数，对应实际升级方式的参数需要放在norflash参数之后
void update_param_priv_fill(UPDATA_PARM *p, void *priv, u16 priv_len)
{
    int parm_offset = 0;
    if (support_norflash_update_en) {
        parm_offset = get_nor_update_param(p->parm_priv);          //如果loader放在外挂norflash,parm_priv前面放norflash参数，后面才是升级类型本身的参数
    }
    memcpy(p->parm_priv + parm_offset, priv, priv_len);
}

void update_param_ext_fill(UPDATA_PARM *p, u8 ext_type, u8 *ext_data, u8 ext_len)
{
    struct ext_arg_t ext_arg;

    ext_arg.type = ext_type;
    ext_arg.len  = ext_len;
    ext_arg.data = ext_data;

    memcpy((u8 *)p + sizeof(UPDATA_PARM) + p->ext_arg_len, &ext_arg, 2);          //2byte:type + len
    memcpy((u8 *)p + sizeof(UPDATA_PARM) + p->ext_arg_len + 2, ext_arg.data, ext_arg.len);
    log_info("ext_fill :");
    log_info_hexdump((u8 *)p + sizeof(UPDATA_PARM) + p->ext_arg_len, ext_arg.len + 2);
    p->ext_arg_len += (2 + ext_arg.len);
    p->ext_arg_crc = CRC16((u8 *)p + sizeof(UPDATA_PARM), p->ext_arg_len);
}

//fill common content \ private content \ crc16
static void update_param_content_fill(int type, UPDATA_PARM *p, void (*priv_param_fill_hdl)(UPDATA_PARM *P))
{
    u8 ext_len = 0;
    u8 *ext_data = NULL;

    memset((u8 *)p, 0x00, sizeof(UPDATA_PARM));

    if (support_norflash_update_en) {
        p->parm_type = NORFLASH_UPDATA;                                //uboot通过该标识从外挂flash读取ota.bin
        *((u16 *)((u8 *)p + sizeof(UPDATA_PARM) + 32)) = (u16)type;    //将实际的升级类型保存到UPDATA_PARM后
    } else {
        p->parm_type = (u16)type;
    }

    p->parm_result = (u16)UPDATA_READY;
    p->magic = UPDATE_PARAM_MAGIC;
    p->ota_addr = succ_report.loader_saddr;
    if (support_update_backup_btif_addr && succ_report.priv_param) {
        // 更新ext_arg_len，更新对应内容
        p->ext_arg_len += update_res_param_opt(succ_report.priv_param, 0, (u8 *)p + sizeof(UPDATA_PARM), 0);
    }

    //支持loader放到外挂flash里ota_addr为0
    if (0 == p->ota_addr && !support_norflash_update_en) {
        log_error("ota addr err\n");
        return;
    }

    if (priv_param_fill_hdl) {
        priv_param_fill_hdl(p);
    }

#ifdef CONFIG_CPU_BR23
#if TCFG_APP_BT_EN
    if (type == BT_UPDATA || type == BLE_APP_UPDATA || type == SPP_APP_UPDATA || type == BLE_TEST_UPDATA) {     //D版芯片蓝牙相关的升级需要保存LDO_TRIM_RES
        ext_data = malloc(128);
        if (ext_data != NULL) {
            ext_len = get_ldo_trim_res(ext_data);
            update_param_ext_fill(p, EXT_LDO_TRIM_RES, ext_data, ext_len);
            free(ext_data);
        }
    }
#endif
#endif
    u8 ext_flag = 0;
    ext_len = 1;
#if CONFIG_UPDATE_JUMP_TO_MASK
    ext_flag = 1;
#endif
    update_param_ext_fill(p, EXT_JUMP_FLAG, &ext_flag, ext_len);
    /* u8 *flag = update_param_ext_get(p, EXT_JUMP_FLAG); */
    /* r_printf(">>>[test]:flag = %d\n", flag[0]); */

#if USER_FILE_UPDATE_V2_EN
    extern u8 reserve_file_flag_get(void);
    ext_flag = reserve_file_flag_get();
    update_param_ext_fill(p, EXT_RESERVED_UPDATE, &ext_flag, ext_len);
#endif

    p->parm_crc = CRC16(((u8 *)p) + 2, sizeof(UPDATA_PARM) - 2);	//2 : crc_val
}

static void update_param_ram_set(u8 *buf, u16 len)
{
    u8 *update_ram = UPDATA_FLAG_ADDR;
    memcpy(update_ram, (u8 *)buf, len);
}

__attribute__((weak))
void update_process_before_cpu_reset(void)
{

}

void update_mode_api_v2(UPDATA_TYPE type, void (*priv_param_fill_hdl)(UPDATA_PARM *p), void (*priv_update_jump_handle)(int type))
{
    u16 update_param_len = sizeof(UPDATA_PARM) + UPDATE_PRIV_PARAM_LEN;

    UPDATA_PARM *p = malloc(update_param_len);

    if (p) {
        update_param_content_fill(type, p, priv_param_fill_hdl);

        if (succ_report.update_param_write_hdl) {
            succ_report.update_param_write_hdl(succ_report.priv_param, (u8 *)p, update_param_len);
        }

        update_process_before_cpu_reset();

        //临时修改，升级不能跑太快的时钟，否则升级失败
        clk_set("sys", 48000000);

#ifdef UPDATE_LED_REMIND
        led_update_start();
#endif

        update_param_ram_set((u8 *)p, update_param_len);

#if CPU_CORE_NUM > 1            //双核需要把CPU1关掉
        printf("Before Suspend Current Cpu ID:%d Cpu In Irq?:%d\n", current_cpu_id(),  cpu_in_irq());
        if (current_cpu_id() == 1) {
            os_suspend_other_core();
        }
        ASSERT(current_cpu_id() == 0);          //确保跳转前CPU1已经停止运行
        cpu_suspend_other_core(0x55);
        extern void cpu1_power_off(void);
        cpu1_power_off();
        printf("After Suspend Current Cpu ID:%d\n", current_cpu_id());
#endif
        update_before_jump_common_handle(type);

        if (priv_update_jump_handle) {
            priv_update_jump_handle(type);
        }
        free(p);
    } else {
        ASSERT(p, "malloc update param err \n");
    }
}

int update_check_sniff_en(void)

{
    if (!UPDATE_SUPPORT_DEV_IS_NULL()) {
        if (get_ota_status()) {
            log_info("ota ing...");
            return 0;
        } else {
            return 1;
        }
    }
    return 1;
}


void set_ota_status(u8 stu)
{
    ota_status = stu;
}

u8 get_ota_status()
{
    return ota_status;
}

static u8 ota_idle_query(void)
{
    return !ota_status;
}

//防止升级过程进入powerdown
REGISTER_LP_TARGET(ota_lp_target) = {
    .name = "ota",
    .is_idle = ota_idle_query,
};

extern void tws_sync_update_api_register(const update_op_tws_api_t *op);
extern update_op_tws_api_t *get_tws_update_api(void);

extern const int support_dual_bank_update_en;
extern int tws_ota_init(void);
extern void sys_auto_shut_down_disable(void);
extern void sys_auto_shut_down_enable(void);
extern void tws_api_auto_role_switch_disable();
extern void tws_api_auto_role_switch_enable();

#if FLASH_PROTECT_OPT_BEFORE_UPDATE
extern int  norflash_set_write_protect(u32 enable);
#endif

static void update_init_common_handle(int type)
{
    ota_status = 1;
    g_cur_update_type = type;
#if FLASH_PROTECT_OPT_BEFORE_UPDATE
    // 兼容双备份，升级开始就解除flash保护
    printf("%s, remove_flash_protect\n", __func__);
    norflash_set_write_protect(0);
#endif
    if (UPDATE_DUAL_BANK_IS_SUPPORT()) {
#if TCFG_AUTO_SHUT_DOWN_TIME
        sys_auto_shut_down_disable();
#endif

#if OTA_TWS_SAME_TIME_ENABLE
        tws_api_auto_role_switch_disable();
        tws_sync_update_api_register(get_tws_update_api());
        tws_ota_init();
#endif
    }
}

static void update_exit_common_handle(int type, void *priv)
{
    update_ret_code_t *ret_code = (update_ret_code_t *)priv;
    if (UPDATE_RESULT_ERR_NONE != ret_code->err_code && (UPDATE_RESULT_FLAG_BITMAP | UPDATE_RESULT_ERR_NONE) != ret_code->err_code) {
#if FLASH_PROTECT_OPT_BEFORE_UPDATE
        // 兼容双备份，升级错误就添加flash保护
        printf("%s, %x, add_flash_protect\n", __func__, ret_code->err_code);
        norflash_set_write_protect(1);
#endif
        if (!UPDATE_DUAL_BANK_IS_SUPPORT()) {
            g_write_vm_flag = true;
            if (support_update_backup_btif_addr) {
                // 还原btif信息
                after_update_btif_resume(0);
            }
        }
    }

#if TCFG_AUTO_SHUT_DOWN_TIME
    sys_auto_shut_down_enable();
#endif

#if OTA_TWS_SAME_TIME_ENABLE
    if (UPDATE_DUAL_BANK_IS_SUPPORT()) {
        tws_api_auto_role_switch_enable();
    }
#endif

    g_cur_update_type = 0;
    ota_status = 0;
}

static void update_common_state_cbk(update_mode_info_t *info, u32 state, void *priv)
{
    int type = info->type;

    log_info("type:%x state:%x code:%x\n", type, state, priv);

    switch (state) {
    case UPDATE_CH_INIT:
        memset((u8 *)&succ_report, 0x00, sizeof(succ_report_t));
        update_init_common_handle(info->type);
        break;

    case UPDATE_CH_SUCESS_REPORT:
        log_info("succ report stored\n");
        memcpy((u8 *)&succ_report, (u8 *)priv, sizeof(succ_report_t));
        break;
    }

    if (info->state_cbk) {
        info->state_cbk(type, state, priv);
    }

    switch (state) {
    case UPDATE_CH_EXIT:
        update_exit_common_handle(info->type, priv);
        break;
    case EX_UPDATE_CH_UPDATE_START:
        if (!UPDATE_DUAL_BANK_IS_SUPPORT()) {
            g_write_vm_flag = false;
        }
        break;
    }
}


static int app_update_init(void)
{
    update_module_init(update_common_state_cbk);
    testbox_update_init();
    return 0;
}

__initcall(app_update_init);


void update_start_exit_sniff(void)
{
#if TCFG_USER_TWS_ENABLE
    volatile u8 wait_tws_sniff_exit = 1;
    if (get_tws_phone_connect_state() == TRUE) {
        g_printf("exit sniff mode...\n");
        user_send_cmd_prepare(USER_CTRL_ALL_SNIFF_EXIT, 0, NULL);
    } else {
        tws_tx_unsniff_req();
    }
    tws_sniff_controle_check_disable();
#else
    user_send_cmd_prepare(USER_CTRL_ALL_SNIFF_EXIT, 0, NULL);
#endif
    sys_auto_sniff_controle(0, NULL);
}

