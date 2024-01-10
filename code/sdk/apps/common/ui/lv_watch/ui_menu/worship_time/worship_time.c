#include "worship_time.h"

/****************元素容器点击索引****************/
static const uint16_t elem_container_idx[\
    Wsptime_List_Elem_Num] = 
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 
};

/****************礼拜时间列表滚动参数****************/
static bool wsptime_list_hor_scroll = false;
static int16_t wsptime_list_scroll_dela = 0;
static int16_t wsptime_list_scroll_offset = 0;

/****************礼拜时间列表按压点相关****************/
static lv_point_t wsptime_list_min_point = {0};
static lv_point_t wsptime_list_max_point = {0};
static lv_point_t wsptime_list_now_point = {0};
static lv_point_t wsptime_list_start_point = {0};

/****************礼拜时间列表可视化个数****************/
static const uint8_t wsptime_list_visual_num = \
    1;

/****************礼拜时间列表元素总数****************/
static const uint16_t wsptime_list_elem_num = \
    Wsptime_List_Elem_Num;

/****************礼拜时间列表元素容器的宽度****************/
static const uint16_t wsptime_list_elem_container_w = \
    260;

/****************礼拜时间列表元素容器的高度****************/
static const uint16_t wsptime_list_elem_container_h = \
    348;

/****************礼拜时间列表元素容器起始x****************/
static const int16_t wsptime_list_elem_container_sx = \
    54;

/****************礼拜时间列表元素容器间隔****************/
static const int16_t wsptime_list_elem_container_inv = \
    (260 + 20);

/****************礼拜时间列表参数内容****************/
static wsptime_list_ctx_t wsptime_list_ctx = {0};



/****************函数声明定义****************/
static void wsptime_list_elem_container_scroll(void);
static void wsptime_list_container_event_cb(lv_event_t *e);


/*********************************************************************************
                                  通过对象删除正在进行的动画                       
*********************************************************************************/
static void del_anim_with_var(void *var)
{
    if(!var) return;

    if(lv_anim_get(var, NULL))
        lv_anim_del(var, NULL);
        
    return;
}

/*********************************************************************************
                                  通过对象获取正在进行的动画                       
*********************************************************************************/
static bool anim_progress_with_var(void *var)
{
    if(lv_anim_get(var, NULL))
        return true;

    return false;
}

/*********************************************************************************
                                  礼拜时间列表容器透明度算法                                 
*********************************************************************************/
static uint8_t wsptime_list_elem_container_opa_algo(int16_t x)
{
    int16_t scr_center_x = \
        Wsptime_List_Container_W/2;
    uint16_t center_x_diff = \
        LV_ABS((x + wsptime_list_elem_container_w/2) - \
            scr_center_x);
    uint16_t center_x_diff_max = \
        wsptime_list_elem_container_inv*2;

    uint8_t lv_opax = LV_OPA_0;

    if(center_x_diff == 0)
        return LV_OPA_100;
    else if(center_x_diff >= center_x_diff_max)
        return LV_OPA_0;

    lv_opax = LV_OPA_100 - \
        (center_x_diff*LV_OPA_100)/center_x_diff_max;
    
    return lv_opax;
}

/*********************************************************************************
                                  礼拜时间列表横向滚动判断                             
*********************************************************************************/
static void wsptime_list_hor_scroll_judge(void)
{
    lv_indev_t *indev_act = lv_indev_get_act();

    lv_indev_get_point(indev_act, &wsptime_list_now_point);

    if(wsptime_list_now_point.x > wsptime_list_max_point.x)
        wsptime_list_max_point.x = wsptime_list_now_point.x;

    if(wsptime_list_now_point.x < wsptime_list_min_point.x)
        wsptime_list_min_point.x = wsptime_list_now_point.x;

    if(wsptime_list_now_point.y > wsptime_list_max_point.y)
        wsptime_list_max_point.y = wsptime_list_now_point.y;

    if(wsptime_list_now_point.y < wsptime_list_min_point.y)
        wsptime_list_min_point.y = wsptime_list_now_point.y;

    int16_t wsptime_list_x_max = wsptime_list_max_point.x - \
        wsptime_list_min_point.x;
    int16_t wsptime_list_y_max = wsptime_list_max_point.y - \
        wsptime_list_min_point.y;

    if(LV_ABS(wsptime_list_x_max) >= LV_ABS(wsptime_list_y_max) && \
        LV_ABS(wsptime_list_x_max) >= 10)
        wsptime_list_hor_scroll = true;
    else
        wsptime_list_hor_scroll = false;

    return;
}

