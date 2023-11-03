#ifndef __POC_MODEM_UI_H__
#define __POC_MODEM_UI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "poc_modem_cache.h"
#include "../include/ui_menu.h"
#include "../include/ui_act_id.h"
#include "../../../../../cpu/br28/ui_driver/lvgl/lvgl_main.h"


void ui_menu_jump_handle(ui_act_id_t act_id);
void ui_menu_jump_post_msg(ui_act_id_t act_id);
ui_menu_load_info_t *ui_menu_load_info(ui_act_id_t act_id);
#ifdef __cplusplus
}
#endif

#endif
