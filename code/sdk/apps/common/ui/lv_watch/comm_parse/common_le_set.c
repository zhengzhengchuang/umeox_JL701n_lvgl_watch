#include "../lv_watch.h"
#include "common_le_set.h"

void common_le_set_watch_time(uint8_t *para_buf, \
    uint16_t para_len)
{
    uint8_t idx = 0;

    uint8_t time_zone = para_buf[idx++];
    set_vm_para_cache_with_label(vm_label_time_zone, \
        time_zone);

    uint8_t time_format = para_buf[idx++];
    set_vm_para_cache_with_label(vm_label_time_format, \
        time_format);

    struct sys_time utc_time;
    utc_time.year = para_buf[idx++] + 2000;
    utc_time.month = para_buf[idx++];
    utc_time.day = para_buf[idx++];
    utc_time.hour = para_buf[idx++];
    utc_time.min = para_buf[idx++];
    utc_time.sec = para_buf[idx++];
    ui_set_sys_time(&utc_time);

    return;
}



