#include "lv_watch.h"
#include "../../../watch/include/ui/lcd_spi/lcd_drive.h"

/*
    函数名称：ui_menu_jump
    函数描述：跳转到目标id的页面
    参数描述：
       act_id：目标id

    返回：void
*/
void ui_menu_jump(ui_act_id_t act_id)
{
    if(!ui_act_id_validity(act_id))
        return;

    ui_menu_jump_post_msg(act_id);

    return;
}

/*
    函数名称：ui_act_id_validity
    函数描述：菜单id的有效性
    参数描述：
       act_id：菜单id

    返回：true:有效  false:无效
*/
bool ui_act_id_validity(ui_act_id_t act_id)
{
    if(act_id > ui_act_id_null && act_id < ui_act_id_max)
        return true;

    return false;
}

/*
    函数名称：ui_set_sys_time
    函数描述：设置系统时间
    参数描述：
       utc_time：指向描述系统时间的结构体

    返回：void
*/
void ui_set_sys_time(struct sys_time *utc_time)
{
    void *fd = dev_open("rtc", NULL);
    if(!fd) return;

    dev_ioctl(fd, IOCTL_SET_SYS_TIME, (uint32_t)utc_time);

    dev_close(fd);

    return;
}

/*
    函数名称：ui_get_sys_time
    函数描述：获取系统时间
    参数描述：
       utc_time：指向描述系统时间的结构体

    返回：void
*/
void ui_get_sys_time(struct sys_time *utc_time)
{
    void *fd = dev_open("rtc", NULL);
    if(!fd) return;

    dev_ioctl(fd, IOCTL_GET_SYS_TIME, (uint32_t)utc_time);

    dev_close(fd);

    return;
}

/*
    函数名称：ui_ctl_lcd_enter_sleep
    函数描述：ui应用层控制屏幕进入休眠
    参数描述：
       sleep:
        true:进入休眠
        false:退出休眠

    返回：void
*/
extern int lcd_sleep_ctrl(u8 enter);
void ui_ctl_lcd_enter_sleep(bool sleep)
{
    lcd_sleep_ctrl(sleep);
 
    struct lcd_interface *lcd = lcd_get_hdl();
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