#include "nor_vm_main.h"

vm_message_ctx_t w_message;
vm_message_ctx_t r_message;
static const nor_vm_type_t nor_vm_type = \
    nor_vm_type_message;

/*********************************************************************************
                              清除                                         
*********************************************************************************/
void VmMessageCtxClear(void)
{
    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);

    if(!nor_vm_file)
        return;

    uint8_t num = \
        VmMessageItemNum();

    while(num)
    {
        flash_common_delete_by_index(\
            nor_vm_file, 0);

        num--;
    }
    
    return;
}

/*********************************************************************************
                              通过index删除指定信息                                         
*********************************************************************************/
void VmMessageDelByIdx(uint8_t index)
{
    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);

    if(!nor_vm_file)
        return;

    flash_common_delete_by_index(\
        nor_vm_file, index);

    return;
}

/*********************************************************************************
                              存储数量                                         
*********************************************************************************/
uint8_t VmMessageItemNum(void)
{
    uint8_t num = 0;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);

    if(!nor_vm_file)
        return num;

    num = flash_common_get_total(nor_vm_file);

    if(num > Message_Max_Num)
        num = Message_Max_Num;

    return num;
}

/*********************************************************************************
                              获取内容                                        
*********************************************************************************/
bool VmMessageCtxByIdx(uint8_t idx)
{
    uint8_t num = \
        VmMessageItemNum();

    if(idx >= num)
        return false;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);
    int ctx_len = \
        sizeof(vm_message_ctx_t);
    
    if(!nor_vm_file)
        return false;

    idx = (num - 1) - idx;
    
    memset(&r_message, 0, ctx_len);
    flash_common_read_by_index(nor_vm_file, idx, 0, \
        ctx_len, (uint8_t *)&r_message);

    if(r_message.check_code != \
        Nor_Vm_Check_Code)
        return false;

    return true;
}

/*********************************************************************************
                              内容存储                                   
*********************************************************************************/
void VmMessageCtxFlashSave(void *p)
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
        sizeof(vm_message_ctx_t);

    if(!nor_vm_file)
        return;

    uint8_t num = \
        VmMessageItemNum();
    
    if(num >= Message_Max_Num)
        flash_common_delete_by_index(\
            nor_vm_file, 0);

    flash_common_write_file(nor_vm_file, 0, \
        ctx_len, (uint8_t *)p);

    return;
}

#if 0
vm_message_ctx_t message_ctx_test[Message_Max_Num] = {
    [0] = {
        .check_code = Nor_Vm_Check_Code, .message_type = message_type_facebook, \
        .message_content_str = "dhakjd", \
        .message_time = {.year = 2024, .month = 3, .day = 4, .hour = 11, .min = 17},
    },

    [1] = {
        .check_code = Nor_Vm_Check_Code, .message_type = message_type_vkontakte, \
        .message_content_str = "dhakjd回调函数对", \
        .message_time = {.year = 2024, .month = 3, .day = 4, .hour = 11, .min = 18},
    },

    [2] = {
        .check_code = Nor_Vm_Check_Code, .message_type = message_type_instagram, \
        .message_content_str = "dhakjd回调函数对加沙的就看大海上的贷记卡还", \
        .message_time = {.year = 2024, .month = 3, .day = 4, .hour = 11, .min = 19},
    },

    [3] = {
        .check_code = Nor_Vm_Check_Code, .message_type = message_type_linkedin, \
        .message_content_str = "dhakjd回调函数对加沙的就看大海上的贷记卡", \
        .message_time = {.year = 2024, .month = 3, .day = 4, .hour = 11, .min = 20},
    },

    [4] = {
        .check_code = Nor_Vm_Check_Code, .message_type = message_type_tiktok, \
        .message_content_str = "dhakjd回调函数对加沙的就看大海上的贷记卡", \
        .message_time = {.year = 2024, .month = 3, .day = 4, .hour = 11, .min = 21},
    },

    [5] = {
        .check_code = Nor_Vm_Check_Code, .message_type = message_type_whatsapp, \
        .message_content_str = "dhakjd回调函数对加沙的就看大海上的贷记卡", \
        .message_time = {.year = 2024, .month = 3, .day = 4, .hour = 11, .min = 22},
    },

    [6] = {
        .check_code = Nor_Vm_Check_Code, .message_type = message_type_wechat, \
        .message_content_str = "回调函数对加沙的就看大海上的贷函数对加沙的就看大海上的贷大海上的贷回调函数对加沙的就看大海上的贷函数对加沙的就看大海上的贷大海上的贷", \
        .message_time = {.year = 2024, .month = 3, .day = 4, .hour = 11, .min = 23},
    },

    [7] = {
        .check_code = Nor_Vm_Check_Code, .message_type = message_type_snapchat, \
        .message_content_str = "dhakjdمرحبا海上的贷记卡", \
        .message_time = {.year = 2024, .month = 3, .day = 4, .hour = 11, .min = 24},
    },

    [8] = {
        .check_code = Nor_Vm_Check_Code, .message_type = message_type_telegram, \
        .message_content_str = "dhakjd回调函数مرحبا", \
        .message_time = {.year = 2024, .month = 3, .day = 4, .hour = 11, .min = 25},
    },

    [9] = {
        .check_code = Nor_Vm_Check_Code, .message_type = message_type_twitter, \
        .message_content_str = "dhakjdمرحبا", \
        .message_time = {.year = 2024, .month = 3, .day = 4, .hour = 11, .min = 26},
    },
};

void vm_message_ctx_falsh_save_test(void)
{
    for(uint8_t i = 0; i < Message_Max_Num; i++)
    {
        VmMessageCtxFlashSave(\
            &message_ctx_test[i]); 
    }
}
#endif
