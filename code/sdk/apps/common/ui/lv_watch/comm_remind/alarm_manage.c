#include "../lv_watch.h"
#include "alarm_manage.h"
#include "../poc_modem/poc_modem_vm.h"
#include "../../../../watch/include/task_manager/rtc/alarm.h"

static uint8_t reminding_alarm_id;
static const uint32_t no_alarm_info = No_Alarm_Info;

uint8_t get_reminding_alarm_id(void)
{
    return reminding_alarm_id;
}

void set_reminding_alarm_id(uint8_t id)
{
    reminding_alarm_id = \
        id;

    return;
}

uint32_t common_user_alarm_read_info(uint8_t alarm_id)
{
    uint8_t alarm_num = \
        p_vm_para_cache->alarm_manage_para.alarm_num;

    alarm_info_union_t *alarm_info = \
        p_vm_para_cache->alarm_manage_para.alarm_info;

    if(alarm_id >= alarm_num)
        return no_alarm_info;

    return alarm_info[alarm_id].info;
}

void common_user_alarm_add(uint32_t alarm_union)
{
    uint8_t alarm_offset = 0;

    uint8_t *alarm_num = \
        &p_vm_para_cache->alarm_manage_para.alarm_num;

    alarm_info_union_t *alarm_info = \
        p_vm_para_cache->alarm_manage_para.alarm_info;

    if(*alarm_num >= Alarm_Max_Num)
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

    printf("%s:alarm_id = %d\n", __func__, \
        alarm_info[*alarm_num].bit_field.alarm_id);
    printf("%s:alarm_hour = %d\n", __func__, \
        alarm_info[*alarm_num].bit_field.alarm_hour);
    printf("%s:alarm_minute = %d\n", __func__, \
        alarm_info[*alarm_num].bit_field.alarm_minute);
    printf("%s:alarm_enable = %d\n", __func__, \
        alarm_info[*alarm_num].bit_field.alarm_enable);
    printf("%s:alarm_repeat = 0x%02x\n", __func__, \
        alarm_info[*alarm_num].bit_field.alarm_repeat);

    *alarm_num += 1;

    return;
}

void common_user_alarm_time_modify(uint32_t alarm_union)
{
    uint8_t i = 0;
    uint8_t alarm_id = 0;
    uint8_t alarm_offset = 0;

    uint8_t alarm_num = \
        p_vm_para_cache->alarm_manage_para.alarm_num;

    alarm_info_union_t *alarm_info = \
        p_vm_para_cache->alarm_manage_para.alarm_info;

    if(alarm_num > Alarm_Max_Num)
        return;

    alarm_id = alarm_union & 0xf;

    for(i = 0; i < alarm_num; i++)
	{
		if(alarm_id == \
            alarm_info[i].bit_field.alarm_id)
            break;
	}

    if(i >= alarm_num)
        return;

    alarm_offset += 4;
    alarm_info[i].bit_field.alarm_hour = \
        (alarm_union >> alarm_offset) & 0x1f;

    alarm_offset += 5;
    alarm_info[i].bit_field.alarm_minute = \
        (alarm_union >> alarm_offset) & 0x3f;

    printf("%s:alarm_id = %d\n", __func__, \
        alarm_info[i].bit_field.alarm_id);
    printf("%s:alarm_hour = %d\n", __func__, \
        alarm_info[i].bit_field.alarm_hour);
    printf("%s:alarm_minute = %d\n", __func__, \
        alarm_info[i].bit_field.alarm_minute);
    printf("%s:alarm_enable = %d\n", __func__, \
        alarm_info[i].bit_field.alarm_enable);
    printf("%s:alarm_repeat = 0x%02x\n", __func__, \
        alarm_info[i].bit_field.alarm_repeat);

    return;
}

void common_user_alarm_repeat_modify(uint32_t alarm_union)
{
    uint8_t i = 0;
    uint8_t alarm_id = 0;
    uint8_t alarm_offset = 0;

    uint8_t alarm_num = \
        p_vm_para_cache->alarm_manage_para.alarm_num;

    alarm_info_union_t *alarm_info = \
        p_vm_para_cache->alarm_manage_para.alarm_info;

    if(alarm_num > Alarm_Max_Num)
        return;

    alarm_id = alarm_union & 0xf;

    for(i = 0; i < alarm_num; i++)
	{
		if(alarm_id == alarm_info[i].bit_field.alarm_id)
            break;
	}

    if(i >= alarm_num)
        return;

    alarm_offset += 16;
    alarm_info[i].bit_field.alarm_repeat = \
        (alarm_union >> alarm_offset) & 0x7f;

    printf("%s:alarm_id = %d\n", __func__, \
        alarm_info[i].bit_field.alarm_id);
    printf("%s:alarm_hour = %d\n", __func__, \
        alarm_info[i].bit_field.alarm_hour);
    printf("%s:alarm_minute = %d\n", __func__, \
        alarm_info[i].bit_field.alarm_minute);
    printf("%s:alarm_enable = %d\n", __func__, \
        alarm_info[i].bit_field.alarm_enable);
    printf("%s:alarm_repeat = 0x%02x\n", __func__, \
        alarm_info[i].bit_field.alarm_repeat);

    return;
}

