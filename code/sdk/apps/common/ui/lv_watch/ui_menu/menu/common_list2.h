#ifndef __COMMON_LIST2_H__
#define __COMMON_LIST2_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lv_watch.h"

/****************元素总数****************/
#define Common_List2_Elem_Num      (17)

/****************通用列表1宽、高度****************/
#define Common_List2_Container_W   (LCD_WIDTH)
#define Common_List2_Container_H   \
    (LCD_HEIGHT - LCD_UI_Y_OFFSET)

/****************通用列表参数内容****************/
typedef struct 
{
    lv_obj_t *common_list2_container;
    lv_obj_t *common_list2_icon[Common_List2_Elem_Num];
    lv_obj_t *common_list2_label[Common_List2_Elem_Num];
    lv_obj_t *common_list2_elem_container[Common_List2_Elem_Num];
}common_list2_ctx_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
