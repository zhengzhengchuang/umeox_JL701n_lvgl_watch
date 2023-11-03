#include "weather.h"


static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_left_menu(Act_Id_Watchface);
    tileview_register_center_menu(Act_Id_Weather);
    tileview_menu_create(obj);

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    return;
}

static void menu_refresh_cb(lv_obj_t *obj)
{
    return;
}

static void menu_display_cb(lv_obj_t *obj)
{
    if(!obj) return;

    widget_img_para.img_parent = obj;
    widget_img_para.img_x = 0;
    widget_img_para.img_y = 0;
    widget_img_para.file_img_dat = FILE_weather_bg_dat;
    common_widget_img_create(&widget_img_para, NULL);

    return;
}

const ui_menu_load_info_t menu_load_weather = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = Act_Id_Weather,
    .user_display_time = 0,
    .user_refresh_time_inv = 0,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
