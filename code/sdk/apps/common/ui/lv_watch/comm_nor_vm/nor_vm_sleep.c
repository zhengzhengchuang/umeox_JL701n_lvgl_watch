#include "nor_vm_main.h"
#include "../lv_watch.h"

vm_sleep_ctx_t w_sleep;
vm_sleep_ctx_t r_sleep;
static const nor_vm_type_t nor_vm_type = \
    nor_vm_type_sleep;

/*********************************************************************************
                              清除                                         
*********************************************************************************/
void VmSleepCtxClear(void)
{
    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);

    if(!nor_vm_file)
        return;

    uint8_t sleep_num = \
        VmSleepItemNum();

    while(sleep_num)
    {
        flash_common_delete_by_index(\
            nor_vm_file, 0);

        sleep_num--;
    }
    
    return;
}

/*********************************************************************************
                              存储数量                                         
*********************************************************************************/
uint8_t VmSleepItemNum(void)
{
    uint8_t sleep_num = 0;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);

    if(!nor_vm_file)
        return sleep_num;

    sleep_num = \
        flash_common_get_total(nor_vm_file);

    if(sleep_num > Sleep_Max_Days)
        sleep_num = Sleep_Max_Days;

    return sleep_num;
}

/*********************************************************************************
                              获取内容                                        
*********************************************************************************/
bool VmSleepCtxByIdx(uint8_t idx)
{
    uint8_t sleep_num = \
        VmSleepItemNum();
    if(sleep_num == 0)
        return false;

    if(idx >= sleep_num)
        return false;
    
    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);
    int ctx_len = \
        sizeof(vm_sleep_ctx_t);
    
    if(!nor_vm_file)
        return false;

    memset(&r_sleep, 0, ctx_len);
    flash_common_read_by_index(nor_vm_file, idx, 0, \
        ctx_len, (uint8_t *)&r_sleep);

    if(r_sleep.check_code != \
        Nor_Vm_Check_Code)
        return false;

    return true;
}

/*********************************************************************************
                              内容存储                                   
*********************************************************************************/
void VmSleepCtxFlashSave(void *p)
{
#if !Vm_Debug_En
    /*如果设备不绑定、不允许存储任何数据*/
    int DevBondFlag = \
        GetVmParaCacheByLabel(\
            vm_label_dev_bond);
    if(!DevBondFlag)
        return;
#endif

    if(!p) return;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);
    int ctx_len = \
        sizeof(vm_sleep_ctx_t);

    if(!nor_vm_file)
        return;

    uint8_t sleep_num = \
        VmSleepItemNum();

    printf("sleep_num = %d\n", \
        sleep_num);
    
    if(sleep_num >= Sleep_Max_Days)
        flash_common_delete_by_index(\
            nor_vm_file, 0);

    flash_common_write_file(nor_vm_file, 0, \
        ctx_len, (u8 *)p);

    return;
}

#if 0
static const vm_sleep_sec_ctx_t vm_ctx_test[9] = {
    {
        .state = sl_light_sleep, \
        .ss_time.year = 2024, .ss_time.month = 4, .ss_time.day = 20, \
        .ss_time.hour = 22, .ss_time.min = 0, .ss_time.sec = 0, \
        .se_time.year = 2024, .se_time.month = 4, .se_time.day = 20, \
        .se_time.hour = 22, .se_time.min = 30, .se_time.sec = 0
    },

    {
        .state = sl_deep_sleep, \
        .ss_time.year = 2024, .ss_time.month = 4, .ss_time.day = 20, \
        .ss_time.hour = 22, .ss_time.min = 30, .ss_time.sec = 0, \
        .se_time.year = 2024, .se_time.month = 4, .se_time.day = 20, \
        .se_time.hour = 23, .se_time.min = 0, .se_time.sec = 0
    },

    {
        .state = sl_light_sleep, \
        .ss_time.year = 2024, .ss_time.month = 4, .ss_time.day = 20, \
        .ss_time.hour = 23, .ss_time.min = 0, .ss_time.sec = 0, \
        .se_time.year = 2024, .se_time.month = 4, .se_time.day = 20, \
        .se_time.hour = 23, .se_time.min = 30, .se_time.sec = 0
    },

    {
        .state = sl_rem_sleep, \
        .ss_time.year = 2024, .ss_time.month = 4, .ss_time.day = 20, \
        .ss_time.hour = 23, .ss_time.min = 30, .ss_time.sec = 0, \
        .se_time.year = 2024, .se_time.month = 4, .se_time.day = 20, \
        .se_time.hour = 23, .se_time.min = 35, .se_time.sec = 0
    },

    {
        .state = sl_wake_up, \
        .ss_time.year = 2024, .ss_time.month = 4, .ss_time.day = 20, \
        .ss_time.hour = 23, .ss_time.min = 35, .ss_time.sec = 0, \
        .se_time.year = 2024, .se_time.month = 4, .se_time.day = 20, \
        .se_time.hour = 23, .se_time.min = 55, .se_time.sec = 0
    },

    {
        .state = sl_light_sleep, \
        .ss_time.year = 2024, .ss_time.month = 4, .ss_time.day = 20, \
        .ss_time.hour = 23, .ss_time.min = 55, .ss_time.sec = 0, \
        .se_time.year = 2024, .se_time.month = 4, .se_time.day = 21, \
        .se_time.hour = 3, .se_time.min = 40, .se_time.sec = 0
    },

    {
        .state = sl_deep_sleep, \
        .ss_time.year = 2024, .ss_time.month = 4, .ss_time.day = 21, \
        .ss_time.hour = 3, .ss_time.min = 40, .ss_time.sec = 0, \
        .se_time.year = 2024, .se_time.month = 4, .se_time.day = 21, \
        .se_time.hour = 5, .se_time.min = 30, .se_time.sec = 0
    },

    {
        .state = sl_light_sleep, \
        .ss_time.year = 2024, .ss_time.month = 4, .ss_time.day = 21, \
        .ss_time.hour = 5, .ss_time.min = 30, .ss_time.sec = 0, \
        .se_time.year = 2024, .se_time.month = 4, .se_time.day = 21, \
        .se_time.hour = 7, .se_time.min = 40, .se_time.sec = 0
    },

    {
        .state = sl_wake_up, \
        .ss_time.year = 2024, .ss_time.month = 4, .ss_time.day = 21, \
        .ss_time.hour = 7, .ss_time.min = 40, .ss_time.sec = 0, \
        .se_time.year = 2024, .se_time.month = 4, .se_time.day = 21, \
        .se_time.hour = 8, .se_time.min = 0, .se_time.sec = 0
    },
};

void vm_sleep_data_test(void)
{
    memset(&w_sleep, 0, \
        sizeof(vm_sleep_ctx_t));

    w_sleep.check_code = \
        Nor_Vm_Check_Code;
    w_sleep.CurSecNum = \
        9;

    w_sleep.time.year = 2024;
    w_sleep.time.month = 4;
    w_sleep.time.day = 20;
    w_sleep.time.hour = 18;
    w_sleep.time.min = 0;
    w_sleep.time.sec = 0;

    for(uint8_t i = 0; i < w_sleep.CurSecNum; i++)
        memcpy(&w_sleep.vm_ctx[i], \
            &vm_ctx_test[i], sizeof(vm_sleep_sec_ctx_t));

    VmSleepCtxFlashSave(&w_sleep);

    return;
}
#endif
