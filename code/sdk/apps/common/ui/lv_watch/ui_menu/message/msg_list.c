#include "msg_list.h"

vm_message_ctx_t ui_message_ctx;
static lv_obj_t *msg_list_container;
static int16_t msg_list_scroll_y = 0;

static const uint8_t msg_elem_container_idx[\
    Message_Max_Num] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
};

static uint8_t query_id;
uint8_t get_msg_detail_query_id(void)
{
    return query_id;
}

void set_msg_detail_query_id(uint8_t id)
{
    query_id = id;

    return;
}

static void msg_list_scroll_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *obj = \
        lv_event_get_target(e);
    msg_list_scroll_y = \
        lv_obj_get_scroll_y(obj);

    return;
}

static void msg_list_delete_button_cb(lv_event_t *e)
{
    if(!e) return;

    vm_message_ctx_clear();

    ui_act_id_t cur_act_id = \
        p_ui_info_cache->cur_act_id;
    ui_menu_jump(cur_act_id);

    return;
}

static void msg_list_elem_container_cb(lv_event_t *e)
{
    if(!e) return;

    uint8_t idx = \
        *(uint8_t *)lv_event_get_user_data(e);
    uint8_t msg_num = \
        vm_message_item_num();

    if(idx >= msg_num)
        return;

    set_msg_detail_query_id(idx);

    ui_menu_jump(ui_act_id_msg_detail);

    return;
}

static void msg_list_container_create(lv_obj_t *obj)
{
    widget_obj_para.obj_parent = obj;
    widget_obj_para.obj_x = 0;
    widget_obj_para.obj_y = \
        LCD_UI_Y_OFFSET;
    widget_obj_para.obj_width = \
        LCD_WIDTH;
    widget_obj_para.obj_height = \
        LCD_HEIGHT - LCD_UI_Y_OFFSET;
    widget_obj_para.obj_bg_opax = \
        LV_OPA_0;
    widget_obj_para.obj_bg_color = \
        lv_color_hex(0x000000);
    widget_obj_para.obj_border_opax = \
        LV_OPA_0;
    widget_obj_para.obj_border_width = 0;
    widget_obj_para.obj_border_color = \
        lv_color_hex(0x000000);
    widget_obj_para.obj_radius = 0;
    widget_obj_para.obj_is_scrollable = \
        true;
    msg_list_container = \
        common_widget_obj_create(&widget_obj_para);
    lv_obj_set_style_pad_bottom(msg_list_container, \
        25, LV_PART_MAIN);
    lv_obj_add_event_cb(msg_list_container, \
        msg_list_scroll_cb, LV_EVENT_SCROLL, NULL);

    return;
}

static void no_message_menu_create(lv_obj_t *obj)
{
    widget_img_para.img_parent = \
        obj;
    widget_img_para.file_img_dat = \
        message_icon_00_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = \
        NULL;
    lv_obj_t *no_msg_icon = \
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(no_msg_icon, LV_ALIGN_TOP_MID, \
        0, 88);

    widget_img_para.file_img_dat = \
        comm_icon_11_index;
    lv_obj_t *comm_11_icon =
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(comm_11_icon, LV_ALIGN_TOP_MID, \
        0, 266);

    widget_label_para.label_w = \
        (300);
    widget_label_para.label_h = \
        Label_Line_Height*2;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_WRAP;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_ver_center = \
        true;
    widget_label_para.user_text_font = NULL;
    widget_label_para.label_parent = \
        obj;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_no_message);
    lv_obj_t *no_msg_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align(no_msg_label, LV_ALIGN_TOP_MID, \
        0, 342);

    return;
}

