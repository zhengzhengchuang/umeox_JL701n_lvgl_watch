#ifndef __COMMON_DISTANCE_H__
#define __COMMON_DISTANCE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common_data.h"
#include "../include/ui_menu.h"

/*********************************************************************************
                                  配速显示最大值                                    
*********************************************************************************/
#define Distance_Disp_Max (99999)


void common_distance_refresh(void);
void common_distance_widget_init(void);
void common_distance_widget_create(comm_data_para_t *data_para, \
    common_data_type_t type, void *data_val);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
