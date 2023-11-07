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
    /*平移个数*/
    uint8_t translate_valid_cnt;

    /*平移菜单id*/
    ui_act_id_t translate_id_cache[TRANSLATE_DIR_NUM];

    /*平移方向*/
    lv_point_t translate_dir_points[TRANSLATE_DIR_NUM];

    /*平移菜单对象*/
    lv_obj_t *translate_menu_cache[TRANSLATE_DIR_NUM];

    /*平移菜单加载*/
    ui_menu_load_info_t *translate_menu_load[TRANSLATE_DIR_NUM];
}ui_translate_info_t;

void translate_menu_create(lv_obj_t *obj);
void translate_register_up_menu(ui_act_id_t act_id);
void translate_register_down_menu(ui_act_id_t act_id);
void translate_register_left_menu(ui_act_id_t act_id);
void translate_register_right_menu(ui_act_id_t act_id);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
