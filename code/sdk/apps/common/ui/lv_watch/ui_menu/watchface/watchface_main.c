#include "watchface_main.h"


void wf_register_tileview_menu(lv_obj_t *obj)
{
    tileview_register_all_menu(Act_Id_Null, Act_Id_Null, \
        Act_Id_Null, Act_Id_Null, Act_Id_Watchface);
    tileview_menu_create(obj);

    return;
}

void wf_register_translate_menu(void)
{
    lv_obj_t *translate_container = tileview_get_center_menu();

    translate_register_all_menu(Act_Id_Null, Act_Id_Null, \
        Act_Id_Null, Act_Id_Weather);
    translate_menu_create(translate_container);

    return;
}
