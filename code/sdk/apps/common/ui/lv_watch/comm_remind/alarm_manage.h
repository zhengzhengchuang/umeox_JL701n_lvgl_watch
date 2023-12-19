#ifndef __ALARM_MANAGE_H__
#define __ALARM_MANAGE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

#define No_Alarm_Info (0xffffffff)

//*********************************************************************************//
//                                  闹钟最大个数                                     //
//*********************************************************************************//
#define ALARM_MAX_NUM (5)

//*********************************************************************************//
//                                  闹钟信息位域                                     //
//*********************************************************************************//
typedef struct 
{
    uint32_t alarm_id       :4;
	
	uint32_t alarm_hour     :5;
	uint32_t alarm_minute   :6;
	
	uint32_t alarm_enable   :1;
	
	uint32_t alarm_repeat   :7;

	uint32_t alarm_reserved :9;
}alarm_info_bit_field_t;

//*********************************************************************************//
//                                  闹钟信息共同体                                   //
//*********************************************************************************//
typedef union
{
    uint32_t info;
    alarm_info_bit_field_t bit_field;
}alarm_info_union_t;

//*********************************************************************************//
//                                  闹钟管理参数                                     //
//*********************************************************************************//
typedef struct
{
    uint8_t alarm_num;
    alarm_info_union_t alarm_info[ALARM_MAX_NUM];
}alarm_manage_para_t;

void common_user_alarm_delete_all(void);
void common_user_alarm_add(uint32_t alarm_union);
void common_user_alarm_delete_one(uint8_t alarm_id);
uint32_t common_user_alarm_read_info(uint8_t alarm_id);
void common_user_alarm_time_modify(uint32_t alarm_union);
void common_user_alarm_repeat_modify(uint32_t alarm_union);
void common_user_alarm_enable_modify(uint32_t alarm_union);

void common_user_alarm_real_time_monitor(void);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
