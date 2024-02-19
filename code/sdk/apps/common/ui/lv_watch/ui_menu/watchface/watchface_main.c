#include "watchface_main.h"

void wf_tileview_register_all_menu(\
    lv_obj_t *obj)
{
    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_null, \
            ui_act_id_watchface);

    return;
}

