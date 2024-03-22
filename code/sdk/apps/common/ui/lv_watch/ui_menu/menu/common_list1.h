#ifndef __COMMON_LIST1_H__
#define __COMMON_LIST1_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lv_watch.h"

/****************元素总数****************/
#define Common_List1_Elem_Num      (16)

/****************通用列表1宽、高度****************/
#define Common_List1_Container_W   (LCD_WIDTH)
#define Common_List1_Container_H   \
    (LCD_HEIGHT - LCD_UI_Y_OFFSET)

/****************通用列表参数内容****************/
typedef struct 
{
    lv_obj_t *common_list1_container;
    lv_obj_t *common_list1_icon[Common_List1_Elem_Num];
    lv_obj_t *common_list1_label[Common_List1_Elem_Num];
    lv_obj_t *common_list1_elem_container[Common_List1_Elem_Num];
}common_list1_ctx_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
