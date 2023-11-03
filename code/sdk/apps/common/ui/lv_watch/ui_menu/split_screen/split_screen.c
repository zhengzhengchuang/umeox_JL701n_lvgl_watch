#include "split_screen.h"


static lv_anim_t split_screen_anim;
static bool is_split_screen = false; //是否拉出分屏
static lv_obj_t *tileview_menu = NULL;
static int16_t split_screen_dela_x = 0;
static lv_obj_t *split_screen_container = NULL;

static void split_screen_anim_cb(void *var, int32_t anim_val)
{   
    split_screen_dela_x = anim_val;

    lv_obj_set_style_translate_x(split_screen_container, anim_val, LV_PART_MAIN);

    return;
}

static void split_screen_anim_ready_cb(lv_anim_t *a)
{
    int16_t lcd_w = lv_disp_get_hor_res(NULL);

    lv_obj_t *tileview_menu = (lv_obj_t *)lv_anim_get_user_data(a);

    printf("%s:split_screen_dela_x = %d\n", __func__, split_screen_dela_x);

    if(split_screen_dela_x <= 0)
    {
        split_screen_dela_x = 0;
        lv_obj_add_flag(tileview_menu, LV_OBJ_FLAG_SCROLLABLE);
    }else if(split_screen_dela_x >= lcd_w/2)
    {
        split_screen_dela_x = lcd_w/2;   
        lv_obj_clear_flag(tileview_menu, LV_OBJ_FLAG_SCROLLABLE);
    }

    return;
}

static void split_screen_pressed_cb(lv_event_t *e)
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

    printf("%s\n", __func__);
        
    return;
}

static void split_screen_pressing_cb(lv_event_t *e)
{
    lv_point_t vert_p;

    if(!is_split_screen) return;

    int16_t lcd_w = lv_disp_get_hor_res(NULL);

    lv_indev_get_vect(lv_indev_get_act(), &vert_p);

    split_screen_dela_x += vert_p.x;

    if(split_screen_dela_x > 0 && split_screen_dela_x <= lcd_w/2)
    {
        if(split_screen_container)
            lv_obj_set_style_translate_x(split_screen_container, split_screen_dela_x, LV_PART_MAIN);
    }else
    {
        split_screen_dela_x = split_screen_dela_x < 0?0:split_screen_dela_x;
        split_screen_dela_x = split_screen_dela_x > lcd_w/2?lcd_w/2:split_screen_dela_x;
    } 
#if 0
    if(!split_screen_state)
    {
        
    }else
    {

    }
#endif

    return;
}

static void split_screen_released_cb(lv_event_t *e)
{
    if(!is_split_screen) return;

    lv_point_t vert_p;
    
    int16_t lcd_w = lv_disp_get_hor_res(NULL);

    lv_indev_get_vect(lv_indev_get_act(), &vert_p);

    printf("%s:split_screen_dela_x = %d\n", __func__, split_screen_dela_x);

    if(split_screen_dela_x <= 0)
    {
        split_screen_dela_x = 0;
        lv_obj_add_flag(tileview_menu, LV_OBJ_FLAG_SCROLLABLE);
    }else if(split_screen_dela_x >= lcd_w/2)
    {
        split_screen_dela_x = lcd_w/2;   
        lv_obj_clear_flag(tileview_menu, LV_OBJ_FLAG_SCROLLABLE);
    }else
    {
        widget_anim_para.anim = &split_screen_anim;
        widget_anim_para.anim_obj = split_screen_container;
        widget_anim_para.anim_duration = 200;
        widget_anim_para.anim_start_val = split_screen_dela_x + vert_p.x;

        if(vert_p.x < 0)
            widget_anim_para.anim_end_val = 0;
        else if(vert_p.x > 0)
            widget_anim_para.anim_end_val = lcd_w/2;
        else
        {
            if(split_screen_dela_x >= lcd_w/4)
                widget_anim_para.anim_end_val = lcd_w/2;
            else
                widget_anim_para.anim_end_val = 0; 
        }

        widget_anim_para.anim_exec_xcb = split_screen_anim_cb;
        widget_anim_para.is_start_anim = false;
        common_widget_anim_create(&widget_anim_para);
        lv_anim_set_user_data(&split_screen_anim, (void *)tileview_menu);
        lv_anim_set_ready_cb(&split_screen_anim, split_screen_anim_ready_cb);
        lv_anim_start(&split_screen_anim);
    }
#if 0
    if(!split_screen_state)
    {
        if(split_screen_dela_x <= 0)
        {
            split_screen_dela_x = 0;
            split_screen_state = false;
            lv_obj_add_flag(tileview_menu, LV_OBJ_FLAG_SCROLLABLE);
        }else if(split_screen_dela_x >= lcd_w/2)
        {
            split_screen_state = true;
            split_screen_dela_x = lcd_w/2;   
            lv_obj_clear_flag(tileview_menu, LV_OBJ_FLAG_SCROLLABLE);
        }else
        {
            widget_anim_para.anim = &split_screen_anim;
            widget_anim_para.anim_obj = split_screen_container;
            widget_anim_para.anim_duration = 200;
            widget_anim_para.anim_start_val = split_screen_dela_x;

            if(vert_p.x < 0)
                widget_anim_para.anim_end_val = 0;
            else if(vert_p.x > 0)
                widget_anim_para.anim_end_val = lcd_w/2;
            else
            {
                if(split_screen_dela_x >= lcd_w/4)
                   widget_anim_para.anim_end_val = lcd_w/2;
                else
                    widget_anim_para.anim_end_val = 0; 
            }
            widget_anim_para.anim_exec_xcb = split_screen_anim_cb;
            widget_anim_para.is_start_anim = false;
            common_widget_anim_create(&widget_anim_para);
            lv_anim_set_user_data(&split_screen_anim, parent);
            lv_anim_set_ready_cb(&split_screen_anim, split_screen_anim_ready_cb);
            lv_anim_start(&split_screen_anim);
        }
    }
#endif

    return;
}

static void split_screen_event_cb(lv_event_t *e)
{
    if(!e) return;

    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_PRESSED)
        split_screen_pressed_cb(e);
    else if(event_code == LV_EVENT_PRESSING)
        split_screen_pressing_cb(e);
    else if(event_code == LV_EVENT_RELEASED)
        split_screen_released_cb(e);

    return;
}

void menu_split_screen_create(lv_obj_t *obj)
{
    if(!obj) return;

    is_split_screen = false;
    split_screen_dela_x = 0;

    int16_t lcd_w = lv_disp_get_hor_res(NULL);
    int16_t lcd_h = lv_disp_get_ver_res(NULL);

    widget_obj_para.obj_parent = obj;
    widget_obj_para.obj_x = -lcd_w/2;
    widget_obj_para.obj_y = 0;
    widget_obj_para.obj_width = lcd_w/2;
    widget_obj_para.obj_height = lcd_h;
    widget_obj_para.obj_bg_opax = LV_OPA_80;
    widget_obj_para.obj_bg_color = lv_color_hex(0x363636);
    widget_obj_para.obj_border_opax = LV_OPA_0;
    widget_obj_para.obj_border_width = 0;
    widget_obj_para.obj_border_color = lv_color_hex(0x000000);
    widget_obj_para.obj_radius = 0;
    widget_obj_para.obj_is_scrollable = false;
    split_screen_container = common_widget_obj_create(&widget_obj_para);

    tileview_menu = lv_obj_get_parent(obj);

    lv_obj_add_event_cb(obj, split_screen_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(split_screen_container, split_screen_event_cb, LV_EVENT_ALL, NULL);

    return;
}

