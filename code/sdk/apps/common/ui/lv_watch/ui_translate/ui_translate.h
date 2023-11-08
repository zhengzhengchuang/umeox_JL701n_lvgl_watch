#ifndef __UI_TRANSLATE_H__
#define __UI_TRANSLATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"
#include "../include/ui_act_id.h"

#define TRANSLATE_DIR_NUM (4)

typedef struct
{
    /*平移动画中*/
    bool translate_animing;

    /*平移个数*/
    uint8_t translate_valid_cnt;

    /*平移滚动方向*/
    lv_dir_t translate_scroll_dir;

    /*平移滚动总值*/
    lv_point_t translate_scroll_sum;

    /*平移方向容器*/
    lv_obj_t *translate_menu_cache[TRANSLATE_DIR_NUM];

    /*平移菜单id*/
    ui_act_id_t translate_id_cache[TRANSLATE_DIR_NUM];

    /*平移方向点*/
    lv_point_t translate_dir_points[TRANSLATE_DIR_NUM];

    /*平移菜单加载*/
    ui_menu_load_info_t *translate_menu_load[TRANSLATE_DIR_NUM];
}ui_translate_info_t;

void translate_info_clear(void);
void translate_menu_create(lv_obj_t *obj);
void translate_register_up_menu(ui_act_id_t act_id);
void translate_register_down_menu(ui_act_id_t act_id);
void translate_register_left_menu(ui_act_id_t act_id);
void translate_register_right_menu(ui_act_id_t act_id);
void translate_register_all_menu(ui_act_id_t up, ui_act_id_t down, ui_act_id_t left, \
    ui_act_id_t right);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
