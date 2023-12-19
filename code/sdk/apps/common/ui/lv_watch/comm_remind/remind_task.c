#include "includes.h"
#include "remind_task.h"
#include "../lv_watch.h"
#include "alarm_manage.h"


static uint16_t remind_timer_id = 0;

static void remind_timerout_cb(void *priv)
{
    int remind_msg[5] = {0xff};

    /*******一秒钟去监测一下闹钟信息*******/
    remind_msg[0] = remind_msg_alarm_monitor;
    post_remind_msg(remind_msg, 1);

    return;
}

static void remind_task(void *p)
{
    printf("%s\n", __func__);

    int rev_ret;
    int rev_msg[8] = {0};

    /*注意：这里看看有没有影响到功耗*/
    if(!remind_timer_id)
        remind_timer_id = sys_timer_add(NULL, remind_timerout_cb, 950);

    while(1){
        rev_ret = os_taskq_pend(NULL, rev_msg, ARRAY_SIZE(rev_msg)); 

        if(rev_ret == OS_TASKQ)
            remind_msg_handle(rev_msg, ARRAY_SIZE(rev_msg));
    }
    
    return;
}

void remind_msg_handle(int *rev_msg, u8 len)
{
    if(!rev_msg || len == 0)
        return;

    int msg_cmd = rev_msg[0];

    switch(msg_cmd)
    {
        case remind_msg_alarm_monitor:
        {
            common_user_alarm_real_time_monitor();
        }
            break;

        case remind_msg_countdown_timeout:
        {
            common_user_countdown_timeout_handle();
        }
            break;

        case remind_msg_stopwatch_timeout:
        {
            common_user_stopwatch_timeout_handle();
        }
            break;

        default:
        {
            printf("*************ui msg not found\n");
        }
            break;
    }

    return;
}

void remind_task_init(void)
{
    int err = task_create(remind_task, NULL, REMIND_TASK_NAME);
    if(err) 
        r_printf("remind task create err:%d \n", err);

    return;
}

int post_remind_msg(int *post_msg, u8 len)
{
    int err = 0;
    int count = 0;

    if(!post_msg || len == 0)
        return -1;

__retry:
    err =  os_taskq_post_type(REMIND_TASK_NAME, post_msg[0], len - 1, &post_msg[1]);

    if (cpu_in_irq() || cpu_irq_disabled()) {
        return err;
    }

    if(err) 
    {
        if(!strcmp(os_current_task(), REMIND_TASK_NAME)) 
            return err;

        if(count > 20) 
            return -1;
        
        count++;
        os_time_dly(1);
        goto __retry;
    }

    return err;
}
