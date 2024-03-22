#ifndef __SENSOR_MAG_TASK_H__
#define __SENSOR_MAG_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"
#include "../../../device/m_sensor/qmc6309/qmc6309.h"

#define Sensor_Mag_Task_Name \
    "sensor_mag_task"

enum
{
    SensorMagMsgProcess,
    SensorMagMsgEnableModule,
    SensorMagMsgDisableModule,
};

void SensorMagTaskCreate(void);
int PostSensorMagTaskMsg(int *post_msg, u8 len);
void SensorMagTaskMsgHandle(int *rev_msg, u8 len);

void AppCtrlMagEnableModule(void);
void AppCtrlMagDisableModule(void);

void AppCtrlMagProcessTimerCreate(void);
void AppCtrlMagProcessTimerDestory(void);

void AppCtrlMagAlgoProcess(void);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
