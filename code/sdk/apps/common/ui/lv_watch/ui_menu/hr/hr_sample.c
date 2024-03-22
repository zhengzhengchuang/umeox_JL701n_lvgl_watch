#include "hr_sample.h"

static uint8_t hr_GIF_cnt;
static lv_obj_t *hr_GIF_icon;
static uint16_t hr_GIF_dsc_idx;
static lv_obj_t *hr_sample_container;

#define CHART_PRIX_MAJOR_CNT 5
static const char *chart_prix_label_str[\
    CHART_PRIX_MAJOR_CNT] = {
    "00:00", "06:00", "12:00", "18:00", "00:00",
};

#define CHART_PRIY_MAJOR_CNT 5

#define CHART_ITEM_CNT 24
#define CHART_SERIES_NUM 1
static int16_t hr_sample_chart_points[\
    CHART_SERIES_NUM][CHART_ITEM_CNT] = {
    LV_CHART_POINT_NONE
};

static lv_color_t hr_sample_chart_color[\
    CHART_SERIES_NUM];
static lv_chart_series_t *hr_sample_chart_series[\
    CHART_SERIES_NUM];

static void hr_sample_container_create(\
    lv_obj_t *obj)
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
        true;
    hr_sample_container = \
        common_widget_obj_create(&widget_obj_para);
    lv_obj_set_style_pad_bottom(hr_sample_container, \
        84, LV_PART_MAIN);

    return;
}

static uint8_t hr_sample_data[2][CHART_ITEM_CNT] = {
    [0] = {
        54, 56, 58, 62, 66, 64, 62, 65, 68, 66, \
        67, 54, 58, 62, 66, 64, 62, 65, 68, 66, \
        67, 54, 58, 62,
    },

    [1] = {
        90, 84, 74, 80, 86, 90, 85, 90, 80, 87, \
        87, 94, 74, 85, 86, 90, 85, 90, 80, 87, \
        87, 94, 74, 85,
    },
};

static void hr_sample_minmax_chart_create(void)
{
    const uint8_t hr_chart_min = \
        0;
    const uint8_t hr_chart_max = \
        140;
    const uint8_t hr_pixel_per = \
        2;

    hr_sample_chart_color[0] = \
        lv_color_hex(0x000000);

    widget_chart_para.chart_parent = \
        hr_sample_container;
    widget_chart_para.chart_width = \
        300;
    widget_chart_para.chart_height = \
        (hr_chart_max - hr_chart_min)*hr_pixel_per;
    widget_chart_para.chart_type = \
        LV_CHART_TYPE_NONE;
    widget_chart_para.chart_item_cnt = \
        CHART_ITEM_CNT;
    widget_chart_para.chart_update_mode = \
        LV_CHART_UPDATE_MODE_CIRCULAR;
    widget_chart_para.chart_hor_div = \
        CHART_PRIY_MAJOR_CNT;
    widget_chart_para.chart_ver_div = \
        0;
    widget_chart_para.chart_priy_range_min = \
        hr_chart_min;
    widget_chart_para.chart_priy_range_max = \
        hr_chart_max;
    widget_chart_para.chart_prix_major_cnt = \
        CHART_PRIX_MAJOR_CNT;
    widget_chart_para.chart_priy_major_cnt = \
        CHART_PRIY_MAJOR_CNT;
    widget_chart_para.chart_prix_label_str = \
        chart_prix_label_str;
    widget_chart_para.chart_priy_label_str = \
        NULL;
    widget_chart_para.chart_series_num = \
        CHART_SERIES_NUM;
    widget_chart_para.chart_ext_y_array = \
        hr_sample_chart_points[0];
    widget_chart_para.chart_series_color = \
        hr_sample_chart_color;
    widget_chart_para.chart_series = \
        hr_sample_chart_series;
    widget_chart_para.chart_main_opax = \
        LV_OPA_0;
    widget_chart_para.chart_main_color = \
        lv_color_hex(0x000000);
    lv_obj_t *hr_sample_chart = \
        common_widget_chart_create(&widget_chart_para);
    lv_obj_align(hr_sample_chart, LV_ALIGN_TOP_MID, \
        0, LCD_HEIGHT + 84);
    lv_obj_clear_flag(hr_sample_chart, LV_OBJ_FLAG_SCROLLABLE);


    const uint8_t hr_sample_bar_w = \
        8;
    const uint8_t hr_sample_bar_inv = \
        4;
    
    widget_obj_para.obj_parent = \
        hr_sample_chart;
    widget_obj_para.obj_width = \
        hr_sample_bar_w;
    widget_obj_para.obj_bg_opax = \
        LV_OPA_100;
    widget_obj_para.obj_bg_color = \
        lv_color_hex(0xfe375e);
    widget_obj_para.obj_border_opax = \
        LV_OPA_0;
    widget_obj_para.obj_border_width = \
        0;
    widget_obj_para.obj_border_color = \
        lv_color_hex(0x000000);
    widget_obj_para.obj_radius = \
        hr_sample_bar_w/2;
    widget_obj_para.obj_is_scrollable = \
        false;
    
    uint8_t hr_sample_min;
    uint8_t hr_sample_max;
    uint16_t hr_sample_bar_h;
    for(uint8_t i = 0; i < CHART_ITEM_CNT; i++)
    {
        hr_sample_min = \
            hr_sample_data[0][i];
        hr_sample_max = \
            hr_sample_data[1][i];

        if(hr_sample_max < \
            hr_sample_min)
            continue;

        if(hr_sample_min == 0 && \
            hr_sample_max == 0)
            continue;

        if(hr_sample_max > hr_chart_max)
            hr_sample_max = hr_chart_max;
        if(hr_sample_min < hr_chart_min)
            hr_sample_min = hr_chart_min;
        
        hr_sample_bar_h = \
            (hr_sample_max - hr_sample_min)*hr_pixel_per;
        if(hr_sample_bar_h < hr_pixel_per)
            hr_sample_bar_h = hr_pixel_per*4;
        widget_obj_para.obj_height = \
            hr_sample_bar_h;

        lv_obj_t *hr_sample_bar = \
            common_widget_obj_create(&widget_obj_para);
        lv_obj_align(hr_sample_bar, LV_ALIGN_TOP_LEFT, \
            (hr_sample_bar_w + hr_sample_bar_inv)*i, \
                (hr_chart_max - hr_sample_max)*hr_pixel_per - 2);
    }
    
    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    hr_GIF_cnt = 0;
    set_vm_para_cache_with_label(\
        vm_label_hr, 0);

    ui_act_id_t prev_act_id = \
        read_menu_return_level_id();

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, prev_act_id, ui_act_id_bo_sample, \
            ui_act_id_hr_sample);

    AppCtrlvcHr02StartSample(\
        VCWORK_MODE_HRWORK);

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    AppCtrlvcHr02StopSample();

    return;
}

