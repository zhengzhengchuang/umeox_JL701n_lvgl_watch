﻿#ifndef __NOR_VM_CFG_H__
#define __NOR_VM_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ui_vm/ui_vm.h"
#include "../include/ui_menu.h"

/*********************************************************************************
                                  Nor vm校验码                                     
*********************************************************************************/
#define Nor_Vm_Check_Code (0x5555)

/*********************************************************************************
                                  Nor vm类型                                     
*********************************************************************************/
enum
{
    nor_vm_type_contacts,
    nor_vm_type_weather,
    nor_vm_type_call_log,
    nor_vm_type_message,

    nor_vm_type_max,
};
typedef uint8_t nor_vm_type_t;

#define Nor_Vm_Type_Max \
    (nor_vm_type_max)
#define Nor_Vm_Type_Invalid \
    (Nor_Vm_Type_Max)

/*********************************************************************************
                                  Nor vm具体分块大小                                     
*********************************************************************************/
#define Nor_Vm_Contacts_Size  \
    (1*4096)
#define Nor_Vm_Weather_Size   \
    (1*4096)
#define Nor_Vm_Call_log_Size  \
    (1*4096)
#define Nor_Vm_Message_Size   \
    (10*4096)

/*********************************************************************************
                                  Nor vm具体分块偏移                                     
*********************************************************************************/
#define Nor_Vm_Contacts_Offset \
    (0)
#define Nor_Vm_Weather_Offset \
    (Nor_Vm_Contacts_Offset + Nor_Vm_Contacts_Size)
#define Nor_Vm_Call_log_Offset \
    (Nor_Vm_Weather_Offset + Nor_Vm_Weather_Size)
#define Nor_Vm_Message_Offset \
    (Nor_Vm_Call_log_Offset + Nor_Vm_Call_log_Size)

/*********************************************************************************
                                  Nor vm信息载体                                       
*********************************************************************************/
typedef struct
{   
    nor_vm_type_t type; 
    uint8_t vm_num_max;

    uint32_t vm_size;
    uint32_t vm_offset;    
}nor_vm_para_t;

#ifdef __cplusplus
}
#endif

#endif
