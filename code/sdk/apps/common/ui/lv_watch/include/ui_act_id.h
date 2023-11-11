#ifndef __UI_ACT_ID_H__
#define __UI_ACT_ID_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lvgl/lvgl.h"

enum
{
    Watchface_Id_00 = 0x00,
    Watchface_Id_01,
    Watchface_Id_Max,
};
typedef uint8_t ui_watchface_id_t;

enum
{
    Act_Id_Null = 0,

    /********表盘相关页面*********/
    Act_Id_Watchface,

    /********天气页面*********/
    Act_Id_Weather,

    /********工具页面*********/
    Act_Id_Tool_Box,

    Act_Id_Max,
};
typedef uint16_t ui_act_id_t;


#ifdef __cplusplus
}
#endif

#endif
