#ifndef __POC_MODEM_CACHE_H__
#define __POC_MODEM_CACHE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"
#include "../include/ui_act_id.h"
#include "../ui_cover/ui_cover.h"
#include "../ui_tileview/ui_tileview.h"
#include "../ui_translate/ui_translate.h"

typedef struct
{
    ui_act_id_t cur_act_id;
    ui_act_id_t prev_act_id;

    lv_obj_t *ui_menu_container;

    ui_cover_info_t ui_cover_info;

    ui_menu_load_info_t menu_load_info;

    ui_watchface_id_t cur_watchface_id;

    ui_tileview_info_t ui_tileview_info;

    ui_translate_info_t ui_translate_info;
}ui_info_cache_t;
extern ui_info_cache_t *p_ui_info_cache;
extern const ui_menu_load_info_t *watchface_load_info_cache[Watchface_Id_Max];

ui_act_id_t ui_cache_get_cur_act_id(void);
void ui_cache_set_cur_act_id(ui_act_id_t cur_act_id);

ui_act_id_t ui_cache_get_prev_act_id(void);
void ui_cache_set_prev_act_id(ui_act_id_t prev_act_id);

ui_watchface_id_t ui_cache_get_cur_watchface_id(void);
void ui_cache_set_cur_watchface_id(ui_watchface_id_t id);

void ui_info_cache_init(ui_act_id_t act_id);
#ifdef __cplusplus
}
#endif

#endif
