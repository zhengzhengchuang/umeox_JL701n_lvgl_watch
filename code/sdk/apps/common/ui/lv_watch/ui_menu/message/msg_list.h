#ifndef __MSG_LIST_H__
#define __MSG_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lv_watch.h"

extern vm_message_ctx_t ui_message_ctx;

uint8_t get_msg_detail_query_id(void);
void set_msg_detail_query_id(uint8_t id);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
