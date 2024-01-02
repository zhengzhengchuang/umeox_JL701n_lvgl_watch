#ifndef __COMMON_CALORIE_H__
#define __COMMON_CALORIE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common_data.h"
#include "../include/ui_menu.h"

/*********************************************************************************
                                  卡路里显示最大值                                    
*********************************************************************************/
#define Calorie_Disp_Max (9999)


void common_calorie_refresh(void);
void common_calorie_widget_init(void);
void common_calorie_widget_create(comm_data_para_t *data_para, \
    common_data_type_t type, void *data_val);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
