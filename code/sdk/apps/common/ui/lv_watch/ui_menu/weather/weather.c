#include "weather.h"

static uint16_t compass_angle = 0;
static lv_obj_t *compass_clock = NULL;

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, Act_Id_Null, Act_Id_Null, \
        Act_Id_Watchface, Act_Id_Null, Act_Id_Weather);

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    return;
}

static void menu_refresh_cb(lv_obj_t *obj)
{
    if(!obj) return;

    compass_angle += 100;
    compass_angle %= 3600;
    lv_img_set_angle(compass_clock, compass_angle);

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

    compass_angle = 0;
    widget_img_para.file_img_dat = compass_clock_index;
    compass_clock = common_widget_img_create(&widget_img_para, NULL);
    lv_obj_center(compass_clock);

    return;
}

const ui_menu_load_info_t menu_load_weather = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = Act_Id_Weather,
    .user_display_time = 0,
    .user_refresh_time_inv = 100,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
