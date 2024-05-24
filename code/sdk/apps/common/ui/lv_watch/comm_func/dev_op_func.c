#include "../lv_watch.h"

#if 0
void watch_reboot_or_shutdown(u8 flag, u8 erase)
{
    void *p = NULL;
    if (erase) {
        p = SYSCFG_WRITE_ERASE_STATUS;
    }
    extern void watch_sensor_test(void);
    extern int watch_sensor_close(void);

    watch_sensor_close();
    watch_syscfg_write_all(p);
    if (flag) {
        cpu_reset();
    } else {
        sys_enter_soft_poweroff(NULL);
    }
}
#endif

static u16 dev_op_timer;

static void enter_shutdown_cb(void *priv)
{
    if(dev_op_timer)
        sys_timeout_del(dev_op_timer);
    dev_op_timer = 0;

    int shutdown_post[1];
    shutdown_post[0] = \
        comm_msg_dev_shutdown;
    post_comm_task_msg(shutdown_post, 1);

    return;
}

static void DevAllSensorClose(void)
{
    DisableSensorGsModule();
    DisableSensorGmModule();
    HrSensorStopSample();

    return;
}

void DevOpMenuPopUp(void)
{
    //当前菜单是否支持弹窗
    if(!MenuSupportPopup())
        return;

    ui_menu_jump(ui_act_id_device_op);

    return;
}

void DevOpShutdownHandle(void)
{
    /*当天储存的心率血氧数据写进nor vm*/
    PowerOffSetHrVmFlashSave();
    PowerOffSetBoVmFlashSave();

    /*关闭所有Sensor*/
    DevAllSensorClose();

    /*灭屏处理*/
    common_offscreen_handle(); 

    /*震动*/
    motor_run(1, sdw_motor_duty);

    /*延时500ms关机操作*/
    dev_op_timer = \
        sys_timeout_add(NULL, enter_shutdown_cb, 500);

    return;
}

