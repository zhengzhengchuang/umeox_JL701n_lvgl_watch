#include "weather_report.h"

static lv_obj_t *weather_report_container = \
    NULL;

static void weather_report_container_create(lv_obj_t *obj)
{
    widget_obj_para.obj_parent = obj;
    widget_obj_para.obj_x = 0;
    widget_obj_para.obj_y = 0;
    widget_obj_para.obj_width = \
        LCD_WIDTH;
    widget_obj_para.obj_height = \
        LCD_HEIGHT;
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
    weather_report_container = \
        common_widget_obj_create(&widget_obj_para);
    lv_obj_set_style_pad_bottom(weather_report_container, \
        25, LV_PART_MAIN);

    return;
}

/*********************************************************************************
                                  第一天天气预报                       
*********************************************************************************/
static void weather_report_1_elem_create(void)
{
    weather_type_t weather_0_type = \
        vm_weather_data_weather_type(0);
        
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
        true;
    widget_label_para.user_text_font = NULL;
    widget_label_para.label_parent = \
        weather_report_container;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_sunny + \
            weather_0_type);
    lv_obj_t *weather_type_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align(weather_type_label, LV_ALIGN_TOP_MID, \
        0, 40);

    widget_img_para.img_parent = \
        weather_report_container;
    widget_img_para.file_img_dat = \
        weather_148x140_00_index + \
            weather_0_type;
    widget_img_para.img_click_attr = false;
    widget_img_para.event_cb = NULL;
    lv_obj_t *weather_type_icon = \
        common_widget_img_create(&widget_img_para, \
            NULL);
    lv_obj_align(weather_type_icon, LV_ALIGN_TOP_MID, \
        0, 136);

    int16_t weather_other_00_x = \
        150;
    int16_t weather_other_01_x = \
        247;

    widget_img_para.img_x = \
        weather_other_00_x;
    widget_img_para.img_y = 292;
    widget_img_para.file_img_dat = \
        weather_other_00_index;
    common_widget_img_create(&widget_img_para, \
        NULL);

    widget_img_para.img_x = \
        weather_other_01_x;
    widget_img_para.file_img_dat = \
        weather_other_01_index;
    common_widget_img_create(&widget_img_para, \
        NULL);

    int16_t weather_min0_temper = \
        vm_weather_data_min_temper(0);
    widget_data_para.data_x = \
        weather_other_00_x - (67);
    widget_data_para.data_y = 295;
    widget_data_para.num_inv = 0;
    widget_data_para.data_parent = \
        weather_report_container;
    widget_data_para.num_addr_index = \
        comm_num_14x22_wh_00_index;
    widget_data_para.data_align = \
        widget_data_align_right;
    common_data_widget_create(&widget_data_para, \
        widget_data_type_min0_weather, \
            &weather_min0_temper);

    int16_t weather_max0_temper = \
        vm_weather_data_max_temper(0);
    widget_data_para.data_x = \
        weather_other_01_x - (67);
    common_data_widget_create(&widget_data_para, \
        widget_data_type_max0_weather, \
            &weather_max0_temper);

    return;
}

