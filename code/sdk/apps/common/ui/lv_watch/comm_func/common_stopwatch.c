#include "../lv_watch.h"
#include "common_stopwatch.h"
#include "../comm_remind/remind_task.h"
#include "../poc_modem/poc_modem_cache.h"

/*
    注意：秒表进行时，系统不会进入低功耗，只会灭屏。
*/

static u16 stopwatch_timer_id = 0;
static const u32 stopwatch_timer_inv = 10;

static void common_user_stopwatch_timeout_cb(void *priv)
{
    int countdown_timeout_msg[1];
    countdown_timeout_msg[0] = \
        remind_msg_stopwatch_timeout;
    post_remind_msg(countdown_timeout_msg, 1);

    return;
}

/*********************************************************************************
                                  复位通用秒表                                    
*********************************************************************************/
void common_user_stopwatch_reset(void)
{
    uint8_t *stopwatch_record_cnt = \
        &p_ui_info_cache->common_stopwatch_para.stopwatch_record_cnt;
    *stopwatch_record_cnt = 0;

    stopwatch_attribute_data_t *stopwatch_data = \
        &p_ui_info_cache->common_stopwatch_para.stopwatch_data;
    memset(stopwatch_data, 0, sizeof(stopwatch_attribute_data_t));

    stopwatch_attribute_state_t *stopwatch_state = \
        &p_ui_info_cache->common_stopwatch_para.stopwatch_state;
    *stopwatch_state = stopwatch_state_reset;

#if STOPWATCH_RECORD_EN
    stopwatch_attribute_data_t *stopwatch_record_data = \
        p_ui_info_cache->common_stopwatch_para.stopwatch_record_data;
    memset(stopwatch_record_data, 0, sizeof(stopwatch_attribute_data_t)*STOPWATCH_RECORD_MAX);
#endif

    bool *stopwatch_already_exist = \
        &p_ui_info_cache->common_stopwatch_para.stopwatch_already_exist;
    *stopwatch_already_exist = false;

    if(stopwatch_timer_id)
        sys_hi_timer_del(stopwatch_timer_id);

    stopwatch_timer_id = 0;

    return;
}

/*********************************************************************************
                                  暂停通用秒表                                    
*********************************************************************************/
void common_user_stopwatch_pause(void)
{
    stopwatch_attribute_state_t *stopwatch_state = \
        &p_ui_info_cache->common_stopwatch_para.stopwatch_state;
    *stopwatch_state = stopwatch_state_pause;

    if(stopwatch_timer_id)
        sys_hi_timer_del(stopwatch_timer_id);

    stopwatch_timer_id = 0;

    return;
}

/*********************************************************************************
                                  恢复通用秒表                                     
*********************************************************************************/
void common_user_stopwatch_resume(void)
{
    stopwatch_attribute_state_t *stopwatch_state = \
        &p_ui_info_cache->common_stopwatch_para.stopwatch_state;
    *stopwatch_state = stopwatch_state_start;

    if(!stopwatch_timer_id)
        stopwatch_timer_id = sys_hi_timer_add(NULL, \
            common_user_stopwatch_timeout_cb, stopwatch_timer_inv);

    return;
}

#if STOPWATCH_RECORD_EN
/*********************************************************************************
                                  记录通用秒表                                     
*********************************************************************************/
void common_user_stopwatch_record(void)
{
    uint8_t *stopwatch_record_cnt = \
        &p_ui_info_cache->common_stopwatch_para.stopwatch_record_cnt;
    if(*stopwatch_record_cnt >= STOPWATCH_RECORD_MAX)
        return;

    stopwatch_attribute_data_t *stopwatch_data = \
        &p_ui_info_cache->common_stopwatch_para.stopwatch_data;

    stopwatch_attribute_data_t *stopwatch_record_data = \
        p_ui_info_cache->common_stopwatch_para.stopwatch_record_data;

    memcpy(&stopwatch_record_data[*stopwatch_record_cnt], stopwatch_data, \
        sizeof(stopwatch_attribute_data_t));

    *stopwatch_record_cnt += 1;

    return;
}
#endif

/*********************************************************************************
                                  通用秒表超时处理                               
*********************************************************************************/
void common_user_stopwatch_timeout_handle(void)
{
    stopwatch_attribute_data_t *stopwatch_data = \
        &p_ui_info_cache->common_stopwatch_para.stopwatch_data;

    uint8_t time_sec_cnt = 1000/stopwatch_timer_inv;

    stopwatch_data->stopwatch_m_second += 1;

    stopwatch_data->stopwatch_m_second %= time_sec_cnt;
    if(!(stopwatch_data->stopwatch_m_second))
    {
        stopwatch_data->stopwatch_second += 1;
        stopwatch_data->stopwatch_second %= 60;
        if(!(stopwatch_data->stopwatch_second))
        {
            stopwatch_data->stopwatch_minute += 1;
            stopwatch_data->stopwatch_minute %= 100;
            if(!(stopwatch_data->stopwatch_minute))
               stopwatch_data->stopwatch_minute = 0; 
        }     
    }

    return;
}

/*********************************************************************************
                                  创建通用秒表                                    
*********************************************************************************/
void common_user_stopwatch_create(void)
{
    bool *stopwatch_already_exist = \
        &p_ui_info_cache->common_stopwatch_para.stopwatch_already_exist;

    if(*stopwatch_already_exist) 
        return;
    
    uint8_t *stopwatch_record_cnt = \
        &p_ui_info_cache->common_stopwatch_para.stopwatch_record_cnt;
    *stopwatch_record_cnt = 0;

    stopwatch_attribute_data_t *stopwatch_data = \
        &p_ui_info_cache->common_stopwatch_para.stopwatch_data;
    memset(stopwatch_data, 0, sizeof(stopwatch_attribute_data_t));


    stopwatch_attribute_state_t *stopwatch_state = \
        &p_ui_info_cache->common_stopwatch_para.stopwatch_state;
    *stopwatch_state = stopwatch_state_start;

#if STOPWATCH_RECORD_EN
    stopwatch_attribute_data_t *stopwatch_record_data = \
        p_ui_info_cache->common_stopwatch_para.stopwatch_record_data;
    memset(stopwatch_record_data, 0, sizeof(stopwatch_attribute_data_t)*STOPWATCH_RECORD_MAX);
#endif

    if(!stopwatch_timer_id)
        stopwatch_timer_id = sys_hi_timer_add(NULL, \
            common_user_stopwatch_timeout_cb, stopwatch_timer_inv);

    *stopwatch_already_exist = true;

    return;
}
