#ifndef __REMIND_TASK_H__
#define __REMIND_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

#if 0
#define REMIND_TASK_NAME "remind_task"

enum
{
    remind_msg_alarm_monitor = 0x00,
};

void remind_task_init(void);
void remind_msg_handle(int *msg, u8 len);
int post_remind_msg(int *post_msg, u8 len);
#endif
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
