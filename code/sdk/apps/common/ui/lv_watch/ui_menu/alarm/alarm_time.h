#ifndef __ALARM_TIME_H__
#define __ALARM_TIME_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lv_watch.h"

void set_alarm_time_tmp(uint8_t hour, \
    uint8_t minute);
void get_alarm_time_tmp(uint8_t *hour, \
    uint8_t *minute);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
