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
                              通过index删除指定信息                                         
*********************************************************************************/
void vm_message_delete_by_index(uint8_t index)
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

    int file_id = \
        flash_common_open_id(nor_vm_file, 0, \
            message_ctx_len);
    if(!file_id) return;

    flash_common_write_packet(nor_vm_file, file_id, \
        message_ctx_len, (uint8_t *)p);

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
        vm_message_ctx_falsh_save(\
            &message_ctx_test[i]); 
    }
}
#endif
