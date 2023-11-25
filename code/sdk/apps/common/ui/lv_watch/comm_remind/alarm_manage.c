#include "../lv_watch.h"
#include "alarm_manage.h"
#include "../poc_modem/poc_modem_cache.h"
#include "../../../../watch/include/task_manager/rtc/alarm.h"

#if USER_ALARM_EN

static const uint32_t no_alarm_info = 0xffffffff;

uint32_t common_user_alarm_read_info(uint8_t alarm_id)
{
    uint8_t *alarm_num = \
        &p_ui_info_cache->alarm_manage_para.alarm_num;

    alarm_info_union_t *alarm_info = \
        p_ui_info_cache->alarm_manage_para.alarm_info;

    if(alarm_id >= *alarm_num)
        return no_alarm_info;

    return alarm_info[alarm_id].info;
}

void common_user_alarm_add(uint32_t alarm_union)
{
    uint8_t alarm_offset = 0;

    uint8_t *alarm_num = \
        &p_ui_info_cache->alarm_manage_para.alarm_num;

    alarm_info_union_t *alarm_info = \
        p_ui_info_cache->alarm_manage_para.alarm_info;

    if(*alarm_num >= ALARM_MAX_NUM)
        return;

    alarm_info[*alarm_num].info = no_alarm_info;

    alarm_info[*alarm_num].bit_field.alarm_id = \
        (alarm_union >> alarm_offset) & 0xf;

    alarm_offset += 4;
    alarm_info[*alarm_num].bit_field.alarm_hour = \
        (alarm_union >> alarm_offset) & 0x1f;

    alarm_offset += 5;
    alarm_info[*alarm_num].bit_field.alarm_minute = \
        (alarm_union >> alarm_offset) & 0x3f;

    alarm_offset += 6;
    alarm_info[*alarm_num].bit_field.alarm_enable = \
        (alarm_union >> alarm_offset) & 0x1;

    alarm_offset += 1;
    alarm_info[*alarm_num].bit_field.alarm_repeat = \
        (alarm_union >> alarm_offset) & 0x7f;

    printf("%s:alarm_id = %d\n", __func__, alarm_info[*alarm_num].bit_field.alarm_id);
    printf("%s:alarm_hour = %d\n", __func__, alarm_info[*alarm_num].bit_field.alarm_hour);
    printf("%s:alarm_minute = %d\n", __func__, alarm_info[*alarm_num].bit_field.alarm_minute);
    printf("%s:alarm_enable = %d\n", __func__, alarm_info[*alarm_num].bit_field.alarm_enable);
    printf("%s:alarm_repeat = 0x%02x\n", __func__, alarm_info[*alarm_num].bit_field.alarm_repeat);

    *alarm_num += 1;

    return;
}

void common_user_alarm_time_modify(uint32_t alarm_union)
{
    uint8_t i = 0;
    uint8_t alarm_id = 0;
    uint8_t alarm_offset = 0;

    uint8_t *alarm_num = \
        &p_ui_info_cache->alarm_manage_para.alarm_num;

    alarm_info_union_t *alarm_info = \
        p_ui_info_cache->alarm_manage_para.alarm_info;

    if(*alarm_num > ALARM_MAX_NUM)
        return;

    alarm_id = alarm_union & 0xf;

    for(i = 0; i < *alarm_num; i++)
	{
		if(alarm_id == alarm_info[i].bit_field.alarm_id)
            break;
	}

    if(i >= *alarm_num)
        return;

    alarm_offset += 4;
    alarm_info[i].bit_field.alarm_hour = \
        (alarm_union >> alarm_offset) & 0x1f;

    alarm_offset += 5;
    alarm_info[i].bit_field.alarm_minute = \
        (alarm_union >> alarm_offset) & 0x3f;

    printf("%s:alarm_id = %d\n", __func__, alarm_info[i].bit_field.alarm_id);
    printf("%s:alarm_hour = %d\n", __func__, alarm_info[i].bit_field.alarm_hour);
    printf("%s:alarm_minute = %d\n", __func__, alarm_info[i].bit_field.alarm_minute);
    printf("%s:alarm_enable = %d\n", __func__, alarm_info[i].bit_field.alarm_enable);
    printf("%s:alarm_repeat = 0x%02x\n", __func__, alarm_info[i].bit_field.alarm_repeat);

    return;
}

void common_user_alarm_repeat_modify(uint32_t alarm_union)
{
    uint8_t i = 0;
    uint8_t alarm_id = 0;
    uint8_t alarm_offset = 0;

    uint8_t *alarm_num = \
        &p_ui_info_cache->alarm_manage_para.alarm_num;

    alarm_info_union_t *alarm_info = \
        p_ui_info_cache->alarm_manage_para.alarm_info;

    if(*alarm_num > ALARM_MAX_NUM)
        return;

    alarm_id = alarm_union & 0xf;

    for(i = 0; i < *alarm_num; i++)
	{
		if(alarm_id == alarm_info[i].bit_field.alarm_id)
            break;
	}

    if(i >= *alarm_num)
        return;

    alarm_offset += 16;
    alarm_info[i].bit_field.alarm_repeat = \
        (alarm_union >> alarm_offset) & 0x7f;

    printf("%s:alarm_id = %d\n", __func__, alarm_info[i].bit_field.alarm_id);
    printf("%s:alarm_hour = %d\n", __func__, alarm_info[i].bit_field.alarm_hour);
    printf("%s:alarm_minute = %d\n", __func__, alarm_info[i].bit_field.alarm_minute);
    printf("%s:alarm_enable = %d\n", __func__, alarm_info[i].bit_field.alarm_enable);
    printf("%s:alarm_repeat = 0x%02x\n", __func__, alarm_info[i].bit_field.alarm_repeat);

    return;
}

