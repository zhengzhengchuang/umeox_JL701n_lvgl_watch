#include "watchface_main.h"

void wf_register_tileview_menu(lv_obj_t *obj)
{
    tileview_register_right_menu(Act_Id_Weather);
    tileview_register_center_menu(Act_Id_Watchface);
    tileview_menu_create(obj);

    return;
}

void wf_left_split_screen_create(lv_obj_t *obj)
{
    menu_split_screen_create(obj);

    return;
}
