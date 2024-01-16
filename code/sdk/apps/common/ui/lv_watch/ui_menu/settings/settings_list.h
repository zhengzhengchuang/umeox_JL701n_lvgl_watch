#ifndef __SETTINGS_LIST_H__
#define __SETTINGS_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lv_watch.h"

/****************元素总数****************/
#define Settings_List_Elem_Num      (7)

/****************设置列表标题宽、高****************/
#define Settings_List_Title_W (LCD_WIDTH)
#define Settings_List_Title_H (94)

/****************设置列表容器宽、高****************/
#define Settings_List_Container_W   (LCD_WIDTH)
#define Settings_List_Container_H   \
    (LCD_HEIGHT - Settings_List_Title_H)

/****************设置列表参数内容****************/
typedef struct 
{
    lv_obj_t *settings_list_title;
    lv_obj_t *settings_list_title_label;

    lv_obj_t *settings_list_container;
    lv_obj_t *settings_list_icon[Settings_List_Elem_Num];
    lv_obj_t *settings_list_label[Settings_List_Elem_Num];
    lv_obj_t *settings_list_arrow[Settings_List_Elem_Num];
    lv_obj_t *settings_list_elem_container[Settings_List_Elem_Num];
}settings_list_ctx_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