static void has_message_menu_create(lv_obj_t *obj, \
    uint8_t msg_num, menu_align_t menu_align)
{
    if(msg_num >= \
        Message_Max_Num)
        msg_num = Message_Max_Num;

    msg_list_container_create(obj);

    uint8_t i;
    static char time_str[6];
    int16_t elem_container_sy = \
        28;
    for(i = 0; i < msg_num; i++)
    { 
        memset(&ui_message_ctx, 0, \
            sizeof(vm_message_ctx_t));
        vm_message_ctx_by_idx(i, &ui_message_ctx);

        widget_img_para.img_parent = \
            msg_list_container;
        widget_img_para.file_img_dat = \
            message_icon_02_index; 
        widget_img_para.img_click_attr = \
            true;
        widget_img_para.event_cb = \
            msg_list_elem_container_cb;
        widget_img_para.user_data = \
            (void *)&msg_elem_container_idx[i];
        lv_obj_t *elem_container = \
            common_widget_img_create(&widget_img_para, \
                NULL);
        lv_obj_align(elem_container, LV_ALIGN_TOP_MID, \
            0, elem_container_sy + 214*i);

        widget_img_para.img_parent = \
            elem_container;
        widget_img_para.file_img_dat = \
            message_type_00_index + \
                ui_message_ctx.message_type; 
        widget_img_para.img_click_attr = \
            false;
        widget_img_para.event_cb = \
            NULL;
        widget_img_para.user_data = \
            NULL;
        lv_obj_t *msg_type_icon = \
            common_widget_img_create(&widget_img_para, \
                NULL); 
        if(menu_align == menu_align_right)
            lv_obj_align(msg_type_icon, LV_ALIGN_TOP_RIGHT, \
                -20, 10);
        else
            lv_obj_align(msg_type_icon, LV_ALIGN_TOP_LEFT, \
                20, 10);

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
            elem_container;
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
        widget_label_para.label_w = \
            (288);
        widget_label_para.label_h = \
            Label_Line_Height*2;
        widget_label_para.long_mode = \
            LV_LABEL_LONG_DOT;
        if(arabic_letter)
            widget_label_para.text_align = \
                LV_TEXT_ALIGN_RIGHT;
        else
            widget_label_para.text_align = \
                LV_TEXT_ALIGN_LEFT;
        widget_label_para.label_text_color = \
            lv_color_hex(0xffffff);
        widget_label_para.label_ver_center = \
            false;
        widget_label_para.user_text_font = \
            NULL;
        widget_label_para.label_parent = \
            elem_container;
        widget_label_para.label_text = \
            ui_message_ctx.message_content_str;
        lv_obj_t *short_msg_label = \
            common_widget_label_create(&widget_label_para);
        lv_obj_align(short_msg_label, LV_ALIGN_TOP_MID, \
            0, 78);
    }

    widget_img_para.img_parent = \
        msg_list_container;
    widget_img_para.file_img_dat = \
        comm_icon_14_index;
    widget_img_para.img_click_attr = \
        true;
    widget_img_para.event_cb = \
        msg_list_delete_button_cb;
    widget_img_para.user_data = \
        NULL;
    lv_obj_t *delete_button = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_align(delete_button, LV_ALIGN_TOP_MID, \
        0, elem_container_sy + 214*i + 20);
    lv_obj_set_ext_click_area(delete_button, 10);

    lv_obj_scroll_to_y(msg_list_container, 0, \
        LV_ANIM_OFF);
    lv_obj_update_layout(msg_list_container);
    int16_t scroll_bottom_y = \
        lv_obj_get_scroll_bottom(msg_list_container);
    if(msg_list_scroll_y > scroll_bottom_y)
        msg_list_scroll_y = scroll_bottom_y;
    lv_obj_scroll_to_y(msg_list_container, msg_list_scroll_y, \
        LV_ANIM_OFF);

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_null, \
            ui_act_id_msg_list);

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    msg_list_container = \
        NULL;

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

    uint8_t msg_num = \
        vm_message_item_num();
    if(msg_num == 0)
        no_message_menu_create(obj);
    else
        has_message_menu_create(obj, \
            msg_num, menu_align);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_msg_list) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_msg_list,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
