#include "../lv_watch.h"
#include "common_countdown.h"
#include "../comm_task/comm_task.h"
#include "../poc_modem/poc_modem_cache.h"

/*
    注意：倒计时进行时，系统不会进入低功耗，只会灭屏。
*/

static u16 countdown_timer_id = 0;
static u32 countdown_timeout_cnt = 0;
static const s16 countdown_per_max = 10000;
static const u32 countdown_timer_inv = 100;

static void common_user_countdown_timeout_cb(void *priv)
{
    int countdown_timeout_msg[1];
    countdown_timeout_msg[0] = \
        comm_msg_countdown_timeout;
    post_comm_handle_msg(countdown_timeout_msg, 1);

    return;
}

/*********************************************************************************
                                  倒计时比例最大                               
*********************************************************************************/
int16_t get_countdown_per_max(void)
{
    return \
        countdown_per_max;
}

/*********************************************************************************
                                  复位通用倒计时                                   
*********************************************************************************/
void common_user_countdown_reset(void)
{
    countdown_attribute_data_t *countdown_data = \
        &p_ui_info_cache->common_countdown_para.countdown_data;
    memset(countdown_data, 0, sizeof(countdown_attribute_data_t));

    countdown_attribute_state_t *countdown_state = \
        &p_ui_info_cache->common_countdown_para.countdown_state;
    *countdown_state = countdown_state_reset;

    bool *countdown_already_exist = \
        &p_ui_info_cache->common_countdown_para.countdown_already_exist;
    *countdown_already_exist = false;

    if(countdown_timer_id)
        sys_hi_timer_del(countdown_timer_id);
    countdown_timer_id = 0;

    countdown_timeout_cnt = 0;

    return;
}

/*********************************************************************************
                                  暂停通用倒计时                                  
*********************************************************************************/
void common_user_countdown_pause(void)
{
    countdown_attribute_state_t *countdown_state = \
        &p_ui_info_cache->common_countdown_para.countdown_state;
    *countdown_state = countdown_state_puase;

    if(countdown_timer_id)
        sys_hi_timer_del(countdown_timer_id);

    countdown_timer_id = 0;

    return;
}


/*********************************************************************************
                                  恢复通用倒计时                                  
*********************************************************************************/
void common_user_countdown_resume(void)
{
    countdown_attribute_state_t *countdown_state = \
        &p_ui_info_cache->common_countdown_para.countdown_state;
    *countdown_state = countdown_state_start;

    if(!countdown_timer_id)
        countdown_timer_id = sys_hi_timer_add(NULL, \
            common_user_countdown_timeout_cb, countdown_timer_inv);

    return;
}

/*********************************************************************************
                                  通用倒计时超时处理                               
*********************************************************************************/
void common_user_countdown_timeout_handle(void)
{
    countdown_attribute_data_t *countdown_data = \
        &p_ui_info_cache->common_countdown_para.countdown_data;

    uint8_t time_sec_cnt = \
        1000/countdown_timer_inv;

    countdown_timeout_cnt += 1;
    uint8_t second_cnt = \
        countdown_timeout_cnt%time_sec_cnt;
    if(!second_cnt)
    {
        if(countdown_data->countdown_cur_cnt)
        {
            countdown_data->countdown_cur_cnt -= 1;

            if(!(countdown_data->countdown_cur_cnt))
            {
                countdown_attribute_state_t *countdown_state = \
                    &p_ui_info_cache->common_countdown_para.countdown_state;
                *countdown_state = countdown_state_over;

                //马达震动

                //跳转页面
                ui_menu_jump(ui_act_id_countdown_over);
            }
        }else
            countdown_data->countdown_over_total_cnt += 1;
    }

    if(countdown_data->countdown_cur_cnt)
    {
        uint32_t per_timeout_cnt = \
            (countdown_data->countdown_total_cnt*time_sec_cnt) - \
                countdown_timeout_cnt;

        countdown_data->countdown_per = \
            (per_timeout_cnt*countdown_per_max)/ \
                (countdown_data->countdown_total_cnt*time_sec_cnt);
        if(countdown_data->countdown_per > \
            countdown_per_max)
            countdown_data->countdown_per = \
                countdown_per_max;
        if(countdown_data->countdown_per < 0)
            countdown_data->countdown_per = 0;
    }

    return;
}

/*********************************************************************************
                                  创建通用倒计时                                   
*********************************************************************************/
void common_user_countdown_create(uint32_t cnt)
{
    bool *countdown_already_exist = \
        &p_ui_info_cache->common_countdown_para.countdown_already_exist;

    if(*countdown_already_exist) 
        return;

    if(!cnt) return;

    countdown_timeout_cnt = 0;

    countdown_attribute_data_t *countdown_data = \
        &p_ui_info_cache->common_countdown_para.countdown_data;
    countdown_data->countdown_per = \
        countdown_per_max;
    countdown_data->countdown_cur_cnt = cnt;
    countdown_data->countdown_total_cnt = cnt;
    countdown_data->countdown_over_total_cnt = 0;
    
    
    countdown_attribute_state_t *countdown_state = \
        &p_ui_info_cache->common_countdown_para.countdown_state;
    *countdown_state = countdown_state_start;

    if(!countdown_timer_id)
        countdown_timer_id = sys_hi_timer_add(NULL, \
            common_user_countdown_timeout_cb, countdown_timer_inv);

    *countdown_already_exist = true;

    return;
}
