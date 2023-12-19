#ifndef __COMMON_STOPWATCH_H__
#define __COMMON_STOPWATCH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

#define STOPWATCH_RECORD_EN (0)

#if STOPWATCH_RECORD_EN
//*********************************************************************************//
//                                  通用秒表记录最大数                                //
//*********************************************************************************//
#define STOPWATCH_RECORD_MAX (50)
#endif

//*********************************************************************************//
//                                  通用秒表属性状态                                 //
//*********************************************************************************//
typedef enum
{
    stopwatch_state_reset = 0x00,
    stopwatch_state_pause,
    stopwatch_state_start,
}stopwatch_attribute_state_t;

//*********************************************************************************//
//                                  通用秒表属性数据                                  //
//*********************************************************************************//
typedef struct
{
    uint8_t stopwatch_minute;
	uint8_t stopwatch_second;
	uint8_t stopwatch_m_second;
}stopwatch_attribute_data_t;

//*********************************************************************************//
//                                  通用秒表参数                                     //
//*********************************************************************************//
typedef struct
{
    bool stopwatch_already_exist; //true:秒表已经存在   false:秒表不存在
    uint8_t stopwatch_record_cnt;
    stopwatch_attribute_data_t stopwatch_data;
    stopwatch_attribute_state_t stopwatch_state;
#if STOPWATCH_RECORD_EN
    stopwatch_attribute_data_t stopwatch_record_data[STOPWATCH_RECORD_MAX];
#endif
}common_stopwatch_para_t;

void common_user_stopwatch_reset(void);
void common_user_stopwatch_pause(void);
void common_user_stopwatch_resume(void);
#if STOPWATCH_RECORD_EN
void common_user_stopwatch_record(void);
#endif
void common_user_stopwatch_create(void);
void common_user_stopwatch_timeout_handle(void);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
