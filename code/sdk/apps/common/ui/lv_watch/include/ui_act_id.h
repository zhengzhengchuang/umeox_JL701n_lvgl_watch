#ifndef __UI_ACT_ID_H__
#define __UI_ACT_ID_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lvgl/lvgl.h"

#define LCD_WIDTH  (368)
#define LCD_HEIGHT (448)

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
    ui_menu_view_00 = 0x00,
    ui_menu_view_01,
    ui_menu_view_02,

    ui_menu_view_max,
};
typedef uint8_t ui_menu_view_t;

#define list_for_ui_menu_style(id) \
    for(id = ui_menu_view_00; id < ui_menu_view_max; id++)

enum
{
    ui_act_id_null = 0,

    ui_act_id_menu,
    ui_act_id_weather,
    ui_act_id_hr_warn,
    ui_act_id_tool_box,
    ui_act_id_lang_sel,
    ui_act_id_backlight,
    ui_act_id_sedentary,
    ui_act_id_menu_view,
    ui_act_id_watchface,
    ui_act_id_off_wrist,
    ui_act_id_device_op, 
    ui_act_id_ota_update,
    ui_act_id_sound_ctrl,
    ui_act_id_low_battery,
    ui_act_id_screen_sleep,
    ui_act_id_worship_time,
    ui_act_id_settings_list, 
    ui_act_id_watchface_transp,

    ui_act_id_max,
};
typedef uint16_t ui_act_id_t;


#ifdef __cplusplus
}
#endif

#endif