/*********************************************************************************
                                  礼拜时间列表计算横向抛出距离                         
*********************************************************************************/
static int16_t wsptime_list_calc_throw_sum(int16_t throw_vert)
{
    int16_t throw_vert_sum = 0;
    int16_t throw_vert_tmp = throw_vert;
    
    while(throw_vert_tmp)
    {
        throw_vert_sum += throw_vert_tmp;
        throw_vert_tmp = throw_vert_tmp * 90 / 100;
    }
    
    return throw_vert_sum;
}

/*********************************************************************************
                                  礼拜时间列表计算横向抛出动画                         
*********************************************************************************/
static void wsptime_list_throw_anim_cb(void *var, int32_t val)
{
    wsptime_list_scroll_offset = val;

    wsptime_list_elem_container_scroll();

    return;
}

/*********************************************************************************
                                  创建礼拜时间列表容器                                 
*********************************************************************************/
static void wsptime_list_container_create(lv_obj_t *obj)
{
    lv_obj_t **wsptime_list_container = \
        &(wsptime_list_ctx.wsptime_list_container);

    widget_obj_para.obj_parent = obj;
    widget_obj_para.obj_x = 0;
    widget_obj_para.obj_y = 0;
    widget_obj_para.obj_width = Wsptime_List_Container_W;
    widget_obj_para.obj_height = Wsptime_List_Container_H;
    widget_obj_para.obj_bg_opax = LV_OPA_100;
    widget_obj_para.obj_bg_color = lv_color_hex(0x000000);
    widget_obj_para.obj_border_opax = LV_OPA_0;
    widget_obj_para.obj_border_width = 0;
    widget_obj_para.obj_border_color = lv_color_hex(0x000000);
    widget_obj_para.obj_radius = 0;
    widget_obj_para.obj_is_scrollable = false;
    *wsptime_list_container = \
        common_widget_obj_create(&widget_obj_para);
    lv_obj_add_event_cb(*wsptime_list_container, \
        wsptime_list_container_event_cb, \
        LV_EVENT_ALL, NULL);

    return;
}

/*********************************************************************************
                                  礼拜时间列表元素容器点击回调                          
*********************************************************************************/
static void wsptime_list_elem_container_click_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *wsptime_list_container = \
        wsptime_list_ctx.wsptime_list_container;

    bool anim_progress = \
        anim_progress_with_var(wsptime_list_container);

    if(wsptime_list_hor_scroll || anim_progress)
        return;

    uint16_t idx = *(uint16_t *)lv_event_get_user_data(e);

    printf("******%s:%d\n", __func__, idx);

    return;
}

/*********************************************************************************
                                  礼拜时间列表元素容器创建                             
*********************************************************************************/
static void wsptime_list_elem_container_create(void)
{
    lv_obj_t *wsptime_list_container = \
        wsptime_list_ctx.wsptime_list_container;
    lv_obj_t **wsptime_list_elem_container = \
        wsptime_list_ctx.wsptime_list_elem_container;

    widget_obj_para.obj_parent = wsptime_list_container;
    widget_obj_para.obj_width = wsptime_list_elem_container_w;
    widget_obj_para.obj_height = wsptime_list_elem_container_h;
    widget_obj_para.obj_bg_color = lv_color_hex(0xff0000);
    widget_obj_para.obj_border_opax = LV_OPA_0;
    widget_obj_para.obj_border_width = 0;
    widget_obj_para.obj_border_color = lv_color_hex(0x000000);
    widget_obj_para.obj_radius = 30;
    widget_obj_para.obj_is_scrollable = false;

    uint8_t lv_opax = LV_OPA_0;
    int16_t elem_container_y = (Wsptime_List_Container_H - \
        wsptime_list_elem_container_h)/2;
    for(uint16_t idx = 0; idx < wsptime_list_elem_num; idx++)
    {
        widget_obj_para.obj_x = wsptime_list_elem_container_sx + \
            wsptime_list_elem_container_inv*idx + \
            wsptime_list_scroll_offset + wsptime_list_scroll_dela;
        widget_obj_para.obj_y = elem_container_y;
        widget_obj_para.obj_bg_opax = \
            wsptime_list_elem_container_opa_algo(widget_obj_para.obj_x);
        wsptime_list_elem_container[idx] = \
            common_widget_obj_create(&widget_obj_para);
        lv_obj_add_flag(wsptime_list_elem_container[idx], \
            LV_OBJ_FLAG_EVENT_BUBBLE);
        lv_obj_add_event_cb(wsptime_list_elem_container[idx], \
            wsptime_list_elem_container_click_cb, \
            LV_EVENT_SHORT_CLICKED, (void *)&elem_container_idx[idx]);
    }

    return;
}

