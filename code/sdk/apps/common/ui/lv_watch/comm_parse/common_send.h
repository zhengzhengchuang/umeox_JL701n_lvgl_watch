#ifndef __COMMON_SEND_H__
#define __COMMON_SEND_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

void umeox_common_le_resp_fail(uint8_t *notify_buf, \
    uint16_t notify_len);
void umeox_common_le_resp_success(uint8_t *notify_buf, \
    uint16_t notify_len);
bool umeox_common_le_notify_data(uint8_t *notify_buf, \
    uint16_t notify_len);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
