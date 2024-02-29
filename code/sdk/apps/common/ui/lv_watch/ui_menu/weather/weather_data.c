#include "weather_data.h"

static lv_obj_t *weather_type_icon = NULL;
static lv_obj_t *weather_type_label = NULL;
static uint16_t weather_type_dsc_idx = 0xffff;

/*********************************************************************************
                                  创建无天气数据页面                                 
*********************************************************************************/
static void no_weather_data_menu_create(lv_obj_t *obj)
{
    widget_img_para.img_parent = obj;
    widget_img_para.file_img_dat = \
        weather_no_data_00_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = NULL;
    lv_obj_t *no_data_icon = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_align(no_data_icon, LV_ALIGN_TOP_MID, \
        0, 82);

    widget_img_para.file_img_dat = \
        comm_icon_11_index;
    lv_obj_t *no_data_bg_img = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_align_to(no_data_bg_img, no_data_icon, \
        LV_ALIGN_OUT_BOTTOM_MID, 0, 32);

    
    widget_label_para.label_w = \
        (LCD_WIDTH - 30);
    widget_label_para.label_h = \
        Label_Line_Height*2;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_WRAP;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_parent = \
        obj;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_ver_center = \
        false;    
    widget_label_para.user_text_font = NULL;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_no_data);
    lv_obj_t *no_data_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align_to(no_data_label, no_data_bg_img, \
        LV_ALIGN_OUT_BOTTOM_MID, 0, 30);

    return;
}

/*********************************************************************************
                                  创建有天气数据页面                                 
*********************************************************************************/
static void has_weather_data_menu_create(lv_obj_t *obj)
{
    int16_t data_sym_x = 40;

    int16_t weather_min0_temper = \
        vm_weather_data_min_temper(0);
    widget_data_para.data_x = \
        data_sym_x;
    widget_data_para.data_y = 94;
    widget_data_para.num_inv = 0;
    widget_data_para.data_parent = \
        obj;
    widget_data_para.num_addr_index = \
        comm_num_14x22_wh_00_index;
    widget_data_para.data_align = \
        widget_data_align_left;
    int16_t data_end_x = \
         common_data_widget_create(&widget_data_para, \
            widget_data_type_min0_weather, \
                &weather_min0_temper);

    widget_img_para.img_x = \
        data_end_x + 4;
    widget_img_para.img_y = 92;
    widget_img_para.img_parent = \
        obj;
    widget_img_para.file_img_dat = \
        weather_other_00_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = NULL;
    common_widget_img_create(&widget_img_para, \
        NULL);

    int16_t weather_max0_temper = \
        vm_weather_data_max_temper(0);
    widget_data_para.data_x = data_end_x + 30;
    data_end_x = \
        common_data_widget_create(&widget_data_para, \
            widget_data_type_max0_weather, \
                &weather_max0_temper);

    widget_img_para.img_x = data_end_x + 4;
    widget_img_para.file_img_dat = \
        weather_other_01_index;
    common_widget_img_create(&widget_img_para, \
        NULL);

    int16_t weather_real_temper = \
        vm_weather_data_real_temper();
    char weather_real_temper_str[10];
    memset(weather_real_temper_str, 0, \
        sizeof(weather_real_temper_str));
    sprintf(weather_real_temper_str, "%dC", \
        weather_real_temper);
    int16_t data_sx = LCD_WIDTH - data_sym_x;
    uint8_t bit_num = \
        strlen(weather_real_temper_str);
    for(uint8_t i = 0; i < bit_num; i++)
    {
        if(weather_real_temper_str[i] == '-')
            data_sx -= 15;
        else if(weather_real_temper_str[i] == 'C')
            data_sx -= 30;
        else if(weather_real_temper_str[i] >= '0' && \
            weather_real_temper_str[i] <= '9')
            data_sx -= 30;
    }

    widget_data_para.data_x = data_sx;
    widget_data_para.data_y = 84;
    widget_data_para.num_addr_index = \
        comm_num_30x40_wh_00_index;
    widget_data_para.data_align = \
        widget_data_align_left;
    common_data_widget_create(&widget_data_para, \
        widget_data_type_weather, &weather_real_temper);


    weather_type_t weather_type = \
        vm_weather_data_weather_type(0);
    widget_img_para.img_parent = \
        obj;
    widget_img_para.file_img_dat = \
        weather_148x140_00_index + weather_type;
    widget_img_para.img_click_attr = false;
    widget_img_para.event_cb = NULL;
    weather_type_icon = \
        common_widget_img_create(&widget_img_para, \
            &weather_type_dsc_idx);
    lv_obj_align(weather_type_icon, LV_ALIGN_TOP_MID, \
        0, 165);

    widget_label_para.label_w = \
        (LCD_WIDTH - 30);
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
    widget_label_para.user_text_font = NULL;
    widget_label_para.label_parent = obj;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_sunny + \
            weather_type);
    weather_type_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align(weather_type_label, LV_ALIGN_TOP_MID, \
        0, 332);

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_null, \
            ui_act_id_weather_data);

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    weather_type_icon = \
        NULL;
    weather_type_dsc_idx = \
        0xffff;

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

    bool data_is_valid = \
        vm_whether_data_is_valid();
    if(!data_is_valid)
        no_weather_data_menu_create(obj);
    else
        has_weather_data_menu_create(obj);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_weather_data) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_weather_data,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
