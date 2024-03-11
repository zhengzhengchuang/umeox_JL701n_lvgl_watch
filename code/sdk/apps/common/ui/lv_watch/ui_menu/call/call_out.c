#include "call_out.h"

static void call_out_hang_up_cb(lv_event_t *e)
{
    if(!e) return;

    bt_ctrl_call_hang_up();

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_null, \
            ui_act_id_call_out);

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

    widget_label_para.label_w = \
        (220);
    widget_label_para.label_h = \
        Label_Line_Height*2;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_WRAP;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_ver_center = \
        false;
    widget_label_para.user_text_font = \
        NULL;
    widget_label_para.label_parent = \
        obj;
    widget_label_para.label_text = \
        bt_get_call_number_name();
    lv_obj_t *call_number_name_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align(call_number_name_label, LV_ALIGN_TOP_MID, \
        0, 80);

    widget_img_para.img_x = 134;
    widget_img_para.img_y = 168;
    widget_img_para.img_parent = \
        obj;
    widget_img_para.file_img_dat = \
        call_16_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = NULL;
    common_widget_img_create(&widget_img_para, \
        NULL);

    widget_img_para.img_x = 144;
    widget_img_para.img_y = 336;
    widget_img_para.file_img_dat = \
        call_11_index;
    widget_img_para.img_click_attr = \
        true;
    widget_img_para.event_cb = \
        call_out_hang_up_cb;
    widget_img_para.user_data = NULL;
    common_widget_img_create(&widget_img_para, \
        NULL);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_call_out) = 
{
    .menu_arg = NULL,
    .lock_flag = true,
    .return_flag = false,
    .menu_id = \
        ui_act_id_call_out,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
