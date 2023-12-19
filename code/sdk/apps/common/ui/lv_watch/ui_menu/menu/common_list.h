#ifndef __COMMON_LIST_H__
#define __COMMON_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lv_watch.h"

/****************图标源总数****************/
#define Common_List_Icon_Num      (37)

/****************通用列表宽、高度****************/
#define Common_List_Container_W   (368)
#define Common_List_Container_H   (448)

/****************通用列表参数内容****************/
typedef struct 
{
    lv_obj_t *common_list_container;
    lv_obj_t *common_list_icon[Common_List_Icon_Num];
    lv_obj_t *common_list_label[Common_List_Icon_Num];
    lv_obj_t *common_list_elem_container[Common_List_Icon_Num];
}common_list_ctx_t;
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
