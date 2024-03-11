#ifndef __NOR_VM_MESSAGE_H__
#define __NOR_VM_MESSAGE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

/*********************************************************************************
                                  信息最大个数                                  
*********************************************************************************/
#define Message_Max_Num (10)

/*********************************************************************************
                                  信息内容长度                                  
*********************************************************************************/
#define Message_Content_Len (240)


/*********************************************************************************
                                  信息类型(不要改枚举的顺序)                                 
*********************************************************************************/
enum
{
    message_type_facebook = 0x00,
    message_type_vkontakte,
    message_type_instagram,
    message_type_linkedin,
    message_type_tiktok,
    message_type_whatsapp,
    message_type_wechat,
    message_type_snapchat,
    message_type_telegram,
    message_type_twitter,
    message_type_skype,
    message_type_line,
    message_type_gmail,
    message_type_sms,

    /******区别于消息通知*******/
    message_type_phone,

    message_type_unknown,
};
typedef uint8_t message_type_t;

/*********************************************************************************
                                  信息内容                                       
*********************************************************************************/
typedef struct
{
    uint16_t check_code; 	

	message_type_t \
        message_type;
    char message_content_str[\
        Message_Content_Len];
    
    struct sys_time message_time;
}vm_message_ctx_t;

/*********************************************************************************
                                  信息接口                                       
*********************************************************************************/
void vm_message_ctx_clear(void);
uint8_t vm_message_item_num(void);
void vm_message_delete_by_index(uint8_t index);
void vm_message_ctx_falsh_save(vm_message_ctx_t *p);
bool vm_message_ctx_by_idx(uint8_t idx, vm_message_ctx_t *p);
#ifdef __cplusplus
}
#endif

#endif
