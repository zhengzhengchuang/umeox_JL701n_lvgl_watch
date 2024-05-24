#include "lv_watch.h"
#include "ble_user.h"
#include "app_main.h"
#include "user_cfg.h"
#include "../../../../include_lib/btstack/avctp_user.h"
#include "../../../watch/include/ui/lcd_spi/lcd_drive.h"
#include "../../../../watch/include/task_manager/rtc/alarm.h"

/*********************************************************************************
                                时间滚轮共用                                    
*********************************************************************************/
const char time_hour_str[] = {
    "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23"
};

const char time_min_sec_str[] = {
    "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59"
};

const char time_ne30_po30_str[] = {
    "-30\n-29\n-28\n-27\n-26\n-25\n-24\n-23\n-22\n-21\n-20\n-19\n-18\n-17\n-16\n-15\n-14\n-13\n-12\n-11\n-10\n-09\n-08\n-07\n-06\n-05\n-04\n-03\n-02\n-01\n00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30"
};

/*********************************************************************************
                                页面跳转                                    
*********************************************************************************/
void ui_menu_jump(ui_act_id_t act_id)
{
    if(!ui_act_id_validity(act_id))
        return;

    AppCtrlLcdEnterSleep(false);

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
                                设置系统UTC时间                                    
*********************************************************************************/
void SetUtcTime(struct sys_time *utc_time)
{
    void *fd = dev_open("rtc", NULL);
    if(!fd) return;

    dev_ioctl(fd, IOCTL_SET_SYS_TIME, (uint32_t)utc_time);

    dev_close(fd);

    return;
}

/*********************************************************************************
                                获取系统UTC时间                                    
*********************************************************************************/
void GetUtcTime(struct sys_time *utc_time)
{
    void *fd = dev_open("rtc", NULL);
    if(!fd) return;

    dev_ioctl(fd, IOCTL_GET_SYS_TIME, (uint32_t)utc_time);

    dev_close(fd);

    return;
}

/*********************************************************************************
                                获取系统星期                                    
*********************************************************************************/
comm_enum_week_t GetUtcWeek(struct sys_time *utc_time)
{
    return ((comm_enum_week_t)rtc_calculate_week_val(utc_time));
}

/*********************************************************************************
                                获取电池电量                                  
*********************************************************************************/
uint8_t GetBatteryPower(void)
{
    return get_vbat_percent();
}

/*********************************************************************************
                                获取bt蓝牙mac                                  
*********************************************************************************/
const uint8_t *GetDevBtMac(void)
{
    return (bt_get_mac_addr());
}

/*********************************************************************************
                                获取ble蓝牙mac                                   
*********************************************************************************/
const uint8_t *GetDevBleMac(void)
{
    return (jl_ble_get_mac_addr());
}

/*********************************************************************************
                                获取bt蓝牙名称                                
*********************************************************************************/
const char *GetDevBtName(void)
{
    return (bt_get_local_name());
}

/*********************************************************************************
                                获取ble蓝牙名称                                   
*********************************************************************************/
const char *GetDevBleName(void)
{
    return (bt_get_local_name());
}

/*********************************************************************************
                                获取ble、bt连接状态  
                        0:都未连接 1：仅ble连接 2：仅bt连接 3：都连接                                 
*********************************************************************************/
uint8_t GetDevBleBtConnectStatus(void)
{
    uint8_t bt_status = \
        bt_get_connect_status();
    ble_state_e ble_state = \
        smartbox_get_ble_work_state();

    if(bt_status == 1 && \
        (ble_state == BLE_ST_CONNECT || ble_state == BLE_ST_NOTIFY_IDICATE))
        return 3;
    else if(bt_status == 1 && \
        (ble_state == BLE_ST_CONNECT || ble_state == BLE_ST_NOTIFY_IDICATE))
        return 2;
    else if(bt_status == 0 && \
        (ble_state == BLE_ST_CONNECT || ble_state == BLE_ST_NOTIFY_IDICATE))
        return 1;

    return 0;
}

/*********************************************************************************
                                设置系统背光                                    
*********************************************************************************/
void AppSetSysBacklight(int val)
{
    struct lcd_interface *p;

    p = lcd_get_hdl();

    p->backlight_ctrl((u8)val);

    return;
}

/*********************************************************************************
                    控制屏幕进入休眠(0:退出休眠 1:进入休眠)                                   
*********************************************************************************/
extern int lcd_sleep_ctrl(u8 enter);
void AppCtrlLcdEnterSleep(bool sleep)
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
            GetVmParaCacheByLabel(vm_label_backlight);

         if(lcd->backlight_ctrl)
            lcd->backlight_ctrl((uint8_t)lcd_backlight);
    }

    return;
}

/*********************************************************************************
                        判断当前是否支持弹窗(true:支持 false:不支持)                               
*********************************************************************************/
bool MenuSupportPopup(void)
{
    bool popup = true;

    ui_menu_load_info_t *ui_menu_load_info;
    if(lcd_sleep_status())
        ui_menu_load_info = \
            &(p_ui_info_cache->exit_menu_load_info);
    else
        ui_menu_load_info = \
            &(p_ui_info_cache->menu_load_info); 
    /*锁定菜单，不弹出窗口，当前有不能打断的页面事件处理*/
    if(ui_menu_load_info->lock_flag)
        popup = false;

    return popup;
}

/*********************************************************************************
                        设备二维码链接(mac:45  name:66)                              
*********************************************************************************/
static bool InitLinkFlag = false;
static char QRCodeLinkStrBuf[100] = "https://iqibla.com/pages/iqibla-app?f=b&code=FF:FF:FF:FF:FF:FF&fk=QW02";
char *GetQRCodeLinkStrBuf(void)
{
    static char *p = QRCodeLinkStrBuf;

    if(InitLinkFlag == false)
    {
        uint8_t ble_mac_idx = 0;
        char ble_mac_str[18] = {0};
        const u8 *ble_mac = GetDevBleMac();
        for(uint8_t i = 0; i < 17; i++)
        {
            if(((i + 1) % 3) == 0)
            {
                ble_mac_idx++;
                ble_mac_str[i] = ':';
            }else if(((i + 1) % 3) == 1)
            {
                ble_mac_str[i] = ((ble_mac[ble_mac_idx] >> 4) & 0x0f) > 9 ? \
                    ((ble_mac[ble_mac_idx] >> 4) & 0x0f) + 0x37:\
                        ((ble_mac[ble_mac_idx] >> 4) & 0x0f) + 0x30;
            }else if(((i + 1) % 3) == 2)
            {
                ble_mac_str[i] = (ble_mac[ble_mac_idx] & 0x0f) > 9 ? \
                    ((ble_mac[ble_mac_idx]) & 0x0f) + 0x37:\
                        (ble_mac[ble_mac_idx] & 0x0f) + 0x30;
            }
        }
        memcpy(&p[45], ble_mac_str, 17);

        const char *ble_name_str = \
            GetDevBleName();
        memcpy(&p[66], ble_name_str, LOCAL_NAME_LEN);

        InitLinkFlag = true;
    }
    
    return p;
}
