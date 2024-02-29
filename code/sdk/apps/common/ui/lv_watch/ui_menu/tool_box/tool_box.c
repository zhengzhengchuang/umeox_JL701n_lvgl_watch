#include "tool_box.h"

/*************页面元素***************/
static lv_obj_t *tool_box_container = NULL;
static lv_obj_t *tool_box_tips_label = NULL;
static lv_timer_t *tips_label_hd_timer = NULL;
static const uint16_t tips_label_duration = 3*1000;

static void tips_label_hd_timer_cb(lv_timer_t *timer)
{
    if(!tips_label_hd_timer)
        return;

    lv_timer_pause(tips_label_hd_timer);

    lv_obj_add_flag(tool_box_tips_label, \
        LV_OBJ_FLAG_HIDDEN);

    return;
}

static void tips_label_hd_timer_resume(void)
{
    if(!tips_label_hd_timer)
        return;

    lv_timer_reset(tips_label_hd_timer);
    lv_timer_resume(tips_label_hd_timer);

    return;
}

static void tips_label_hd_timer_create(void)
{
    if(tips_label_hd_timer)
    {
        lv_timer_del(tips_label_hd_timer);
        tips_label_hd_timer = NULL;
    }

    tips_label_hd_timer = \
        lv_timer_create(tips_label_hd_timer_cb, \
            tips_label_duration, NULL);
    lv_timer_pause(tips_label_hd_timer);

    return;
}

static void tips_label_hd_timer_destory(void)
{
    if(tips_label_hd_timer)
    {
        lv_timer_del(tips_label_hd_timer);
        tips_label_hd_timer = NULL;
    }

    return;
}

/*************查找手机事件回调***************/
static void tool_box_find_event_cb(lv_event_t *e)
{
    if(!e) return;

    uint8_t ble_bt_connect = \
        ui_get_ble_bt_connect_status();
    if(ble_bt_connect == 0 || \
        ble_bt_connect == 2)
    {
        lv_label_set_text(tool_box_tips_label, \
            get_lang_txt_with_id(\
                lang_txtid_not_connected_phone));  
    }else
    {
        lv_label_set_text(tool_box_tips_label, \
            get_lang_txt_with_id(\
                lang_txtid_searching_for_phone));

        ui_ctrl_ble_dev_find_phone();
    }

    lv_obj_clear_flag(tool_box_tips_label, \
            LV_OBJ_FLAG_HIDDEN);

    tips_label_hd_timer_resume();

    return;
}

/*************相机事件回调***************/
static void tool_box_camera_event_cb(lv_event_t *e)
{
    if(!e) return;

    uint8_t ble_bt_connect = \
        ui_get_ble_bt_connect_status();
    if(ble_bt_connect == 0 || \
        ble_bt_connect == 2)
    {
        lv_label_set_text(tool_box_tips_label, \
            get_lang_txt_with_id(\
                lang_txtid_not_connected_phone));

        lv_obj_clear_flag(tool_box_tips_label, \
            LV_OBJ_FLAG_HIDDEN);

        tips_label_hd_timer_resume();  
    }else
    {
        /****进入相机操作页面****/

        ui_ctrl_phone_enter_camera();
    }

    return;
}

/*************设置事件回调***************/
static void tool_box_setting_event_cb(lv_event_t *e)
{
    if(!e) return;

    ui_menu_jump(ui_act_id_settings_list);

    return;
}

/*************勿扰事件回调***************/
static void tool_box_dnd_state_event_cb(lv_event_t *e)
{
    if(!e) return;

    return;
}

/*************背光事件回调***************/
static void tool_box_backlight_event_cb(lv_event_t *e)
{
    if(!e) return;

    ui_menu_jump(ui_act_id_backlight);

    return;
}

static void tool_box_earphone_state_event_cb(lv_event_t *e)
{
    if(!e) return;

    return;
}

