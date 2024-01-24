#ifndef __POC_MODEM_VM_H__
#define __POC_MODEM_VM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"
#include "../include/ui_act_id.h"
#include "../comm_call/comm_contacts.h"
#include "../comm_remind/alarm_manage.h"
#include "../comm_weather/comm_weather.h"

/*********************************************************************************
                             距离计量单位                              
*********************************************************************************/
enum
{
    unit_distance_kilometre = 0x00,
    unit_distance_mile,
    
    unit_distance_max,
};

/*********************************************************************************
                             温度计量单位                              
*********************************************************************************/
enum
{
    unit_temperature_C = 0x00,
    unit_temperature_F,

    unit_temperature_max,
};

/*********************************************************************************
                             vm存储信息，关机会备份到vm                              
*********************************************************************************/
enum
{
    vm_label_none = 0x00,

    /*******背光亮度*******/
    vm_label_backlight,

    /*******系统时区*******/
    vm_label_time_zone,

    /*******菜单风格*******/
    vm_label_menu_view,

    /*******小时制*******/
    vm_label_time_format,

    /*******表盘选择*******/
    vm_label_watchface_id,

    /*******熄屏时间*******/
    vm_label_offscreen_time,

    /*******系统语言*******/
    vm_label_sys_language,

    /*******系统声音开启*******/
    vm_label_sys_sound_on,

    /*******计量单位*******/
    vm_label_unit_distance,
    vm_label_unit_temperature,
  
    /*******心率数据*******/
    vm_label_hr,
    vm_label_min_hr,
    vm_label_max_hr,

    /*******血氧数据*******/
    vm_label_bo,
    vm_label_min_bo,
    vm_label_max_bo,

    /*******日常数据*******/
    vm_label_daily_step,
    vm_label_daily_pace,
    vm_label_daily_calorie,
    vm_label_daily_distance,

    vm_label_store_max,
};

#define Vm_Store_Para_Num  (vm_label_store_max)
#define Vm_Store_Para_Mask (0x55aa)//每次更新vm参数的时候都需要更改

typedef struct
{
    uint16_t label;
    int store_para_val;
}vm_store_para_with_label_t;

typedef struct
{
    uint16_t vm_store_para_mask;

    alarm_manage_para_t alarm_manage_para;
    weather_manage_para_t weather_manage_para;
    contacts_manage_para_t contacts_manage_para;
    vm_store_para_with_label_t vm_store_para[Vm_Store_Para_Num];  
}vm_store_para_cache_t;
extern vm_store_para_cache_t *p_vm_para_cache;
extern const ui_menu_load_info_t *watchface_load_info[];
extern const ui_menu_load_info_t *menu_style_load_info[];

void vm_store_para_init(void);
int get_vm_para_cache_with_label(uint16_t label);
bool set_vm_para_cache_with_label(uint16_t label, \
    int vm_val);
#ifdef __cplusplus
}
#endif

#endif
