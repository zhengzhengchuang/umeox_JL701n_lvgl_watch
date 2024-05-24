#include "../lv_watch.h"

#define ALARM_VM_MASK (0x55ec)

AlarmInfoPara_t Alarm_Info;

static const AlarmInfoPara_t InitInfo = {
    .alarm_num = 0,
    .alarm_union[0] = {.info = No_Alarm_Info},
    .alarm_union[1] = {.info = No_Alarm_Info},
    .alarm_union[2] = {.info = No_Alarm_Info},
    .alarm_union[3] = {.info = No_Alarm_Info},
    .alarm_union[4] = {.info = No_Alarm_Info},
};

void UserAlarmAdd(uint32_t info)
{
    uint8_t alarm_offset = 0;

    uint8_t *alarm_num = \
        &(Alarm_Info.alarm_num);

    alarm_union_t *p_alarm_union = \
        Alarm_Info.alarm_union;

    if(*alarm_num >= Alarm_Max_Num)
        return;

    uint8_t idx = *alarm_num;

    p_alarm_union[idx].info = No_Alarm_Info;

    p_alarm_union[idx].bit_field.alarm_id = \
        (info >> alarm_offset) & 0xf;

    alarm_offset += 4;
    p_alarm_union[idx].bit_field.alarm_hour = \
        (info >> alarm_offset) & 0x1f;

    alarm_offset += 5;
    p_alarm_union[idx].bit_field.alarm_minute = \
        (info >> alarm_offset) & 0x3f;

    alarm_offset += 6;
    p_alarm_union[idx].bit_field.alarm_enable = \
        (info >> alarm_offset) & 0x1;

    alarm_offset += 1;
    p_alarm_union[idx].bit_field.alarm_repeat = \
        (info >> alarm_offset) & 0x7f;

    *alarm_num += 1;

    AlarmInfoParaUpdate();

    printf("%s:alarm_id = %d\n", __func__, \
        p_alarm_union[idx].bit_field.alarm_id);
    printf("%s:alarm_hour = %d\n", __func__, \
        p_alarm_union[idx].bit_field.alarm_hour);
    printf("%s:alarm_minute = %d\n", __func__, \
        p_alarm_union[idx].bit_field.alarm_minute);
    printf("%s:alarm_enable = %d\n", __func__, \
        p_alarm_union[idx].bit_field.alarm_enable);
    printf("%s:alarm_repeat = 0x%02x\n", __func__, \
        p_alarm_union[idx].bit_field.alarm_repeat);

    return;
}

void UserAlarmTimeModify(uint32_t info)
{
    uint8_t i = 0;
    uint8_t alarm_id = 0;
    uint8_t alarm_offset = 0;

    uint8_t alarm_num = \
        Alarm_Info.alarm_num;

    alarm_union_t *p_alarm_union = \
        Alarm_Info.alarm_union;

    if(alarm_num > Alarm_Max_Num)
        return;

    alarm_id = info & 0xf;

    for(i = 0; i < alarm_num; i++)
	{
		if(alarm_id == \
            p_alarm_union[i].bit_field.alarm_id)
            break;
	}

    if(i >= alarm_num)
        return;

    alarm_offset += 4;
    p_alarm_union[i].bit_field.alarm_hour = \
        (info >> alarm_offset) & 0x1f;

    alarm_offset += 5;
    p_alarm_union[i].bit_field.alarm_minute = \
        (info >> alarm_offset) & 0x3f;

    AlarmInfoParaUpdate();

    printf("%s:alarm_id = %d\n", __func__, \
        p_alarm_union[i].bit_field.alarm_id);
    printf("%s:alarm_hour = %d\n", __func__, \
        p_alarm_union[i].bit_field.alarm_hour);
    printf("%s:alarm_minute = %d\n", __func__, \
        p_alarm_union[i].bit_field.alarm_minute);
    printf("%s:alarm_enable = %d\n", __func__, \
        p_alarm_union[i].bit_field.alarm_enable);
    printf("%s:alarm_repeat = 0x%02x\n", __func__, \
        p_alarm_union[i].bit_field.alarm_repeat);

    return;
}

