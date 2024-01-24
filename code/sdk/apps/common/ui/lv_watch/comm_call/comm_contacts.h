#ifndef __COMM_CONTACTS_H__
#define __COMM_CONTACTS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "comm_call.h"
#include "../include/ui_menu.h"

/*********************************************************************************
                                  通用联系人最大个数                                  
*********************************************************************************/
#define Comm_Contacts_Max_Num (5)

/*********************************************************************************
                                  通用联系人内容                                  
*********************************************************************************/
typedef struct
{
    char contacts_name_str[\
        Call_Name_Max_Len];
    char contacts_number_str[\
        Call_Number_Max_Len];
}common_contacts_ctx_t;

/*********************************************************************************
                                  通用联系人管理参数                                  
*********************************************************************************/
typedef struct
{
    uint8_t contacts_item;
    common_contacts_ctx_t contacts_ctx[\
        Comm_Contacts_Max_Num];
}contacts_manage_para_t;

uint8_t comm_contacts_item_num(void);
void comm_contacts_content_clear(void);
char *comm_contacts_name_with_idx(uint8_t idx);
char *comm_contacts_number_with_idx(uint8_t idx);
char *comm_contacts_name_with_number(char *call_number);
void comm_contacts_content_save(char *call_name, uint8_t name_len, \
    char *call_number, uint8_t number_len);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
