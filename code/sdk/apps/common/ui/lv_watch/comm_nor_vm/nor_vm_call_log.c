#include "nor_vm_main.h"

static vm_call_log_ctx_t vm_call_log_ctx;
static const nor_vm_type_t nor_vm_type = \
    nor_vm_type_call_log;

/*********************************************************************************
                              清除                                         
*********************************************************************************/
void vm_call_log_ctx_clear(void)
{
    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);

    if(!nor_vm_file)
        return;

    uint8_t call_log_num = \
        vm_call_log_item_num();

    if(!call_log_num) 
        return;

    while(call_log_num)
    {
        flash_common_delete_by_index(\
            nor_vm_file, 0);

        call_log_num--;
    }
    
    return;
}

/*********************************************************************************
                              存储数量                                         
*********************************************************************************/
uint8_t vm_call_log_item_num(void)
{
    uint8_t call_log_num = 0;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);

    if(!nor_vm_file)
        return call_log_num;

    call_log_num = \
        flash_common_get_total(nor_vm_file);

    if(call_log_num > Call_log_Max_Num)
        call_log_num = Call_log_Max_Num;

    return call_log_num;
}

/*********************************************************************************
                              获取内容                                        
*********************************************************************************/
bool vm_call_log_ctx_by_idx(uint8_t idx, vm_call_log_ctx_t *p)
{
    uint8_t call_log_num = \
        vm_call_log_item_num();

    if(idx >= call_log_num)
        return false;
    
    if(!p) return false;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);
    int call_log_ctx_len = \
        sizeof(vm_call_log_ctx_t);
    
    if(!nor_vm_file)
        return false;

    idx = (call_log_num - 1) - \
        idx;
    
    memset(&vm_call_log_ctx, 0, \
        call_log_ctx_len);
    flash_common_read_by_index(nor_vm_file, idx, 0, \
        call_log_ctx_len, (uint8_t *)&vm_call_log_ctx);

    if(vm_call_log_ctx.check_code != \
        Nor_Vm_Check_Code)
        return false;

    memcpy(p, &vm_call_log_ctx, \
        call_log_ctx_len);

    return true;
}

/*********************************************************************************
                              内容存储                                   
*********************************************************************************/
void vm_call_log_ctx_falsh_save(vm_call_log_ctx_t *p)
{
    if(!p) return;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);
    int call_log_ctx_len = \
        sizeof(vm_call_log_ctx_t);

    if(!nor_vm_file)
        return;

    uint8_t call_log_num = \
        vm_call_log_item_num();

    printf("call_log_num = %d\n", \
        call_log_num);
    
    if(call_log_num >= Call_log_Max_Num)
        flash_common_delete_by_index(\
            nor_vm_file, 0);

    int file_id = \
        flash_common_open_id(nor_vm_file, 0, \
            call_log_ctx_len);
    if(!file_id) return;

    flash_common_write_packet(nor_vm_file, file_id, \
        call_log_ctx_len, (uint8_t *)p);

    return;
}
