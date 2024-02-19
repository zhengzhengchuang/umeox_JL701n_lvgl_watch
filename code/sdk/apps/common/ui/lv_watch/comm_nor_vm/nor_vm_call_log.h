#ifndef __NOR_VM_CALL_LOG_H__
#define __NOR_VM_CALL_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"
#include "../include/comm_call.h"

/*********************************************************************************
                                  通话记录最大个数                                  
*********************************************************************************/
#define Call_log_Max_Num (10)

/*********************************************************************************
                                  通话记录时间字符串长度 13:50                                 
*********************************************************************************/
#define Call_log_Time_Str_Len (6) 

/*********************************************************************************
                                  通话记录状态枚举                                 
*********************************************************************************/
enum
{
    call_log_state_in,          //拨入
    call_log_state_out,         //拨出
    call_log_state_hangup,      //挂断

    call_log_unknown,
};
typedef uint8_t call_log_state_t;

/*********************************************************************************
                                  通话记录内容                                  
*********************************************************************************/
typedef struct
{
    uint16_t check_code;

    call_log_state_t \
        call_log_state;
    char call_log_name_str[\
        Call_Name_Max_Len];
    char call_log_number_str[\
        Call_Number_Max_Len];
    char call_log_time_str[\
        Call_log_Time_Str_Len];
}vm_call_log_ctx_t;

/*********************************************************************************
                                  通话记录接口                                       
*********************************************************************************/
void vm_call_log_ctx_clear(void);
uint8_t vm_call_log_item_num(void);
void vm_call_log_ctx_falsh_save(vm_call_log_ctx_t *p);
bool vm_call_log_ctx_by_idx(uint8_t idx, vm_call_log_ctx_t *p);
#ifdef __cplusplus
}
#endif

#endif
