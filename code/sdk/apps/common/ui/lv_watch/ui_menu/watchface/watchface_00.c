#include "watchface_00.h"

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, ui_act_id_null, \
        ui_act_id_null, ui_act_id_weather, ui_act_id_watchface);

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    return;
}

static void menu_refresh_cb(lv_obj_t *obj)
{
    if(!obj) return;

    struct sys_time utc_time;
    ui_get_sys_time(&utc_time);
    printf("%d-%d-%d %d:%d:%d\n", utc_time.year, \
        utc_time.month, utc_time.day, utc_time.hour, \
            utc_time.min, utc_time.sec);

    return;
}

static void menu_display_cb(lv_obj_t *obj)
{
    if(!obj) return;

    widget_img_para.img_parent = obj;
    widget_img_para.img_x = 0;
    widget_img_para.img_y = 0;
    widget_img_para.file_img_dat = watchface_00_bg_index;
    widget_img_para.img_click_attr = false;
    widget_img_para.event_cb = NULL;
    common_widget_img_create(&widget_img_para, NULL);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, int key_event)
{
    return;
}

register_ui_menu_load_info(menu_load_watchface_00) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = ui_act_id_watchface,
    .user_offscreen_time = Always_OnScreen,
    .user_refresh_time_inv = 500,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