void common_user_alarm_enable_modify(uint32_t alarm_union)
{
    uint8_t i = 0;
    uint8_t alarm_id = 0;
    uint8_t alarm_offset = 0;

    uint8_t *alarm_num = \
        &p_ui_info_cache->alarm_manage_para.alarm_num;

    alarm_info_union_t *alarm_info = \
        p_ui_info_cache->alarm_manage_para.alarm_info;

    if(*alarm_num > ALARM_MAX_NUM)
        return;

    alarm_id = alarm_union & 0xf;

    for(i = 0; i < *alarm_num; i++)
	{
		if(alarm_id == alarm_info[i].bit_field.alarm_id)
            break;
	}

    if(i >= *alarm_num)
        return;

    alarm_offset += 15;
    alarm_info[i].bit_field.alarm_enable = \
        (alarm_union >> alarm_offset) & 0x1;

    printf("%s:alarm_id = %d\n", __func__, alarm_info[i].bit_field.alarm_id);
    printf("%s:alarm_hour = %d\n", __func__, alarm_info[i].bit_field.alarm_hour);
    printf("%s:alarm_minute = %d\n", __func__, alarm_info[i].bit_field.alarm_minute);
    printf("%s:alarm_enable = %d\n", __func__, alarm_info[i].bit_field.alarm_enable);
    printf("%s:alarm_repeat = 0x%02x\n", __func__, alarm_info[i].bit_field.alarm_repeat);

    return;
}

void common_user_alarm_delete_all(void)
{
    uint8_t *alarm_num = \
        &p_ui_info_cache->alarm_manage_para.alarm_num;

    alarm_info_union_t *alarm_info = \
        p_ui_info_cache->alarm_manage_para.alarm_info;

    if(*alarm_num == 0)
        return;

    for(uint8_t i = 0; i < *alarm_num; i++)
        alarm_info[i].info = no_alarm_info;

    *alarm_num = 0;

    return;
}

void common_user_alarm_delete_one(uint8_t alarm_id)
{
    uint8_t i, j = 0;
    uint8_t alarm_id_tmp = 0xff;

    uint8_t *alarm_num = \
        &p_ui_info_cache->alarm_manage_para.alarm_num;

    alarm_info_union_t *alarm_info = \
        p_ui_info_cache->alarm_manage_para.alarm_info;

    if(*alarm_num == 0) 
        return;

    for(i = 0; i < *alarm_num; i++)
	{
		if(alarm_id == alarm_info[i].bit_field.alarm_id)
            break;
	}
	
	if(i >= *alarm_num)
        return;

    if(*alarm_num > 1)
	{
		for(j = i; j < (*alarm_num - 1); j++)
		{
			alarm_id_tmp = alarm_info[j].bit_field.alarm_id;
			alarm_info[j].info = alarm_info[j + 1].info;
			alarm_info[j].bit_field.alarm_id = (alarm_id_tmp & 0x0f);
		}
		
		alarm_info[j].info = no_alarm_info;
	}else
        alarm_info[i].info = no_alarm_info;

    *alarm_num -= 1;

    return;
}

static void common_user_alarm_is_on_handle(void)
{
    return;
}

void common_user_alarm_real_time_monitor(void)
{
    u8 alarm_weekday = 0;
    struct sys_time alarm_sys_time;

    uint8_t *alarm_num = \
        &p_ui_info_cache->alarm_manage_para.alarm_num;

    alarm_info_union_t *alarm_info = \
        p_ui_info_cache->alarm_manage_para.alarm_info;

    printf("************%s\n", __func__);

    if(*alarm_num == 0)
        return;

    ui_get_sys_time(&alarm_sys_time);

    for(uint8_t i = 0; i < *alarm_num; i++)
    {
        if(alarm_sys_time.hour == alarm_info[i].bit_field.alarm_hour && \
            alarm_sys_time.min == alarm_info[i].bit_field.alarm_minute)
        {
            alarm_weekday = rtc_calculate_week_val(&alarm_sys_time);

            if(!(alarm_info[i].bit_field.alarm_repeat))
            {
                if(alarm_info[i].bit_field.alarm_enable)
                {
                    alarm_info[i].bit_field.alarm_enable = 0;

                    /*闹钟到啦,此处做处理*/
                    common_user_alarm_is_on_handle();     
                }
            }else
            {
                if(alarm_info[i].bit_field.alarm_repeat & (0x1 << alarm_weekday))
                {
                    if(alarm_info[i].bit_field.alarm_enable)
                    {
                        /*闹钟到啦,此处做处理*/
                        common_user_alarm_is_on_handle();
                    }
                }
            }
        }
    }

    return;
}
#endif
