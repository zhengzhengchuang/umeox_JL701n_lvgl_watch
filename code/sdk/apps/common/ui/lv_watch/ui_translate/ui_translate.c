#include "ui_translate.h"
#include "../lv_watch.h"
#include "../poc_modem/poc_modem_ui.h"
#include "../poc_modem/poc_modem_cache.h"

void translate_register_up_menu(ui_act_id_t act_id)
{
    ui_menu_load_info_t *menu_load_info = NULL;

    menu_load_info = ui_menu_load_info(act_id);
    if(!menu_load_info) return;

    uint8_t valid_cnt = p_ui_info_cache->ui_translate_info.translate_valid_cnt;

    p_ui_info_cache->ui_translate_info.translate_dir_points[valid_cnt].x = 0,
    p_ui_info_cache->ui_translate_info.translate_dir_points[valid_cnt].y = -1;
    p_ui_info_cache->ui_translate_info.translate_id_cache[valid_cnt] = act_id;
    p_ui_info_cache->ui_translate_info.translate_menu_load[valid_cnt] = menu_load_info;

    p_ui_info_cache->ui_translate_info.translate_valid_cnt++;

    return;
}

void translate_register_down_menu(ui_act_id_t act_id)
{
    ui_menu_load_info_t *menu_load_info = NULL;

    menu_load_info = ui_menu_load_info(act_id);
    if(!menu_load_info) return;

    uint8_t valid_cnt = p_ui_info_cache->ui_translate_info.translate_valid_cnt;

    p_ui_info_cache->ui_translate_info.translate_dir_points[valid_cnt].x = 0,
    p_ui_info_cache->ui_translate_info.translate_dir_points[valid_cnt].y = 1;
    p_ui_info_cache->ui_translate_info.translate_id_cache[valid_cnt] = act_id;
    p_ui_info_cache->ui_translate_info.translate_menu_load[valid_cnt] = menu_load_info;

    p_ui_info_cache->ui_translate_info.translate_valid_cnt++;

    return;
}

void translate_register_left_menu(ui_act_id_t act_id)
{
    ui_menu_load_info_t *menu_load_info = NULL;

    menu_load_info = ui_menu_load_info(act_id);
    if(!menu_load_info) return;

    uint8_t valid_cnt = p_ui_info_cache->ui_translate_info.translate_valid_cnt;

    p_ui_info_cache->ui_translate_info.translate_dir_points[valid_cnt].x = -1,
    p_ui_info_cache->ui_translate_info.translate_dir_points[valid_cnt].y = 0;
    p_ui_info_cache->ui_translate_info.translate_id_cache[valid_cnt] = act_id;
    p_ui_info_cache->ui_translate_info.translate_menu_load[valid_cnt] = menu_load_info;

    p_ui_info_cache->ui_translate_info.translate_valid_cnt++;

    return;
}

void translate_register_right_menu(ui_act_id_t act_id)
{
    ui_menu_load_info_t *menu_load_info = NULL;

    menu_load_info = ui_menu_load_info(act_id);
    if(!menu_load_info) return;

    uint8_t valid_cnt = p_ui_info_cache->ui_translate_info.translate_valid_cnt;

    p_ui_info_cache->ui_translate_info.translate_dir_points[valid_cnt].x = 1,
    p_ui_info_cache->ui_translate_info.translate_dir_points[valid_cnt].y = 0;
    p_ui_info_cache->ui_translate_info.translate_id_cache[valid_cnt] = act_id;
    p_ui_info_cache->ui_translate_info.translate_menu_load[valid_cnt] = menu_load_info;

    p_ui_info_cache->ui_translate_info.translate_valid_cnt++;

    return;
}

/*********如果那个方向没有的话，传入Act_Id_Null即可************/
void translate_register_all_menu(ui_act_id_t up, ui_act_id_t down, ui_act_id_t left, \
    ui_act_id_t right)
{
    translate_register_up_menu(up);
    translate_register_down_menu(down);
    translate_register_left_menu(left);
    translate_register_right_menu(right); 
  
    return;
}

void translate_menu_create(lv_obj_t *obj)
{
    if(!obj) return;

    return;
}