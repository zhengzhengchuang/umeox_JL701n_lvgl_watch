#ifndef __SENSOR_HR_TASK_H__
#define __SENSOR_HR_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"
#include "../../../device/hr_sensor/vc9201/vcHr02Hci.h"

#define Sensor_Hr_Task_Name \
    "sensor_hr_task"

enum
{
    SensorHrMsgProcess,
    SensorHrMsgEnableModule,
    SensorHrMsgDisableModule,
};

void SensorHrTaskCreate(void);
int PostSensorHrTaskMsg(int *post_msg, u8 len);
void SensorHrTaskMsgHandle(int *rev_msg, u8 len);

bool GetvcHr02EnableFlag(void);
void SetvcHr02EnableFlag(bool en);

bool AppGetvcHr02WearStatus(void);
void AppSetvcHr02WearStatus(bool status);

void AppCtrlvcHr02StopSample(void);
void AppCtrlvcHr02StartSample(vcHr02Mode_t mode);

void vcHr02GsensorDatacbufWrite(u8 *w_buf, u32 w_len);
u16 vcHr02GsensorDatacbufRead(s16 *xdata, s16 *ydata, \
    s16 *zdata, u16 r_max_num);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
