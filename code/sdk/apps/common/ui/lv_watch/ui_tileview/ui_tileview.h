#ifndef __UI_TILEVIEW_H__
#define __UI_TILEVIEW_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"
#include "../include/ui_act_id.h"


/********上、下、左、右、中心********/
#define TILEVIEW_DIR_NUM (5)

typedef struct
{
    /*tileview对象*/
    lv_obj_t *tileview_obj;

    uint8_t tileview_valid_dir;

    /*可视化个数*/
    uint8_t tileview_valid_cnt;

    /*中心菜单容器*/
    lv_obj_t *tileview_center_menu;

    /*可视化菜单容器*/
    ui_act_id_t tileview_id_cache[TILEVIEW_DIR_NUM];
    lv_point_t tileview_dir_points[TILEVIEW_DIR_NUM];
    lv_obj_t *tileview_side_menu_cache[TILEVIEW_DIR_NUM-1];//tileview四边容器 上、下、左、右
    ui_menu_load_info_t *tileview_menu_load[TILEVIEW_DIR_NUM]; 
}ui_tileview_info_t;

void tileview_info_clear(void);
void tileview_menu_create(lv_obj_t *obj);
void tileview_register_up_menu(ui_act_id_t act_id);
void tileview_register_down_menu(ui_act_id_t act_id);
void tileview_register_left_menu(ui_act_id_t act_id);
void tileview_register_right_menu(ui_act_id_t act_id);
void tileview_register_center_menu(ui_act_id_t act_id);
void tileview_register_all_menu(ui_act_id_t up, ui_act_id_t down, ui_act_id_t left, \
    ui_act_id_t right, ui_act_id_t center);
#ifdef __cplusplus
}
#endif

#endif
