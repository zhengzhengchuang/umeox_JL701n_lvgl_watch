#include "common_cmd.h"
#include "../lv_watch.h"
#include "common_send.h"
#include "common_parse.h"
#include "common_le_set.h"

static bool umeox_common_le_crc(uint8_t *rev_buf, \
    uint16_t rev_len)
{ 
    uint32_t verify_crc = 0;
    uint8_t verify_crc_low8bit = 0;

    for(uint8_t i = 0; i < rev_len - 1; i++)
        verify_crc += rev_buf[i];

    verify_crc_low8bit = (uint8_t)(verify_crc&(0xff));

    if(verify_crc_low8bit == rev_buf[rev_len - 1])
        return true;

    return false;
}

void umeox_common_le_cmd_parse(uint8_t *rev_buf, \
    uint16_t rev_len)
{
    le_cmd_gather_t rev_cmd = rev_buf[0];

    // if(!umeox_common_le_crc(rev_buf, rev_len))
    // {
    //     umeox_common_le_resp_fail(rev_buf, rev_len);
    //     return;
    // }   

    switch(rev_cmd)
    {
        case le_cmd_get_dev_info:
            printf("le_cmd_get_dev_info\n");
            break;

        case le_cmd_get_dev_support_func:
            printf("le_cmd_get_dev_support_func\n");
            break;

        case le_cmd_get_dev_func_state:
            printf("le_cmd_get_dev_func_state\n");
            break;

        case le_cmd_set_dev_time:
            common_le_set_utc_time(&rev_buf[1], rev_len - 2);
            break;
        
        default:
            break;
    }

    //umeox_common_le_resp_success(rev_buf, rev_len);

    return;
}
