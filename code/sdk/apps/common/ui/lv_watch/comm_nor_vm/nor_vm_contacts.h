#ifndef __NOR_VM_CONTACTS_H__
#define __NOR_VM_CONTACTS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"
#include "../include/comm_call.h"

/*********************************************************************************
                                  联系人最大个数                                  
*********************************************************************************/
#define Contacts_Max_Num (10)

/*********************************************************************************
                                  联系人内容                                  
*********************************************************************************/
typedef struct
{
    uint16_t check_code;
    
    char contacts_name_str[\
        Call_Name_Max_Len];
    char contacts_number_str[\
        Call_Number_Max_Len];
}vm_contacts_ctx_t;

/*********************************************************************************
                                  联系人接口                                       
*********************************************************************************/
void vm_contacts_ctx_clear(void);
uint8_t vm_contacts_item_num(void);
char *vm_contacts_name_by_number(char *number);
bool vm_contacts_ctx_by_idx(uint8_t idx, vm_contacts_ctx_t *p);
void vm_contacts_ctx_falsh_save(uint8_t idx, vm_contacts_ctx_t *p);
#ifdef __cplusplus
}
#endif

#endif
