#ifndef __KAABA_QIBLA_FUNC_H__
#define __KAABA_QIBLA_FUNC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

typedef struct
{
    u16 vm_mask;

    float vm_latitude;   //纬度
    float vm_longitude;  //经度
    bool position_valid; //位置有效
}ll_info_t;
extern ll_info_t ll_info;

s16 GetKaabaAzimuth(void);
void SetKaabaAzimuth(s16 azimuth);

void KaabaQiblaParaRead(void);
void KaabaQiblaParaWrite(void);
void KaabaQiblaParaUpdate(void);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