static void menu_refresh_cb(lv_obj_t *obj)
{
    if(!obj) return;

    hr_GIF_cnt++;
    hr_GIF_cnt %= 1;
    common_widget_img_replace_src(\
        hr_GIF_icon, hr_GIF_00_index + hr_GIF_cnt, \
            hr_GIF_dsc_idx);

    bool wear_status = \
        AppGetvcHr02WearStatus();
    int hr_sample_val = \
        get_vm_para_cache_with_label(\
            vm_label_hr);
    if(hr_sample_val == 0 && \
        wear_status)
        common_offscreen_timer_restart();

    return;
}

static void menu_display_cb(lv_obj_t *obj)
{
    if(!obj) return;

    hr_sample_container_create(obj);

    widget_img_para.img_parent = \
        hr_sample_container;
    widget_img_para.file_img_dat = \
        hr_00_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = \
        NULL;
    lv_obj_t *hr_sample_icon = \
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(hr_sample_icon, LV_ALIGN_TOP_LEFT, \
        24, 72);

    int hr_sample_val = \
        get_vm_para_cache_with_label(\
            vm_label_hr);

    widget_data_para.data_x = \
        136;
    widget_data_para.data_y = \
        96;
    widget_data_para.num_inv = \
        0;
    widget_data_para.data_parent = \
        hr_sample_container;
    widget_data_para.num_addr_index = \
        comm_num_30x40_wh_00_index;
    widget_data_para.data_align = \
        widget_data_align_center;
    widget_data_para.user0_para_valid = \
        true;
    widget_data_para.user0_num_addr_index = \
        comm_num_30x40_re_00_index;
    common_data_widget_create(&widget_data_para, \
        widget_data_type_hr, &hr_sample_val);

    widget_img_para.img_parent = \
        hr_sample_container;
    widget_img_para.img_x = \
        234;
    widget_img_para.img_y = \
        117;
    widget_img_para.file_img_dat = \
        hr_01_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = \
        NULL;
    common_widget_img_create(&widget_img_para, NULL);

    widget_img_para.file_img_dat = \
        hr_GIF_00_index;
    hr_GIF_icon = \
        common_widget_img_create(&widget_img_para, &hr_GIF_dsc_idx);
    lv_obj_align(hr_GIF_icon, LV_ALIGN_TOP_MID, \
        0, 224);

    widget_img_para.file_img_dat = \
        hr_02_index;
    lv_obj_t *hr_02_icon = \
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(hr_02_icon, LV_ALIGN_TOP_MID, \
        0, 392);

    hr_sample_minmax_chart_create();

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_hr_sample) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_hr_sample,
    .user_offscreen_time = \
        0,
    .user_refresh_time_inv = \
        200,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
