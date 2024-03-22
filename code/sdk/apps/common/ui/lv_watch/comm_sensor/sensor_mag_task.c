#include "../lv_watch.h"

bool calipara_stored = \
    false;
float calipara_cache[4] = {\
    0.0f, 0.0f, 0.0f, 0.0f};

static u16 MagProcessTimerId = 0;


static void SensorMagTask(void *p)
{
    int rev_ret;
    int rev_msg[8] = {0};

    int ret = syscfg_read(CFG_MAG_CALIPARA_INFO, \
        calipara_cache, sizeof(calipara_cache));
    if(ret != sizeof(calipara_cache))
    {
        calipara_stored = false;

        for(uint8_t i = 0; i < 4; i++)
            calipara_cache[i] = 0.0f;

        printf("calipara_cache not store!!!!!!!\n");
    }else
    {
        calipara_stored = true;
    }

    qst_ical_init(calipara_cache);
	fusion_enable();

    /*开机先失能模块*/
    AppCtrlMagDisableModule();

    while(1)
    {
        rev_ret = \
            os_taskq_pend(NULL, rev_msg, \
                ARRAY_SIZE(rev_msg)); 

        if(rev_ret == OS_TASKQ)
            SensorMagTaskMsgHandle(rev_msg, \
                ARRAY_SIZE(rev_msg));
    }
    
    return;
}

void SensorMagTaskCreate(void)
{
    int err = task_create(SensorMagTask, \
        NULL, Sensor_Mag_Task_Name);
    if(err) 
        r_printf("Mag task create err!!!!!!!:%d \n", err);

    return;
}

void SensorMagTaskMsgHandle(int *rev_msg, u8 len)
{
    if(!rev_msg || len == 0)
        return;

    int msg_cmd = rev_msg[0];

    switch(msg_cmd)
    {
        case SensorMagMsgProcess:
        {
            AppCtrlMagAlgoProcess();
        }
            break;
        
        case SensorMagMsgEnableModule:
        {
            qmc6309_enable();

            AppCtrlMagProcessTimerCreate();
        } 
            break;

        case SensorMagMsgDisableModule:
        {
            qmc6309_disable();

            AppCtrlMagProcessTimerDestory();
        }  
            break;

        default:
            printf("*************ui msg not found\n");
            break;
    }

    return;
}

int PostSensorMagTaskMsg(int *post_msg, u8 len)
{
    int err = 0;
    int count = 0;

    if(!post_msg || len == 0)
        return -1;

__retry:
    err = os_taskq_post_type(\
        Sensor_Mag_Task_Name, post_msg[0], \
            len - 1, &post_msg[1]);

    if(cpu_in_irq() || cpu_irq_disabled())
        return err;

    if(err) 
    {
        if(!strcmp(os_current_task(), \
            Sensor_Mag_Task_Name)) 
            return err;

        if(count > 20)
            return -1;
        
        count++;
        os_time_dly(1);
        goto __retry;
    }

    return err;
}

static void SensorMagProcessTimeCb(void *priv)
{
    int SensorMagMsg[1];
	SensorMagMsg[0] = \
		SensorMagMsgProcess;
	PostSensorMagTaskMsg(SensorMagMsg, 1);

    return;
}

void AppCtrlMagProcessTimerCreate(void)
{
    if(MagProcessTimerId)
    {
        sys_hi_timer_del(\
            MagProcessTimerId);

        MagProcessTimerId = 0;
    }

    if(!MagProcessTimerId)
        MagProcessTimerId = \
            sys_hi_timer_add(NULL, \
                SensorMagProcessTimeCb, 20);

    return;
}

void AppCtrlMagProcessTimerDestory(void)
{
    if(MagProcessTimerId)
    {
        sys_hi_timer_del(\
            MagProcessTimerId);

        MagProcessTimerId = 0;
    }
}

void AppCtrlMagEnableModule(void)
{
    int SensorMagMsg[1];
	SensorMagMsg[0] = \
		SensorMagMsgEnableModule;
	PostSensorMagTaskMsg(SensorMagMsg, 1); 

    return;
}

void AppCtrlMagDisableModule(void)
{
    int SensorMagMsg[1];
	SensorMagMsg[0] = \
		SensorMagMsgDisableModule;
	PostSensorMagTaskMsg(SensorMagMsg, 1); 

    return;
}

void AppCtrlMagAlgoProcess(void)
{
    return;
}