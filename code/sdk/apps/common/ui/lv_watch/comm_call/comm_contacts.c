#include "../lv_watch.h"

/*********************************************************************************
                                  通用联系人获取条数                                   
*********************************************************************************/
uint8_t comm_contacts_item_num(void)
{
    uint8_t contacts_item = \
        p_vm_para_cache->contacts_manage_para.contacts_item;

    return contacts_item;
}

/*********************************************************************************
                                  通用联系人下标获取名字                                   
*********************************************************************************/
char *comm_contacts_name_with_idx(uint8_t idx)
{
    char *contacts_name = NULL;

    uint8_t contacts_item = \
        p_vm_para_cache->contacts_manage_para.contacts_item;
    
    if(idx >= contacts_item)
        return contacts_name;

    contacts_name = \
        &p_vm_para_cache->contacts_manage_para.contacts_ctx[\
            idx].contacts_name_str;

    return contacts_name;
}

/*********************************************************************************
                                  通用联系人下标获取号码                                   
*********************************************************************************/
char *comm_contacts_number_with_idx(uint8_t idx)
{
    char *contacts_number = NULL;

    uint8_t contacts_item = \
        p_vm_para_cache->contacts_manage_para.contacts_item;
    
    if(idx >= contacts_item)
        return contacts_number;

    contacts_number = \
        &p_vm_para_cache->contacts_manage_para.contacts_ctx[\
            idx].contacts_number_str;

    return contacts_number;
}

/*********************************************************************************
                                  通用联系人号码获取名字                                   
*********************************************************************************/
char *comm_contacts_name_with_number(char *call_number)
{
    char *contacts_name = NULL;

    if(!call_number)
        return contacts_name;

    uint8_t contacts_item = \
        p_vm_para_cache->contacts_manage_para.contacts_item;

    if(!contacts_item) 
        return contacts_name;

    char *contacts_number = NULL;
    for(uint8_t i = 0; i < contacts_item; i++)
    {
        contacts_number = \
            &p_vm_para_cache->contacts_manage_para.contacts_ctx[\
                i].contacts_number_str;

        if(!strcmp(call_number, contacts_number)) 
        {
            contacts_name = &p_vm_para_cache->contacts_manage_para.contacts_ctx[\
                i].contacts_name_str;
            break;
        }
    }

    return contacts_name;
}

/*********************************************************************************
                                  通用联系人复位操作                                   
*********************************************************************************/
void comm_contacts_content_clear(void)
{
    uint8_t *contacts_item = \
        &p_vm_para_cache->contacts_manage_para.contacts_item;

    common_contacts_ctx_t *contacts_ctx = \
        p_vm_para_cache->contacts_manage_para.contacts_ctx;

    *contacts_item = 0;

    memset(contacts_ctx, 0, \
        sizeof(common_contacts_ctx_t)*Comm_Contacts_Max_Num);

    return;
}

/*********************************************************************************
                                  通用联系人存储操作                                   
*********************************************************************************/
void comm_contacts_content_save(char *call_name, uint8_t name_len, \
    char *call_number, uint8_t number_len)
{
    uint8_t *contacts_item = \
        &p_vm_para_cache->contacts_manage_para.contacts_item;

    if(*contacts_item >= Comm_Contacts_Max_Num)
        return;

    if(!call_name || !name_len || !call_number || \
        !number_len)
        return;

    if(name_len > Call_Name_Max_Len)
        name_len = Call_Name_Max_Len;
    
    if(number_len > Call_Number_Max_Len)
        number_len = Call_Number_Max_Len;

    common_contacts_ctx_t *contacts_ctx = \
        p_vm_para_cache->contacts_manage_para.contacts_ctx;

    memcpy(contacts_ctx[*contacts_item].contacts_name_str, \
        call_name, name_len);
    memcpy(contacts_ctx[*contacts_item].contacts_number_str, \
        call_number, number_len);

    (*contacts_item) += 1;

    return;
}