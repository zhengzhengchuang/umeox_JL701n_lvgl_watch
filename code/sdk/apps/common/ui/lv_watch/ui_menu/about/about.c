#include "about.h"

//static int16_t scroll_y_val = 0;
static lv_obj_t *about_container = NULL;

#if 0
static void about_container_scroll_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *obj = \
        lv_event_get_target(e);
    scroll_y_val = \
        lv_obj_get_scroll_y(obj);

    return;
}
#endif

static void about_container_create(lv_obj_t *obj)
{
    widget_obj_para.obj_parent = obj;
    widget_obj_para.obj_x = 0;
    widget_obj_para.obj_y = 0;
    widget_obj_para.obj_width = \
        LCD_WIDTH;
    widget_obj_para.obj_height = \
        LCD_HEIGHT;
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
    about_container = \
        common_widget_obj_create(&widget_obj_para);
    lv_obj_set_style_pad_bottom(about_container, \
        25, LV_PART_MAIN);

#if 0
    lv_obj_add_event_cb(about_container, \
        about_container_scroll_cb, LV_EVENT_SCROLL, \
            NULL);

    lv_obj_scroll_to_y(about_container, scroll_y_val, \
        LV_ANIM_OFF);
#endif

    return;
}

static void about_title_icon_create(void)
{
    widget_img_para.img_parent = \
        about_container;
    widget_img_para.img_x = 157;
    widget_img_para.img_y = 20;
    widget_img_para.file_img_dat = \
        about_00_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = NULL;
    common_widget_img_create(&widget_img_para, \
        NULL);

    return;
}

static void about_title_label_create(void)
{
    widget_label_para.label_x = 0;
    widget_label_para.label_y = 0;
    widget_label_para.label_w = \
        (LCD_WIDTH - 30);
    widget_label_para.label_h = \
        Label_Line_Height;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_SCROLL;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_ver_center = \
        false;
    widget_label_para.user_text_font = \
        NULL;
    widget_label_para.label_parent = \
        about_container;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_quran_watch);
    lv_obj_t *quran_watch_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align(quran_watch_label, LV_ALIGN_TOP_MID, \
        0, 88);

    return;
}

static void about_ble_name_elem_create(void)
{
    widget_img_para.img_parent = \
        about_container;
    widget_img_para.img_x = 24;
    widget_img_para.img_y = 152;
    widget_img_para.file_img_dat = \
        comm_icon_10_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = NULL;
    lv_obj_t *ble_name_container = \
        common_widget_img_create(&widget_img_para, \
            NULL);

    widget_label_para.label_w = \
        (260);
    widget_label_para.label_h = \
        Label_Line_Height;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_SCROLL;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_text_color = \
        lv_color_hex(0x777777);
    widget_label_para.label_ver_center = \
        false;
    widget_label_para.user_text_font = \
        NULL;
    widget_label_para.label_parent = \
        ble_name_container;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_bluetooth_name);
    lv_obj_t *ble_name_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align(ble_name_label, LV_ALIGN_TOP_MID, \
        0, 6);


    const char *ble_name_str = \
        ui_get_dev_ble_name();
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_text = \
        (char *)ble_name_str;
    lv_obj_t *ble_name_str_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align(ble_name_str_label, LV_ALIGN_BOTTOM_MID, \
        0, -6);

    return;
}

