#include "../lv_watch.h"

#define HrGs_FifoSize (600)

static u32 HrGs_Wlen = 0;
static u32 HrGs_Rlen = 0;
static u32 HrGs_WFifoIdx = 0;
static u32 HrGs_RFifoIdx = 0;
static u8 HrGs_FifoData[HrGs_FifoSize];

static void HrGsFifoParaInit(void)
{
    HrGs_Wlen = 0;
    HrGs_Rlen = 0;
    HrGs_WFifoIdx = 0;
    HrGs_RFifoIdx = 0;
    memset(HrGs_FifoData, 0, \
        HrGs_FifoSize);

    return;
}

static void SensorHrTask(void *p)
{
    int rev_ret;
    int rev_msg[8] = {0};

    HrGsFifoParaInit();

    AppCtrlvcHr02StartSample(\
        VCWORK_MODE_HRWORK);

    while(1)
    {
        rev_ret = \
            os_taskq_pend(NULL, rev_msg, \
                ARRAY_SIZE(rev_msg)); 

        if(rev_ret == OS_TASKQ)
            SensorHrTaskMsgHandle(rev_msg, \
                ARRAY_SIZE(rev_msg));
    }
    
    return;
}

void SensorHrTaskCreate(void)
{
    int err = task_create(SensorHrTask, \
        NULL, Sensor_Hr_Task_Name);
    if(err) 
        r_printf("Hr task create err!!!!!!!:%d \n", err);

    return;
}

void SensorHrTaskMsgHandle(int *rev_msg, u8 len)
{
    if(!rev_msg || len == 0)
        return;

    int msg_cmd = rev_msg[0];

    switch(msg_cmd)
    {
        case SensorHrMsgProcess:
        {
            vcHr02ProcessHanlde();
        }
            break;

        case SensorHrMsgEnableModule:
        {
            HrGsFifoParaInit();

            CtrlvcHr02StartSample(\
                (vcHr02Mode_t)rev_msg[1]);

            SetvcHr02EnableFlag(true);
        }  
            break;

        case SensorHrMsgDisableModule:
        {
            CtrlvcHr02StopSample();

            SetvcHr02EnableFlag(false);
        } 
            break;

        default:
            printf("*************ui msg not found\n");
            break;
    }

    return;
}

int PostSensorHrTaskMsg(int *post_msg, u8 len)
{
    int err = 0;
    int count = 0;

    if(!post_msg || len == 0)
        return -1;

__retry:
    err = os_taskq_post_type(Sensor_Hr_Task_Name, \
        post_msg[0], len - 1, &post_msg[1]);

    if(cpu_in_irq() || cpu_irq_disabled())
        return err;

    if(err) 
    {
        if(!strcmp(os_current_task(), \
            Sensor_Hr_Task_Name)) 
            return err;

        if(count > 20)
            return -1;
        
        count++;
        os_time_dly(1);
        goto __retry;
    }

    return err;
}


static bool EnableFlag = \
    false; 
bool GetvcHr02EnableFlag(void)
{
    return EnableFlag;
}

void SetvcHr02EnableFlag(bool en)
{
    EnableFlag = en;

    return;
}

static bool vcHr02IsWear = true;
bool AppGetvcHr02WearStatus(void)
{
    return vcHr02IsWear;
}

void AppSetvcHr02WearStatus(bool status)
{
    vcHr02IsWear = status;

    return;
}

void AppCtrlvcHr02StopSample(void)
{
    int SensorHrMsg[1];
	SensorHrMsg[0] = \
		SensorHrMsgDisableModule;
	PostSensorHrTaskMsg(SensorHrMsg, 1); 

    return;
}

void AppCtrlvcHr02StartSample(vcHr02Mode_t mode)
{
    int SensorHrMsg[2];
	SensorHrMsg[0] = \
		SensorHrMsgEnableModule;
    SensorHrMsg[1] = \
		(int)mode;
	PostSensorHrTaskMsg(SensorHrMsg, 2); 

    return;
}

