#include "common_key.h"
#include "../lv_watch.h"
#include "../../../../watch/include/app_main.h"
#include "../../../../../include_lib/system/event.h"
#include "../../../../../include_lib/btstack/le/le_user.h"
#include "../../../../watch/include/ui/lcd_spi/lcd_drive.h"

/************使能TE定时器id************/
static uint16_t enable_te_timer_id = 0;

/************页面定时锁定标志************/
static bool menu_timer_lock_flag = false;

bool get_menu_timer_lock_flag(void)
{
    return menu_timer_lock_flag;
}

void set_menu_timer_lock_flag(bool flag)
{
    menu_timer_lock_flag = flag;

    return;
}

/************使能TE超时回调函数************/
static void enable_te_timeout_cb(void *priv)
{
    if(enable_te_timer_id)
        sys_timeout_del(enable_te_timer_id);

    enable_te_timer_id = 0;

    extern volatile u8 usr_wait_te;
    usr_wait_te = 1;
    
    return;
}

void common_key_msg_handle(int key_value, int key_event)
{
    if(app_var.goto_poweroff_flag)
        return;

    if(lcd_sleep_status())
    {
        if(key_value == Common_Key_Val_0 && key_event == KEY_EVENT_CLICK)
        {
            /**************屏幕和tp进入休眠**************/
            ui_ctl_lcd_enter_sleep(false);

            /************按键亮屏显示页************/
            ui_act_id_t act_id = ui_act_id_watchface;
            ui_menu_load_info_t *menu_load_info = \
                &p_ui_info_cache->exit_menu_load_info;
            bool timer_lock_flag = \
                get_menu_timer_lock_flag();

            if(menu_load_info->lock_flag)
                act_id = menu_load_info->menu_id;
            else
            {
                if(timer_lock_flag)
                    act_id = menu_load_info->menu_id;
            }
            ui_menu_jump_handle(act_id);

            common_menu_lock_timer_del();

            /**************亮屏打开TE**************/
            if(!enable_te_timer_id)
                enable_te_timer_id = sys_timeout_add(NULL, \
                    enable_te_timeout_cb, 10);
        }
    }else
    {
        /*******亮屏按键操作时，需重置刷新定时器*******/
        //common_refresh_timer_re_run();

        /*******亮屏按键操作时，需重置熄屏定时器*******/
        common_offscreen_timer_restart();

#if 0
        char call_number_buf[6] = "10086";
        uint8_t call_number_len = 5;
        ui_ctrl_call_out_by_number(call_number_buf, \
            call_number_len);
        printf("***********%s\n", __func__);
#endif

        /*******页面不锁定，主按键返回表盘*******/
        bool menu_lock_flag = \
            p_ui_info_cache->menu_load_info.lock_flag;
        if(key_value == Common_Key_Val_0 && \
            key_event == KEY_EVENT_CLICK && !menu_lock_flag)
        {
            if(p_ui_info_cache->cur_act_id != ui_act_id_watchface)
            {
                ui_menu_jump(ui_act_id_watchface);
                return;
            }     
        }

        /*******按键无通用功能，回调到页面做相应地处理*******/
        lv_obj_t *obj = tileview_get_center_menu();
        ui_menu_key_func_cb key_func_cb = \
            p_ui_info_cache->menu_load_info.key_func_cb;
        if(key_func_cb)
            key_func_cb(obj, key_value, key_event);
    }

    return;
}

