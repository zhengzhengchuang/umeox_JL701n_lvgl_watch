#ifndef __COMMON_BO_H__
#define __COMMON_BO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common_data.h"
#include "../include/ui_menu.h"

void common_bo_refresh(void);
void common_bo_widget_init(void);
void common_bo_widget_create(comm_data_para_t *data_para, \
    common_data_type_t type, void *data_val);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