void vcHr02GsensorDatacbufWrite(u8 *w_buf, u32 w_len)
{ 
    if(!w_buf || w_len == 0)
        return;

    bool EnableFlag = \
        GetvcHr02EnableFlag();
    if(EnableFlag == false)
        return;

    if(HrGs_WFifoIdx + w_len <= HrGs_FifoSize)
    {
        memcpy(&HrGs_FifoData[HrGs_WFifoIdx], \
            w_buf, w_len);

        HrGs_WFifoIdx += w_len;
    }else
    {
        u32 fifo_remain_len = \
            HrGs_FifoSize - HrGs_WFifoIdx;

        if(fifo_remain_len != 0)
            memcpy(&HrGs_FifoData[HrGs_WFifoIdx], \
                w_buf, fifo_remain_len);

        HrGs_WFifoIdx = 0;

        memcpy(&HrGs_FifoData[HrGs_WFifoIdx], \
            &w_buf[fifo_remain_len], (w_len - fifo_remain_len));

        HrGs_WFifoIdx += (w_len - fifo_remain_len);
    }

    HrGs_Wlen += w_len;

    return;
}

u16 vcHr02GsensorDatacbufRead(s16 *xdata, s16 *ydata, \
    s16 *zdata, u16 r_max_num)
{
    u16 r_num = 0;

    if(!xdata || !ydata || !zdata || \
        r_max_num == 0)
        return r_num;

    bool EnableFlag = \
        GetvcHr02EnableFlag();
    if(EnableFlag == false)
        return r_num;

    u8 FifoData[6];
    s16 AccRawData[3];

    u32 r_max_len = \
        r_max_num*6;

    if(HrGs_Rlen + r_max_len > HrGs_Wlen)
    {
        if(HrGs_Rlen >= HrGs_Wlen)
            return r_num;

        r_max_len = \
            HrGs_Wlen - HrGs_Rlen;
        r_max_len -= \
            (r_max_len % 6);

        if(r_max_len == 0)
            return r_num;
    }

    if(HrGs_RFifoIdx + r_max_len <= HrGs_FifoSize)
    {
        u32 i;
        for(i = 0; i < r_max_len/6; i++)
        {
            memcpy(FifoData, \
                &HrGs_FifoData[HrGs_RFifoIdx], 6);

            AccRawData[0] = (s16)(((uint16_t)FifoData[1] << 8) | \
                (FifoData[0]));
            AccRawData[1] = (s16)(((uint16_t)FifoData[3] << 8) | \
                (FifoData[2]));
            AccRawData[2] = (s16)(((uint16_t)FifoData[5] << 8) | \
                (FifoData[4]));

            xdata[i] = AccRawData[0];
            ydata[i] = AccRawData[1];
            zdata[i] = AccRawData[2];

            HrGs_RFifoIdx += 6;
        }
    }else
    {
        u32 fifo_remain_len = \
            HrGs_FifoSize - HrGs_RFifoIdx; 

        if(fifo_remain_len % 6 == 0)
        {
            u32 i;
            for(i = 0; i < fifo_remain_len/6; i++)
            {
                memcpy(FifoData, \
                    &HrGs_FifoData[HrGs_RFifoIdx], 6);

                AccRawData[0] = (s16)(((uint16_t)FifoData[1] << 8) | \
                    (FifoData[0]));
                AccRawData[1] = (s16)(((uint16_t)FifoData[3] << 8) | \
                    (FifoData[2]));
                AccRawData[2] = (s16)(((uint16_t)FifoData[5] << 8) | \
                    (FifoData[4]));

                xdata[i] = AccRawData[0];
                ydata[i] = AccRawData[1];
                zdata[i] = AccRawData[2];

                HrGs_RFifoIdx += 6;
            }

            u32 j;
            HrGs_RFifoIdx %= \
                HrGs_FifoSize;
            u32 data_remain_len = \
                r_max_len - fifo_remain_len;
            
            for(j = 0; j < data_remain_len/6; j++)
            {
                memcpy(FifoData, \
                    &HrGs_FifoData[HrGs_RFifoIdx], 6);

                AccRawData[0] = (s16)(((uint16_t)FifoData[1] << 8) | \
                    (FifoData[0]));
                AccRawData[1] = (s16)(((uint16_t)FifoData[3] << 8) | \
                    (FifoData[2]));
                AccRawData[2] = (s16)(((uint16_t)FifoData[5] << 8) | \
                    (FifoData[4]));

                xdata[j + i] = AccRawData[0];
                ydata[j + i] = AccRawData[1];
                zdata[j + i] = AccRawData[2];

                HrGs_RFifoIdx += 6;
            }
        }else
        {
            fifo_remain_len -= \
                (fifo_remain_len % 6);
            
            u32 i;
            for(i = 0; i < fifo_remain_len/6; i++)
            {
                memcpy(FifoData, \
                    &HrGs_FifoData[HrGs_RFifoIdx], 6);

                AccRawData[0] = (s16)(((uint16_t)FifoData[1] << 8) | \
                    (FifoData[0]));
                AccRawData[1] = (s16)(((uint16_t)FifoData[3] << 8) | \
                    (FifoData[2]));
                AccRawData[2] = (s16)(((uint16_t)FifoData[5] << 8) | \
                    (FifoData[4]));

                xdata[i] = AccRawData[0];
                ydata[i] = AccRawData[1];
                zdata[i] = AccRawData[2];

                HrGs_RFifoIdx += 6;
            }

            u8 cache_idx = 0;
            u8 fifo_remain_len_tmp = \
                HrGs_FifoSize - HrGs_RFifoIdx;
            memcpy(&FifoData[cache_idx], &HrGs_FifoData[HrGs_RFifoIdx], \
                fifo_remain_len_tmp);

            HrGs_RFifoIdx += fifo_remain_len_tmp; 
            HrGs_RFifoIdx %= HrGs_FifoSize;

            cache_idx += fifo_remain_len_tmp;
            memcpy(&FifoData[cache_idx], &HrGs_FifoData[HrGs_RFifoIdx], \
                (6 - fifo_remain_len_tmp));
            AccRawData[0] = (s16)(((uint16_t)FifoData[1] << 8) | \
                (FifoData[0]));
            AccRawData[1] = (s16)(((uint16_t)FifoData[3] << 8) | \
                (FifoData[2]));
            AccRawData[2] = (s16)(((uint16_t)FifoData[5] << 8) | \
                (FifoData[4]));

            xdata[i++] = AccRawData[0];
            ydata[i++] = AccRawData[1];
            zdata[i++] = AccRawData[2];

            HrGs_RFifoIdx += (6 - fifo_remain_len_tmp);

            u32 j;
            u32 data_remain_len = \
                (r_max_len - fifo_remain_len - 6);
            for(j = 0; j < data_remain_len/6; j++)
            {
                memcpy(FifoData, \
                    &HrGs_FifoData[HrGs_RFifoIdx], 6);

                AccRawData[0] = (s16)(((uint16_t)FifoData[1] << 8) | \
                    (FifoData[0]));
                AccRawData[1] = (s16)(((uint16_t)FifoData[3] << 8) | \
                    (FifoData[2]));
                AccRawData[2] = (s16)(((uint16_t)FifoData[5] << 8) | \
                    (FifoData[4]));

                xdata[j + i] = AccRawData[0];
                ydata[j + i] = AccRawData[1];
                zdata[j + i] = AccRawData[2];

                HrGs_RFifoIdx += 6;
            }
        }
    }

    HrGs_Rlen += r_max_len;

    r_num =  r_max_len/6;

    return r_num;
}