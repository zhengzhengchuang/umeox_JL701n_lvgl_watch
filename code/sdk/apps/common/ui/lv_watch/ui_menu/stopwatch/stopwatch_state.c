#include "stopwatch_state.h"

static lv_obj_t *stopwatch_num_obj[8];
static uint16_t stopwatch_num_dsc_idx[8];

static lv_obj_t *stopwatch_state_icon;
static uint16_t stopwatch_state_dsc_idx;

static void stopwatch_reset_cb(lv_event_t *e)
{
    if(!e) return;

    common_user_stopwatch_reset();

    ui_act_id_t prev_act_id = \
        read_menu_return_level_id();
    ui_menu_jump_handle(prev_act_id);

    return;
}

static void stopwatch_state_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *obj = \
        lv_event_get_target(e);

    stopwatch_attribute_state_t stopwatch_state = \
        p_ui_info_cache->common_stopwatch_para.stopwatch_state;

    if(stopwatch_state == stopwatch_state_start)
    {
        common_user_stopwatch_pause();

        common_widget_img_replace_src(obj, \
            comm_icon_28_index, stopwatch_state_dsc_idx);
    }else if(stopwatch_state == stopwatch_state_pause)
    {
        common_user_stopwatch_resume();

        common_widget_img_replace_src(obj, \
            comm_icon_27_index, stopwatch_state_dsc_idx);
    }

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_null, \
            ui_act_id_stopwatch_state);

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    return;
}

static void menu_refresh_cb(lv_obj_t *obj)
{
    if(!obj) return;

    stopwatch_attribute_data_t *stopwatch_over_data = \
        &p_ui_info_cache->common_stopwatch_para.stopwatch_over_data;
    if(stopwatch_over_data->stopwatch_minute >= 60)
    {
        ui_menu_jump_handle(\
            ui_act_id_stopwatch_over);

        return;
    }

    uint32_t file_img_dat;
    stopwatch_attribute_data_t *stopwatch_data = \
        &p_ui_info_cache->common_stopwatch_para.stopwatch_data;
    char stopwatch_data_str[10];
    memset(stopwatch_data_str, 0, \
        sizeof(stopwatch_data_str));
    sprintf(stopwatch_data_str, "%02d:%02d.%02d", \
        stopwatch_data->stopwatch_minute, \
            stopwatch_data->stopwatch_second, \
                stopwatch_data->stopwatch_m_second);
    for(uint8_t i = 0; i < 8; i++)
    {
        if(stopwatch_data_str[i] == ':')
            file_img_dat = \
                comm_num_36x56_wh_10_index;
        else if(stopwatch_data_str[i] == '.')
            file_img_dat = \
                comm_num_36x56_wh_14_index;
        else
            file_img_dat = \
                comm_num_36x56_wh_00_index + \
                    (stopwatch_data_str[i] - '0');

        common_widget_img_replace_src(stopwatch_num_obj[i], \
            file_img_dat, stopwatch_num_dsc_idx[i]);
    }

    return;
}

static void menu_display_cb(lv_obj_t *obj)
{
    if(!obj) return;

    stopwatch_attribute_data_t *stopwatch_data = \
        &p_ui_info_cache->common_stopwatch_para.stopwatch_data;
    char stopwatch_data_str[10];
    memset(stopwatch_data_str, 0, \
        sizeof(stopwatch_data_str));
    sprintf(stopwatch_data_str, "%02d:%02d.%02d", \
        stopwatch_data->stopwatch_minute, \
            stopwatch_data->stopwatch_second, \
                stopwatch_data->stopwatch_m_second);
    num_str_para.parent = \ 
        obj;
    num_str_para.num_obj_x = \
        58;
    num_str_para.num_obj_y = \
        184;
    num_str_para.p_num_str = \
        stopwatch_data_str;
    num_str_para.num_str_len = \
        8;
    num_str_para.num_obj = \
        stopwatch_num_obj;
    num_str_para.num_obj_max = \
        8;
    num_str_para.num_dsc_idx = \
        stopwatch_num_dsc_idx;
    num_str_para.file_00_index = \
        comm_num_36x56_wh_00_index;
    common_widget_num_str_create(&num_str_para);

    widget_img_para.img_parent = \
        obj;
    widget_img_para.file_img_dat = \
        comm_icon_11_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = \
        NULL;
    lv_obj_t *comm_11_icon = \
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(comm_11_icon, LV_ALIGN_TOP_MID, \
        0, 266);

    widget_img_para.img_parent = \
        obj;
    widget_img_para.img_x = \
        60;
    widget_img_para.img_y = \
        376;
    widget_img_para.file_img_dat = \
        comm_icon_29_index;
    widget_img_para.img_click_attr = \
        true;
    widget_img_para.event_cb = \
        stopwatch_reset_cb;
    widget_img_para.user_data = \
        NULL;
    lv_obj_t *stopwatch_reset_icon = \
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_set_ext_click_area(stopwatch_reset_icon, 20);

    stopwatch_attribute_state_t stopwatch_state = \
        p_ui_info_cache->common_stopwatch_para.stopwatch_state;
    widget_img_para.img_x = \
        214;
    if(stopwatch_state == stopwatch_state_start)
        widget_img_para.file_img_dat = \
            comm_icon_27_index;
    else if(stopwatch_state == stopwatch_state_pause)
        widget_img_para.file_img_dat = \
            comm_icon_28_index;   
    widget_img_para.event_cb = \
        stopwatch_state_cb; 
    stopwatch_state_icon = \
        common_widget_img_create(&widget_img_para, \
            &stopwatch_state_dsc_idx);
    lv_obj_set_ext_click_area(stopwatch_state_icon, 20);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_stopwatch_state) = 
{
    .menu_arg = NULL,
    .lock_flag = true,
    .return_flag = false,
    .menu_id = \
        ui_act_id_stopwatch_state,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 10,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
