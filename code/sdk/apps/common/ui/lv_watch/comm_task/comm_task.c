#include "includes.h"
#include "../lv_watch.h"

static bool minute_handle = true;
static uint16_t minute_timer_id = 0;

static void minute_timerout_cb(void *priv)
{
    struct sys_time \
        utc_time;
    get_utc_time(&utc_time);
    if(utc_time.sec >= 58)
        minute_handle = true;
    if(utc_time.sec != 0)
        return;
    if(!minute_handle)
        return;

    minute_handle = false;

    int minute_handle_msg[1];
    minute_handle_msg[0] = \
        comm_msg_minute_handle;
    post_comm_task_msg(\
        minute_handle_msg, 1);

    return;
}

static void comm_task_handle(void *p)
{
    int rev_ret;
    int rev_msg[8] = {0};

    /*注意：这里看看有没有影响到功耗*/
    if(!minute_timer_id)
        minute_timer_id = sys_s_hi_timer_add(NULL, \
            minute_timerout_cb, 500);

    while(1)
    {
        rev_ret = \
            os_taskq_pend(NULL, rev_msg, \
                ARRAY_SIZE(rev_msg)); 

        if(rev_ret == OS_TASKQ)
            comm_task_msg_handle(rev_msg, \
                ARRAY_SIZE(rev_msg));
    }
    
    return;
}

void comm_task_msg_handle(int *rev_msg, u8 len)
{
    if(!rev_msg || len == 0)
        return;

    int msg_cmd = rev_msg[0];

    switch(msg_cmd)
    {
        case comm_msg_minute_handle:
            watch_minute_task_msg_handle();
            break;

        case comm_msg_countdown_timeout:
            common_user_countdown_timeout_handle();
            break;

        case comm_msg_stopwatch_timeout:
            common_user_stopwatch_timeout_handle();
            break;

        default:
            printf("*************ui msg not found\n");
            break;
    }

    return;
}

void comm_task_create(void)
{
    int err = task_create(comm_task_handle, \
        NULL, Comm_Task_Name);
    if(err) 
        r_printf("comm task create err!!!!!!!:%d \n", err);

    return;
}

int post_comm_task_msg(int *post_msg, u8 len)
{
    int err = 0;
    int count = 0;

    if(!post_msg || len == 0)
        return -1;

__retry:
    err = os_taskq_post_type(Comm_Task_Name, \
        post_msg[0], len - 1, &post_msg[1]);

    if(cpu_in_irq() || cpu_irq_disabled())
        return err;

    if(err) 
    {
        if(!strcmp(os_current_task(), Comm_Task_Name)) 
            return err;

        if(count > 20)
            return -1;
        
        count++;
        os_time_dly(1);
        goto __retry;
    }

    return err;
}
