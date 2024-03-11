#include "call_end.h"

#define Menu_Jump_Dur (5)
static lv_timer_t *menu_jump_timer = NULL;
static uint8_t menu_jump_duration = Menu_Jump_Dur;

static void call_end_container_event_cb(lv_event_t *e)
{
    if(!e) return;

    ui_act_id_t prev_act_id = \
        read_menu_return_level_id();
    ui_menu_jump(prev_act_id);

    return;
}

static void menu_jump_timer_cb(lv_timer_t *timer)
{
    if(!menu_jump_timer)
        return;

    ui_act_id_t prev_act_id = \
        read_menu_return_level_id();

    lv_timer_del(menu_jump_timer);
    menu_jump_timer = NULL;

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
            ui_act_id_call_end);

    menu_jump_duration = \
        Menu_Jump_Dur;
    if(!menu_jump_timer)
        menu_jump_timer = \
            lv_timer_create(menu_jump_timer_cb, \
                menu_jump_duration*1000, NULL);

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    if(menu_jump_timer)
    {
        lv_timer_del(menu_jump_timer);
        menu_jump_timer = NULL;
    }

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

    uint32_t call_online_duration = \
        get_call_online_duration();
    char call_online_duration_str[9];
    memset(call_online_duration_str, 0, \
        sizeof(call_online_duration_str));
    sprintf(call_online_duration_str, "%02d:%02d:%02d", \
        call_online_duration/3600, (call_online_duration%3600)/60, \
            (call_online_duration%3600)%60);
 
    int16_t img_x_offset = 0;
    widget_img_para.img_y = 155;
    widget_img_para.img_parent = obj;
    widget_img_para.img_click_attr = false;
    widget_img_para.event_cb = NULL;
    for(uint8_t i = 0; i < 8; i++)
    {
        widget_img_para.img_x = \
            135 + img_x_offset;
        if(call_online_duration_str[i] == ':')
            widget_img_para.file_img_dat = \
                comm_num_14x22_gr_10_index;
        else
             widget_img_para.file_img_dat = \
                comm_num_14x22_gr_00_index + \
                    (call_online_duration_str[i] - '0');
        
        if(call_online_duration_str[i] == ':')
            img_x_offset += 7;
        else
            img_x_offset += 14;
        
        common_widget_img_create(&widget_img_para, NULL);
    }

    widget_img_para.file_img_dat = \
        comm_icon_13_index;
    widget_img_para.img_click_attr = true;
    widget_img_para.event_cb = \
        call_end_container_event_cb;
    widget_img_para.user_data = NULL;
    lv_obj_t *call_end_container = \
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(call_end_container, LV_ALIGN_TOP_MID, \
        0, 308);
    
    widget_label_para.label_w = \
        (320);
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
        call_end_container;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_call_end);
    lv_obj_t *call_end_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_center(call_end_label);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_call_end) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = false,
    .menu_id = \
        ui_act_id_call_end,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
