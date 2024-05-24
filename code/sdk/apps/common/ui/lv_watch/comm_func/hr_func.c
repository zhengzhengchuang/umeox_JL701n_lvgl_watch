#include "../lv_watch.h"

static u8 HrAutoCnt = 0;
static const u8 HrAutoDur = 45;//自动心率时长 s

u8 GetHrRealVal(void)
{
    int real_val = \
        GetVmParaCacheByLabel(\
            vm_label_hr_real_val);

    return ((u8)real_val);
}
void SetHrRealVal(u8 val)
{
    SetVmParaCacheByLabel(\
        vm_label_hr_real_val, (int)val);

    return;
}

void SetHrVmCtxCache(u8 val)
{
    if(val == 0)
        return;

    u8 VmIdx = \
        w_hr.CurIdx;
    if(VmIdx >= Hr_Day_Num)
        return;

    w_hr.data[VmIdx] = val;

    u8 HIdx = \
       VmIdx/(60/Hr_Inv_Dur);
    if(HIdx >= 24)
        return;

    if(w_hr.min_data[HIdx] == 0)
        w_hr.min_data[HIdx] = val;

    if(w_hr.max_data[HIdx] == 0)
        w_hr.max_data[HIdx] = val;

    if(val < w_hr.min_data[HIdx])
        w_hr.min_data[HIdx] = val;

    if(val > w_hr.max_data[HIdx])
        w_hr.max_data[HIdx] = val;

    // printf("%d:min = %d, max = %d\n", HIdx, \
    //     w_hr.min_data[HIdx], w_hr.max_data[HIdx]);

    return;
}

//false 没过期  true 过期
static bool HrVmDataIsPast(struct sys_time *hr_time)
{
    if(!hr_time) return true;

    //今天
    struct sys_time *utc_time1 = \
        &(w_hr.time);
    struct sys_time *utc_time2 = \
        hr_time;

    if(utc_time1->year == utc_time2->year && \
        utc_time1->month == utc_time2->month && \
            utc_time1->day == utc_time2->day)
    {
        return false;
    }
        

    return true;
}

static bool GetHrData(void)
{
    bool ret = false;

    uint8_t hr_num = \
        VmHrItemNum();
    if(hr_num == 0)
        goto __end;

    u8 idx = hr_num - 1;
    bool r_hr_ret = \
        VmHrCtxByIdx(idx);
    if(r_hr_ret == false)
        goto __end;

    ret = true;

__end:
    return ret;
}


void PowerOnSetHrVmCache(void)
{
    /*初始化今天的vm缓存参数*/
    memset(&w_hr, 0, sizeof(vm_hr_ctx_t));
    w_hr.check_code = Nor_Vm_Check_Code;
    GetUtcTime(&(w_hr.time));
    w_hr.CurIdx = \
        (w_hr.time.hour*60 + w_hr.time.min)/Hr_Inv_Dur;

    /*读取vm的最新一条数据*/
    bool data_ret = GetHrData();
    if(!data_ret) return;

    /*判断vm的最新数据是否已经过期*/
    bool IsPast = \
        HrVmDataIsPast(&(r_hr.time));
    if(IsPast == true)
        return;

    //删除副本数据，继续新的vm缓存
    uint8_t hr_num = \
        VmHrItemNum();
    u8 del_idx = hr_num - 1;
    VmHrCtxDelByIdx(del_idx);

    //拷贝保存的数据
    memcpy(w_hr.data, r_hr.data, Hr_Day_Num);
    memcpy(w_hr.min_data, r_hr.min_data, 24);
    memcpy(w_hr.max_data, r_hr.max_data, 24);
  
    return;
}

void PowerOffSetHrVmFlashSave(void)
{
    VmHrCtxFlashSave(&w_hr);

    return;
}

void HrTimerSecProcess(void)
{
    bool EnableFlag = \
        GetHrSensorEnableFlag();
    if(EnableFlag)
    {
        u8 work_type = \
            GetHrSensorWorkType();
        if(work_type == SensorWorkBo || \
            work_type == SensorWorkNone)
            return;

        u8 work_mode = \
            GetHrSensorMode();
        if(work_mode == SensorModeAuto)
        {
            HrAutoCnt++;
            if(HrAutoCnt >= HrAutoDur)
            {
                HrAutoCnt = 0;
                HrSensorStopSample();
            }
        }else
        {
            HrAutoCnt = 0;
        }
    }

    return;
}

void HrProcess(struct sys_time *utc_time)
{
    if(!utc_time) return;

#if !Vm_Debug_En
    int DevBondFlag = \
        GetVmParaCacheByLabel(\
            vm_label_dev_bond);
    if(!DevBondFlag)
        return;
#endif

    if(utc_time->hour == 0 && \
        utc_time->min == 0)
    {
        //保存上一天的心率历史数据
        VmHrCtxFlashSave(&w_hr);

        //清除缓存数据，开始新一天的数据记录
        memset(&w_hr, 0, sizeof(vm_hr_ctx_t));
        w_hr.check_code = \
            Nor_Vm_Check_Code;
        memcpy(&(w_hr.time), utc_time, \
            sizeof(struct sys_time));
    }

    u16 utc_timestamp = \
        utc_time->hour*60 + utc_time->min;
    u8 HrInvOn = \
        utc_timestamp % Hr_Inv_Dur;
    u8 HrCurIdx = \
        utc_timestamp / Hr_Inv_Dur;
    if(HrInvOn == 0)
    {
        printf("++++++%s\n", __func__);

        //整点15分钟到 启动自动心率
        w_hr.CurIdx = \
            HrCurIdx;
        bool EnableFlag = \
            GetHrSensorEnableFlag();
        if(!EnableFlag)
        {
            HrAutoCnt = 0;
            SetHrRealVal(0);

            //如果PPG手动启动，禁止自动启动，只是辅助
            HrSensorStartSample(\
                SensorWorkHr, SensorModeAuto);
        }
    }
    
    return;
}