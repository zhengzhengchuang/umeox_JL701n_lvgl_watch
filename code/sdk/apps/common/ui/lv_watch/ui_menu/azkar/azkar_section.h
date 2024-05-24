#ifndef __AZKAR_SECTION_H__
#define __AZKAR_SECTION_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lv_watch.h"

#define Azkar_Sec_Container_W (LCD_WIDTH)
#define Azkar_Sec_Container_H \
    (LCD_HEIGHT - LCD_UI_Y_OFFSET)

typedef struct
{
    lv_obj_t *azkar_sec_container;

    lv_obj_t *azkar_sec_ctx_label[\
        Azkar_Sec_Max];
    lv_obj_t *azkar_sec_elem_container[\
        Azkar_Sec_Max];
}azkar_sec_ctx_t;

void set_azkar_sec_scroll_offset(\
    int16_t val);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
