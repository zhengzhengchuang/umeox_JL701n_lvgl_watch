#ifndef __WATCHFACE_MAIN_H__
#define __WATCHFACE_MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lv_watch.h"

void wf_register_tileview_menu(lv_obj_t *obj);
void wf_left_split_screen_create(lv_obj_t *obj);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