void UserAlarmRepeatModify(uint32_t info)
{
    uint8_t i = 0;
    uint8_t alarm_id = 0;
    uint8_t alarm_offset = 0;

    uint8_t alarm_num = \
        Alarm_Info.alarm_num;

    alarm_union_t *p_alarm_union = \
        Alarm_Info.alarm_union;

    if(alarm_num > Alarm_Max_Num)
        return;

    alarm_id = info & 0xf;

    for(i = 0; i < alarm_num; i++)
	{
		if(alarm_id == \
            p_alarm_union[i].bit_field.alarm_id)
            break;
	}

    if(i >= alarm_num)
        return;

    alarm_offset += 16;
    p_alarm_union[i].bit_field.alarm_repeat = \
        (info >> alarm_offset) & 0x7f;

    AlarmInfoParaUpdate();

    printf("%s:alarm_id = %d\n", __func__, \
        p_alarm_union[i].bit_field.alarm_id);
    printf("%s:alarm_hour = %d\n", __func__, \
        p_alarm_union[i].bit_field.alarm_hour);
    printf("%s:alarm_minute = %d\n", __func__, \
        p_alarm_union[i].bit_field.alarm_minute);
    printf("%s:alarm_enable = %d\n", __func__, \
        p_alarm_union[i].bit_field.alarm_enable);
    printf("%s:alarm_repeat = 0x%02x\n", __func__, \
        p_alarm_union[i].bit_field.alarm_repeat);

    return;
}

void UserAlarmEnableModify(uint32_t info)
{
    uint8_t i = 0;
    uint8_t alarm_id = 0;
    uint8_t alarm_offset = 0;

    uint8_t alarm_num = \
        Alarm_Info.alarm_num;

    alarm_union_t *p_alarm_union = \
        Alarm_Info.alarm_union;

    if(alarm_num > Alarm_Max_Num)
        return;

    alarm_id = info & 0xf;

    for(i = 0; i < alarm_num; i++)
	{
		if(alarm_id == \
            p_alarm_union[i].bit_field.alarm_id)
            break;
	}

    if(i >= alarm_num)
        return;

    alarm_offset += 15;
    p_alarm_union[i].bit_field.alarm_enable = \
        (info >> alarm_offset) & 0x1;

    AlarmInfoParaUpdate();

    printf("%s:alarm_id = %d\n", __func__, \
        p_alarm_union[i].bit_field.alarm_id);
    printf("%s:alarm_hour = %d\n", __func__, \
        p_alarm_union[i].bit_field.alarm_hour);
    printf("%s:alarm_minute = %d\n", __func__, \
        p_alarm_union[i].bit_field.alarm_minute);
    printf("%s:alarm_enable = %d\n", __func__, \
        p_alarm_union[i].bit_field.alarm_enable);
    printf("%s:alarm_repeat = 0x%02x\n", __func__, \
        p_alarm_union[i].bit_field.alarm_repeat);

    return;
}

void UserAlarmAllModify(uint32_t info)
{
    uint8_t i = 0;
    uint8_t alarm_id = 0;
    uint8_t alarm_offset = 0;

    uint8_t alarm_num = \
        Alarm_Info.alarm_num;
    alarm_union_t *p_alarm_union = \
        Alarm_Info.alarm_union;

    if(alarm_num > Alarm_Max_Num)
        return;

    alarm_id = info & 0xf;

    for(i = 0; i < alarm_num; i++)
	{
		if(alarm_id == \
            p_alarm_union[i].bit_field.alarm_id)
            break;
	}

    if(i >= alarm_num)
        return;

    alarm_offset += 4;
    p_alarm_union[i].bit_field.alarm_hour = \
        (info >> alarm_offset) & 0x1f;

    alarm_offset += 5;
    p_alarm_union[i].bit_field.alarm_minute = \
        (info >> alarm_offset) & 0x3f;

    alarm_offset += 15;
    p_alarm_union[i].bit_field.alarm_enable = \
        (info >> alarm_offset) & 0x1;

    alarm_offset += 16;
    p_alarm_union[i].bit_field.alarm_repeat = \
        (info >> alarm_offset) & 0x7f;

    AlarmInfoParaUpdate();

    printf("%s:alarm_id = %d\n", __func__, \
        p_alarm_union[i].bit_field.alarm_id);
    printf("%s:alarm_hour = %d\n", __func__, \
        p_alarm_union[i].bit_field.alarm_hour);
    printf("%s:alarm_minute = %d\n", __func__, \
        p_alarm_union[i].bit_field.alarm_minute);
    printf("%s:alarm_enable = %d\n", __func__, \
        p_alarm_union[i].bit_field.alarm_enable);
    printf("%s:alarm_repeat = 0x%02x\n", __func__, \
        p_alarm_union[i].bit_field.alarm_repeat);
        
    return;
}

void UserAlarmDeleteAll(void)
{
    memcpy(&Alarm_Info, &InitInfo, \
        sizeof(AlarmInfoPara_t));

    Alarm_Info.vm_mask = \
        ALARM_VM_MASK;

    AlarmInfoParaUpdate();

    return;
}

