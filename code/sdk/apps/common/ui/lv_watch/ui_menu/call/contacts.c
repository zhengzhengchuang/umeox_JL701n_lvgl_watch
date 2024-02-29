#include "contacts.h"

/*********************************************************************************
                                  联系人点击下标                                 
*********************************************************************************/
static const uint8_t contacts_click_idx[\
    Contacts_Max_Num] = 
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
};

/*********************************************************************************
                                  联系人存储结构体                                 
*********************************************************************************/
static vm_contacts_ctx_t vm_contacts_ctx;

/*********************************************************************************
                                  无联系人页面                                 
*********************************************************************************/
static void no_contacts_menu_create(lv_obj_t *obj)
{
    widget_img_para.img_parent = \
        obj;
    widget_img_para.img_x = 104;
    widget_img_para.img_y = 88;
    widget_img_para.file_img_dat = \
        call_03_index;
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
                                  联系人列表容器                                 
*********************************************************************************/
static lv_obj_t *contacts_list_container_create(lv_obj_t *obj)
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
    lv_obj_t *contacts_list_container = \
        common_widget_obj_create(&widget_obj_para);

    return contacts_list_container;
}

/*********************************************************************************
                                  联系人元素点击回调                                 
*********************************************************************************/
static void contacts_elem_click_cb(lv_event_t *e)
{
    if(!e) return;

    uint8_t idx = \
        *(uint8_t *)lv_event_get_user_data(e);

    memset(&vm_contacts_ctx, 0, \
        sizeof(vm_contacts_ctx_t));
    bool ret = vm_contacts_ctx_by_idx(idx, \
        &vm_contacts_ctx);
    if(!ret) return;

    ui_ctrl_call_out_by_number(\
        vm_contacts_ctx.contacts_number_str, \
            strlen(vm_contacts_ctx.contacts_number_str));

    return;
}

/*********************************************************************************
                                  有联系人页面                                
*********************************************************************************/
static void has_contacts_menu_create(lv_obj_t *obj, \
    uint8_t num, menu_align_t menu_align)
{
    lv_obj_t *contacts_list_container = \
        contacts_list_container_create(obj);

    int16_t elem_container_h = \
        118;
    widget_obj_para.obj_parent = \
        contacts_list_container;  
    widget_obj_para.obj_width = \
        LCD_WIDTH; 
    widget_obj_para.obj_height = \
        elem_container_h;
    widget_obj_para.obj_is_scrollable = \
        false;

    widget_img_para.img_click_attr = \
            false;
    widget_img_para.event_cb = NULL;

    widget_label_para.label_w = \
        (220);
    widget_label_para.label_h = \
        Label_Line_Height;
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

    for(uint8_t i = 0; i < num; i++)
    {
        bool ret = vm_contacts_ctx_by_idx(i, \
            &vm_contacts_ctx);
        if(!ret) continue;

        widget_obj_para.obj_y = 40 + \
            elem_container_h*i;
        lv_obj_t *elem_container = \
            common_widget_obj_create(&widget_obj_para);
        lv_obj_add_event_cb(elem_container, \
            contacts_elem_click_cb, LV_EVENT_SHORT_CLICKED, \
                (void *)&contacts_click_idx[i]);

        widget_img_para.img_parent = \
            elem_container;
        widget_img_para.file_img_dat = \
            call_18_index;
        lv_obj_t *contacts_icon = \
             common_widget_img_create(&widget_img_para, \
                NULL);
        if(menu_align == menu_align_right)
            lv_obj_align(contacts_icon, LV_ALIGN_RIGHT_MID, \
                -24, 0);
        else
            lv_obj_align(contacts_icon, LV_ALIGN_LEFT_MID, \
                24, 0);

        widget_label_para.label_text_color = \
            lv_color_hex(0xffffff);
        widget_label_para.label_parent = \
            elem_container;
        widget_label_para.label_text = \
            vm_contacts_ctx.contacts_name_str;
        lv_obj_t *contacts_name_label = \
            common_widget_label_create(&widget_label_para);
        if(menu_align == menu_align_right)
            lv_obj_align_to(contacts_name_label, contacts_icon, \
                LV_ALIGN_OUT_LEFT_TOP, -15, 4);
        else
            lv_obj_align_to(contacts_name_label, contacts_icon, \
                LV_ALIGN_OUT_RIGHT_TOP, 15, 4);

        widget_label_para.label_text_color = \
            lv_color_hex(0x666666);
        widget_label_para.label_text = \
            vm_contacts_ctx.contacts_number_str;
        lv_obj_t *contacts_number_label = \
            common_widget_label_create(&widget_label_para);
        if(menu_align == menu_align_right)
            lv_obj_align_to(contacts_number_label, contacts_icon, \
                LV_ALIGN_OUT_LEFT_BOTTOM, -15, 0);
        else
            lv_obj_align_to(contacts_number_label, contacts_icon, \
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
            ui_act_id_contacts);

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

    uint8_t contacts_num = \
        vm_contacts_item_num();

    if(!contacts_num)
        no_contacts_menu_create(obj);
    else
    {
        menu_align_t menu_align = \
            menu_align_left;

        if(lang_txt_is_arabic())
            menu_align = \
                menu_align_right;

        has_contacts_menu_create(obj, \
            contacts_num, menu_align);
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
    menu_load_contacts) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_contacts,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
