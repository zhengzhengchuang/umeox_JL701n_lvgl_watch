#include "lv_watch.h"
#include "../../../watch/include/ui/lcd_spi/lcd_drive.h"
#include "../../../../watch/include/task_manager/rtc/alarm.h"

/*********************************************************************************
                                ui层页面跳转                                    
*********************************************************************************/
void ui_menu_jump(ui_act_id_t act_id)
{
    if(!ui_act_id_validity(act_id))
        return;

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
                                ui层获取bt蓝牙mac(双模蓝牙 ble和bt一样)                                  
*********************************************************************************/
const uint8_t *ui_get_dev_bt_mac(void)
{
    return (bt_get_mac_addr());
}

/*********************************************************************************
                                ui层获取ble蓝牙mac(双模蓝牙 ble和bt一样)                                   
*********************************************************************************/
const uint8_t *ui_get_dev_ble_mac(void)
{
    return (bt_get_mac_addr());
}

/*********************************************************************************
                                ui层获取bt蓝牙名称(双模蓝牙 ble和bt一样)                                  
*********************************************************************************/
const char *ui_get_dev_bt_name(void)
{
    return (bt_get_local_name());
}

/*********************************************************************************
                                ui层获取ble蓝牙名称(双模蓝牙 ble和bt一样)                                   
*********************************************************************************/
const char *ui_get_dev_ble_name(void)
{
    return (bt_get_local_name());
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
                                ui层控制屏幕进入休眠                                    
*********************************************************************************/
extern int lcd_sleep_ctrl(u8 enter);
void ui_ctl_lcd_enter_sleep(bool sleep)
{
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