void common_user_alarm_enable_modify(uint32_t alarm_union)
{
    uint8_t i = 0;
    uint8_t alarm_id = 0;
    uint8_t alarm_offset = 0;

    uint8_t alarm_num = \
        p_vm_para_cache->alarm_manage_para.alarm_num;

    alarm_info_union_t *alarm_info = \
        p_vm_para_cache->alarm_manage_para.alarm_info;

    if(alarm_num > Alarm_Max_Num)
        return;

    alarm_id = alarm_union & 0xf;

    for(i = 0; i < alarm_num; i++)
	{
		if(alarm_id == \
            alarm_info[i].bit_field.alarm_id)
            break;
	}

    if(i >= alarm_num)
        return;

    alarm_offset += 15;
    alarm_info[i].bit_field.alarm_enable = \
        (alarm_union >> alarm_offset) & 0x1;

    printf("%s:alarm_id = %d\n", __func__, \
        alarm_info[i].bit_field.alarm_id);
    printf("%s:alarm_hour = %d\n", __func__, \
        alarm_info[i].bit_field.alarm_hour);
    printf("%s:alarm_minute = %d\n", __func__, \
        alarm_info[i].bit_field.alarm_minute);
    printf("%s:alarm_enable = %d\n", __func__, \
        alarm_info[i].bit_field.alarm_enable);
    printf("%s:alarm_repeat = 0x%02x\n", __func__, \
        alarm_info[i].bit_field.alarm_repeat);

    return;
}

void common_user_alarm_delete_all(void)
{
    uint8_t *alarm_num = \
        &p_vm_para_cache->alarm_manage_para.alarm_num;

    alarm_info_union_t *alarm_info = \
        p_vm_para_cache->alarm_manage_para.alarm_info;

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
        &p_vm_para_cache->alarm_manage_para.alarm_num;

    alarm_info_union_t *alarm_info = \
        p_vm_para_cache->alarm_manage_para.alarm_info;

    if(*alarm_num == 0) 
        return;

    for(i = 0; i < *alarm_num; i++)
	{
		if(alarm_id == \
            alarm_info[i].bit_field.alarm_id)
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
    ui_menu_load_info_t *ui_menu_load_info;
    if(lcd_sleep_status())
        ui_menu_load_info = \
            &(p_ui_info_cache->exit_menu_load_info);
    else
        ui_menu_load_info = \
            &(p_ui_info_cache->menu_load_info); 
    /*锁定菜单，闹钟不提醒，当前有不能打断的页面事件处理*/
    if(ui_menu_load_info->lock_flag)
        return;

    /*有其他事件不能提醒闹钟得，在此添加*/
    //.......

    /*在此响铃、震动*/

    /*弹出ui页面*/
    ui_menu_jump(ui_act_id_alarm_remind);

    return;
}

void common_user_alarm_real_time_monitor(void)
{
    u8 alarm_weekday = 0;
    struct sys_time alarm_sys_time;

    uint8_t alarm_num = \
        p_vm_para_cache->alarm_manage_para.alarm_num;

    alarm_info_union_t *alarm_info = \
        p_vm_para_cache->alarm_manage_para.alarm_info;

    if(alarm_num == 0)
        return;

    get_utc_time(&alarm_sys_time);

    for(uint8_t i = 0; i < alarm_num; i++)
    {
        if(alarm_sys_time.hour == alarm_info[i].bit_field.alarm_hour && \
            alarm_sys_time.min == alarm_info[i].bit_field.alarm_minute)
        {
            alarm_weekday = \
                rtc_calculate_week_val(&alarm_sys_time);

            if(!(alarm_info[i].bit_field.alarm_repeat))
            {
                if(alarm_info[i].bit_field.alarm_enable)
                {
                    set_reminding_alarm_id(i);

                    alarm_info[i].bit_field.alarm_enable = 0;

                    common_user_alarm_is_on_handle();

                    /*如果找到一个生效的闹钟，就不会往后查找啦*/
                    break;  
                }
            }else
            {
                if(alarm_info[i].bit_field.alarm_repeat & \
                    (0x1 << alarm_weekday))
                {
                    if(alarm_info[i].bit_field.alarm_enable)
                    {
                        set_reminding_alarm_id(i);

                        common_user_alarm_is_on_handle();

                        /*如果找到一个生效的闹钟，就不会往后查找啦*/
                        break;
                    }
                }
            }
        }
    }

    return;
}

