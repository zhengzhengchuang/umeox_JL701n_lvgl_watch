#include "al_name_ex.h"
#include "al_name_list.h"

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    ui_act_id_t prev_act_id = \
        read_menu_return_level_id();

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, prev_act_id, ui_act_id_null, \
            ui_act_id_al_name_ex);

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

    widget_img_para.img_parent = \
        obj;
    widget_img_para.file_img_dat = \
        comm_icon_30_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = \
        NULL;
    lv_obj_t *al_name_ex_container = \
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(al_name_ex_container, LV_ALIGN_TOP_MID, \
        0, 20);

    uint8_t id = \
        get_al_name_ex_id();

    widget_label_para.label_w = \
        170;
    widget_label_para.label_h = \
        Label_Line_Height;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_SCROLL;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_text_color = \
        lv_color_hex(0x000000);
    widget_label_para.label_ver_center = \
        false;
    widget_label_para.user_text_font = \
        NULL;
    widget_label_para.label_parent = \
        al_name_ex_container;
    widget_label_para.label_text = \
        al_name_lang_txt_with_id(id);
    lv_obj_t *al_name_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align(al_name_label, LV_ALIGN_TOP_MID, \
        0, 50);

    widget_textarea_para.parent = \
        al_name_ex_container;
    widget_textarea_para.width = \
        280;
    widget_textarea_para.height = \
        236;
    widget_textarea_para.txt = \
        al_name_ex_lang_txt_with_id(id);
    widget_textarea_para.font = \
        NULL;
    widget_textarea_para.color = \
        lv_color_hex(0x000000);
    if(menu_align == menu_align_right)
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
    lv_obj_t *al_name_ex_textarea = \
        common_widget_textarea_create(&widget_textarea_para);
    lv_obj_align(al_name_ex_textarea, LV_ALIGN_TOP_MID, \
        0, 96);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_al_name_ex) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_al_name_ex,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
