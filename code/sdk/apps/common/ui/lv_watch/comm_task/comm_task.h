#ifndef __COMM_TASK_H__
#define __COMM_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

#define SYS_COMM_TASK_NAME \
    "comm_handle_task"

enum
{
    comm_msg_alarm_monitor = 0x00,
    comm_msg_countdown_timeout,
    comm_msg_stopwatch_timeout,
};

void comm_handle_task_init(void);
void comm_task_msg_handle(int *msg, u8 len);
int post_comm_handle_msg(int *post_msg, u8 len);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
