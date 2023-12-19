#include "common_rev.h"
#include "common_cmd.h"
#include "../lv_watch.h"
#include "common_parse.h"

//*********************************************************************************//
//                                  注册用户接收接口                                 //
//*********************************************************************************//
void umeox_common_le_rev_cb(void *priv, uint8_t *rev_buf, \
    uint16_t rev_len)
{
    if(rev_buf == NULL || rev_len == 0)
        return;

    if(rev_len > Le_Cmd_Max_Len)
        rev_len = Le_Cmd_Max_Len;

    umeox_common_le_cmd_parse(rev_buf, rev_len);

    return;
}

