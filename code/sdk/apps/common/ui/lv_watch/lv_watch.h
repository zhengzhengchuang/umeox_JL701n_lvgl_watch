#ifndef __LV_WATCH_H__
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
#include "./include/ui_act_id.h"
#include "./comm_lang/lang_conf.h"
#include "./comm_key/common_key.h"
#include "./comm_lang/lang_txtid.h"
#include "./comm_widget/widget_bo.h"
#include "./comm_widget/widget_hr.h"
#include "./comm_nor_vm/nor_vm_cfg.h"
#include "./poc_modem/poc_modem_ui.h"
#include "./ui_tileview/ui_tileview.h"
#include "./comm_widget/common_symb.h"
#include "./comm_widget/widget_step.h"
#include "./comm_widget/widget_pace.h"
#include "./comm_widget/widget_week.h"
#include "./comm_widget/common_data.h"
#include "./comm_widget/widget_date.h"
#include "./comm_widget/widget_time.h"
#include "./comm_refr/common_refresh.h"
#include "./comm_widget/widget_clock.h"
#include "./comm_remind/alarm_manage.h"
#include "./poc_modem/poc_modem_cache.h"
#include "./comm_widget/common_widget.h"
#include "./ui_menu/tool_box/tool_box.h"
#include "./comm_nor_vm/nor_vm_weather.h"
#include "./comm_widget/widget_weather.h"
#include "./comm_widget/widget_calorie.h"
#include "./comm_func/common_stopwatch.h"
#include "./comm_func/common_countdown.h"
#include "./comm_widget/widget_refresh.h"
#include "./comm_nor_vm/nor_vm_call_log.h"
#include "./ui_menu/scrollbar/scrollbar.h"
#include "./comm_widget/widget_distance.h"
#include "./comm_nor_vm/nor_vm_contacts.h"
#include "./ui_menu/split_screen/split_screen.h"
#include "../../../../include_lib/system/timer.h"
#include "../../../../include_lib/system/sys_time.h"
#include "../../../../include_lib/system/device/ioctl_cmds.h"

/**********ui层页面菜单跳转**************/
void ui_menu_jump(ui_act_id_t act_id);

/**********ui层获取蓝牙mac**************/
const uint8_t *ui_get_dev_bt_mac(void);
const uint8_t *ui_get_dev_ble_mac(void);

/**********ui层获取蓝牙名**************/
const char *ui_get_dev_bt_name(void);
const char *ui_get_dev_ble_name(void);

/**********ui层获取双模蓝牙连接状态**************/
uint8_t ui_get_ble_bt_connect_status(void);

/**********ui层控制屏幕休眠**************/
void ui_ctl_lcd_enter_sleep(bool sleep);

/**********ui层判断页面id的有效性**************/
bool ui_act_id_validity(ui_act_id_t act_id);

/**********ui层设置系统背光**************/
void ui_set_sys_backlight(int backlight_val);

/**********ui层设置、获取系统时间**************/
void ui_set_sys_time(struct sys_time *utc_time);
void ui_get_sys_time(struct sys_time *utc_time);

/**********ui层获取星期**************/
comm_enum_week_t ui_get_sys_week(struct sys_time *utc_time);

/**********通过电话号码拨出电话**************/
void ui_ctrl_call_out_by_number(char *call_number, uint8_t number_len);


/*********************************************************************************
                                获取来电号码
                    (如果联系人列表有，返回名字，否则返回号码)                                    
*********************************************************************************/
char *ui_get_call_number_name(void);

/*********************************************************************************
                                控制通话接听                                   
*********************************************************************************/
void ui_ctrl_call_answer(void);

/*********************************************************************************
                                控制通话挂断                                   
*********************************************************************************/
void ui_ctrl_call_hang_up(void);

/*********************************************************************************
                                通话记录状态及信息保存                                   
*********************************************************************************/
void record_call_out_or_in(uint8_t out_or_in);
void record_call_is_answer(bool is_answer);
void record_call_status_clear(void);
void update_call_log_message_flash(void);

/*********************************************************************************
                                通话中获取音量                                   
*********************************************************************************/
uint8_t ui_get_calling_volumn(void);

/*********************************************************************************
                                拨出、拨入弹出页面                                   
*********************************************************************************/
void ui_call_out_or_in_menu_jump(void);

/*********************************************************************************
                                挂断后页面跳转                                  
*********************************************************************************/
void ui_call_hang_up_menu_jump(void);

/*********************************************************************************
                                接通后页面跳转                                  
*********************************************************************************/
void ui_call_answer_menu_jump(void);

/*********************************************************************************
                                通话在线时长操作                                  
*********************************************************************************/
uint16_t get_call_online_timer_id(void);
uint32_t ui_get_call_online_duration(void);
void call_online_duration_timer_create(void);
void call_online_duration_timer_delete(void);

/*********************************************************************************
                                ui控制查找手机                                  
*********************************************************************************/
void ui_ctrl_ble_dev_find_phone(void);

/*********************************************************************************
                                ui控制手机相机相关操作                                 
*********************************************************************************/
void ui_ctrl_phone_enter_camera(void);    //进入相机
void ui_ctrl_phone_exit_camera(void);     //退出相机
void ui_ctrl_phone_take_photos(void);     //拍照
void ui_ctrl_phone_dly_take_photos(void); //延时拍照

#ifdef __cplusplus
}
#endif

#endif
