#ifndef __LV_WATCH_H__
#define __LV_WATCH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "app_config.h"
#include "./include/ui_conf.h"
#include "./include/ui_menu.h"
#include "./include/version.h"
#include "./include/ui_act_id.h"
#include "./comm_lang/lang_conf.h"
#include "./comm_key/common_key.h"
#include "./comm_lang/lang_txtid.h"
#include "./poc_modem/poc_modem_ui.h"
#include "./ui_tileview/ui_tileview.h"
#include "./comm_widget/common_symb.h"
#include "./comm_widget/common_week.h"
#include "./comm_widget/common_data.h"
#include "./comm_widget/common_date.h"
#include "./comm_widget/common_time.h"
#include "./comm_refr/common_refresh.h"
#include "./comm_widget/common_clock.h"
#include "./poc_modem/poc_modem_cache.h"
#include "./comm_widget/common_widget.h"
#include "./ui_menu/tool_box/tool_box.h"
#include "./comm_func/common_stopwatch.h"
#include "./comm_func/common_countdown.h"
#include "./comm_widget/widget_refresh.h"
#include "./ui_menu/scrollbar/scrollbar.h"
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

#ifdef __cplusplus
}
#endif

#endif
