#include "split_screen.h"

#if 0
static lv_anim_t split_screen_anim;
static bool is_split_screen = false; //是否满足拉出分屏的条件
static lv_obj_t *tileview_menu = NULL;
static int16_t split_screen_dela_x = 0;
static lv_obj_t *split_screen_container = NULL;

static void split_screen_anim_cb(void *var, int32_t anim_val)
{   
    split_screen_dela_x = anim_val;

    if(split_screen_container)
        lv_obj_set_style_translate_x(split_screen_container, anim_val, LV_PART_MAIN);

    return;
}

static void split_screen_anim_ready_cb(lv_anim_t *a)
{
    int16_t lcd_w = lv_disp_get_hor_res(NULL);

    lv_obj_t *tileview_menu = (lv_obj_t *)lv_anim_get_user_data(a);

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

    printf("%s:%d\n", __func__, is_split_screen);
        
    return;
}

static void split_screen_pressing_cb(lv_event_t *e)
{
    lv_point_t vert_p;

    if(!is_split_screen) return;

    int16_t lcd_w = lv_disp_get_hor_res(NULL);

    lv_indev_get_vect(lv_indev_get_act(), &vert_p);

    split_screen_dela_x += vert_p.x;

    split_screen_dela_x = split_screen_dela_x < 0?0:split_screen_dela_x;
    split_screen_dela_x = split_screen_dela_x > lcd_w/2?lcd_w/2:split_screen_dela_x;

    if(split_screen_container)
        lv_obj_set_style_translate_x(split_screen_container, split_screen_dela_x, LV_PART_MAIN);

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

        uint16_t anim_diff = LV_ABS(widget_anim_para.anim_end_val - \
            widget_anim_para.anim_start_val);
        uint16_t anim_duration = anim_diff*2;
        if(!anim_duration) anim_duration = 2;
        widget_anim_para.anim_duration = anim_duration;

        printf("%s:s=%d,e=%d\n", __func__, widget_anim_para.anim_start_val, \
            widget_anim_para.anim_end_val);

        widget_anim_para.anim_exec_xcb = split_screen_anim_cb;
        widget_anim_para.is_start_anim = false;
        common_widget_anim_create(&widget_anim_para);
        lv_anim_set_user_data(&split_screen_anim, (void *)tileview_menu);
        lv_anim_set_ready_cb(&split_screen_anim, split_screen_anim_ready_cb);
        lv_anim_start(&split_screen_anim);
    }

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

static void record_img_click_event_cb(lv_event_t *e)
{   
    if(!e) return;

    printf("%s\n", __func__);

    return;
}
#endif

#if 0
lv_obj_t *wf_register_left_split_screen(lv_obj_t *obj)
{
    if(!obj) return NULL;

    int16_t lcd_w = lv_disp_get_hor_res(NULL);
    int16_t lcd_h = lv_disp_get_ver_res(NULL);

    /*************分屏容器*************/
    widget_obj_para.obj_parent = obj;
    widget_obj_para.obj_x = -lcd_w/2;
    widget_obj_para.obj_y = 0;
    widget_obj_para.obj_width = lcd_w/2;
    widget_obj_para.obj_height = lcd_h;
    widget_obj_para.obj_bg_opax = LV_OPA_100;
    widget_obj_para.obj_bg_color = lv_color_hex(0x000000);
    widget_obj_para.obj_border_opax = LV_OPA_0;
    widget_obj_para.obj_border_width = 0;
    widget_obj_para.obj_border_color = lv_color_hex(0x000000);
    widget_obj_para.obj_radius = 0;
    widget_obj_para.obj_is_scrollable = false;
    lv_obj_t *split_screen_container = common_widget_obj_create(&widget_obj_para);

    /*************分屏:后台记录图标*************/
    widget_img_para.img_x = 11;
    widget_img_para.img_y = 178;
    widget_img_para.img_parent = split_screen_container;
    widget_img_para.file_img_dat = FILE_menu_icon_64x64_00_dat;
    widget_img_para.img_click_attr = true;
    widget_img_para.event_cb = NULL;
    widget_img_para.user_data = NULL;
    common_widget_img_create(&widget_img_para, NULL);

    widget_img_para.img_x = 86;
    widget_img_para.img_y = 178;
    widget_img_para.file_img_dat = FILE_menu_icon_64x64_01_dat;
    common_widget_img_create(&widget_img_para, NULL);

    widget_img_para.img_x = 11;
    widget_img_para.img_y = 262;
    widget_img_para.file_img_dat = FILE_menu_icon_64x64_02_dat;
    common_widget_img_create(&widget_img_para, NULL);

    widget_img_para.img_x = 86;
    widget_img_para.img_y = 262;
    widget_img_para.file_img_dat = FILE_menu_icon_64x64_03_dat;
    common_widget_img_create(&widget_img_para, NULL);

#if 0
    is_split_screen = false;
    split_screen_dela_x = 0;
    tileview_menu = p_ui_info_cache->ui_tileview_info.tileview_obj;

    lv_obj_add_event_cb(obj, split_screen_event_cb, LV_EVENT_ALL, NULL);
#endif

    return split_screen_container;
}
#endif
