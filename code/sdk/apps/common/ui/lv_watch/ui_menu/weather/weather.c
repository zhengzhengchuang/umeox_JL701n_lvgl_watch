#include "weather.h"

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, ui_act_id_null, \
        ui_act_id_watchface, ui_act_id_null, ui_act_id_weather);

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    return;
}

static void menu_refresh_cb(lv_obj_t *obj)
{
    if(!obj) return;

    return;
}

static void menu_display_cb(lv_obj_t *obj)
{
    if(!obj) return;

    widget_img_para.img_parent = obj;
    widget_img_para.img_x = 0;
    widget_img_para.img_y = 0;
    widget_img_para.file_img_dat = compass_bg_index;
    widget_img_para.img_click_attr = false;
    widget_img_para.event_cb = NULL;
    common_widget_img_create(&widget_img_para, NULL);

#if 0
    comm_time_para.time_x = 100;
    comm_time_para.time_y = 330;
    comm_time_para.num_inv = 0;
    comm_time_para.num_width = 16;
    comm_time_para.num_height = 21;
    comm_time_para.time_parent = obj;
    comm_time_para.num_addr_index = \
        watchface_00_time_00_index;
    comm_time_para.time_mode = \
        comm_time_mode_hh_mm_ss;
    common_time_widget_create(&comm_time_para);

    comm_date_para.date_x = 100;
    comm_date_para.date_y = 290;
    comm_date_para.num_inv = 0;
    comm_date_para.num_width = 16;
    comm_date_para.num_height = 21;
    comm_date_para.date_parent = obj;
    comm_date_para.num_addr_index = \
        watchface_00_time_00_index;
    comm_date_para.date_mode = \
        comm_date_mode_yyyy_mm_dd;
    common_date_widget_create(&comm_date_para);

    comm_week_para.week_x = 100;
    comm_week_para.week_y = 260;
    comm_week_para.week_parent = obj;
    comm_week_para.week_addr_index = \
        watchface_00_week_en_00_index;
    common_week_widget_create(&comm_week_para);
#endif

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    return;
}

register_ui_menu_load_info(menu_load_weather) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = ui_act_id_weather,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 100,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
