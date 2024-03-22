#ifndef __AL_NAME_LIST_H__
#define __AL_NAME_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lv_watch.h"

#define Al_Name_Elem_Num (Al_Name_Num)

#define Al_Name_List_Container_W (LCD_WIDTH)
#define Al_Name_List_Container_H \
    (LCD_HEIGHT - LCD_UI_Y_OFFSET)

typedef struct 
{
    lv_obj_t *al_name_list_container;
    lv_obj_t *al_name_list_elem_container[Al_Name_Elem_Num];
}al_name_list_ctx_t;
extern al_name_list_ctx_t al_name_list_ctx;

extern const uint8_t al_name_idx[Al_Name_Num];

uint8_t get_al_name_ex_id(void);
void set_al_name_ex_id(uint8_t id);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
