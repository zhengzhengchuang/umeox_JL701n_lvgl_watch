#include "watchface_00.h"

static const common_clock_pointer_para_t \
    clk_p_para[] = 
{
    [0] = 
    {
        .clk_p_width = 16,
        .clk_p_height = 103,
        .clk_p_center = 103,
        .clk_p_type = \
            clk_pointer_type_hour,
        .clk_p_file_dat = \
            watchface_00_clock_hour_index,
    },

    [1] = 
    {
        .clk_p_width = 16,
        .clk_p_height = 172,
        .clk_p_center = 172,
        .clk_p_type = \
            clk_pointer_type_minute,
        .clk_p_file_dat = \
            watchface_00_clock_minute_index,
    },

    [2] = 
    {
        .clk_p_width = 16,
        .clk_p_height = 208,
        .clk_p_center = 158,
        .clk_p_type = \
            clk_pointer_type_second,
        .clk_p_file_dat = \
            watchface_00_clock_second_index,
    },
};

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_weather, \
            ui_act_id_watchface);

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

    widget_img_para.img_parent = obj;
    widget_img_para.img_x = 0;
    widget_img_para.img_y = 0;
    widget_img_para.file_img_dat = watchface_00_bg_index;
    widget_img_para.img_click_attr = false;
    widget_img_para.event_cb = NULL;
    common_widget_img_create(&widget_img_para, NULL);

#if 0
    widget_label_para.label_parent = obj;
    widget_label_para.label_x = 100;
    widget_label_para.label_y = 300;
    widget_label_para.label_w = 150;
    widget_label_para.label_h = \
        Label_Line_Height*2;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_WRAP;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_LEFT;
    widget_label_para.label_text = \
        "你好呀，优美创新";
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.user_text_font = NULL;
    lv_obj_t *test_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_set_style_bg_opa(test_label, LV_OPA_100, \
        LV_PART_MAIN);
    lv_obj_set_style_bg_color(test_label, lv_color_hex(0xff0000), \
        LV_PART_MAIN);
#endif

    uint8_t clk_p_num = sizeof(clk_p_para)/sizeof(common_clock_pointer_para_t);
    common_clock_pointer_create(obj, &clk_p_para, clk_p_num);

    widget_img_para.img_parent = obj;
    widget_img_para.file_img_dat = watchface_00_clock_dot_index;
    widget_img_para.img_click_attr = false;
    widget_img_para.event_cb = NULL;
    lv_obj_t *clock_dot = \
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_center(clock_dot);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_watchface_00) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_watchface,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 500,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
