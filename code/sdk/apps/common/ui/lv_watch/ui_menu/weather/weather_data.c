#include "weather_data.h"

/*********************************************************************************
                                  创建无天气数据页面                                 
*********************************************************************************/
static void no_weather_data_menu_create(lv_obj_t *obj)
{
    widget_img_para.img_parent = obj;
    widget_img_para.file_img_dat = \
        weather_no_data_00_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = NULL;
    lv_obj_t *no_data_icon = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_align(no_data_icon, LV_ALIGN_TOP_MID, \
        0, 82);

    widget_img_para.file_img_dat = \
        comm_icon_11_index;
    lv_obj_t *no_data_bg_img = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_align_to(no_data_bg_img, no_data_icon, \
        LV_ALIGN_OUT_BOTTOM_MID, 0, 32);

    
    widget_label_para.label_w = \
        (LCD_WIDTH - 30);
    widget_label_para.label_h = \
        Label_Line_Height*2;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_WRAP;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_parent = \
        obj;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_ver_center = \
        true;    
    widget_label_para.user_text_font = NULL;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_no_data);
    lv_obj_t *no_data_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align_to(no_data_label, no_data_bg_img, \
        LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

    return;
}

/*********************************************************************************
                                  创建有天气数据页面                                 
*********************************************************************************/
static void has_weather_data_menu_create(lv_obj_t *obj)
{
    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_null, \
            ui_act_id_weather_data);

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

    bool data_is_valid = \
        comm_whether_data_is_valid();
    if(!data_is_valid)
        no_weather_data_menu_create(obj);
    else
        has_weather_data_menu_create(obj);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_weather_data) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_weather_data,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
