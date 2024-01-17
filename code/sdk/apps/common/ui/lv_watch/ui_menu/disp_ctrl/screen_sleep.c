#include "screen_sleep.h"

static const char scr_sleep_roller_str[] =
{
    "10\n20\n30\n40\n50\n60"
};

static lv_obj_t *scr_sleep_title = NULL;
static lv_obj_t *scr_sleep_title_label = NULL;

/*********************************************************************************
                                  创建屏幕休眠标题                                 
*********************************************************************************/
static void screen_sleep_title_create(lv_obj_t *obj)
{
    widget_obj_para.obj_parent = \
        obj;
    widget_obj_para.obj_x = 0;
    widget_obj_para.obj_y = 0;
    widget_obj_para.obj_width = \
        Screen_Sleep_Title_W;
    widget_obj_para.obj_height = \
        Screen_Sleep_Title_H;
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
    widget_obj_para.obj_is_scrollable = false;
    scr_sleep_title = \
        common_widget_obj_create(&widget_obj_para);
  
    return;
}

/*********************************************************************************
                                  创建屏幕休眠标题标签                                 
*********************************************************************************/
static void screen_sleep_title_label_create(void)
{
    widget_label_para.label_x = 0;
    widget_label_para.label_y = 0;
    widget_label_para.label_w = \
        (Screen_Sleep_Title_W - 30);
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
        scr_sleep_title;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_screen_sleep);
    scr_sleep_title_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_center(scr_sleep_title_label);

    return;
}

static void scr_sleep_roller_event_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *obj = \  
        lv_event_get_target(e);
    uint16_t roller_sel = \
        lv_roller_get_selected(obj);
    
    int scr_sleep_time = \
        (roller_sel + 1)*(10*1000);
    
    set_vm_para_cache_with_label(\
        vm_label_offscreen_time, scr_sleep_time);

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_backlight, ui_act_id_null, \
            ui_act_id_screen_sleep);

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

    screen_sleep_title_create(obj);

    screen_sleep_title_label_create();

    widget_img_para.img_x = 0;
    widget_img_para.img_y = 0;   
    widget_img_para.event_cb = \
        NULL;
    widget_img_para.img_parent = obj;
    widget_img_para.file_img_dat = \
        comm_icon_09_index;
    widget_img_para.img_click_attr = \
        false;
    lv_obj_t *scr_sleep_sel = \
        common_widget_img_create(&widget_img_para, NULL);
    lv_obj_align(scr_sleep_sel, LV_ALIGN_CENTER, \
        0, 1);

    int cur_scr_sleep_time = \
        get_vm_para_cache_with_label(\
            vm_label_offscreen_time);
    uint16_t roller_sel = \
        cur_scr_sleep_time/(10*1000);
    if(roller_sel > 0)
        roller_sel -= 1;

    widget_roller_para.roller_parent = \
        obj;
    widget_roller_para.roller_x = 0;
    widget_roller_para.roller_y = 0;
    widget_roller_para.roller_width = 160;
    widget_roller_para.roller_height = 0;
    widget_roller_para.roller_row_count = 3;
    widget_roller_para.roller_options = \
        scr_sleep_roller_str;
    widget_roller_para.roller_mode = \
        LV_ROLLER_MODE_INFINITE;
    widget_roller_para.roller_sel = roller_sel;
    widget_roller_para.roller_line_inv = 20;
    widget_roller_para.roller_main_bg_opax = \
        LV_OPA_0;
    widget_roller_para.roller_main_bg_color = \
        lv_color_hex(0x000000);
    widget_roller_para.roller_selected_bg_opax = \
        LV_OPA_0;
    widget_roller_para.roller_selected_bg_color = \
        lv_color_hex(0x000000);
    widget_roller_para.roller_border_width = 0;
    widget_roller_para.roller_border_opax = \
        LV_OPA_0;
    widget_roller_para.roller_border_color = \
        lv_color_hex(0x000000);
    widget_roller_para.roller_main_text_font = \
        &font_common_num_52;
    widget_roller_para.roller_main_text_color = \
        lv_color_hex(0x999999);
    widget_roller_para.roller_selected_text_font = \
        &font_common_num_64;
    widget_roller_para.roller_selected_text_color = \
        lv_color_hex(0xF0D990);
    widget_roller_para.event_cb = \
        scr_sleep_roller_event_cb;
    widget_roller_para.user_data = NULL;
    lv_obj_t *scr_sleep_roller = \
        common_widget_roller_create(&widget_roller_para);
    lv_obj_center(scr_sleep_roller);


    /********************圆点********************/
    widget_img_para.img_x = 170;
    widget_img_para.img_y = 398;
    widget_img_para.file_img_dat = \
        comm_icon_08_index;
    common_widget_img_create(&widget_img_para, \
        NULL);

    widget_img_para.img_x = 190;
    widget_img_para.file_img_dat = \
        comm_icon_07_index;
    common_widget_img_create(&widget_img_para, \
        NULL);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_screen_sleep) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_screen_sleep,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
