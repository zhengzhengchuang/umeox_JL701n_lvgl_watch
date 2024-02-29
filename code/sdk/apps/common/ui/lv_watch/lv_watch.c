#include "lv_watch.h"
#include "ble_user.h"
#include "app_main.h"
#include "../../../../include_lib/btstack/avctp_user.h"
#include "../../../watch/include/ui/lcd_spi/lcd_drive.h"
#include "../../../../watch/include/task_manager/rtc/alarm.h"

extern BT_USER_PRIV_VAR bt_user_priv_var;

/*********************************************************************************
                                ui层页面跳转                                    
*********************************************************************************/
void ui_menu_jump(ui_act_id_t act_id)
{
    if(!ui_act_id_validity(act_id))
        return;

    ui_ctl_lcd_enter_sleep(false);

    ui_menu_jump_post_msg(act_id);

    return;
}

/*********************************************************************************
                                判断页面id的有效性                                    
*********************************************************************************/
bool ui_act_id_validity(ui_act_id_t act_id)
{
    if(act_id > ui_act_id_null && act_id < ui_act_id_max)
        return true;

    return false;
}

/*********************************************************************************
                                ui层设置系统UTC时间                                    
*********************************************************************************/
void ui_set_sys_time(struct sys_time *utc_time)
{
    void *fd = dev_open("rtc", NULL);
    if(!fd) return;

    dev_ioctl(fd, IOCTL_SET_SYS_TIME, (uint32_t)utc_time);

    dev_close(fd);

    return;
}

/*********************************************************************************
                                ui层获取系统UTC时间                                    
*********************************************************************************/
void ui_get_sys_time(struct sys_time *utc_time)
{
    void *fd = dev_open("rtc", NULL);
    if(!fd) return;

    dev_ioctl(fd, IOCTL_GET_SYS_TIME, (uint32_t)utc_time);

    dev_close(fd);

    return;
}

/*********************************************************************************
                                ui层获取系统星期                                    
*********************************************************************************/
comm_enum_week_t ui_get_sys_week(struct sys_time *utc_time)
{
    return ((comm_enum_week_t)rtc_calculate_week_val(utc_time));
}

/*********************************************************************************
                                ui层获取bt蓝牙mac                                  
*********************************************************************************/
const uint8_t *ui_get_dev_bt_mac(void)
{
    return (bt_get_mac_addr());
}

/*********************************************************************************
                                ui层获取ble蓝牙mac                                   
*********************************************************************************/
const uint8_t *ui_get_dev_ble_mac(void)
{
    return (jl_ble_get_mac_addr());
}

/*********************************************************************************
                                ui层获取bt蓝牙名称                                
*********************************************************************************/
const char *ui_get_dev_bt_name(void)
{
    return (bt_get_local_name());
}

/*********************************************************************************
                                ui层获取ble蓝牙名称                                   
*********************************************************************************/
const char *ui_get_dev_ble_name(void)
{
    return (bt_get_local_name());
}

/*********************************************************************************
                                ui层获取ble、bt连接状态  
                        0:都未连接 1：仅ble连接 2：仅bt连接 3：都连接                                 
*********************************************************************************/
uint8_t ui_get_ble_bt_connect_status(void)
{
    uint8_t bt_status = \
        bt_get_connect_status();
    ble_state_e ble_state = \
        smartbox_get_ble_work_state();

    if(bt_status == 1 && \
        ble_state == BLE_ST_CONNECT)
        return 3;
    else if(bt_status == 1 && \
        ble_state != BLE_ST_CONNECT)
        return 2;
    else if(bt_status == 0 && \
        ble_state == BLE_ST_CONNECT)
        return 1;

    return 0;
}

/*********************************************************************************
                                ui层设置系统背光                                    
*********************************************************************************/
void ui_set_sys_backlight(int backlight_val)
{
    struct lcd_interface *p;

    p = lcd_get_hdl();

    p->backlight_ctrl((u8)backlight_val);

    return;
}

/*********************************************************************************
                    ui层控制屏幕进入休眠(0:退出休眠 1:进入休眠)                                   
*********************************************************************************/
extern int lcd_sleep_ctrl(u8 enter);
void ui_ctl_lcd_enter_sleep(bool sleep)
{
    if(lcd_sleep_status() == \
        sleep)
        return;

    lcd_sleep_ctrl(sleep);
 
    struct lcd_interface *lcd = \
        lcd_get_hdl();
    if(lcd->power_ctrl)
        lcd->power_ctrl(!sleep);

    if(!sleep)
    {
        int lcd_backlight = \
            get_vm_para_cache_with_label(vm_label_backlight);

         if(lcd->backlight_ctrl)
            lcd->backlight_ctrl((uint8_t)lcd_backlight);
    }

    return;
}

/*********************************************************************************
                                通过号码拨出电话                                    
*********************************************************************************/
void ui_ctrl_call_out_by_number(char *call_number, uint8_t number_len)
{
    if(!call_number || !number_len)
        return;

    uint8_t ble_bt_connect = \
        ui_get_ble_bt_connect_status();
    if(ble_bt_connect == 0 || \
        ble_bt_connect == 1)
    {
        ui_menu_jump(ui_act_id_call_disc);
        
        return;
    }

    user_send_cmd_prepare(USER_CTRL_DIAL_NUMBER, \
        number_len, (uint8_t *)call_number);

    return;
}


/*********************************************************************************
                                获取来电号码
                    (如果联系人列表有，返回名字，否则返回号码)                                    
*********************************************************************************/
char *ui_get_call_number_name(void)
{
    static char *call_name;
    static uint8_t *call_number;

    uint8_t number_len = \
        bt_user_priv_var.income_phone_len;

    if(!number_len)
        return NULL;

    call_number = \
        bt_user_priv_var.income_phone_num;

    call_name = \
        vm_contacts_name_by_number((char *)call_number);

    if(call_name) 
        return call_name;

    return call_number;
}

