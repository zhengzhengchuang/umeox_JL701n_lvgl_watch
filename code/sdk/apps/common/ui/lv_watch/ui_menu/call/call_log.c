#include "call_log.h"

/*********************************************************************************
                                  通话记录点击下标                                 
*********************************************************************************/
static const uint8_t call_log_click_idx[\
    Call_log_Max_Num] = 
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
};

/*********************************************************************************
                                  通话记录存储结构体                                 
*********************************************************************************/
static vm_call_log_ctx_t vm_call_log_ctx;

/*********************************************************************************
                                  无通话记录页面                                 
*********************************************************************************/
static void no_call_log_menu_create(lv_obj_t *obj)
{
    widget_img_para.img_parent = \
        obj;
    widget_img_para.img_x = 104;
    widget_img_para.img_y = 88;
    widget_img_para.file_img_dat = \
        call_04_index;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = \
        NULL;
    common_widget_img_create(&widget_img_para, NULL);

    widget_img_para.img_x = 32;
    widget_img_para.img_y = 266;
    widget_img_para.file_img_dat = \
        comm_icon_11_index;
    common_widget_img_create(&widget_img_para, NULL);

    widget_label_para.label_w = \
        (300);
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
        obj;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_no_record);
    lv_obj_t *no_record_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_align(no_record_label, LV_ALIGN_TOP_MID, \
        0, 332);

    return;
}

/*********************************************************************************
                                  通话记录列表容器                                 
*********************************************************************************/
static lv_obj_t *call_log_list_container_create(lv_obj_t *obj)
{
    widget_obj_para.obj_parent = \
        obj;
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
    lv_obj_t *call_log_list_container = \
        common_widget_obj_create(&widget_obj_para);

    return call_log_list_container;
}

/*********************************************************************************
                                  通话记录状态图标                                 
*********************************************************************************/
static uint32_t call_log_state_icon(call_log_state_t state)
{
    uint32_t file_img_dat = \
        call_05_index;

    if(state == call_log_state_in)
        file_img_dat = call_07_index;
    else if(state == call_log_state_out)
        file_img_dat = call_06_index;

    return file_img_dat;
}

/*********************************************************************************
                                  通话记录元素点击回调                                 
*********************************************************************************/
static void call_log_elem_click_cb(lv_event_t *e)
{
    if(!e) return;

    uint8_t idx = \
        *(uint8_t *)lv_event_get_user_data(e);

    memset(&vm_call_log_ctx, 0, \
        sizeof(vm_call_log_ctx_t));
    bool ret = vm_call_log_ctx_by_idx(idx, \
        &vm_call_log_ctx);
    if(!ret) return;

    ui_ctrl_call_out_by_number(\
        vm_call_log_ctx.call_log_number_str, \
            strlen(vm_call_log_ctx.call_log_number_str));

    return;
}

