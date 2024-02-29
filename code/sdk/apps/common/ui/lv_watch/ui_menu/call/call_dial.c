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
                                  拨号盘数字字符串                                 
*********************************************************************************/
#define Call_Dial_Num_Max (15)
static uint8_t call_dial_num_len = 0;
static lv_obj_t *call_dial_num_label = NULL;
char call_dial_num_str[Call_Dial_Num_Max + 1] = {0};

/*********************************************************************************
                                  拨号盘数字点击处理                                 
*********************************************************************************/
static void call_dial_num_click_handle(uint8_t num)
{
    if(call_dial_num_len >= \
        Call_Dial_Num_Max)
        return;

    if(!call_dial_num_label)
        return;

    call_dial_num_str[\
        call_dial_num_len] = num + '0';

    lv_label_set_text(call_dial_num_label, \
        call_dial_num_str);
  
    call_dial_num_len += 1;

    return;
}

/*********************************************************************************
                                  拨号盘回退点击处理                                 
*********************************************************************************/
static void call_dial_back_click_handle(void)
{
    if(!call_dial_num_len)
        return;

    if(!call_dial_num_label)
        return;

    call_dial_num_str[\
        call_dial_num_len - 1] = '\0';

    lv_label_set_text(call_dial_num_label, \
        call_dial_num_str);
  
    call_dial_num_len -= 1;

    return;
}

/*********************************************************************************
                                  拨号盘拨打点击处理                                 
*********************************************************************************/
static void call_dial_dial_click_handle(void)
{
    if(!call_dial_num_len)
        return;

    ui_ctrl_call_out_by_number(\
        call_dial_num_str, \
            call_dial_num_len);
    
    return;
}

/*********************************************************************************
                                  拨号盘点击回调                                 
*********************************************************************************/
static void call_dial_click_cb(lv_event_t *e)
{
    if(!e) return;

    uint8_t idx = \
        *(uint8_t *)lv_event_get_user_data(e);

    if(idx >= 0 && idx <= 9)
        call_dial_num_click_handle(idx);
    else if(idx == 10)
        call_dial_back_click_handle();
    else if(idx == 11)
        call_dial_dial_click_handle();

    return;
}

/*********************************************************************************
                                  拨号盘回退按键长按回调                                 
*********************************************************************************/
static lv_timer_t *long_press_back_timer = NULL;

static void long_press_back_timer_cb(lv_timer_t *timer)
{
    if(!long_press_back_timer)
        return;

    if(!call_dial_num_len)
    {
        lv_timer_del(long_press_back_timer);
        long_press_back_timer = NULL;
        return;
    }

    call_dial_back_click_handle();

    return;
}

static void call_dial_back_long_press_cb(lv_event_t *e)
{
    if(!e) return;

    if(long_press_back_timer)
    {
        lv_timer_del(long_press_back_timer);
        long_press_back_timer = NULL;
    }

    long_press_back_timer = \
        lv_timer_create(long_press_back_timer_cb, \
            150, NULL);

    return;
}

static void call_dial_back_release_cb(lv_event_t *e)
{
    if(!e) return;

    if(long_press_back_timer)
    {
        lv_timer_del(long_press_back_timer);
        long_press_back_timer = NULL;
    }

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    ui_act_id_t prev_act_id = \
        read_menu_return_level_id();

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, prev_act_id, ui_act_id_null, \
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

        if(i == 10)
        {
            lv_obj_add_event_cb(button_container, \
                call_dial_back_long_press_cb, LV_EVENT_LONG_PRESSED, \
                    NULL);

            lv_obj_add_event_cb(button_container, \
                call_dial_back_release_cb, LV_EVENT_RELEASED, \
                    NULL);      
        }
            
    }
  
    call_dial_num_len = 0;
    call_dial_num_label = NULL;
    memset(call_dial_num_str, 0, \
        sizeof(call_dial_num_str));

    widget_label_para.label_w = \
        (300);
    widget_label_para.label_h = \
        49;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_CLIP;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_ver_center = \
        false;
    widget_label_para.user_text_font = \
        &font_common_num_36;
    widget_label_para.label_parent = \
        obj;
    widget_label_para.label_text = \
        call_dial_num_str;
    call_dial_num_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align(call_dial_num_label, LV_ALIGN_TOP_MID, \
        0, 44);

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
