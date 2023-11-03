#include "poc_modem_cache.h"

ui_info_cache_t *p_ui_info_cache = NULL;
static ui_info_cache_t ui_info_cache = {0};
const ui_menu_load_info_t *watchface_load_info_cache[Watchface_Id_Max] =
{
    &menu_load_watchface_00,
    &menu_load_watchface_01,
};

ui_act_id_t ui_cache_get_cur_act_id(void)
{
    return p_ui_info_cache->cur_act_id;
}

void ui_cache_set_cur_act_id(ui_act_id_t cur_act_id)
{
    p_ui_info_cache->cur_act_id = cur_act_id;
}

ui_act_id_t ui_cache_get_prev_act_id(void)
{
    return p_ui_info_cache->prev_act_id;
}

void ui_cache_set_prev_act_id(ui_act_id_t prev_act_id)
{
    p_ui_info_cache->prev_act_id = prev_act_id;
}

ui_watchface_id_t ui_cache_get_cur_watchface_id(void)
{
    return p_ui_info_cache->cur_watchface_id;
}

void ui_cache_set_cur_watchface_id(ui_watchface_id_t id)
{
    p_ui_info_cache->cur_watchface_id = id;
}

void ui_info_cache_init(ui_act_id_t act_id)
{
    p_ui_info_cache = &ui_info_cache;

    if(!p_ui_info_cache) ASSERT(0);

    memset(p_ui_info_cache, 0, sizeof(ui_info_cache_t));

    /************启动默认开机页面************/
    ui_cache_set_cur_act_id(act_id);
    ui_cache_set_prev_act_id(Act_Id_Null);

    /************启动默认表盘************/
    ui_cache_set_cur_watchface_id(Watchface_Id_00);

    return;
}