/*********************************************************************************
                                  礼拜时间列表元素容器滚动                             
*********************************************************************************/
static void wsptime_list_elem_container_scroll(void)
{
    int16_t obj_x = 0;
    lv_opa_t lv_opax = LV_OPA_100;
    lv_obj_t **wsptime_list_elem_container = \
        wsptime_list_ctx.wsptime_list_elem_container;
 
    for(uint16_t idx = 0; idx < wsptime_list_elem_num; idx++)
    {
        obj_x = wsptime_list_elem_container_sx + \
            wsptime_list_elem_container_inv*idx + \
            wsptime_list_scroll_offset + wsptime_list_scroll_dela;
        lv_opax = \
            wsptime_list_elem_container_opa_algo(obj_x);
        lv_obj_set_x(wsptime_list_elem_container[idx], obj_x);
        lv_obj_set_style_bg_opa(wsptime_list_elem_container[idx], \
            lv_opax, LV_PART_MAIN);
    }

    return;
}

/*********************************************************************************
                                  礼拜时间列表容器事件回调                                 
*********************************************************************************/
static void wsptime_list_container_pressed_cb(lv_event_t *e)
{
    wsptime_list_scroll_dela = 0;

    wsptime_list_hor_scroll = false;

    lv_indev_t *indev_act = lv_indev_get_act();

    lv_indev_get_point(indev_act, &wsptime_list_start_point);

    memcpy(&wsptime_list_now_point, &wsptime_list_start_point, \
        sizeof(lv_point_t));
    memcpy(&wsptime_list_min_point, &wsptime_list_start_point, \
        sizeof(lv_point_t));
    memcpy(&wsptime_list_max_point, &wsptime_list_start_point, \
        sizeof(lv_point_t));

    return;
}

static void wsptime_list_container_pressing_cb(lv_event_t *e)
{
    if(!wsptime_list_hor_scroll)
    {
        wsptime_list_hor_scroll_judge();

        if(wsptime_list_hor_scroll)
        {
            lv_obj_t *wsptime_list_container = \
                wsptime_list_ctx.wsptime_list_container;
            del_anim_with_var(wsptime_list_container);
        }
    }else
    {
        lv_point_t wsptime_list_scroll_vert;
        lv_indev_t *indev_act = lv_indev_get_act();
        lv_indev_get_vect(indev_act, &wsptime_list_scroll_vert);
        wsptime_list_scroll_dela += wsptime_list_scroll_vert.x;

        int16_t scroll_left_val = 0;
        int16_t scroll_right_val = \
            (-1)*(wsptime_list_elem_num - wsptime_list_visual_num) * \
            wsptime_list_elem_container_inv;

        if(wsptime_list_scroll_offset + wsptime_list_scroll_dela > \
            scroll_left_val + wsptime_list_elem_container_inv/2)
        {
            wsptime_list_scroll_dela = \
                (scroll_left_val + wsptime_list_elem_container_inv/2) - \
                    wsptime_list_scroll_offset;
        }else if(wsptime_list_scroll_offset + wsptime_list_scroll_dela < \
            scroll_right_val - wsptime_list_elem_container_inv/2)
        {
            wsptime_list_scroll_dela = \
                (scroll_right_val - wsptime_list_elem_container_inv/2) - \
                    wsptime_list_scroll_offset;
        }
        
        wsptime_list_elem_container_scroll();
    }

    return;
}

