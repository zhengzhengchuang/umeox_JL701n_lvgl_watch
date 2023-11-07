#include "tool_box.h"

#if 0
static bool is_tool_box = false;
static int16_t tool_box_dela_y = 0;
static lv_obj_t *tileview_menu = NULL;
static lv_obj_t *tool_box_container = NULL;

static void tool_box_pressed_cb(lv_event_t *e)
{
    lv_point_t act_p;

    int16_t lcd_w = lv_disp_get_hor_res(NULL);

    lv_indev_get_point(lv_indev_get_act(), &act_p);
 
    if(lv_obj_has_flag(tileview_menu, LV_OBJ_FLAG_SCROLLABLE))
    {
        if(act_p.x < lcd_w/10)
            is_split_screen = true;
        else
            is_split_screen = false;
    }else
        is_split_screen = true;
    

    if(is_split_screen)
        lv_obj_clear_flag(tileview_menu, LV_OBJ_FLAG_SCROLLABLE);

    return;
}

static void tool_box_pressing_cb(lv_event_t *e)
{
    printf("%s\n", __func__);

    return;
}

static void tool_box_released_cb(lv_event_t *e)
{
    printf("%s\n", __func__);

    return;
}

static void tool_box_event_cb(lv_event_t *e)
{
    if(!e) return;

    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_PRESSED)
        tool_box_pressed_cb(e);
    else if(event_code == LV_EVENT_PRESSING)
        tool_box_pressing_cb(e);
    else if(event_code == LV_EVENT_RELEASED)
        tool_box_released_cb(e);

    return;
}
#endif

#if 0
lv_obj_t *wf_register_up_tool_box(lv_obj_t *obj)
{
    if(!obj) return NULL;

    int16_t lcd_w = lv_disp_get_hor_res(NULL);
    int16_t lcd_h = lv_disp_get_ver_res(NULL);

    /*************盒子容器*************/
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
    widget_obj_para.obj_is_scrollable = true;
    lv_obj_t *tool_box_container = common_widget_obj_create(&widget_obj_para);
    lv_obj_set_style_pad_bottom(tool_box_container, 60, LV_PART_MAIN);

    widget_button_para.button_parent = tool_box_container;
    widget_button_para.button_x = 10;
    widget_button_para.button_y = 60;
    widget_button_para.button_width = 145;
    widget_button_para.button_height = 90;
    widget_button_para.button_main_opax = LV_OPA_100;
    widget_button_para.button_main_color = lv_color_hex(0x545454);
    widget_button_para.button_radius = 90/2;
    widget_button_para.event_cb = NULL;
    widget_button_para.user_data = NULL;
    common_widget_button_create(&widget_button_para);

    widget_button_para.button_x = 165;
    widget_button_para.button_y = 60;
    common_widget_button_create(&widget_button_para);

    widget_button_para.button_x = 10;
    widget_button_para.button_y = 160;
    common_widget_button_create(&widget_button_para);

    widget_button_para.button_x = 165;
    widget_button_para.button_y = 160;
    common_widget_button_create(&widget_button_para);

    widget_button_para.button_x = 10;
    widget_button_para.button_y = 260;
    common_widget_button_create(&widget_button_para);

    widget_button_para.button_x = 165;
    widget_button_para.button_y = 260;
    common_widget_button_create(&widget_button_para);

    widget_button_para.button_x = 10;
    widget_button_para.button_y = 360;
    common_widget_button_create(&widget_button_para);

    widget_button_para.button_x = 165;
    widget_button_para.button_y = 360;
    common_widget_button_create(&widget_button_para);

    widget_button_para.button_x = 10;
    widget_button_para.button_y = 460;
    common_widget_button_create(&widget_button_para);

    widget_button_para.button_x = 165;
    widget_button_para.button_y = 460;
    common_widget_button_create(&widget_button_para);

    
#if 0
    is_tool_box = false;
    tool_box_dela_y = 0;
    tileview_menu = p_ui_info_cache->ui_tileview_info.tileview_obj;

    lv_obj_add_event_cb(obj, tool_box_event_cb, LV_EVENT_ALL, NULL);
#endif

    return tool_box_container;
}
#endif
