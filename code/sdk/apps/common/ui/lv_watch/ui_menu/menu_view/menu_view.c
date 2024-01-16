#include "menu_view.h"

static const uint32_t menu_view_icon_src[\
    ui_menu_view_max] = 
{
    menu_view_00_index, menu_view_01_index, \
    menu_view_02_index,
};

static const uint16_t menu_view_text_id[\
    ui_menu_view_max] = 
{
    lang_txtid_view_list, lang_txtid_view_grid_1, \
    lang_txtid_view_grid_2,
};

static const uint8_t menu_view_elem_container_idx[\
    ui_menu_view_max] = 
{
    ui_menu_view_00, ui_menu_view_01, \
    ui_menu_view_02,
};

static ui_menu_view_t menu_view_cache = \
    ui_menu_view_max;
static uint16_t elem_container_dsc_idx[\
    ui_menu_view_max] = {0xffff};
static lv_obj_t *menu_view_elem_container[\
    ui_menu_view_max] = {NULL};


static void menu_view_elem_container_cb(lv_event_t *e)
{
    if(!e) return;

    uint8_t menu_view_sel = \
        *(uint8_t *)lv_event_get_user_data(e);

    if(menu_view_sel == menu_view_cache)
        return;

    menu_view_cache = menu_view_sel;

    uint32_t file_img_dat;
    for(uint8_t i = ui_menu_view_00; i < ui_menu_view_max; i++)
    {
        if(menu_view_cache == i)
            file_img_dat = \
                menu_view_04_index;
        else
           file_img_dat = \
                menu_view_03_index;

        common_widget_img_replace_src(\
            menu_view_elem_container[i], file_img_dat, \
                elem_container_dsc_idx[i]);
    }

    return;
}

static void menu_view_confirm_button_cb(lv_event_t *e)
{
    if(!e) return;

    int menu_view_vm_cache = \
        (int)menu_view_cache;
    
    set_vm_para_cache_with_label(\
        vm_label_menu_view, menu_view_vm_cache);

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_null, \
            ui_act_id_menu_view);

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

    int cur_menu_view = \
        get_vm_para_cache_with_label(\
            vm_label_menu_view);

    menu_view_cache = \
        (ui_menu_view_t)cur_menu_view;
    
    widget_img_para.img_parent = obj;
    widget_img_para.img_x = 24;

    for(uint8_t i = ui_menu_view_00; i < \
        ui_menu_view_max; i++)
    {
        widget_img_para.img_y = 52 + \
            96*i;
        if(i == menu_view_cache)
            widget_img_para.file_img_dat = \
                menu_view_04_index;
        else
            widget_img_para.file_img_dat = \
                menu_view_03_index;
        widget_img_para.img_click_attr = true;
        widget_img_para.event_cb = \
            menu_view_elem_container_cb;
        widget_img_para.user_data = \
            (void *)&menu_view_elem_container_idx[i];
        menu_view_elem_container[i] = \
            common_widget_img_create(&widget_img_para, \
                &elem_container_dsc_idx[i]);
    }

    for(uint8_t i = ui_menu_view_00; i < \
        ui_menu_view_max; i++)
    {
        widget_img_para.img_parent = \
            menu_view_elem_container[i];
        widget_img_para.file_img_dat = \
            menu_view_icon_src[i];
        widget_img_para.img_click_attr = false;
        widget_img_para.event_cb = NULL;
        lv_obj_t *menu_view_icon = \
            common_widget_img_create(&widget_img_para, \
                NULL);
        lv_obj_align(menu_view_icon, LV_ALIGN_LEFT_MID, \
            44, 0);
    }

    widget_label_para.label_x = 0;
    widget_label_para.label_y = 0;
    widget_label_para.label_w = 180;
    widget_label_para.label_h = \
        Label_Line_Height;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_SCROLL;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_LEFT;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_ver_center = \
        false;
    widget_label_para.user_text_font = NULL;
    for(uint8_t i = ui_menu_view_00; i < \
        ui_menu_view_max; i++)
    {
        widget_label_para.label_parent = \
            menu_view_elem_container[i];
        widget_label_para.label_text = \
            get_lang_txt_with_id(menu_view_text_id[i]);
        lv_obj_t *menu_view_label = \
            common_widget_label_create(&widget_label_para);
        lv_obj_align(menu_view_label, LV_ALIGN_LEFT_MID, \
            104, 0);
    }

    widget_img_para.img_parent = obj;
    widget_img_para.img_x = 137;
    widget_img_para.img_y = 376;
    widget_img_para.img_click_attr = \
        true;
    widget_img_para.file_img_dat = \
        comm_icon_02_index;
    widget_img_para.event_cb = \
        menu_view_confirm_button_cb;
    widget_img_para.user_data = NULL;
    lv_obj_t *confirm_button = \
        common_widget_img_create(&widget_img_para,  NULL);
    lv_obj_set_ext_click_area(confirm_button, 15);
    
    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_menu_view) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_menu_view,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
