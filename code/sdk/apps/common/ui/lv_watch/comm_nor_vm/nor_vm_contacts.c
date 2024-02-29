#include "nor_vm_main.h"

static vm_contacts_ctx_t vm_contacts_ctx;
static const nor_vm_type_t nor_vm_type = \
    nor_vm_type_contacts;

/*********************************************************************************
                              清除                                         
*********************************************************************************/
void vm_contacts_ctx_clear(void)
{
    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);

    if(!nor_vm_file)
        return;

    uint8_t contacts_num = \
        vm_contacts_item_num();

    if(!contacts_num) 
        return;

    while(contacts_num)
    {
        flash_common_delete_by_index(\
            nor_vm_file, 0);

        contacts_num--;
    }
    
    return;
}

/*********************************************************************************
                              存储数量                                         
*********************************************************************************/
uint8_t vm_contacts_item_num(void)
{
    uint8_t contacts_num = 0;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);

    if(!nor_vm_file)
        return contacts_num;

    contacts_num = \
        flash_common_get_total(nor_vm_file);

    if(contacts_num > Contacts_Max_Num)
        contacts_num = Contacts_Max_Num;

    return contacts_num;
}

/*********************************************************************************
                              通过下标获取联系人内容                                        
*********************************************************************************/
bool vm_contacts_ctx_by_idx(uint8_t idx, vm_contacts_ctx_t *p)
{
    uint8_t contacts_num = \
        vm_contacts_item_num();

    if(idx >= contacts_num)
        return false;
    
    if(!p) return false;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);
    int contacts_ctx_len = \
        sizeof(vm_contacts_ctx_t);
    
    if(!nor_vm_file)
        return false;
    
    memset(&vm_contacts_ctx, 0, \
        contacts_ctx_len);
    flash_common_read_by_index(nor_vm_file, idx, 0, \
        contacts_ctx_len, (uint8_t *)&vm_contacts_ctx);

    if(vm_contacts_ctx.check_code != \
        Nor_Vm_Check_Code)
        return false;

    memcpy(p, &vm_contacts_ctx, \
        contacts_ctx_len);

    return true;
}
 
/*********************************************************************************
                              通过号码获取名字                                   
*********************************************************************************/
char *vm_contacts_name_by_number(char *number)
{
    char *vm_contacts_name = \
        NULL;

    if(!number) 
        return vm_contacts_name;

    uint8_t contacts_num = \
        vm_contacts_item_num();

    if(!contacts_num)
        return vm_contacts_name;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);
    int contacts_ctx_len = \
        sizeof(vm_contacts_ctx_t);

    if(!nor_vm_file)
        return vm_contacts_name;

    for(uint8_t idx = 0; idx < contacts_num; \
        idx++)
    {
        memset(&vm_contacts_ctx, 0, \
            contacts_ctx_len);
        flash_common_read_by_index(nor_vm_file, idx, 0, \
            contacts_ctx_len, (uint8_t *)&vm_contacts_ctx);

        if(vm_contacts_ctx.check_code != \
            Nor_Vm_Check_Code)
            continue;

        if(!strcmp(number, vm_contacts_ctx.contacts_number_str))
        {
            vm_contacts_name = \
                vm_contacts_ctx.contacts_name_str;
            break;
        }
    }

    return vm_contacts_name;
}

/*********************************************************************************
                              联系人存储                                   
*********************************************************************************/
void vm_contacts_ctx_falsh_save(uint8_t idx, vm_contacts_ctx_t *p)
{
    if(!p) return;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);
    int contacts_ctx_len = \
        sizeof(vm_contacts_ctx_t);

    if(!nor_vm_file)
        return;

    uint8_t contacts_num = \
        vm_contacts_item_num();
    if(idx < contacts_num)
        vm_contacts_ctx_clear();

    int file_id = \
        flash_common_open_id(nor_vm_file, 0, \
            contacts_ctx_len);
    if(!file_id) return;

    flash_common_write_packet(nor_vm_file, file_id, \
        contacts_ctx_len, (uint8_t *)p);

    return;
}

#if 0
static const vm_contacts_ctx_t vm_contacts_ctx_1[\
    Contacts_Max_Num] = 
{
    {.check_code = Nor_Vm_Check_Code, .contacts_name_str = "张三", \
        .contacts_number_str = "17820295895"},
    {.check_code = Nor_Vm_Check_Code, .contacts_name_str = "张三", \
        .contacts_number_str = "17820295895"},
    {.check_code = Nor_Vm_Check_Code, .contacts_name_str = "张三", \
        .contacts_number_str = "17820295895"},
    {.check_code = Nor_Vm_Check_Code, .contacts_name_str = "张三", \
        .contacts_number_str = "17820295895"},
    {.check_code = Nor_Vm_Check_Code, .contacts_name_str = "张三", \
        .contacts_number_str = "17820295895"},
    {.check_code = Nor_Vm_Check_Code, .contacts_name_str = "张三", \
        .contacts_number_str = "17820295895"},
    {.check_code = Nor_Vm_Check_Code, .contacts_name_str = "张三", \
        .contacts_number_str = "17820295895"},
    {.check_code = Nor_Vm_Check_Code, .contacts_name_str = "张三", \
        .contacts_number_str = "17820295895"},
    {.check_code = Nor_Vm_Check_Code, .contacts_name_str = "张三", \
        .contacts_number_str = "17820295895"},
    {.check_code = Nor_Vm_Check_Code, .contacts_name_str = "张三", \
        .contacts_number_str = "17820295895"},
};

void vm_contacts_ctx_falsh_test(void)
{
    for(uint8_t i = 0; i < Contacts_Max_Num; i++)
    {
        vm_contacts_ctx_falsh_save(i, \
            &vm_contacts_ctx_1[i]);
    }

    return;
}
#endif