static void wsptime_list_container_release_cb(lv_event_t *e)
{
    if(!wsptime_list_hor_scroll)
        return;

    lv_point_t wsptime_list_throw_vert;
    lv_indev_t *indev_act = lv_indev_get_act();
    lv_indev_get_throw(indev_act, &wsptime_list_throw_vert);

    int16_t throw_sum = wsptime_list_calc_throw_sum(wsptime_list_throw_vert.x);

    wsptime_list_scroll_offset += wsptime_list_scroll_dela;
    wsptime_list_scroll_dela = 0;

    int16_t scroll_left_val = 0;
    int16_t scroll_right_val = \
        (-1)*(wsptime_list_elem_num - wsptime_list_visual_num)* \
        wsptime_list_elem_container_inv;

    int16_t throw_start = wsptime_list_scroll_offset;
    int16_t throw_end = wsptime_list_scroll_offset + throw_sum;

    int16_t throw_adjust = 0;
    uint32_t anim_duration = 0;
    uint32_t anim_min_duration = 300;
    uint32_t anim_max_duration = 900;

    if(throw_end > scroll_right_val && \
        throw_end < scroll_left_val)
    {
        throw_adjust = \
            throw_end%wsptime_list_elem_container_inv;
		if(throw_adjust <= (-1)*(wsptime_list_elem_container_inv/2))
            throw_end -= \
                (wsptime_list_elem_container_inv + throw_adjust);	
		else
            throw_end -= throw_adjust;

        anim_duration = LV_ABS(throw_sum)*2;
        
    }else if(throw_end > scroll_left_val)
    {
        throw_end = scroll_left_val;

        if(throw_start != scroll_left_val)
            anim_duration = \
                LV_ABS(scroll_left_val - throw_start)*2;
        else
            anim_duration = anim_min_duration;
    }else if(throw_end < scroll_right_val)
    {
        throw_end = scroll_right_val;

        if(throw_start != scroll_left_val)
            anim_duration = \
                LV_ABS(scroll_right_val - throw_start)*2;
        else
            anim_duration = anim_min_duration;
    }

    if(anim_duration < anim_min_duration) 
        anim_duration = anim_min_duration;
    if(anim_duration > anim_max_duration) 
        anim_duration = anim_max_duration;

    lv_anim_t throw_anim;
    lv_obj_t *wsptime_list_container = \
        wsptime_list_ctx.wsptime_list_container;

    widget_anim_para.anim = &throw_anim;
    widget_anim_para.anim_obj = \
        wsptime_list_container;
    widget_anim_para.anim_exec_xcb = \
        wsptime_list_throw_anim_cb; 
    widget_anim_para.anim_duration = anim_duration;
    widget_anim_para.anim_start_val = throw_start;
    widget_anim_para.anim_end_val = throw_end;
    widget_anim_para.is_start_anim = false;
    common_widget_anim_create(&widget_anim_para);
    lv_anim_set_path_cb(widget_anim_para.anim, \
        lv_anim_path_ease_out);
    lv_anim_start(widget_anim_para.anim);

    return;
}

static void wsptime_list_container_event_cb(lv_event_t *e)
{
    if(!e) return;

    lv_event_code_t event_code = \
        lv_event_get_code(e);

    if(event_code == LV_EVENT_PRESSED)
        wsptime_list_container_pressed_cb(e);
    else if(event_code == LV_EVENT_PRESSING)
        wsptime_list_container_pressing_cb(e);
    else if(event_code == LV_EVENT_RELEASED)
        wsptime_list_container_release_cb(e);

    return;
} 

/*********************************************************************************
                                  礼拜时间列表布局创建                                 
*********************************************************************************/
static void wsptime_list_layout_create(void)
{
    wsptime_list_elem_container_create();

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_null, \
            ui_act_id_worship_time);

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    return;
}

static void menu_refresh_cb(lv_obj_t *obj)
{
    if(!obj) return;

    return;
}

static void menu_display_cb(lv_obj_t *obj)
{
    if(!obj) return;

    memset(&wsptime_list_ctx, 0, \
        sizeof(wsptime_list_ctx_t));

    wsptime_list_container_create(obj);

    wsptime_list_layout_create();

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_worship_time) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_worship_time,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
