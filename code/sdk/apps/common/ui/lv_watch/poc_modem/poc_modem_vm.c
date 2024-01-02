#include "syscfg_id.h"
#include "app_config.h"
#include "../lv_watch.h"
#include "poc_modem_vm.h"


#define Vm_Debug_En (1)

vm_store_para_cache_t *p_vm_para_cache = NULL;
static vm_store_para_cache_t vm_para_cache = {0};
const ui_menu_load_info_t *watchface_load_info[] = 
{
    &menu_load_watchface_00, &menu_load_watchface_01,
};
const ui_menu_load_info_t *menu_style_load_info[] = 
{
    &menu_load_common_list, /*&menu_load_apple_network,*/
};

/*********************************************************************************
                             系统带标签参数的缺省值                                  
*********************************************************************************/
static const vm_store_para_with_label_t default_label_para[Vm_Store_Para_Num] = \
{
    /*********默认屏幕背光亮度 80%*********/
    {.label = vm_label_backlight, \
        .store_para_val = 80}, 

    /*********时区默认 深圳：东八区*********/
    {.label = vm_label_time_zone, \
        .store_para_val = 0x08}, 

    /*********默认菜单风格*********/
    {.label = vm_label_menu_style, \
        .store_para_val = ui_menu_style_00},

    /*********默认时间格式:24小时制*********/
    {.label = vm_label_time_format, \
        .store_para_val = 0x00},

    /*********默认屏幕熄屏时间 10s*********/
    {.label = vm_label_offscreen_time, \
        .store_para_val = 10*1000},

    /*********默认表盘*********/
    {.label = vm_label_watchface_id, \
        .store_para_val = ui_watchface_id_00},

    /*********默认系统语言*********/
    {.label = vm_label_sys_language, \
        .store_para_val = comm_language_id_english},

    /*********默认心率*********/
    {.label = vm_label_hr, .store_para_val = 0},
    {.label = vm_label_min_hr, .store_para_val = 0},
    {.label = vm_label_max_hr, .store_para_val = 0},

    /*********默认血氧*********/
    {.label = vm_label_bo, .store_para_val = 0},
    {.label = vm_label_min_bo, .store_para_val = 0},
    {.label = vm_label_max_bo, .store_para_val = 0},

    /*********默认日常数据*********/
    {.label = vm_label_daily_step, .store_para_val = 0},
    {.label = vm_label_daily_pace, .store_para_val = 0},
    {.label = vm_label_daily_calorie, .store_para_val = 0},
    {.label = vm_label_daily_distance, .store_para_val = 0},
};

/*********************************************************************************
                             系统用户闹钟的缺省值                                  
*********************************************************************************/
static const alarm_manage_para_t default_alarm_para = 
{
    .alarm_num = 0,
    .alarm_info[0] = {.info = No_Alarm_Info},
    .alarm_info[1] = {.info = No_Alarm_Info},
    .alarm_info[2] = {.info = No_Alarm_Info},
    .alarm_info[3] = {.info = No_Alarm_Info},
    .alarm_info[4] = {.info = No_Alarm_Info},
};

int get_vm_para_cache_with_label(uint16_t label)
{
    for(uint16_t i = 0; i < Vm_Store_Para_Num; i++)
    {
        if(p_vm_para_cache->vm_store_para[i].label == label)
            return (p_vm_para_cache->vm_store_para[i].store_para_val);
    }
    
    return default_label_para[label].store_para_val;
}

bool set_vm_para_cache_with_label(uint16_t label, \
    int vm_val)
{
    for(uint16_t i = 0; i < Vm_Store_Para_Num; i++)
    {
        if(p_vm_para_cache->vm_store_para[i].label == label)
        {
            p_vm_para_cache->vm_store_para[i].store_para_val = \
                vm_val;
            return true;
        }     
    }

    return false;
}

void vm_store_para_init(void)
{
    p_vm_para_cache = &vm_para_cache;

    if(!p_vm_para_cache) ASSERT(0);

    int ret = 0;
    uint8_t repeat_cnt = 3;
    ret = syscfg_read(CFG_USER_PARA_INFO, (uint8_t *)&vm_para_cache, sizeof(vm_store_para_cache_t));
#if Vm_Debug_En
    if(1)
#else
    if(ret != sizeof(vm_store_para_cache_t) || p_vm_para_cache->vm_store_para_mask != Vm_Store_Para_Mask)
#endif
    {
        p_vm_para_cache->vm_store_para_mask = \
            Vm_Store_Para_Mask;

        memcpy(&p_vm_para_cache->alarm_manage_para, &default_alarm_para, \
            sizeof(alarm_manage_para_t));

        memcpy(p_vm_para_cache->vm_store_para, default_label_para, \
            sizeof(vm_store_para_with_label_t)*Vm_Store_Para_Num);

        ret = 0;
        repeat_cnt = 3;
        ret = syscfg_write(CFG_USER_PARA_INFO, (uint8_t *)&vm_para_cache, \
            sizeof(vm_store_para_cache_t));
        while(repeat_cnt && ret != sizeof(vm_store_para_cache_t))
        {
            ret = syscfg_write(CFG_USER_PARA_INFO, (uint8_t *)&vm_para_cache, \
                sizeof(vm_store_para_cache_t));
            repeat_cnt--;
        }
    }

    return;
}