/*********************************************************************************
                                  第二~七天天气预报                       
*********************************************************************************/
static void weather_report_2_7_elem_create(menu_align_t menu_align)
{  
    int16_t elem_container_w = \
        LCD_WIDTH;
    int16_t elem_container_h = 97;
    int16_t elem_container_sy = 354;
    weather_type_t weather_x_type;

    struct sys_time utc_time;
    ui_get_sys_time(&utc_time);
    comm_enum_week_t enum_week = \
        ui_get_sys_week(&utc_time);

    /*********obj容器***********/
    widget_obj_para.obj_x = 0;
    widget_obj_para.obj_parent = \
        weather_report_container;
    widget_obj_para.obj_width = \
        elem_container_w;
    widget_obj_para.obj_height = \
        elem_container_h;
    widget_obj_para.obj_bg_opax = \
        LV_OPA_0;
    widget_obj_para.obj_bg_color = \
        lv_color_hex(0x000000);
    widget_obj_para.obj_border_width = \
        0;
    widget_obj_para.obj_is_scrollable = \
        false;
    widget_obj_para.obj_radius = 0;

    /*********img图片***********/
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = NULL;

    /*********label标签***********/
    widget_label_para.label_w = \
        (220);
    widget_label_para.label_h = \
        Label_Line_Height;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_SCROLL;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_ver_center = \
        false;
    widget_label_para.user_text_font = NULL;

    int16_t data_sx = 0;
    for(uint8_t i = 1; i < 7; i++)
    {   
        widget_obj_para.obj_y = \
            elem_container_sy + elem_container_h*(i-1);
        lv_obj_t *elem_container = \
            common_widget_obj_create(&widget_obj_para);

        weather_x_type = \
            vm_weather_data_weather_type(i);
        widget_img_para.img_parent = \
            elem_container;
        widget_img_para.file_img_dat = \
            weather_72x68_00_index + weather_x_type;
        lv_obj_t *weather_type_icon = \
            common_widget_img_create(&widget_img_para, NULL);
        if(menu_align == menu_align_right)
            lv_obj_align(weather_type_icon, LV_ALIGN_RIGHT_MID, \
                -24, 0);
        else 
            lv_obj_align(weather_type_icon, LV_ALIGN_LEFT_MID, \
                24, 0);

        enum_week += 1;
        enum_week %= Comm_Enum_Week_Max;
        widget_label_para.label_parent = \
            elem_container;
        widget_label_para.label_text = \
            get_lang_txt_with_id(lang_txtid_sunday + \
                enum_week);
        if(menu_align == menu_align_right)
            widget_label_para.text_align = \
                LV_TEXT_ALIGN_RIGHT;
        else
            widget_label_para.text_align = \
                LV_TEXT_ALIGN_LEFT;
        lv_obj_t *enum_week_label = \
            common_widget_label_create(&widget_label_para);
        if(menu_align == menu_align_right)
            lv_obj_align_to(enum_week_label, weather_type_icon, \
                LV_ALIGN_OUT_LEFT_TOP, -20, -10);
        else
            lv_obj_align_to(enum_week_label, weather_type_icon, \
                LV_ALIGN_OUT_RIGHT_TOP, 20, -10);

        int16_t weather_min_tempera = \
                vm_weather_data_min_temper(i);
        int16_t weather_max_tempera = \
                vm_weather_data_max_temper(i); 
        widget_data_para.data_y = 56;
        widget_data_para.num_inv = 0;
        widget_data_para.data_parent = \
            elem_container;
        widget_data_para.num_addr_index = \
            comm_num_14x22_wh_00_index;
        widget_data_para.data_align = \
                widget_data_align_left;
        if(menu_align == menu_align_right)
        {
            data_sx = 252;

            char tempera_str[10];
            memset(tempera_str, 0, \
                sizeof(tempera_str));
            sprintf(tempera_str, "%dC", \
                weather_min_tempera);
            uint8_t bit_num = \
                strlen(tempera_str);
            uint16_t num_width = 0;
            for(uint8_t i = 0; i < bit_num; i++)
            {
                if(tempera_str[i] == '-')
                    num_width += 7;
                else if(tempera_str[i] == 'C')
                    num_width += 14;
                else if(tempera_str[i] >= '0' && \
                    tempera_str[i] <= '9')
                    num_width += 14;
            }
            data_sx -= (num_width + 10 + 4);
            widget_data_para.data_x = \
                data_sx;
            int16_t data_end_x = \
                common_data_widget_create(&widget_data_para, \
                    widget_data_type_min0_weather + (i*2), \
                        &weather_min_tempera); 

            widget_img_para.img_x = \
                data_end_x + 4;
            widget_img_para.img_y = 53;
            widget_img_para.file_img_dat = \
                weather_other_00_index;
            common_widget_img_create(&widget_img_para, NULL);


            memset(tempera_str, 0, \
                sizeof(tempera_str));
            sprintf(tempera_str, "%dC", \
                weather_max_tempera);
            bit_num = \
                strlen(tempera_str);
            num_width = 0;
            for(uint8_t i = 0; i < bit_num; i++)
            {
                if(tempera_str[i] == '-')
                    num_width += 7;
                else if(tempera_str[i] == 'C')
                    num_width += 14;
                else if(tempera_str[i] >= '0' && \
                    tempera_str[i] <= '9')
                    num_width += 14;
            }
            data_sx -= (num_width + 30 + 10 + 4);
            widget_data_para.data_x = \
                data_sx;
            data_end_x = \
                common_data_widget_create(&widget_data_para, \
                    widget_data_type_max0_weather + (i*2), \
                        &weather_max_tempera);

            widget_img_para.img_x = \
                data_end_x + 4;
            widget_img_para.file_img_dat = \
                weather_other_01_index;
            common_widget_img_create(&widget_img_para, NULL);
        }else
        {
            data_sx = 116;
  
            widget_data_para.data_x = \
                data_sx;           
            int16_t data_end_x = \
                common_data_widget_create(&widget_data_para, \
                    widget_data_type_min0_weather + (i*2), \
                        &weather_min_tempera); 

            widget_img_para.img_x = \
                data_end_x + 4;
            widget_img_para.img_y = 53;
            widget_img_para.file_img_dat = \
                weather_other_00_index;
            common_widget_img_create(&widget_img_para, NULL);

            widget_data_para.data_x = \
                data_end_x + 30;
            data_end_x = \
                common_data_widget_create(&widget_data_para, \
                    widget_data_type_max0_weather + (i*2), \
                        &weather_max_tempera);

            widget_img_para.img_x = \
                data_end_x + 4;
            widget_img_para.file_img_dat = \
                weather_other_01_index;
            common_widget_img_create(&widget_img_para, NULL);
        }
    }

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_null, \
            ui_act_id_weather_report);

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

    weather_report_container_create(obj);

    weather_report_1_elem_create();

    menu_align_t menu_align = \
        menu_align_left;
    if(lang_txt_is_arabic())
        menu_align = \
            menu_align_right;
    weather_report_2_7_elem_create(menu_align);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_weather_report) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_weather_report,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