static void about_ble_mac_elem_create(void)
{   
    widget_img_para.img_parent = \
        about_container;
    widget_img_para.img_x = 24;
    widget_img_para.img_y = 272;
    widget_img_para.file_img_dat = \
        comm_icon_10_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = NULL;
    lv_obj_t *ble_mac_container = \
        common_widget_img_create(&widget_img_para, \
            NULL);

    widget_label_para.label_w = \
        (260);
    widget_label_para.label_h = \
        Label_Line_Height;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_SCROLL;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_text_color = \
        lv_color_hex(0x777777);
    widget_label_para.label_ver_center = \
        false;
    widget_label_para.user_text_font = \
        NULL;
    widget_label_para.label_parent = \
        ble_mac_container;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_bluetooth_mac);
    lv_obj_t *ble_mac_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align(ble_mac_label, LV_ALIGN_TOP_MID, \
        0, 6);

    uint8_t ble_mac_idx = 0;
    char ble_mac_str[18] = {0};
    const uint8_t *ble_mac = \
        ui_get_dev_ble_mac();

    for(uint8_t i = 0; i < 17; i++)
    {
        if(((i + 1) % 3) == 0)
		{
			ble_mac_idx++;
			ble_mac_str[i] = ':';
		}else if(((i + 1) % 3) == 1)
		{
			ble_mac_str[i] = ((ble_mac[ble_mac_idx] >> 4) & 0x0f) > 9 ? \
			    ((ble_mac[ble_mac_idx] >> 4) & 0x0f) + 0x37:\
                    ((ble_mac[ble_mac_idx] >> 4) & 0x0f) + 0x30;
		}else if(((i + 1) % 3) == 2)
		{
			ble_mac_str[i] = (ble_mac[ble_mac_idx] & 0x0f) > 9 ? \
			    ((ble_mac[ble_mac_idx]) & 0x0f) + 0x37:\
                    (ble_mac[ble_mac_idx] & 0x0f) + 0x30;
		}
    }
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_text = \
        ble_mac_str;
    lv_obj_t *ble_mac_str_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align(ble_mac_str_label, LV_ALIGN_BOTTOM_MID, \
        0, -6);

    return;
}

static void about_version_elem_create(void)
{
    widget_img_para.img_parent = \
        about_container;
    widget_img_para.img_x = 24;
    widget_img_para.img_y = 392;
    widget_img_para.file_img_dat = \
        comm_icon_10_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = NULL;
    lv_obj_t *version_container = \
        common_widget_img_create(&widget_img_para, \
            NULL);

    widget_label_para.label_w = \
        (260);
    widget_label_para.label_h = \
        Label_Line_Height;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_SCROLL;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_text_color = \
        lv_color_hex(0x777777);
    widget_label_para.label_ver_center = \
        false;
    widget_label_para.user_text_font = \
        NULL;
    widget_label_para.label_parent = \
        version_container;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_version);
    lv_obj_t *version_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align(version_label, LV_ALIGN_TOP_MID, \
        0, 6);

    char *version_str = \
        Version_Release_Str;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_text = \
        version_str;
    lv_obj_t *version_str_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align(version_str_label, LV_ALIGN_BOTTOM_MID, \
        0, -6);

    return;
}

static void about_QR_code_elem_create(void)
{
    widget_label_para.label_w = \
        (LCD_WIDTH - 30);
    widget_label_para.label_h = \
        Label_Line_Height;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_SCROLL;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_ver_center = \
        false;
    widget_label_para.user_text_font = \
        NULL;
    widget_label_para.label_parent = \
        about_container;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_QR_code);
    lv_obj_t *QR_code_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align(QR_code_label, LV_ALIGN_TOP_MID, \
        0, LCD_HEIGHT + 102);

    widget_img_para.img_parent = \
        about_container;
    widget_img_para.file_img_dat = \
        about_01_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = NULL;
    lv_obj_t *QR_code_icon = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_align_to(QR_code_icon, QR_code_label, \
        LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    return;
}

static void about_reset_button_cb(lv_event_t *e)
{
    if(!e) return;

    ui_menu_jump(ui_act_id_reset);

    return;
}

static void about_reset_button_elem_create(void)
{
    widget_img_para.img_parent = \
        about_container;
    widget_img_para.file_img_dat = \
        about_02_index;
    widget_img_para.img_click_attr = \
        true;
    widget_img_para.event_cb = \
        about_reset_button_cb;
    widget_img_para.user_data = NULL;
    lv_obj_t *reset_button = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_align(reset_button, LV_ALIGN_TOP_MID, \
        0, LCD_HEIGHT + 370);
    lv_obj_set_ext_click_area(reset_button, 10);

    widget_label_para.label_w = \
        (200);
    widget_label_para.label_h = \
        Label_Line_Height;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_SCROLL;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_ver_center = \
        false;
    widget_label_para.user_text_font = \
        NULL;
    widget_label_para.label_parent = \
        reset_button;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_factory_reset);
    lv_obj_t *reset_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_center(reset_label);

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_null, \
            ui_act_id_about);

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

    about_container_create(obj);

    about_title_icon_create();

    about_title_label_create();

    about_ble_name_elem_create();

    about_ble_mac_elem_create();

    about_version_elem_create();

    about_QR_code_elem_create();

    about_reset_button_elem_create();

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_about) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_about,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
