#ifndef __COMMON_COUNTDOWN_H__
#define __COMMON_COUNTDOWN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

/*********************************************************************************
                                  通用倒计时属性状态                                
*********************************************************************************/
typedef enum
{
    countdown_state_reset = 0x00,
    countdown_state_puase,
    countdown_state_start,
    countdown_state_over,
}countdown_attribute_state_t;

/*********************************************************************************
                                  通用倒计时属性数据                                
*********************************************************************************/
typedef struct
{
    uint8_t countdown_per; //倒计时进行中百分比 最大范围0~100。
    uint32_t countdown_cur_cnt;
    uint32_t countdown_total_cnt;
    uint32_t countdown_over_total_cnt;
}countdown_attribute_data_t;

/*********************************************************************************
                                  通用倒计时参数                                   
*********************************************************************************/
typedef struct
{
    bool countdown_already_exist; //true:倒计时已经存在   false:倒计时不存在
    countdown_attribute_data_t countdown_data;
    countdown_attribute_state_t countdown_state;
}common_countdown_para_t;

void common_user_countdown_reset(void);
void common_user_countdown_pause(void);
void common_user_countdown_resume(void);
void common_user_countdown_timeout_handle(void);
void common_user_countdown_create(uint32_t cnt);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