/*********************************************************************************
                                  有通话记录页面                                
*********************************************************************************/
static void has_call_log_menu_create(lv_obj_t *obj, \
    uint8_t num, menu_align_t menu_align)
{
    lv_obj_t *call_log_list_container = \
        call_log_list_container_create(obj);

    int16_t elem_container_h = \
        118;
    widget_obj_para.obj_parent = \
        call_log_list_container;
    widget_obj_para.obj_width = \
        LCD_WIDTH;   
    widget_obj_para.obj_height = \
        elem_container_h;
    widget_obj_para.obj_is_scrollable = \
        false;

    widget_img_para.img_click_attr = \
            false;
    widget_img_para.event_cb = NULL;

    widget_label_para.long_mode = \
        LV_LABEL_LONG_SCROLL;
    if(menu_align == menu_align_right)
        widget_label_para.text_align = \
            LV_TEXT_ALIGN_RIGHT;
    else
        widget_label_para.text_align = \
            LV_TEXT_ALIGN_LEFT;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_ver_center = \
        false;
    widget_label_para.user_text_font = NULL;

    uint8_t am_or_pm = 0;
    static char call_log_time_str[6];

    for(uint8_t i = 0; i < num; i++)
    {
        bool ret = vm_call_log_ctx_by_idx(i, \
            &vm_call_log_ctx);
        if(!ret) continue;

        widget_obj_para.obj_y = 40 + \
            elem_container_h*i;
        lv_obj_t *elem_container = \
            common_widget_obj_create(&widget_obj_para);
        lv_obj_add_event_cb(elem_container, \
            call_log_elem_click_cb, LV_EVENT_SHORT_CLICKED, \
                (void *)&call_log_click_idx[i]);

        widget_img_para.img_parent = \
            elem_container;
        widget_img_para.file_img_dat = \
            call_log_state_icon(\
                vm_call_log_ctx.call_log_state);
        lv_obj_t *call_log_icon = \
             common_widget_img_create(&widget_img_para, \
                NULL);
        if(menu_align == menu_align_right)
            lv_obj_align(call_log_icon, LV_ALIGN_RIGHT_MID, \
                -24, 0);
        else
            lv_obj_align(call_log_icon, LV_ALIGN_LEFT_MID, \
                24, 0);

        uint8_t call_log_hour;
        uint8_t call_log_minute;
        memset(call_log_time_str, 0, \
            sizeof(call_log_time_str));
        int time_format = \
            get_vm_para_cache_with_label(vm_label_time_format);
        if(time_format == comm_time_format_24)
        {
            call_log_hour = \
                vm_call_log_ctx.call_log_time.hour;     
        }else
        {
            call_log_hour = \
                vm_call_log_ctx.call_log_time.hour;

            if(call_log_hour >= 12)
                am_or_pm = 1;
            else
                am_or_pm = 0;

            if(call_log_hour > 12)
                call_log_hour -= 12;
            else if(call_log_hour == 0)
                call_log_hour = 12;
  
        }
        call_log_minute = \
                vm_call_log_ctx.call_log_time.min;  
        sprintf(call_log_time_str, "%02d:%02d", \
            call_log_hour, call_log_minute);

        widget_label_para.label_w = 80;
        widget_label_para.label_h = \
            Label_Line_Height;
        widget_label_para.label_text_color = \
            lv_color_hex(0xffffff);
        widget_label_para.label_parent = \
            elem_container;
        widget_label_para.label_text = \
            call_log_time_str;
        lv_obj_t *call_log_time_label = \
            common_widget_label_create(&widget_label_para);
        if(menu_align == menu_align_right)
            lv_obj_align_to(call_log_time_label, call_log_icon, \
                LV_ALIGN_OUT_LEFT_TOP, -15, 4);
        else
            lv_obj_align_to(call_log_time_label, call_log_icon, \
                LV_ALIGN_OUT_RIGHT_TOP, 15, 4);

        widget_img_para.img_parent = \
            elem_container;
        widget_img_para.file_img_dat = \
            am_or_pm + call_19_index;
        lv_obj_t *ampm_icon = \
             common_widget_img_create(&widget_img_para, \
                NULL);
        if(menu_align == menu_align_right)
            lv_obj_align_to(ampm_icon, call_log_time_label, \
                LV_ALIGN_OUT_LEFT_BOTTOM, 0, -5);
        else
            lv_obj_align_to(ampm_icon, call_log_time_label, \
                LV_ALIGN_OUT_RIGHT_BOTTOM, 0, -5);
        if(time_format == comm_time_format_24)
            lv_obj_add_flag(ampm_icon, LV_OBJ_FLAG_HIDDEN);
        
        char *call_log_str;
        if(strlen(vm_call_log_ctx.call_log_name_str))
            call_log_str = \
                vm_call_log_ctx.call_log_name_str;
        else
            call_log_str = \
                vm_call_log_ctx.call_log_number_str;

        widget_label_para.label_w = 220;
        widget_label_para.label_h = \
            Label_Line_Height;
        widget_label_para.label_text_color = \
            lv_color_hex(0x666666);
        widget_label_para.label_text = \
            call_log_str;
        lv_obj_t *call_log_str_label = \
            common_widget_label_create(&widget_label_para);
        if(menu_align == menu_align_right)
            lv_obj_align_to(call_log_str_label, call_log_icon, \
                LV_ALIGN_OUT_LEFT_BOTTOM, -15, 0);
        else
            lv_obj_align_to(call_log_str_label, call_log_icon, \
                LV_ALIGN_OUT_RIGHT_BOTTOM, 15, 0);
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
            ui_act_id_call_log);

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

    uint8_t call_log_num = \
        vm_call_log_item_num();

    if(!call_log_num)
        no_call_log_menu_create(obj);
    else
    {
        menu_align_t menu_align = \
            menu_align_left;

        if(lang_txt_is_arabic())
            menu_align = \
                menu_align_right;

        has_call_log_menu_create(obj, \
            call_log_num, menu_align);
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
    menu_load_call_log) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_call_log,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
