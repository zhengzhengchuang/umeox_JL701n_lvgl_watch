#include "call_volume.h"
#include "audio_config.h"
#include "../../../../../../include_lib/btstack/avctp_user.h"

/*滑块范围增大*/
#define Slider_Range_Inc (5)
static uint8_t last_call_vol = 0;
static lv_obj_t *call_vol_slider = NULL;

static void call_vol_slider_event_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *obj = \
        lv_event_get_target(e);
    int32_t cur_call_vol = \
        lv_slider_get_value(obj)/Slider_Range_Inc;

    if(cur_call_vol != last_call_vol)
    {
        last_call_vol = cur_call_vol;

        app_audio_set_volume(APP_AUDIO_STATE_CALL, \
            cur_call_vol, 1);

        user_send_cmd_prepare(USER_CTRL_HFP_CALL_SET_VOLUME, 1, \
            &cur_call_vol);
    }

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_call_online, ui_act_id_null, \
            ui_act_id_call_volume);

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    call_vol_slider = NULL;

    return;
}

static void menu_refresh_cb(lv_obj_t *obj)
{
    if(!obj) return;

    //TODO:手机同步下来的音量怎么更新

    return;
}

static void menu_display_cb(lv_obj_t *obj)
{
    if(!obj) return;

     int32_t cur_call_vol = \
        app_audio_get_volume(\
            APP_AUDIO_STATE_CALL);
    int32_t max_call_vol = \
        (get_max_sys_vol() - 1);

    last_call_vol = cur_call_vol;

    widget_slider_para.slider_parent = obj;
    widget_slider_para.slider_x = 0;
    widget_slider_para.slider_y = 0;
    widget_slider_para.slider_width = 82;
    widget_slider_para.slider_height = 284;
    widget_slider_para.slider_min_value = 0;
    widget_slider_para.slider_max_value = \
        max_call_vol*Slider_Range_Inc;
    widget_slider_para.slider_cur_value = \
        cur_call_vol*Slider_Range_Inc;
    widget_slider_para.slider_main_color = \
        lv_color_hex(0xB28146);
    widget_slider_para.slider_indic_color = \
        lv_color_hex(0xF0D990);
    widget_slider_para.slider_knob_opax = \
        LV_OPA_0;
    widget_slider_para.slider_knob_color = \
        lv_color_hex(0x000000);
    widget_slider_para.event_cb = \
        call_vol_slider_event_cb;
    widget_slider_para.user_data = NULL;
    call_vol_slider = \
        common_widget_slider_create(&widget_slider_para);
    lv_obj_center(call_vol_slider);

    widget_img_para.event_cb = NULL;
    widget_img_para.user_data = NULL;
    widget_img_para.img_parent = \
        call_vol_slider;
    widget_img_para.file_img_dat = \
        sound_ctrl_01_index;
    widget_img_para.img_click_attr = false;
    lv_obj_t *vol_down_icon = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_align(vol_down_icon, LV_ALIGN_BOTTOM_MID, \
        0, -20);

    widget_img_para.file_img_dat = \
        sound_ctrl_02_index;
    lv_obj_t *vol_up_icon = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_align(vol_up_icon, LV_ALIGN_TOP_MID, \
        0, 20);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_call_volume) = 
{
    .menu_arg = NULL,
    .lock_flag = true,
    .return_flag = false,
    .menu_id = \
        ui_act_id_call_volume,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 100,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
