#ifndef __LV_WATCH_H__
#define __LV_WATCH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "./include/ui_conf.h"
#include "./include/ui_menu.h"
#include "./include/ui_act_id.h"
#include "./poc_modem/poc_modem_ui.h"
#include "./ui_tileview/ui_tileview.h"
#include "./comm_widget/common_clock.h"
#include "./poc_modem/poc_modem_cache.h"
#include "./comm_widget/common_widget.h"
#include "./ui_menu/tool_box/tool_box.h"
#include "./ui_menu/split_screen/split_screen.h"
#include "../../../../include_lib/system/timer.h"
#include "../../../../include_lib/system/sys_time.h"
#include "../../../../include_lib/system/device/ioctl_cmds.h"

void ui_menu_jump(ui_act_id_t act_id);
bool ui_act_id_validity(ui_act_id_t act_id);
void ui_get_sys_time(struct sys_time *utc_time);
#ifdef __cplusplus
}
#endif

#endif
