#include "../lv_watch.h"
#include "common_refresh.h"
#include "../poc_modem/poc_modem_cache.h"

/**************刷新定时器id**************/
static uint16_t refresh_timer_id = 0;

/**************默认刷新间隔**************/
static const uint32_t default_refresh_timer_inv = 500;

static void common_refresh_timer_cb(void *priv)
{
    int menu_refr_img[1];
    menu_refr_img[0] = ui_msg_menu_refresh;\
    post_ui_msg(menu_refr_img, 1);

    return;
}

void common_refresh_msg_handle(void)
{
    lv_obj_t *obj = tileview_get_center_menu();

    ui_menu_refresh_func_cb refresh_func_cb = \
        p_ui_info_cache->menu_load_info.refresh_func_cb;

    if(refresh_func_cb)
        refresh_func_cb(obj);

    return;
}

void common_refresh_timer_create(void)
{
    uint32_t refresh_timer_inv = 500;
    uint32_t user_refresh_time_inv = \
        p_ui_info_cache->menu_load_info.user_refresh_time_inv;

    if(!user_refresh_time_inv)
        refresh_timer_inv = default_refresh_timer_inv;
    else
        refresh_timer_inv = user_refresh_time_inv;

    if(!refresh_timer_id)
        refresh_timer_id = sys_timer_add(NULL, common_refresh_timer_cb, refresh_timer_inv);

    return;
}

void common_refresh_timer_destroy(void)
{
    if(refresh_timer_id)
        sys_timer_del(refresh_timer_id);

    refresh_timer_id = 0;

    return;
}