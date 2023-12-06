#ifndef __UI_MENU_H__
#define __UI_MENU_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ui_act_id.h"
#include "../../lvgl/lvgl.h"

typedef void (*ui_menu_key_func_cb)(int, int);
typedef void (*ui_menu_create_func_cb)(lv_obj_t *);
typedef void (*ui_menu_refresh_func_cb)(lv_obj_t *);
typedef void (*ui_menu_destory_func_cb)(lv_obj_t *);
typedef void (*ui_menu_display_func_cb)(lv_obj_t *);


typedef struct 
{  
    void *menu_arg;
    bool lock_flag;//当前页面是否上锁。
    bool return_flag;  //当前页面是否返回上一级的机制。
    ui_act_id_t menu_id; 
    uint32_t user_display_time;//0默认显示时间，>0用户自定义显示时间，0xffffffff常亮
    uint32_t user_refresh_time_inv;  //0默认刷新时间间隔，>0用户自定义刷新时间间隔
    ui_menu_key_func_cb key_func_cb;//菜单按键回调函数
    ui_menu_create_func_cb create_func_cb;
    ui_menu_refresh_func_cb refresh_func_cb;
    ui_menu_destory_func_cb destory_func_cb;
    ui_menu_display_func_cb display_func_cb;
}ui_menu_load_info_t;

extern const ui_menu_load_info_t menu_load_weather;
extern const ui_menu_load_info_t menu_load_tool_box;
extern const ui_menu_load_info_t menu_load_watchface_00;
extern const ui_menu_load_info_t menu_load_watchface_01;

#ifdef __cplusplus
}
#endif

#endif
