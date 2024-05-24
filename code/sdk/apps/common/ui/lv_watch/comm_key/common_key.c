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

static void enable_te_timeout_cb(void *priv)
{
    if(enable_te_timer_id)
        sys_timeout_del(enable_te_timer_id);
    enable_te_timer_id = 0;

    struct lcd_interface *lcd = \
        lcd_get_hdl();
    if(lcd->power_ctrl)
        lcd->power_ctrl(true);

    int lcd_backlight = \
        GetVmParaCacheByLabel(vm_label_backlight);

    if(lcd->backlight_ctrl)
        lcd->backlight_ctrl((uint8_t)lcd_backlight);

    // extern volatile u8 usr_wait_te;
    // usr_wait_te = 1;
    
    return;
}

void common_key_msg_handle(int key_value, int key_event)
{
    if(app_var.goto_poweroff_flag)
        return;

    printf("key_value = %d, key_event = %d\n", \
        key_value, key_event);

    if(lcd_sleep_status())
    {
        if(key_value >= Common_Key_Val_Max)
            return;

        if(key_event == KEY_EVENT_CLICK)
        {
            lcd_sleep_ctrl(false);

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
            
            ui_menu_jump(act_id);

            common_menu_lock_timer_del();

            if(!enable_te_timer_id)
                enable_te_timer_id = sys_timeout_add(NULL, \
                    enable_te_timeout_cb, 50);
        }
    }else
    {
        /*******亮屏按键操作时，需重置刷新定时器*******/
        //common_refresh_timer_re_run();

        /*******亮屏按键操作时，需重置熄屏定时器*******/
        common_offscreen_timer_restart();

        bool menu_lock = \
            p_ui_info_cache->menu_load_info.lock_flag;
        ui_act_id_t cur_act_id = \
            p_ui_info_cache->cur_act_id;

        if(key_value == Common_Key_Val_1)
        {
            //电源键
            if(key_event == KEY_EVENT_CLICK)
                common_offscreen_handle(); 
            else if(key_event == KEY_EVENT_LONG_3S)
                DevOpMenuPopUp();
        }else if(key_value == Common_Key_Val_0)
        {
            //菜单键 Home键
            if(cur_act_id == ui_act_id_watchface)
            {
                if(key_event == KEY_EVENT_CLICK)
                {
                    ui_menu_jump(\
                        ui_act_id_menu);
                    return;
                }
            }else
            {
                if(key_event == KEY_EVENT_CLICK)
                {
                    if(menu_lock == false)
                    {
                        ui_menu_jump(\
                            ui_act_id_watchface);
                        return;
                    }
                }
            }
        }else
        {
            return;
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

