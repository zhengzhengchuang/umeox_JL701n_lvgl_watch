#include "tool_box.h"


static lv_obj_t *tool_box_container = NULL;

void menu_tool_box_create(lv_obj_t *obj)
{
    if(!obj) return;

    int16_t lcd_w = lv_disp_get_hor_res(NULL);
    int16_t lcd_h = lv_disp_get_ver_res(NULL);

    /*************分屏容器*************/
    widget_obj_para.obj_parent = obj;
    widget_obj_para.obj_x = 0;
    widget_obj_para.obj_y = -lcd_h;
    widget_obj_para.obj_width = lcd_w;
    widget_obj_para.obj_height = lcd_h;
    widget_obj_para.obj_bg_opax = LV_OPA_100;
    widget_obj_para.obj_bg_color = lv_color_hex(0x000000);
    widget_obj_para.obj_border_opax = LV_OPA_0;
    widget_obj_para.obj_border_width = 0;
    widget_obj_para.obj_border_color = lv_color_hex(0x000000);
    widget_obj_para.obj_radius = 0;
    widget_obj_para.obj_is_scrollable = false;
    tool_box_container = common_widget_obj_create(&widget_obj_para);

    return;
}


