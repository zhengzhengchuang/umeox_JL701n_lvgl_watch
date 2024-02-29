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
    ui_watchface_id_02,
    ui_watchface_id_03,
    ui_watchface_id_04,
    ui_watchface_id_05,
    ui_watchface_id_06,
    ui_watchface_id_07,
    ui_watchface_id_08,
    ui_watchface_id_09,
    ui_watchface_id_10,
    ui_watchface_id_11,
  
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
    ui_act_id_null = 0x0000,

    /*****表盘相关页面*****/
    ui_act_id_watchface,

    /*****菜单相关页面*****/
    ui_act_id_menu,

    /*****设置相关页面*****/
    ui_act_id_about,
    ui_act_id_reset, 
    ui_act_id_lang_sel,
    ui_act_id_backlight,
    ui_act_id_menu_view,
    ui_act_id_sound_ctrl,
    ui_act_id_unit_switch,
    ui_act_id_screen_sleep,
    ui_act_id_settings_list,

    /*****通话相关页面*****/
    ui_act_id_call_main,
    ui_act_id_call_disc,
    ui_act_id_contacts,
    ui_act_id_call_log,
    ui_act_id_call_dial,
    ui_act_id_call_in,
    ui_act_id_call_out,
    ui_act_id_call_online,
    ui_act_id_call_volume,
    ui_act_id_call_end,

    /*****提醒相关页面*****/
    ui_act_id_hr_warn,
    ui_act_id_sedentary,
    ui_act_id_off_wrist,
    ui_act_id_device_op,
    ui_act_id_ota_update,
    ui_act_id_low_battery,
    ui_act_id_watchface_transp,
    
    /*****工具盒子相关页面*****/
    ui_act_id_tool_box,
    
    /*****礼拜时间相关页面*****/
    ui_act_id_worship_time,
    
    /*****天气相关页面*****/
    ui_act_id_weather_data,
    ui_act_id_weather_report,
    
    ui_act_id_max,
};
typedef uint16_t ui_act_id_t;


#ifdef __cplusplus
}
#endif

#endif
