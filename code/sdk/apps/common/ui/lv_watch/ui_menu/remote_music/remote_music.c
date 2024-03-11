#include "remote_music.h"

#define Slider_Range_Inc (6)
static uint8_t last_remote_music_vol;
static uint16_t music_state_icon_dsc;
static lv_obj_t *remote_music_state_icon;
static lv_obj_t *remote_music_vol_slider;
static lv_obj_t *remote_music_title_label;
static remote_music_state_t last_music_state;


static void music_prev_event_cb(lv_event_t *e)
{
    if(!e) return;

    ble_dev_ctrl_remote_music_prev();

    return;
}

static void music_next_event_cb(lv_event_t *e)
{
    if(!e) return;

    ble_dev_ctrl_remote_music_next();

    return;
}

static void music_state_event_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *obj = \
        lv_event_get_target(e);

    remote_music_state_t music_state = 
        get_remote_music_state();
    if(music_state == \
        remote_music_puase)
        music_state = \
            remote_music_play;
    else if(music_state == \
        remote_music_play)
        music_state = \
            remote_music_puase;

    last_music_state = music_state;
    
    uint32_t file_img_dat = \
        remote_music_02_index + music_state;
    common_widget_img_replace_src(obj, \
        file_img_dat, music_state_icon_dsc);

    set_remote_music_state(music_state);

    ble_dev_ctrl_remote_music_state();

    return;
}

static void music_volume_slider_event_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *obj = \
        lv_event_get_target(e);
    int32_t remote_music_vol = \
        lv_slider_get_value(obj)/\
            Slider_Range_Inc;

    if(remote_music_vol != \
        last_remote_music_vol)
    {
        last_remote_music_vol = \
            remote_music_vol;

        set_remote_music_volume(\
            remote_music_vol);

        sync_remote_music_volume();
    }

    return;
}

static void remote_music_disc_menu_create(lv_obj_t *obj)
{
    widget_obj_para.obj_parent = \
        obj;
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
        false;
    lv_obj_t *menu_cover_container = \
        common_widget_obj_create(&widget_obj_para);

    widget_img_para.img_parent = \
        menu_cover_container;
    widget_img_para.file_img_dat = \
        comm_icon_13_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = NULL;
    lv_obj_t *disc_tips_label_container = 
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(disc_tips_label_container, LV_ALIGN_TOP_MID, \
        0, 308);
    
    widget_label_para.label_parent = \
        disc_tips_label_container;
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
    widget_label_para.user_text_font = \
        NULL;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_connect_and_open);
    lv_obj_t *disc_tips_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_center(disc_tips_label);

    return;
}

