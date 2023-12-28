#ifndef __WORSHIP_TIME_H__
#define __WORSHIP_TIME_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lv_watch.h"

/****************元素总数****************/
#define Wsptime_List_Elem_Num      (12)

/****************通用列表宽、高度****************/
#define Wsptime_List_Container_W   (LCD_WIDTH)
#define Wsptime_List_Container_H   (LCD_HEIGHT)

typedef struct
{
    lv_obj_t *wsptime_list_container;
    lv_obj_t *wsptime_list_elem_container[Wsptime_List_Elem_Num];
}wsptime_list_ctx_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
