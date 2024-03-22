#include "../lv_watch.h"

void watch_minute_task_msg_handle(void)
{
    /*********一分钟处理事件*********/
    common_user_alarm_real_time_monitor();

    return;
}