static void remote_music_ctrl_menu_create(lv_obj_t *obj)
{
    uint8_t remote_music_vol = \
        get_remote_music_volume();
    uint8_t remote_music_max_vol = \
        Remote_Music_Max_Vol;

    last_remote_music_vol = \
        remote_music_vol;

    int32_t slider_min_val = 0;
    int32_t slider_cur_val = \
        remote_music_vol*Slider_Range_Inc;
    int32_t slider_max_val = \
        remote_music_max_vol*Slider_Range_Inc;

    widget_slider_para.slider_parent = \
        obj;
    widget_slider_para.slider_width = 304;
    widget_slider_para.slider_height = 72;
    widget_slider_para.slider_min_value = \
        slider_min_val;
    widget_slider_para.slider_max_value = \
        slider_max_val;
    widget_slider_para.slider_cur_value = \
        slider_cur_val;
    widget_slider_para.slider_main_color = \
        lv_color_hex(0xB28146);
    widget_slider_para.slider_indic_color = \
        lv_color_hex(0xF0D990);
    widget_slider_para.slider_knob_opax = \
        LV_OPA_0;
    widget_slider_para.slider_knob_color = \
        lv_color_hex(0x000000);
    widget_slider_para.event_cb = \
        music_volume_slider_event_cb;
    widget_slider_para.user_data = NULL;
    remote_music_vol_slider = \
        common_widget_slider_create(&widget_slider_para);
    lv_obj_align(remote_music_vol_slider, LV_ALIGN_TOP_MID, \
        0, 70);

    widget_img_para.event_cb = NULL;
    widget_img_para.img_parent = \
        remote_music_vol_slider;
    widget_img_para.file_img_dat = \
        sound_ctrl_01_index;
    widget_img_para.img_click_attr = \
        false;
    lv_obj_t *volume_down_icon = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_align(volume_down_icon, LV_ALIGN_LEFT_MID, \
        20, 0);

    widget_img_para.file_img_dat = \
        sound_ctrl_02_index;
    lv_obj_t *volume_up_icon = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_align(volume_up_icon, LV_ALIGN_RIGHT_MID, \
        -20, 0);

    widget_img_para.img_parent = \
        obj;
    widget_img_para.file_img_dat = \
        remote_music_04_index;
    lv_obj_t *remote_music_container = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_align(remote_music_container, LV_ALIGN_TOP_MID, \
        0, 166);


    widget_img_para.img_x = \
        24;
    widget_img_para.img_y = \
        124;
    widget_img_para.img_parent = \
        remote_music_container;
    widget_img_para.file_img_dat = \
        remote_music_00_index;
    widget_img_para.img_click_attr = \
        true;
    widget_img_para.event_cb = \
        music_prev_event_cb;
    lv_obj_t *remote_music_prev = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_set_ext_click_area(remote_music_prev, 5);

    widget_img_para.img_x = \
        222;
    widget_img_para.file_img_dat = \
        remote_music_01_index;
    widget_img_para.event_cb = \
        music_next_event_cb;
    lv_obj_t *remote_music_next = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_set_ext_click_area(remote_music_next, 5);

    remote_music_state_t music_state;
    music_state = \
        get_remote_music_state();
    last_music_state = \
        music_state;
    widget_img_para.img_x = \
        123;
    widget_img_para.file_img_dat = \
        remote_music_02_index + music_state;
    widget_img_para.event_cb = \
        music_state_event_cb;
    remote_music_state_icon = \
        common_widget_img_create(&widget_img_para, \
            &music_state_icon_dsc);
    lv_obj_set_ext_click_area(remote_music_state_icon, 5);


    widget_label_para.label_x = \
        42;
    widget_label_para.label_y = \
        30;
    widget_label_para.label_w = \
        (220);
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
        remote_music_container;
    widget_label_para.label_text = \
        get_remote_music_title();
    remote_music_title_label = \
        common_widget_label_create(&widget_label_para);
    
    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    ui_act_id_t prev_act_id = \
        read_menu_return_level_id();

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, prev_act_id, ui_act_id_null, \
            ui_act_id_remote_music);

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    return;
}

static void menu_refresh_cb(lv_obj_t *obj)
{
    if(!obj) return;

    uint8_t ble_bt_connect = \
        get_ble_bt_connect_status();
    if(ble_bt_connect == 0 || \
        ble_bt_connect == 2)
        return;
    
    /*如果说当前是设备更新音量，就不要同步手机的音量*/
    bool slider_dragged = \
        lv_slider_is_dragged(\
            remote_music_vol_slider);
    if(slider_dragged)
        goto __refr_music;

    uint8_t remote_music_vol = \
        get_remote_music_volume();
    if(remote_music_vol == \
        last_remote_music_vol)
        goto __refr_music;

    last_remote_music_vol = \
        remote_music_vol;

    int32_t slider_cur_value = \
        remote_music_vol*Slider_Range_Inc;
    lv_slider_set_value(remote_music_vol_slider, \
        slider_cur_value, LV_ANIM_OFF);

__refr_music:
    remote_music_state_t music_state;
    music_state = 
        get_remote_music_state();
    if(music_state == last_music_state)
        goto __refr_title;
    last_music_state = music_state;
    uint32_t file_img_dat = \
        remote_music_02_index + music_state;
    common_widget_img_replace_src(\
        remote_music_state_icon, file_img_dat, \
            music_state_icon_dsc);
    set_remote_music_state(music_state);

__refr_title:
    lv_label_set_text(remote_music_title_label, \
        get_remote_music_title());

    return;
}

static void menu_display_cb(lv_obj_t *obj)
{
    if(!obj) return;

    remote_music_ctrl_menu_create(obj);

    uint8_t ble_bt_connect = \
        get_ble_bt_connect_status();
    if(ble_bt_connect == 0 || \
        ble_bt_connect == 2)
        remote_music_disc_menu_create(obj);  

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_remote_music) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_remote_music,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 100,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
