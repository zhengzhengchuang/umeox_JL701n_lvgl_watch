#include "watchface_00.h"

static struct sys_time utc_time = {0};
static const common_clock_pointer_para_t clk_p_para[] = 
{
    [0] = 
    {
        .clk_p_width = 10,
        .clk_p_height = 84,
        .clk_p_center = 80,
        .clk_p_type = Clk_Pointer_Type_Hour,
        .clk_p_file_dat = FILE_watchface_00_hour_dat,
    },

    [1] = 
    {
        .clk_p_width = 10,
        .clk_p_height = 120,
        .clk_p_center = 116,
        .clk_p_type = Clk_Pointer_Type_Minute,
        .clk_p_file_dat = FILE_watchface_00_minute_dat,
    },

    [2] = 
    {
        .clk_p_width = 5,
        .clk_p_height = 132,
        .clk_p_center = 128,
        .clk_p_type = Clk_Pointer_Type_Second,
        .clk_p_file_dat = FILE_watchface_00_second_dat,
    },
};

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    wf_register_tileview_menu(obj);

    wf_register_translate_menu();

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

    widget_img_para.img_parent = obj;
    widget_img_para.img_x = 0;
    widget_img_para.img_y = 0;
    widget_img_para.file_img_dat = FILE_watchface_00_bg_dat;
    widget_img_para.img_click_attr = false;
    widget_img_para.event_cb = NULL;
    common_widget_img_create(&widget_img_para, NULL);

    uint8_t clk_p_num = sizeof(clk_p_para)/sizeof(common_clock_pointer_para_t);
    common_clock_pointer_create(obj, &clk_p_para, clk_p_num);
 
    return;
}

const ui_menu_load_info_t menu_load_watchface_00 = 
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
