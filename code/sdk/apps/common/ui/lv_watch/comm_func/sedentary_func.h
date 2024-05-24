﻿#ifndef __SEDENTARY_FUNC_H__
#define __SEDENTARY_FUNC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

typedef struct
{
    u16 vm_mask;

    bool enable;
    u8 start_hour;
    u8 start_minute;
    u8 end_hour;
    u8 end_minute;
    u8 repeat;
}SedInfoPara_t;
extern SedInfoPara_t Sed_Info;

void SedInfoParaRead(void);
void SedInfoParaWrite(void);
void SedInfoParaUpdate(void);

void SedProcess(struct sys_time *utc_time);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
