#include "backlight.h"

/*滑块范围增大*/
#define Slider_Range_Inc (3)

static void backlight_slider_event_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *obj = \
        lv_event_get_target(e);
    int32_t cur_backlight_val = \
        lv_slider_get_value(obj)/ \
            Slider_Range_Inc;

    int min_backlight_val = \
        TCFG_MIN_BACKLIGHT_VAL;
    int max_backlight_val = \
        TCFG_MAX_BACKLIGHT_VAL;
    
    if(cur_backlight_val < min_backlight_val)
        cur_backlight_val = min_backlight_val;

    if(cur_backlight_val > max_backlight_val)
        cur_backlight_val = max_backlight_val;

    set_vm_para_cache_with_label(\
        vm_label_backlight, cur_backlight_val);
    
    ui_set_sys_backlight(cur_backlight_val);
  
    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_screen_sleep, \
            ui_act_id_backlight);

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

    int cur_backlight_val = \
        get_vm_para_cache_with_label(\
            vm_label_backlight)*\
                Slider_Range_Inc;
    int min_backlight_val = \
        TCFG_MIN_BACKLIGHT_VAL*\
            Slider_Range_Inc;
    int max_backlight_val = \
        TCFG_MAX_BACKLIGHT_VAL*\
            Slider_Range_Inc;

    widget_slider_para.slider_parent = obj;
    widget_slider_para.slider_x = 0;
    widget_slider_para.slider_y = 0;
    widget_slider_para.slider_width = 82;
    widget_slider_para.slider_height = 284;
    widget_slider_para.slider_min_value = \ 
        min_backlight_val;
    widget_slider_para.slider_max_value = \
        max_backlight_val;
    widget_slider_para.slider_cur_value = \
        cur_backlight_val;
    widget_slider_para.slider_main_color = \
        lv_color_hex(0xB28146);
    widget_slider_para.slider_indic_color = \
        lv_color_hex(0xF0D990);
    widget_slider_para.slider_knob_opax = \
        LV_OPA_0;
    widget_slider_para.slider_knob_color = \
        lv_color_hex(0x000000);
    widget_slider_para.event_cb = \
        backlight_slider_event_cb;
    widget_slider_para.user_data = NULL;
    lv_obj_t *backlight_slider = \
        common_widget_slider_create(&widget_slider_para);
    lv_obj_align(backlight_slider, LV_ALIGN_TOP_MID, 0, \
        80);

    widget_img_para.event_cb = NULL;
    widget_img_para.user_data = NULL;
    widget_img_para.img_parent = \
        backlight_slider;
    widget_img_para.file_img_dat = \
        disp_ctrl_00_index;
    widget_img_para.img_click_attr = \
        false;
    lv_obj_t *backlight_down_icon = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_align(backlight_down_icon, LV_ALIGN_BOTTOM_MID, \
        0, -20);

    widget_img_para.file_img_dat = \
        disp_ctrl_01_index;
    lv_obj_t *backlight_up_icon = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_align(backlight_up_icon, LV_ALIGN_TOP_MID, \
        0, 20);

    /********************圆点********************/
    widget_img_para.img_x = 170;
    widget_img_para.img_y = 398;
    widget_img_para.img_parent = \
        obj;
    widget_img_para.file_img_dat = \
        comm_icon_07_index;
    common_widget_img_create(&widget_img_para, \
        NULL);

    widget_img_para.img_x = 190;
    widget_img_para.file_img_dat = \
        comm_icon_08_index;
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
    menu_load_backlight) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_backlight,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
