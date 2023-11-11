#include "lv_watch.h"

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
    if(act_id > Act_Id_Null && act_id < Act_Id_Max)
        return true;

    return false;
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