void UserAlarmDeleteOne(uint8_t alarm_id)
{
    uint8_t i, j = 0;
    uint8_t alarm_id_tmp = 0xff;

    uint8_t *alarm_num = \
        &(Alarm_Info.alarm_num);

    alarm_union_t *p_alarm_union = \
        Alarm_Info.alarm_union;

    if(*alarm_num == 0) 
        return;

    for(i = 0; i < *alarm_num; i++)
	{
		if(alarm_id == \
            p_alarm_union[i].bit_field.alarm_id)
            break;
	}
	
	if(i >= *alarm_num)
        return;

    if(*alarm_num > 1)
	{
		for(j = i; j < (*alarm_num - 1); j++)
		{
			alarm_id_tmp = p_alarm_union[j].bit_field.alarm_id;
			p_alarm_union[j].info = p_alarm_union[j + 1].info;
			p_alarm_union[j].bit_field.alarm_id = (alarm_id_tmp & 0x0f);
		}
		
		p_alarm_union[j].info = No_Alarm_Info;
	}else
        p_alarm_union[i].info = No_Alarm_Info;

    *alarm_num -= 1;

    AlarmInfoParaUpdate();

    return;
}

uint32_t GetUserAlarmInfo(uint8_t alarm_id)
{
    uint8_t alarm_num = \
        Alarm_Info.alarm_num;

    alarm_union_t *p_alarm_union = \
        Alarm_Info.alarm_union;

    if(alarm_id >= alarm_num)
        return No_Alarm_Info;

    return p_alarm_union[alarm_id].info;
}

static uint8_t AlarmIsOnId;
uint8_t GetAlarmIsOnId(void)
{
    return AlarmIsOnId;
}

void SetAlarmIsOnId(uint8_t id)
{
    AlarmIsOnId = id;

    return;
}

static void UserAlarmIsOnHandle(void)
{
    //当前菜单是否支持弹窗
    if(!MenuSupportPopup())
        return;

    //震动、播放

    ui_menu_jump(\
        ui_act_id_alarm_remind);

    return;
}

void UserAlarmProcess(struct sys_time *utc_time)
{
    if(!utc_time) return;

#if !Vm_Debug_En
    int DevBondFlag = \
        GetVmParaCacheByLabel(\
            vm_label_dev_bond);
    if(!DevBondFlag)
        return;
#endif

    u8 alarm_weekday = 0;
 
    uint8_t alarm_num = \
        Alarm_Info.alarm_num;

    alarm_union_t *p_alarm_union = \
        Alarm_Info.alarm_union;

    if(alarm_num == 0)
        return;

    for(uint8_t i = 0; i < alarm_num; i++)
    {
        if(utc_time->hour == p_alarm_union[i].bit_field.alarm_hour && \
            utc_time->min == p_alarm_union[i].bit_field.alarm_minute)
        {
            alarm_weekday = \
                GetUtcWeek(utc_time);

            uint8_t alarm_repeat = \
                p_alarm_union[i].bit_field.alarm_repeat;
            bool alarm_enable = \
                p_alarm_union[i].bit_field.alarm_enable;
            if(!alarm_repeat)
            {
                //无重复
                if(alarm_enable)
                {
                    SetAlarmIsOnId(i);
                    alarm_enable = false;
                    p_alarm_union[i].bit_field.alarm_enable = \
                        alarm_enable;
                    AlarmInfoParaUpdate();
                    UserAlarmIsOnHandle();
                    break;  
                }
            }else
            {
                if(alarm_repeat & (0x1 << alarm_weekday))
                {
                    if(alarm_enable)
                    {
                        SetAlarmIsOnId(i);
                        UserAlarmIsOnHandle();
                        break;
                    }
                }
            }
        }
    }

    return;
}

void AlarmInfoParaRead(void)
{
    int vm_op_len = \
        sizeof(AlarmInfoPara_t);

    int ret = syscfg_read(CFG_ALARM_PARA_INFO, \
        &Alarm_Info, vm_op_len);
    if(ret != vm_op_len || \
        Alarm_Info.vm_mask != ALARM_VM_MASK)
    {
        memcpy(&Alarm_Info, &InitInfo, \
            vm_op_len);

        Alarm_Info.vm_mask = \
            ALARM_VM_MASK;

        AlarmInfoParaUpdate();
    }

    return;
}

void AlarmInfoParaWrite(void)
{
    int vm_op_len = \
        sizeof(AlarmInfoPara_t);
    
    for(u8 i = 0; i < 3; i++)
    {
        int ret = syscfg_write(CFG_ALARM_PARA_INFO, \
            &Alarm_Info, vm_op_len);
        if(ret == vm_op_len)
            break;
    }

    return;
}

void AlarmInfoParaUpdate(void)
{
    AlarmInfoParaWrite();

    return;
}