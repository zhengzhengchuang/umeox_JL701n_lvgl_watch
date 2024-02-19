#include "nor_vm_main.h"

static vm_message_ctx_t vm_message_ctx;
static const nor_vm_type_t nor_vm_type = \
    nor_vm_type_message;

/*********************************************************************************
                              清除                                         
*********************************************************************************/
void vm_message_ctx_clear(void)
{
    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);

    if(!nor_vm_file)
        return;

    uint8_t message_num = \
        vm_message_item_num();

    if(!message_num) 
        return;

    while(message_num)
    {
        flash_common_delete_by_index(\
            nor_vm_file, 0);

        message_num--;
    }
    
    return;
}

/*********************************************************************************
                              存储数量                                         
*********************************************************************************/
uint8_t vm_message_item_num(void)
{
    uint8_t message_num = 0;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);

    if(!nor_vm_file)
        return message_num;

    message_num = \
        flash_common_get_total(nor_vm_file);

    if(message_num > Message_Max_Num)
        message_num = Message_Max_Num;

    return message_num;
}

/*********************************************************************************
                              获取内容                                        
*********************************************************************************/
bool vm_message_ctx_by_idx(uint8_t idx, vm_message_ctx_t *p)
{
    uint8_t message_num = \
        vm_message_item_num();

    if(idx >= message_num)
        return false;
    
    if(!p) return false;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);
    int message_ctx_len = \
        sizeof(vm_message_ctx_t);
    
    if(!nor_vm_file)
        return false;

    idx = (message_num - 1) - \
        idx;
    
    memset(&vm_message_ctx, 0, \
        message_ctx_len);
    flash_common_read_by_index(nor_vm_file, idx, 0, \
        message_ctx_len, (uint8_t *)&vm_message_ctx);

    if(vm_message_ctx.check_code != \
        Nor_Vm_Check_Code)
        return false;

    memcpy(p, &vm_message_ctx, \
        message_ctx_len);

    return true;
}

/*********************************************************************************
                              内容存储                                   
*********************************************************************************/
void vm_message_ctx_falsh_save(vm_message_ctx_t *p)
{
    if(!p) return;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);
    int message_ctx_len = \
        sizeof(vm_message_ctx_t);

    if(!nor_vm_file)
        return;

    uint8_t message_num = \
        vm_message_item_num();
    
    if(message_num >= Message_Max_Num)
        flash_common_delete_by_index(\
            nor_vm_file, 0);

    flash_common_write_file(nor_vm_file, \
        0, message_ctx_len, (uint8_t *)p);

    return;
}
