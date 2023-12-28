#ifndef __COMMON_OFFSCREEN_H__
#define __COMMON_OFFSCREEN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

void common_offscreen_msg_handle(void);
void common_offscreen_timer_create(void);
void common_offscreen_timer_restart(void);
void common_offscreen_timer_destroy(void);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
