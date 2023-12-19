#ifndef __POC_MODEM_VM_H__
#define __POC_MODEM_VM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"
#include "../include/ui_act_id.h"
#include "../comm_remind/alarm_manage.h"


//*********************************************************************************//
//                             vm存储信息，关机会备份到vm                              //
//*********************************************************************************//
enum
{
    vm_label_backlight,
    vm_label_time_zone,
    vm_label_menu_style,
    vm_label_time_format,
    vm_label_watchface_id,
    vm_label_offscreen_time,
      
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
    vm_store_para_with_label_t vm_store_para[Vm_Store_Para_Num];  
}vm_store_para_cache_t;
extern vm_store_para_cache_t *p_vm_para_cache;
extern const ui_menu_load_info_t *watchface_load_info[];
extern const ui_menu_load_info_t *menu_style_load_info[];

void vm_store_para_init(void);
int get_vm_para_cache_with_label(uint16_t label);
bool set_vm_para_cache_with_label(uint16_t label, int16_t vm_val);
#ifdef __cplusplus
}
#endif

#endif
