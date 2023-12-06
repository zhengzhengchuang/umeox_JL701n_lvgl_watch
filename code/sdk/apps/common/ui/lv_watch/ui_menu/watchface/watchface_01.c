#include "watchface_01.h"

static struct sys_time utc_time = {0};
#if 0
static const common_clock_pointer_para_t clk_p_para[] = 
{
    [0] = 
    {
        .clk_p_width = 15,
        .clk_p_height = 160,
        .clk_p_center = 156,
        .clk_p_type = clk_pointer_type_hour,
        .clk_p_file_dat = watchface_00_hour_index,
    },

    [1] = 
    {
        .clk_p_width = 15,
        .clk_p_height = 160,
        .clk_p_center = 156,
        .clk_p_type = clk_pointer_type_minute,
        .clk_p_file_dat = watchface_00_min_index,
    },

    [2] = 
    {
        .clk_p_width = 15,
        .clk_p_height = 160,
        .clk_p_center = 156,
        .clk_p_type = clk_pointer_type_second,
        .clk_p_file_dat = watchface_00_sec_index,
    },
};
#endif

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    return;
}

static void menu_refresh_cb(lv_obj_t *obj)
{
    return;
}

static void menu_display_cb(lv_obj_t *obj)
{
    if(!obj) return;

    ui_get_sys_time(&utc_time);

#if 0
    widget_img_para.img_parent = obj;
    widget_img_para.img_x = 0;
    widget_img_para.img_y = 0;
    widget_img_para.file_img_dat = watchface_00_bg_index;
    widget_img_para.img_click_attr = false;
    widget_img_para.event_cb = NULL;
    common_widget_img_create(&widget_img_para, NULL);
#endif

#if 0
    widget_img_para.img_x = 100;
    widget_img_para.img_y = 100;
    widget_img_para.file_img_dat = watchface_00_sports_index; 
    common_widget_img_create(&widget_img_para, NULL); 

    widget_img_para.img_x = 200;
    widget_img_para.img_y = 100;
    widget_img_para.file_img_dat = watchface_00_sports_index; 
    common_widget_img_create(&widget_img_para, NULL); 

    widget_img_para.img_x = 100;
    widget_img_para.img_y = 200;
    widget_img_para.file_img_dat = watchface_00_sports_index; 
    common_widget_img_create(&widget_img_para, NULL); 

    widget_img_para.img_x = 200;
    widget_img_para.img_y = 200;
    widget_img_para.file_img_dat = watchface_00_sports_index; 
    common_widget_img_create(&widget_img_para, NULL);

    widget_img_para.img_x = 100;
    widget_img_para.img_y = 300;
    widget_img_para.file_img_dat = watchface_00_sports_index; 
    common_widget_img_create(&widget_img_para, NULL); 

    widget_img_para.img_x = 200;
    widget_img_para.img_y = 300;
    widget_img_para.file_img_dat = watchface_00_sports_index; 
    common_widget_img_create(&widget_img_para, NULL);

    widget_img_para.img_x = 100;
    widget_img_para.img_y = 400;
    widget_img_para.file_img_dat = watchface_00_sports_index; 
    common_widget_img_create(&widget_img_para, NULL); 

    widget_img_para.img_x = 200;
    widget_img_para.img_y = 400;
    widget_img_para.file_img_dat = watchface_00_sports_index; 
    common_widget_img_create(&widget_img_para, NULL);
#endif

#if 0
    // widget_label_para.label_parent = obj;
    // widget_label_para.label_x = 10;
    // widget_label_para.label_y = 60;
    // widget_label_para.label_w = 348;
    // widget_label_para.label_h = 37*8;
    // widget_label_para.long_mode = LV_LABEL_LONG_WRAP;
    // widget_label_para.text_align = LV_TEXT_ALIGN_LEFT;
    // widget_label_para.label_text = "hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world hello world";
    // widget_label_para.label_text_color = lv_color_hex(0xffffff);
    // widget_label_para.user_text_font = NULL;//&lv_font_montserrat_32;
    // lv_obj_t *label_1 = common_widget_label_create(&widget_label_para);
    // lv_obj_set_style_bg_opa(label_1, LV_OPA_100, LV_PART_MAIN);
    // lv_obj_set_style_bg_color(label_1, lv_color_hex(0x999999), LV_PART_MAIN);

    // widget_label_para.label_x = 10;
    // widget_label_para.label_y = 240;
    // widget_label_para.label_text_color = lv_color_hex(0xffffff);
    // lv_obj_t *label_2 = common_widget_label_create(&widget_label_para);
    // lv_obj_set_style_bg_opa(label_2, LV_OPA_100, LV_PART_MAIN);
    // lv_obj_set_style_bg_color(label_2, lv_color_hex(0x363636), LV_PART_MAIN);

    // widget_label_para.label_x = 10;
    // widget_label_para.label_y = 300;
    // widget_label_para.label_text_color = lv_color_hex(0xffffff);
    // common_widget_label_create(&widget_label_para);

    // widget_label_para.label_x = 10;
    // widget_label_para.label_y = 410;
    // widget_label_para.label_text_color = lv_color_hex(0xff0000);
    // common_widget_label_create(&widget_label_para);

    // widget_label_para.label_x = 100;
    // widget_label_para.label_y = 400;
    // widget_label_para.label_text_color = lv_color_hex(0x0000ff);
    // common_widget_label_create(&widget_label_para);
#endif

#if 0
    widget_img_para.img_x = 100;
    widget_img_para.img_y = 100;
    widget_img_para.file_img_dat = watchface_00_sunny_index;
    common_widget_img_create(&widget_img_para, NULL);
#endif

#if 0
    uint8_t clk_p_num = sizeof(clk_p_para)/sizeof(common_clock_pointer_para_t);
    common_clock_pointer_create(obj, &clk_p_para, clk_p_num);
#endif

#if 0
    widget_arc_para.arc_parent = obj;
    widget_arc_para.arc_x = 0;
    widget_arc_para.arc_y = 0;
    widget_arc_para.arc_bg_width = 368;
    widget_arc_para.arc_bg_height = 368;
    widget_arc_para.arc_bg_opax = LV_OPA_0;
    widget_arc_para.arc_main_start_angle = 0;
    widget_arc_para.arc_main_end_angle = 360;
    widget_arc_para.arc_indic_start_angle = 0;
    widget_arc_para.arc_indic_end_angle = 360;
    widget_arc_para.arc_rotation_angle = 270;
    widget_arc_para.arc_min_value = 0;
    widget_arc_para.arc_max_value = 100;
    widget_arc_para.arc_cur_value = 100;
    widget_arc_para.arc_main_line_width = 35;
    widget_arc_para.arc_indic_line_width = 35;
    widget_arc_para.arc_main_line_color = lv_color_hex(0x320411);
    widget_arc_para.arc_indic_line_color = lv_color_hex(0xff0000);//lv_color_hex(0xf61e5f);
    widget_arc_para.arc_main_is_rounded = true;
    widget_arc_para.arc_indic_is_rounded = true;
    widget_arc_para.arc_click_is_clear = true;
    lv_obj_t *steps_target_arc = common_widget_arc_create(&widget_arc_para);
    lv_obj_center(steps_target_arc);
#endif


    return;
}

const ui_menu_load_info_t menu_load_watchface_01 = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = Act_Id_Watchface,
    .user_display_time = 0,
    .user_refresh_time_inv = 0,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
