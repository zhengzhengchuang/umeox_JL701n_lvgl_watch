#include "math.h"
#include "../lv_watch.h"

#define M_PI (3.14159f)
#define LL_VM_MASK (0x55aa)

ll_info_t ll_info;

static const ll_info_t init_info = {
    .vm_latitude = 22.57390f, \
    .vm_longitude = 113.94300f, 
    .position_valid = false,
};

static float deg2rad(float deg)
{
    return (deg * (M_PI / 180.0f));
}

static float rad2deg(float rad)
{
    return (rad * (180.0f / M_PI));
}

static s16 KaabaQiblaAzimuthCalc(void)
{   
    float X = 0.0f;
    float Y = 0.0f;
    float B = 0.0f;
    float latitude_Kaaba = 21.422530f;
    float longitude_Kaaba = 39.826181f;
    float latitude_temp = ll_info.vm_latitude;
    float longitude_temp = ll_info.vm_longitude;


    Y = cosf(deg2rad(latitude_Kaaba)) * sinf(deg2rad(longitude_Kaaba - longitude_temp));

    X = cosf(deg2rad(latitude_temp)) * sinf(deg2rad(latitude_Kaaba)) - \
        sinf(deg2rad(latitude_temp)) * cosf(deg2rad(latitude_Kaaba)) * \
            cosf(deg2rad(longitude_Kaaba - longitude_temp));

    B = atan2f(Y, X);

    float angle = rad2deg(B);

    s16 azimuth = (s16)(angle);

    if(azimuth < 0)
        azimuth = 360 + azimuth;

    return azimuth;
}

static s16 KaabaAzimuth;
s16 GetKaabaAzimuth(void)
{
    return KaabaAzimuth;
}

void SetKaabaAzimuth(s16 azimuth)
{
    KaabaAzimuth = azimuth;

    return;
}

void KaabaQiblaParaRead(void)
{
    int vm_op_len = \
        sizeof(ll_info_t);

    int ret = syscfg_read(CFG_LATITUDE_LONGITUDE_INFO, \
        &ll_info, vm_op_len);
    if(ret != vm_op_len || \
        ll_info.vm_mask != LL_VM_MASK)
    {
        memcpy(&ll_info, &init_info, \
            sizeof(ll_info_t));

        ll_info.vm_mask = LL_VM_MASK;

        KaabaQiblaParaUpdate();
    }else
    {
        s16 azimuth = \
            KaabaQiblaAzimuthCalc();
        SetKaabaAzimuth(azimuth);
    }

    return;
}

void KaabaQiblaParaWrite(void)
{
    int vm_op_len = \
        sizeof(ll_info_t);
    
    for(u8 i = 0; i < 3; i++)
    {
        int ret = syscfg_write(CFG_LATITUDE_LONGITUDE_INFO, \
            &ll_info, vm_op_len);
        if(ret == vm_op_len)
            break;
    }

    return;
}

void KaabaQiblaParaUpdate(void)
{
    s16 azimuth = \
        KaabaQiblaAzimuthCalc();
    SetKaabaAzimuth(azimuth);

    KaabaQiblaParaWrite();

    return;
}