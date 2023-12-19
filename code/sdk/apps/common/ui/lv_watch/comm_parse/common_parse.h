#ifndef __COMMON_PARSE_H__
#define __COMMON_PARSE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

void umeox_common_le_cmd_parse(uint8_t *rev_buf, \
    uint16_t rev_len);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