/*********************************************************************************
                                控制通话接听                                   
*********************************************************************************/
void ui_ctrl_call_answer(void)
{
    user_send_cmd_prepare(USER_CTRL_HFP_CALL_ANSWER, \
        0, NULL);

    return;
}

/*********************************************************************************
                                控制通话挂断                                   
*********************************************************************************/
void ui_ctrl_call_hang_up(void)
{
    user_send_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, \
        0, NULL);

    return;
}


/*********************************************************************************
                                通话记录状态及信息保存                                   
*********************************************************************************/
static uint8_t call_out_or_in = 0;//0:未知 1:拨出 2:拨入
void record_call_out_or_in(uint8_t out_or_in)
{
    call_out_or_in = out_or_in;

    return;
}

static bool call_is_answer = false;//是否接通
void record_call_is_answer(bool is_answer)
{
    call_is_answer = is_answer;

    return;
}

void record_call_status_clear(void)
{
    record_call_out_or_in(0);
    record_call_is_answer(false);
}

void update_call_log_message_flash(void)
{
    if(call_out_or_in == 0)
        return;

    call_log_state_t call_log_state = \
        call_log_unknown;

    if(call_out_or_in == 1)
    {
        if(call_is_answer == true)
            call_log_state = \
                call_log_state_out;
        else
            call_log_state = \
                call_log_state_hangup;
    }else if(call_out_or_in == 2)
    {
        if(call_is_answer == true)
            call_log_state = \
                call_log_state_in;
        else
            call_log_state = \
                call_log_state_hangup;
    }

    vm_call_log_ctx_t vm_call_log_ctx \
        = {0};

    vm_call_log_ctx.check_code = \
        Nor_Vm_Check_Code;
    vm_call_log_ctx.call_log_state = \
        call_log_state;

    uint8_t number_len = \
        bt_user_priv_var.income_phone_len;
    uint8_t *call_number = \
        bt_user_priv_var.income_phone_num;

    if(!number_len)
        return;
    
    memcpy((void *)(vm_call_log_ctx.call_log_number_str), \
        (void *)call_number, number_len);

    char *call_name = \
        vm_contacts_name_by_number((char *)call_number);
    if(call_name)
       memcpy((void *)(vm_call_log_ctx.call_log_name_str), \
        (void *)call_name, Call_Name_Max_Len);

    ui_get_sys_time(&(vm_call_log_ctx.call_log_time));
    
    vm_call_log_ctx_falsh_save(&vm_call_log_ctx);

    printf("******call_log falsh success\n");
    
    return;
}

/*********************************************************************************
                                通话中获取音量                                   
*********************************************************************************/
uint8_t ui_get_calling_volumn(void)
{
    return app_var.call_volume;
}

/*********************************************************************************
                                拨出、拨入页面跳转                                
*********************************************************************************/
void ui_call_out_or_in_menu_jump(void)
{
    //判断当前是否符合弹出的条件
    //.......

    if(call_out_or_in == 1)
        ui_menu_jump(ui_act_id_call_out); 
    else if(call_out_or_in == 2)
        ui_menu_jump(ui_act_id_call_in);   

    return;
}

/*********************************************************************************
                                挂断后页面跳转                                  
*********************************************************************************/
void ui_call_hang_up_menu_jump(void)
{
    ui_act_id_t prev_act_id = \
        read_menu_return_level_id();

    call_online_duration_timer_delete();

    if(call_is_answer == false)
        ui_menu_jump(prev_act_id);    
    else
        ui_menu_jump(ui_act_id_call_end);
    
    return;
}

/*********************************************************************************
                                接通后页面跳转                                  
*********************************************************************************/
void ui_call_answer_menu_jump(void)
{
    ui_menu_jump(ui_act_id_call_online);

    return;
}

/*********************************************************************************
                                通话在线时长操作                                  
*********************************************************************************/
static uint16_t call_online_timer_id = 0;
static uint32_t call_online_duration = 0;
static void call_online_duration_timer_cb(void *priv)
{
    if(call_online_duration < 0xffffffff)
        call_online_duration += 1;

    printf("%s:%d\n", __func__, call_online_duration);

    return;
}

uint32_t ui_get_call_online_duration(void)
{
    return call_online_duration;
}

uint16_t get_call_online_timer_id(void)
{
    return call_online_timer_id;
}

void call_online_duration_timer_create(void)
{
    if(call_online_timer_id)
    {
        sys_hi_timer_del(\
            call_online_timer_id);
        call_online_timer_id = 0;
    }

    call_online_duration = 0;

    call_online_timer_id = \
        sys_hi_timer_add(NULL, \
            call_online_duration_timer_cb, 1000);

    return;
}

void call_online_duration_timer_delete(void)
{
    if(call_online_timer_id)
    {
        sys_hi_timer_del(\
            call_online_timer_id);
        call_online_timer_id = 0;
    }

    return;
}

/*********************************************************************************
                                ui控制查找手机                                  
*********************************************************************************/
void ui_ctrl_ble_dev_find_phone(void)
{
    printf("%s\n", __func__);

    return;
}

/*********************************************************************************
                                ui控制手机相机相关操作                                 
*********************************************************************************/
void ui_ctrl_phone_enter_camera(void)
{
    printf("%s\n", __func__);

    return;
}

void ui_ctrl_phone_exit_camera(void)
{
    printf("%s\n", __func__);

    return;
}

void ui_ctrl_phone_take_photos(void)
{
    printf("%s\n", __func__);

    return;
}

void ui_ctrl_phone_dly_take_photos(void)
{
    printf("%s\n", __func__);

    return;
}
