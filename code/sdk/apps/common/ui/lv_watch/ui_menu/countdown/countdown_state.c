#include "countdown_time.h"
#include "countdown_state.h"

static lv_obj_t *countdown_time_arc;
static lv_obj_t *countdown_time_obj[8];
static uint16_t countdown_state_dsc_idx;
static uint16_t countdown_num_dsc_idx[8];

static void countdown_reset_cb(lv_event_t *e)
{
    if(!e) return;

    common_user_countdown_reset();

    ui_act_id_t prev_act_id = \
        read_menu_return_level_id();
    ui_menu_jump(prev_act_id);

    return;
}

static void countdown_state_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *obj = \
        lv_event_get_target(e);

    countdown_attribute_state_t countdown_state = \
        p_ui_info_cache->common_countdown_para.countdown_state;
    if(countdown_state == countdown_state_start)
    {
        common_user_countdown_pause();

        common_widget_img_replace_src(obj, \
            comm_icon_28_index, countdown_state_dsc_idx);
    }else if(countdown_state == countdown_state_puase)
    {
        common_user_countdown_resume();

        common_widget_img_replace_src(obj, \
            comm_icon_27_index, countdown_state_dsc_idx);
    }
        
    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_null, \
            ui_act_id_countdown_state);

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    return;
}

static void menu_refresh_cb(lv_obj_t *obj)
{
    if(!obj) return;

    uint32_t file_img_dat;
    countdown_attribute_data_t *countdown_data = \
        &p_ui_info_cache->common_countdown_para.countdown_data;

    uint8_t countdown_time_hour = \
        countdown_data->countdown_cur_cnt/3600;
    uint8_t countdown_time_minute = \
        (countdown_data->countdown_cur_cnt%3600)/60;
    uint8_t countdown_time_second = \
        (countdown_data->countdown_cur_cnt%3600)%60;
    char countdown_time_str[10];
    memset(countdown_time_str, 0, \
        sizeof(countdown_time_str));
    sprintf(countdown_time_str, "%02d:%02d:%02d", \
        countdown_time_hour, countdown_time_minute, \
            countdown_time_second);
    for(uint8_t i = 0; i < 8; i++)
    {
        if(countdown_time_str[i] == ':')
            file_img_dat = \
                comm_num_30x50_wh_10_index;
        else
            file_img_dat = \
                comm_num_30x50_wh_00_index + \
                    (countdown_time_str[i] - '0');

        common_widget_img_replace_src(countdown_time_obj[i], \
            file_img_dat, countdown_num_dsc_idx[i]);
    }

    lv_arc_set_value(countdown_time_arc, \
        countdown_data->countdown_per);

    return;
}

static void menu_display_cb(lv_obj_t *obj)
{
    if(!obj) return;

    uint32_t countdown_time_total = \
        get_countdown_time_total();
    common_user_countdown_create(\
        countdown_time_total);

    countdown_attribute_data_t *countdown_data = \
        &p_ui_info_cache->common_countdown_para.countdown_data;

    widget_arc_para.arc_parent = \
        obj;
    widget_arc_para.arc_bg_width = \
        320;
    widget_arc_para.arc_bg_height = \
        320;
    widget_arc_para.arc_bg_opax = \
        LV_OPA_0;
    widget_arc_para.arc_main_start_angle = \
        0;
    widget_arc_para.arc_main_end_angle = \
        360;
    widget_arc_para.arc_indic_start_angle = \
        0;
    widget_arc_para.arc_indic_end_angle = \
        360;
    widget_arc_para.arc_rotation_angle = \
        270;
    widget_arc_para.arc_min_value = \
        0;
    widget_arc_para.arc_max_value = \
        get_countdown_per_max();
    widget_arc_para.arc_cur_value = \
        countdown_data->countdown_per;
    widget_arc_para.arc_main_line_width = \
        10;
    widget_arc_para.arc_indic_line_width = \
        10;
    widget_arc_para.arc_main_line_color = \
        lv_color_hex(0x13130b);
    widget_arc_para.arc_indic_line_color = \
        lv_color_hex(0xD0BD84);
    widget_arc_para.arc_main_is_rounded = \
        true;
    widget_arc_para.arc_indic_is_rounded = \
        true;
    widget_arc_para.arc_click_is_clear = \
        true;
    countdown_time_arc = \
        common_widget_arc_create(&widget_arc_para);
    lv_obj_align(countdown_time_arc, LV_ALIGN_TOP_MID, \
        0, 40);

    widget_img_para.img_parent = \
        obj;
    widget_img_para.img_x = \
        113;
    widget_img_para.img_y = \
        123;
    widget_img_para.file_img_dat = \
        countdown_00_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = \
        NULL;
    common_widget_img_create(&widget_img_para, NULL);

    uint8_t countdown_time_hour = \
        countdown_data->countdown_cur_cnt/3600;
    uint8_t countdown_time_minute = \
        (countdown_data->countdown_cur_cnt%3600)/60;
    uint8_t countdown_time_second = \
        (countdown_data->countdown_cur_cnt%3600)%60;
    char countdown_time_str[10];
    memset(countdown_time_str, 0, \
        sizeof(countdown_time_str));
    sprintf(countdown_time_str, "%02d:%02d:%02d", \
        countdown_time_hour, countdown_time_minute, \
            countdown_time_second);

    num_str_para.parent = \ 
        obj;
    num_str_para.num_obj_x = \
        160;
    num_str_para.num_obj_y = \
        130;
    num_str_para.p_num_str = \
        countdown_time_str;
    num_str_para.num_str_len = \
        8;
    num_str_para.num_obj = \
        NULL;
    num_str_para.num_obj_max = \
        0;
    num_str_para.num_dsc_idx = \
        NULL;
    num_str_para.file_00_index = \
        comm_num_14x22_gr_00_index;
    common_widget_num_str_create(&num_str_para);

    num_str_para.num_obj_x = \
        79;
    num_str_para.num_obj_y = \
        190;
    num_str_para.num_obj = \
        countdown_time_obj;
    num_str_para.num_obj_max = \
        8;
    num_str_para.num_dsc_idx = \
        countdown_num_dsc_idx;
    num_str_para.file_00_index = \
        comm_num_30x50_wh_00_index;
    common_widget_num_str_create(&num_str_para);

    widget_img_para.img_parent = \
        obj;
    widget_img_para.img_x = \
        60;
    widget_img_para.img_y = \
        376;
    widget_img_para.file_img_dat = \
        comm_icon_26_index;
    widget_img_para.img_click_attr = \
        true;
    widget_img_para.event_cb = \
        countdown_reset_cb;
    widget_img_para.user_data = \
        NULL;
    lv_obj_t *countdown_reset_icon = \
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_set_ext_click_area(countdown_reset_icon, 20);

    countdown_attribute_state_t countdown_state = \
        p_ui_info_cache->common_countdown_para.countdown_state;
    widget_img_para.img_x = \
        214;
    if(countdown_state == countdown_state_start)
        widget_img_para.file_img_dat = \
            comm_icon_27_index;
    else if(countdown_state == countdown_state_puase)
        widget_img_para.file_img_dat = \
            comm_icon_28_index;
    widget_img_para.event_cb = \
        countdown_state_cb;
    lv_obj_t *countdown_state_icon = \
    common_widget_img_create(&widget_img_para, \
        &countdown_state_dsc_idx);
    lv_obj_set_ext_click_area(countdown_state_icon, 20);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_countdown_state) = 
{
    .menu_arg = NULL,
    .lock_flag = true,
    .return_flag = false,
    .menu_id = \
        ui_act_id_countdown_state,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 100,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
