#include "ui_cover.h"
#include "../lv_watch.h"
#include "../poc_modem/poc_modem_ui.h"
#include "../poc_modem/poc_modem_cache.h"

static const int16_t cover_scroll_limit = 10;

void cover_info_clear(void)
{
    memset(&p_ui_info_cache->ui_cover_info, 0, sizeof(ui_cover_info_t));

    return;
}

static void cover_register_bg_menu(ui_act_id_t act_id)
{
    ui_menu_load_info_t *menu_load_info = NULL;

    menu_load_info = ui_menu_load_info(act_id);
    if(!menu_load_info) return;

    p_ui_info_cache->ui_cover_info.cover_id_cache[0] = act_id;
    p_ui_info_cache->ui_cover_info.cover_menu_load[0] = menu_load_info;

    return;
}

static void cover_register_fg_menu(ui_act_id_t act_id)
{
    ui_menu_load_info_t *menu_load_info = NULL;

    menu_load_info = ui_menu_load_info(act_id);
    if(!menu_load_info) return;

    p_ui_info_cache->ui_cover_info.cover_id_cache[1] = act_id;
    p_ui_info_cache->ui_cover_info.cover_menu_load[1] = menu_load_info;

    return;
}

static void cover_menu_scroll_judge(void)
{
    bool hor_scroll_en = false;
    bool ver_scroll_en = false;
    lv_point_t vert_point = {0};

    lv_indev_get_vect(lv_indev_get_act(), &vert_point);

    lv_point_t *cover_scroll_sum = \
        &p_ui_info_cache->ui_cover_info.cover_scroll_sum;

    cover_scroll_sum->x += vert_point.x;
    cover_scroll_sum->y += vert_point.y;

    if(LV_ABS(cover_scroll_sum->x) > LV_ABS(cover_scroll_sum->y))
        hor_scroll_en = true;
    else
        ver_scroll_en = true;

    lv_dir_t *cover_candidate_scroll_dir = \
        &p_ui_info_cache->ui_cover_info.cover_candidate_scroll_dir;

    if(hor_scroll_en && LV_ABS(cover_scroll_sum->x) > cover_scroll_limit)
    {
        if(cover_scroll_sum->x < 0)
            *cover_candidate_scroll_dir = LV_DIR_LEFT;
        else
           *cover_candidate_scroll_dir = LV_DIR_RIGHT; 
    }else if(ver_scroll_en && LV_ABS(cover_scroll_sum->y) > cover_scroll_limit)
    {
        if(cover_scroll_sum->y < 0)
            *cover_candidate_scroll_dir = LV_DIR_TOP;
        else
           *cover_candidate_scroll_dir = LV_DIR_BOTTOM;
    }else
        *cover_candidate_scroll_dir = LV_DIR_NONE;

    if(*cover_candidate_scroll_dir != LV_DIR_NONE)
        memset(cover_scroll_sum, 0, sizeof(lv_point_t));

    return;
}

static void cover_menu_scroll_handle(void)
{
    

    return;
}

static void cover_menu_pressed_cb(lv_event_t *e)
{
    bool *cover_animing = \
        &p_ui_info_cache->ui_cover_info.cover_animing;

    if(*cover_animing) return;

    lv_dir_t *cover_candidate_scroll_dir = \
        &p_ui_info_cache->ui_cover_info.cover_candidate_scroll_dir;

    *cover_candidate_scroll_dir = LV_DIR_NONE;

    lv_point_t *cover_scroll_sum = \
        &p_ui_info_cache->ui_cover_info.cover_scroll_sum;

    memset(cover_scroll_sum, 0, sizeof(lv_point_t));

    return;
}

static void cover_menu_pressing_cb(lv_event_t *e)
{
    bool *cover_animing = \
        &p_ui_info_cache->ui_cover_info.cover_animing;

    if(*cover_animing) return;

    lv_dir_t *cover_candidate_scroll_dir = \
        &p_ui_info_cache->ui_cover_info.cover_candidate_scroll_dir;

    lv_dir_t *cover_register_scroll_dir = \
        &p_ui_info_cache->ui_cover_info.cover_register_scroll_dir;

    if(*cover_candidate_scroll_dir != LV_DIR_NONE && \
        *cover_candidate_scroll_dir != *cover_register_scroll_dir)
        return;

    if(*cover_candidate_scroll_dir == LV_DIR_NONE)
        cover_menu_scroll_judge();
    else
        cover_menu_scroll_handle();

    return;
}

static void cover_menu_released_cb(lv_event_t *e)
{
    printf("%s\n", __func__);

    return;
}

static void cover_menu_event_cb(lv_event_t *e)
{
    if(!e) return;

    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_PRESSED)
        cover_menu_pressed_cb(e);
    else if(event_code == LV_EVENT_PRESSING)
        cover_menu_pressing_cb(e);
    else if(event_code == LV_EVENT_RELEASED)
        cover_menu_released_cb(e);

    return;
}

static void cover_menu_create(lv_obj_t *obj)
{
    if(!obj) return;
    
    int16_t lcd_w = lv_disp_get_hor_res(NULL);
    int16_t lcd_h = lv_disp_get_ver_res(NULL);
    ui_menu_load_info_t *cover_menu_load = NULL;

    widget_obj_para.obj_x = 0;
    widget_obj_para.obj_y = 0;
    widget_obj_para.obj_parent = obj;
    widget_obj_para.obj_width = lcd_w;
    widget_obj_para.obj_height = lcd_h;
    widget_obj_para.obj_bg_opax = LV_OPA_100;
    widget_obj_para.obj_bg_color = lv_color_hex(0x000000);
    widget_obj_para.obj_border_opax = LV_OPA_0;
    widget_obj_para.obj_border_width = 0;
    widget_obj_para.obj_border_color = lv_color_hex(0x000000);
    widget_obj_para.obj_radius = 0;
    widget_obj_para.obj_is_scrollable = false;

    /*******************背景菜单创建*******************/
    cover_menu_load = p_ui_info_cache->ui_cover_info.cover_menu_load[0];
    lv_obj_t *cover_bg_container = common_widget_obj_create(&widget_obj_para);  
    if(cover_menu_load)
    {
        if(cover_menu_load->display_func_cb)
            cover_menu_load->display_func_cb(cover_bg_container);
    }

    /*******************前景菜单创建*******************/
    cover_menu_load = p_ui_info_cache->ui_cover_info.cover_menu_load[1];
    lv_obj_t *cover_fg_container = common_widget_obj_create(&widget_obj_para);
    if(cover_menu_load)
    {
        if(cover_menu_load->display_func_cb)
            cover_menu_load->display_func_cb(cover_fg_container);
    }

    lv_obj_add_event_cb(cover_fg_container, cover_menu_event_cb, LV_EVENT_ALL, NULL);

    return;
}

void cover_register_all_menu(lv_obj_t *obj, ui_act_id_t bg, \
    ui_act_id_t fg, lv_dir_t dir)
{
    if(ui_act_id_validity(bg))
        cover_register_bg_menu(bg);

    if(ui_act_id_validity(fg))
        cover_register_fg_menu(fg);

    if(dir == LV_DIR_NONE) return;

    lv_dir_t *cover_register_scroll_dir = \
        &p_ui_info_cache->ui_cover_info.cover_register_scroll_dir;

    *cover_register_scroll_dir = dir;

    cover_menu_create(obj);

    return;
}