static void tool_box_container_create(lv_obj_t *obj)
{
    widget_obj_para.obj_parent = \
        obj;
    widget_obj_para.obj_width = \
        320;
    widget_obj_para.obj_height = \
        196;
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
    widget_obj_para.obj_is_scrollable = false;
    tool_box_container = \
        common_widget_obj_create(&widget_obj_para);
    lv_obj_align(tool_box_container, LV_ALIGN_TOP_MID, \
        0, 80);

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_null, \
            ui_act_id_tool_box);

    tips_label_hd_timer_create();

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    tips_label_hd_timer_destory();

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

    tool_box_container_create(obj);

    int cur_backlight_val = \
        get_vm_para_cache_with_label(\
            vm_label_backlight);
    uint8_t backlight_level = \
        (cur_backlight_val - TCFG_BACKLIGHT_MIN_VAL)/ \
            TCFG_BACKLIGHT_STEPS_VAL;
    backlight_level = backlight_level > TCFG_BACKLIGHT_MAX_LEVEL?\
        TCFG_BACKLIGHT_MAX_LEVEL:backlight_level;
    widget_img_para.img_parent = \
        tool_box_container;
    widget_img_para.file_img_dat = \
        tool_box_light_00_index + backlight_level;
    widget_img_para.img_click_attr = true;
    widget_img_para.event_cb = \
        tool_box_backlight_event_cb;
    widget_img_para.user_data = NULL;
    lv_obj_t *backlight_icon = 
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(backlight_icon, LV_ALIGN_TOP_LEFT, \
        0, 0);

    widget_img_para.file_img_dat = \
        tool_box_find_00_index;
    widget_img_para.event_cb = \
        tool_box_find_event_cb;
    lv_obj_t *find_icon = 
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(find_icon, LV_ALIGN_TOP_MID, \
        0, 0);

    widget_img_para.file_img_dat = \
        tool_box_camera_00_index;
    widget_img_para.event_cb = \
        tool_box_camera_event_cb;
    lv_obj_t *camera_icon = 
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(camera_icon, LV_ALIGN_TOP_RIGHT, \
        0, 0);

    int dnd_state = \
        get_vm_para_cache_with_label(\
            vm_label_dnd_state);
    widget_img_para.file_img_dat = \
        tool_box_dnd_00_index + dnd_state;
    widget_img_para.event_cb = \
        tool_box_dnd_state_event_cb;
    lv_obj_t *dnd_state_icon = 
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(dnd_state_icon, LV_ALIGN_BOTTOM_LEFT, \
        0, 0);

    int earphone_state = \
        get_vm_para_cache_with_label(\
            vm_label_earphone_state);
    widget_img_para.file_img_dat = \
        tool_box_ear_00_index + earphone_state;
    widget_img_para.event_cb = \
        tool_box_earphone_state_event_cb;
    lv_obj_t *earphone_state_icon = 
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(earphone_state_icon, LV_ALIGN_BOTTOM_MID, \
        0, 0);

    widget_img_para.file_img_dat = \
        tool_box_setting_00_index;
    widget_img_para.event_cb = \
        tool_box_setting_event_cb;
    lv_obj_t *setting_icon = 
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(setting_icon, LV_ALIGN_BOTTOM_RIGHT, \
        0, 0);

    widget_img_para.img_parent = \
        obj;
    widget_img_para.file_img_dat = \
        comm_icon_13_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = NULL;
    lv_obj_t *tips_label_container = 
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(tips_label_container, LV_ALIGN_TOP_MID, \
        0, 308);
    
    widget_label_para.label_parent = \
        tips_label_container;
    widget_label_para.label_w = \
        (280);
    widget_label_para.label_h = \
        Label_Line_Height*2;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_WRAP;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_text_color = \
        lv_color_hex(0x000000);
    widget_label_para.label_ver_center = \
        true;
    widget_label_para.user_text_font = NULL;
    widget_label_para.label_text = \
        NULL;
    tool_box_tips_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_center(tool_box_tips_label);
    lv_obj_add_flag(tool_box_tips_label, \
        LV_OBJ_FLAG_HIDDEN);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_tool_box) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_tool_box,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};

