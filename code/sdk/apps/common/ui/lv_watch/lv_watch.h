﻿#ifndef __LV_WATCH_H__
#define __LV_WATCH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fs.h"
#include "device.h"
#include "app_config.h"


#include "./include/ui_conf.h"
#include "./include/ui_menu.h"
#include "./include/version.h"
#include "./include/dev_info.h"
#include "./comm_func/hr_func.h"
#include "./comm_func/bo_func.h"
#include "./include/ui_act_id.h"
#include "./comm_func/dnd_func.h"
#include "./comm_func/find_func.h"
#include "./comm_task/comm_task.h"
#include "./comm_lang/lang_conf.h"
#include "./comm_key/common_key.h"
#include "./comm_func/call_func.h"
#include "./comm_func/alarm_func.h"
#include "./comm_func/sleep_func.h"
#include "./comm_lang/lang_txtid.h"
#include "./comm_func/camera_func.h"
#include "./comm_nor_vm/nor_vm_hr.h"
#include "./comm_nor_vm/nor_vm_bo.h"
#include "./comm_lang/azkar_table.h"
#include "./comm_widget/widget_bo.h"
#include "./comm_widget/widget_hr.h"
#include "./comm_parse/common_cmd.h"
#include "./comm_parse/common_rev.h"
#include "./comm_func/gomore_func.h"
#include "./comm_func/dev_op_func.h"
#include "./comm_parse/common_send.h"
#include "./comm_func/message_func.h"
#include "./comm_func/weather_func.h"
#include "./comm_nor_vm/nor_vm_cfg.h"
#include "./poc_modem/poc_modem_ui.h"
#include "./comm_func/dev_bond_func.h"
#include "./comm_parse/common_parse.h"
#include "./comm_lang/al_name_table.h"
#include "./comm_task/utc_time_task.h"
#include "./ui_tileview/ui_tileview.h"
#include "./comm_widget/common_symb.h"
#include "./comm_widget/widget_step.h"
#include "./comm_widget/widget_pace.h"
#include "./comm_widget/widget_week.h"
#include "./comm_widget/common_data.h"
#include "./comm_widget/widget_date.h"
#include "./comm_widget/widget_time.h"
#include "./comm_func/sedentary_func.h"
#include "./comm_func/user_info_func.h"
#include "./comm_parse/common_le_set.h"
#include "./comm_parse/common_le_get.h"
#include "./comm_func/countdown_func.h"
#include "./comm_func/stopwatch_func.h"
#include "./comm_nor_vm/nor_vm_sleep.h"
#include "./comm_refr/common_refresh.h"
#include "./comm_widget/widget_clock.h"
#include "./poc_modem/poc_modem_cache.h"
#include "./comm_widget/common_widget.h"
#include "./ui_menu/tool_box/tool_box.h"
#include "./comm_func/allah_name_func.h"
#include "../../../device/motor/motor.h"
#include "./comm_sensor/sensor_hr_task.h"
#include "./comm_sensor/sensor_gs_task.h"
#include "./comm_sensor/sensor_gm_task.h"
#include "./comm_nor_vm/nor_vm_weather.h"
#include "./comm_widget/widget_weather.h"
#include "./comm_widget/widget_num_str.h"
#include "./comm_widget/widget_calorie.h"
#include "./comm_func/kaaba_qibla_func.h"
#include "./comm_widget/widget_refresh.h"
#include "./comm_nor_vm/nor_vm_message.h"
#include "./comm_func/prayer_time_func.h"
#include "./comm_func/remote_music_func.h"
#include "./comm_nor_vm/nor_vm_activity.h"
#include "./comm_func/quran_player_func.h"
#include "./comm_func/azkar_prayer_func.h"
#include "./comm_nor_vm/nor_vm_call_log.h"
#include "./ui_menu/scrollbar/scrollbar.h"
#include "./comm_widget/widget_distance.h"
#include "./comm_nor_vm/nor_vm_contacts.h"
#include "./comm_func/hijri_calendar_func.h"
#include "./comm_func/tasbih_reminder_func.h"
#include "./ui_menu/split_screen/split_screen.h"
#include "../../../../include_lib/system/timer.h"
#include "../../../../include_lib/system/sys_time.h"
#include "../../../../include_lib/system/device/ioctl_cmds.h"


/**********时间滚轮共用**************/
extern const char time_hour_str[];
extern const char time_min_sec_str[];
extern const char time_ne30_po30_str[];

/**********页面跳转**************/
void ui_menu_jump(ui_act_id_t act_id);

/**********获取蓝牙mac**************/
const uint8_t *GetDevBtMac(void);
const uint8_t *GetDevBleMac(void);

/**********获取蓝牙名**************/
const char *GetDevBtName(void);
const char *GetDevBleName(void);

/**********获取双模蓝牙连接状态**************/
uint8_t GetDevBleBtConnectStatus(void);

/**********控制屏幕休眠**************/
void AppCtrlLcdEnterSleep(bool sleep);

/**********判断当前是否支持弹窗**************/
bool MenuSupportPopup(void);

/**********判断页面id的有效性**************/
bool ui_act_id_validity(ui_act_id_t act_id);

/**********设置系统背光**************/
void AppSetSysBacklight(int val);

/**********设置、获取系统时间**************/
void SetUtcTime(struct sys_time *utc_time);
void GetUtcTime(struct sys_time *utc_time);

/**********获取电池电量**************/
uint8_t GetBatteryPower(void);

/**********获取星期**************/
comm_enum_week_t GetUtcWeek(struct sys_time *utc_time);

/**********设备二维码链接(mac:45  name:66)**************/
char *GetQRCodeLinkStrBuf(void);                                                    

#ifdef __cplusplus
}
#endif

#endif
