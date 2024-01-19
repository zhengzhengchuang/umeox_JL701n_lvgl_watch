#include "../lv_watch.h"
#include "common_offscreen.h"
#include "../poc_modem/poc_modem_vm.h"

/**************熄屏定时器id**************/
static uint16_t offscreen_timer_id = 0;

/**************页面定时锁定定时器id**************/
static uint16_t menu_lock_timer_id = 0;

/**************当前熄屏时间**************/
static uint32_t cur_offscreen_time = 0;

/**************函数声明**************/
static void common_menu_lock_timer_cb(void *priv);


void common_menu_lock_timer_del(void)
{
    set_menu_timer_lock_flag(false);

    if(menu_lock_timer_id)
    {
        sys_timeout_del(menu_lock_timer_id);
        menu_lock_timer_id = 0;
    }
        
    return;
}

void common_menu_lock_timer_add(void)
{
    set_menu_timer_lock_flag(true);

    /*三分钟解锁*/
    if(!menu_lock_timer_id)
        menu_lock_timer_id = sys_timeout_add(NULL, \
            common_menu_lock_timer_cb, 3*60*1000);

    return;
}

static void common_offscreen_timer_cb(void *priv)
{
    if(cur_offscreen_time == Always_OnScreen)
        return;
        
    // int menu_offscreen_msg[1];
    // menu_offscreen_msg[0] = ui_msg_menu_offscreen;
    // post_ui_msg(menu_offscreen_msg, 1);

    return;
}

static void common_menu_lock_timer_cb(void *priv)
{
    common_menu_lock_timer_del();

    return;
}

extern int lcd_sleep_ctrl(u8 enter);
void common_offscreen_msg_handle(void)
{
    ui_ctl_lcd_enter_sleep(true);

    /**************清除当前页面**************/
    ui_menu_jump_handle(ui_act_id_null);//传ui_act_id_null即是销毁页面

    /**************关掉TE, 下次亮屏能缩短时间**************/
    extern volatile u8 usr_wait_te;
    usr_wait_te = 0;

    /**************灭屏菜单定时锁定机制**************/
    common_menu_lock_timer_add();

    return;
}

void common_offscreen_timer_create(void)
{
    uint32_t user_offscreen_time = \
        p_ui_info_cache->menu_load_info.user_offscreen_time;
    int sys_offscreen_time = \
        get_vm_para_cache_with_label(vm_label_offscreen_time);

    if(user_offscreen_time > 0)
        cur_offscreen_time = user_offscreen_time;
    else
        cur_offscreen_time = sys_offscreen_time;

    if(!offscreen_timer_id)
        offscreen_timer_id = sys_timeout_add(NULL, \
            common_offscreen_timer_cb, cur_offscreen_time);

    return;
}

void common_offscreen_timer_restart(void)
{
    if(offscreen_timer_id)
        sys_timer_re_run(offscreen_timer_id);

    return;
}

void common_offscreen_timer_destroy(void)
{
    if(offscreen_timer_id)
        sys_timeout_del(offscreen_timer_id);

    offscreen_timer_id = 0;

    return;
}