#include "call_dial.h"

/*********************************************************************************
                                  拨号盘坐标                                 
*********************************************************************************/
static const lv_point_t call_dial_coord[12] = 
{
    {24, 352}, \
    {24, 100}, {137, 100}, {250, 100}, \
    {24, 184}, {137, 184}, {250, 184}, \
    {24, 268}, {137, 268}, {250, 268}, \
    {137, 352}, {250, 352},
};

/*********************************************************************************
                                  拨号盘点击下标                               
*********************************************************************************/
static const uint8_t call_dial_click_idx[12] = 
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
};

/*********************************************************************************
                                  拨号盘点击回调                                 
*********************************************************************************/
static void call_dial_click_cb(lv_event_t *e)
{
    if(!e) return;

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_null, \
            ui_act_id_call_dial);

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

    
    uint8_t i = 0;

    for(i = 0; i < 10; i++)
    {
        widget_img_para.img_x = \
            call_dial_coord[i].x;
        widget_img_para.img_y = \
            call_dial_coord[i].y;
        widget_img_para.img_parent = \
            obj;
        widget_img_para.file_img_dat = \
            call_08_index;
        widget_img_para.img_click_attr = \
            true;
        widget_img_para.event_cb = \
            call_dial_click_cb;
        widget_img_para.user_data = \
            (void *)&call_dial_click_idx[i];
        lv_obj_t *button_container = \
            common_widget_img_create(&widget_img_para, \
                NULL);
        lv_obj_set_ext_click_area(button_container, 5);

        widget_img_para.img_parent = \
            button_container;
        widget_img_para.file_img_dat = \
            comm_num_20x32_wh_00_index + i;
        widget_img_para.img_click_attr = \
            false;
        widget_img_para.event_cb = \
            NULL;
        lv_obj_t *button_num = \
            common_widget_img_create(&widget_img_para, \
                NULL);
        lv_obj_center(button_num);
    }

    uint32_t spec_button_file[2] = { 
        call_09_index, call_10_index,
    };

    for(; i < 12; i++)
    {
        widget_img_para.img_x = \
            call_dial_coord[i].x;
        widget_img_para.img_y = \
            call_dial_coord[i].y;
        widget_img_para.img_parent = \
            obj;
        widget_img_para.file_img_dat = \
            spec_button_file[i - 10];
        widget_img_para.img_click_attr = \
            true;
        widget_img_para.event_cb = \
            call_dial_click_cb;
        widget_img_para.user_data = \
            (void *)&call_dial_click_idx[i];
        lv_obj_t *button_container = \
            common_widget_img_create(&widget_img_para, \
                NULL);
        lv_obj_set_ext_click_area(button_container, 5);
    }
        

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_call_dial) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_call_dial,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
