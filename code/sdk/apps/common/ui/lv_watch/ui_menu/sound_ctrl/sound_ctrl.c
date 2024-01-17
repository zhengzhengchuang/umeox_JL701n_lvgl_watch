#include "audio_config.h"
#include "sound_ctrl.h"

/*滑块范围增大*/
#define Slider_Range_Inc (5)

static uint16_t switch_dsc_idx = 0xffff;
static lv_obj_t *music_vol_slider = NULL;

static void sound_on_switch_event_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *obj = \
        lv_event_get_target(e);

    int sound_on_flag = \
        get_vm_para_cache_with_label(\
            vm_label_sys_sound_on);
    sound_on_flag = !sound_on_flag;
    set_vm_para_cache_with_label(\
        vm_label_sys_sound_on, sound_on_flag);

    common_widget_img_replace_src(obj, \
        comm_icon_00_index + sound_on_flag, \
            switch_dsc_idx);

    if(!sound_on_flag)
    {
        lv_obj_add_flag(music_vol_slider, \
            LV_OBJ_FLAG_HIDDEN);
    }else
    {
        lv_obj_clear_flag(music_vol_slider, \
            LV_OBJ_FLAG_HIDDEN);
    }
        
    return;
}

static void sound_vol_slider_event_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *obj = \
        lv_event_get_target(e);
    int32_t cur_music_vol = \
        lv_slider_get_value(obj)/Slider_Range_Inc;

    // printf("cur_music_vol = %d\n", \
    //     cur_music_vol);
    
    app_audio_set_volume(APP_AUDIO_STATE_MUSIC, \
        cur_music_vol, 1);
 
    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_null, \
            ui_act_id_sound_ctrl);

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

    widget_img_para.img_x = 24;
    widget_img_para.img_y = 32;   
    widget_img_para.event_cb = NULL;
    widget_img_para.user_data = NULL;
    widget_img_para.img_parent = obj;
    widget_img_para.file_img_dat = \
        comm_icon_09_index;
    widget_img_para.img_click_attr = false;
    lv_obj_t *sound_on_container = \
        common_widget_img_create(&widget_img_para, NULL);

    widget_label_para.label_parent = \
        sound_on_container;
    widget_label_para.label_x = 0;
    widget_label_para.label_y = 0;
    widget_label_para.label_w = \
        (180);
    widget_label_para.label_h = \
        Label_Line_Height;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_SCROLL;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_LEFT;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_ver_center = \
        false;
    widget_label_para.user_text_font = NULL;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_sound_on);
    lv_obj_t *sound_on_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align(sound_on_label, LV_ALIGN_LEFT_MID, \
        10, 0);

    int sound_on_flag = \
        get_vm_para_cache_with_label(\
            vm_label_sys_sound_on);
    if(sound_on_flag)
        sound_on_flag = !!sound_on_flag;
    
    widget_img_para.img_x = 218;
    widget_img_para.img_y = 26;
    widget_img_para.event_cb = \
        sound_on_switch_event_cb;
    widget_img_para.user_data = NULL;
    widget_img_para.img_parent = \
        sound_on_container;
    widget_img_para.file_img_dat = \
        comm_icon_00_index + sound_on_flag;
    widget_img_para.img_click_attr = true;
    lv_obj_t *sound_on_switch = \
        common_widget_img_create(&widget_img_para, \
            &switch_dsc_idx);
    lv_obj_set_ext_click_area(sound_on_switch, \
        10);

    int32_t cur_music_vol = \
        app_audio_get_volume(\
            APP_AUDIO_STATE_MUSIC)*Slider_Range_Inc;
    int32_t max_music_vol = \
        get_max_sys_vol()*Slider_Range_Inc;

    widget_slider_para.slider_parent = obj;
    widget_slider_para.slider_x = 148;
    widget_slider_para.slider_y = 140;
    widget_slider_para.slider_width = 82;
    widget_slider_para.slider_height = 284;
    widget_slider_para.slider_min_value = 0;
    widget_slider_para.slider_max_value = \
        max_music_vol;
    widget_slider_para.slider_cur_value = \
        cur_music_vol;
    widget_slider_para.slider_main_color = \
        lv_color_hex(0xB28146);
    widget_slider_para.slider_indic_color = \
        lv_color_hex(0xF0D990);
    widget_slider_para.slider_knob_opax = \
        LV_OPA_0;
    widget_slider_para.slider_knob_color = \
        lv_color_hex(0x000000);
    widget_slider_para.event_cb = \
        sound_vol_slider_event_cb;
    widget_slider_para.user_data = NULL;
    music_vol_slider = \
        common_widget_slider_create(&widget_slider_para);
    if(!sound_on_flag)
        lv_obj_add_flag(music_vol_slider, \
            LV_OBJ_FLAG_HIDDEN);

    
    widget_img_para.event_cb = NULL;
    widget_img_para.user_data = NULL;
    widget_img_para.img_parent = \
        music_vol_slider;
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
    menu_load_sound_ctrl) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_sound_ctrl,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
