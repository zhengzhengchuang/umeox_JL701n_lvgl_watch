#include "watchface_02.h"

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    wf_tileview_register_all_menu(obj);

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

    widget_img_para.img_x = 0;
    widget_img_para.img_y = 0;
    widget_img_para.img_parent = obj;
    widget_img_para.file_img_dat = \
        watchface_02_bg_index;
    widget_img_para.img_click_attr = false;
    widget_img_para.event_cb = NULL;
    common_widget_img_create(&widget_img_para, NULL);

    widget_time_para.time_x = 102;
    widget_time_para.time_y = 52;
    widget_time_para.num_inv = 0;
    widget_time_para.time_parent = \
        obj;
    widget_time_para.num_addr_index = \
        watchface_02_52x78_00_index;
    common_time_widget_create(\
        &widget_time_para, widget_time_mode_hh_mm);

    comm_language_id_t lang_id = \
        get_comm_sys_language();
    comm_week_para.week_x = 226;
    comm_week_para.week_y = 138;
    comm_week_para.week_parent = obj;
    if(lang_id == comm_language_id_french)
        comm_week_para.week_addr_index = \
            watchface_02_week_fr_00_index; 
    else if(lang_id == comm_language_id_arabic)
        comm_week_para.week_addr_index = \
            watchface_02_week_ar_00_index; 
    else
        comm_week_para.week_addr_index = \
            watchface_02_week_en_00_index;
    common_week_widget_create(&comm_week_para);

    widget_date_para.date_x = 242;
    widget_date_para.date_y = 182;
    widget_date_para.num_inv = 0;
    widget_date_para.date_parent = obj;
    widget_date_para.num_addr_index = \
        watchface_02_14x22_00_index;
    common_date_widget_create(\
        &widget_date_para, widget_date_mode_mm_dd);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_watchface_02) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_watchface,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
