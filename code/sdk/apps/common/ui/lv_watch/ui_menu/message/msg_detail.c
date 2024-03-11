#include "msg_detail.h"

static void msg_detail_delete_button_cb(lv_event_t *e)
{
    if(!e) return;

    uint8_t query_id = \
        get_msg_detail_query_id();
    uint8_t msg_num = \
        vm_message_item_num();
    if(query_id >= msg_num)
        return;

    query_id = (msg_num - 1) - \
        query_id;

    vm_message_delete_by_index(query_id);

    ui_act_id_t prev_act_id = \
        read_menu_return_level_id();
    ui_menu_jump(prev_act_id);
    
    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    ui_act_id_t prev_act_id = \
        read_menu_return_level_id();

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, prev_act_id, ui_act_id_null, \
            ui_act_id_msg_detail);

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

    menu_align_t menu_align = \
        menu_align_left;
    if(lang_txt_is_arabic())
        menu_align = \
            menu_align_right;

    uint8_t query_id = \
        get_msg_detail_query_id();
    memset(&ui_message_ctx, 0, \
            sizeof(vm_message_ctx_t));
    vm_message_ctx_by_idx(query_id, \
        &ui_message_ctx);

    widget_img_para.img_parent = \
        obj;
    widget_img_para.file_img_dat = \
        message_icon_03_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = \
        NULL;
    lv_obj_t *msg_detail_container = \
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(msg_detail_container, LV_ALIGN_TOP_MID, \
        0, 48);

    widget_img_para.img_parent = \
        msg_detail_container;
    widget_img_para.file_img_dat = \
        message_type_00_index + \
            ui_message_ctx.message_type; 
    lv_obj_t *msg_type_icon = \
        common_widget_img_create(&widget_img_para, \
            NULL); 
    if(menu_align == menu_align_right)
        lv_obj_align(msg_type_icon, LV_ALIGN_TOP_RIGHT, \
            -20, 10);
    else
        lv_obj_align(msg_type_icon, LV_ALIGN_TOP_LEFT, \
            20, 10);

    static char time_str[6];
    memset(time_str, 0, sizeof(time_str));
    sprintf(time_str, "%02d:%02d", \
        ui_message_ctx.message_time.hour, \
            ui_message_ctx.message_time.min);
    widget_label_para.label_w = \
        (80);
    widget_label_para.label_h = \
        Label_Line_Height;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_CLIP;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_ver_center = \
        false;
    widget_label_para.user_text_font = \
        NULL;
    widget_label_para.label_parent = \
        msg_detail_container;
    widget_label_para.label_text = \
        time_str;
    lv_obj_t *time_str_label = \
        common_widget_label_create(&widget_label_para);
    if(menu_align == menu_align_right)
        lv_obj_align(time_str_label, LV_ALIGN_TOP_LEFT, \
            20, 10);
    else
        lv_obj_align(time_str_label, LV_ALIGN_TOP_RIGHT, \
            -20, 10); 

    uint32_t str_len = \
        strlen(ui_message_ctx.message_content_str);
    bool arabic_letter = \
        utf8_str_is_arabic(\
            ui_message_ctx.message_content_str, str_len);

    widget_textarea_para.parent = \
        msg_detail_container;
    widget_textarea_para.width = \
        310;
    widget_textarea_para.height = \
        210;
    widget_textarea_para.txt = \
        ui_message_ctx.message_content_str;
    widget_textarea_para.font = \
        NULL;
    widget_textarea_para.color = \
        lv_color_hex(0xffffff);
    if(arabic_letter)
        widget_textarea_para.align = \
            LV_TEXT_ALIGN_RIGHT;
    else
        widget_textarea_para.align = \
            LV_TEXT_ALIGN_LEFT;
    widget_textarea_para.bg_opa_x = \
        LV_OPA_0;
    widget_textarea_para.bg_color = \
        lv_color_hex(0x000000);
    widget_textarea_para.border_width = \
        0;
    widget_textarea_para.border_opa_x = \
        LV_OPA_0;
    widget_textarea_para.border_color = \
        lv_color_hex(0x000000);
    lv_obj_t *msg_detail_ctx = \
        common_widget_textarea_create(&widget_textarea_para);
    lv_obj_align(msg_detail_ctx, LV_ALIGN_TOP_MID, \
        0, 68);

    widget_img_para.img_parent = \
        obj;
    widget_img_para.file_img_dat = \
        comm_icon_14_index;
    widget_img_para.img_click_attr = \
        true;
    widget_img_para.event_cb = \
        msg_detail_delete_button_cb;
    widget_img_para.user_data = \
        NULL;
    lv_obj_t *delete_button = \
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(delete_button, LV_ALIGN_TOP_MID, \
        0, 376);
    lv_obj_set_ext_click_area(delete_button, 10);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_msg_detail) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_msg_detail,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
