#ifndef __UI_ACT_ID_H__
#define __UI_ACT_ID_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lvgl/lvgl.h"

enum
{
    ui_watchface_id_00 = 0x00,
    ui_watchface_id_01,

    ui_watchface_id_max,
};
typedef uint8_t ui_watchface_id_t;

#define list_for_ui_watchface_load(id) \
    for(id = ui_watchface_id_00; id < ui_watchface_id_max; id++)

enum
{
    ui_menu_style_00 = 0x00,
    ui_menu_style_01,

    ui_menu_style_max,
};
typedef uint8_t ui_menu_style_t;

#define list_for_ui_menu_style(id) \
    for(id = ui_menu_style_00; id < ui_menu_style_max; id++)

enum
{
    ui_act_id_null = 0,

    ui_act_id_menu,
    ui_act_id_weather,
    ui_act_id_tool_box,
    ui_act_id_watchface,

    ui_act_id_max,
};
typedef uint16_t ui_act_id_t;


#ifdef __cplusplus
}
#endif

#endif
