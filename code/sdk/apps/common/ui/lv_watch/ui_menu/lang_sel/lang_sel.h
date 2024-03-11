#ifndef __LANG_SEL_H__
#define __LANG_SEL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lv_watch.h"

/****************元素总数****************/
#define Lang_List_Elem_Num      (Comm_Lang_Num)

/****************语言列表标题宽、高****************/
#define Lang_List_Title_W (LCD_WIDTH)
#define Lang_List_Title_H (94)

/****************语言列表容器宽、高****************/
#define Lang_List_Container_W   (LCD_WIDTH)
#define Lang_List_Container_H   \
    (LCD_HEIGHT - Lang_List_Title_H - LCD_UI_Y_OFFSET)

/****************语言列表参数内容****************/
typedef struct 
{
    lv_obj_t *lang_list_title;
    lv_obj_t *lang_list_title_label;

    lv_obj_t *lang_list_container;
    lv_obj_t *lang_list_icon[Lang_List_Elem_Num];
    lv_obj_t *lang_list_label[Lang_List_Elem_Num];
    lv_obj_t *lang_list_elem_container[Lang_List_Elem_Num];
}lang_list_ctx_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
