#include "common_list2.h"

/****************菜单id****************/
static const ui_act_id_t common_list2_act_id[\
    Common_List2_Elem_Num] = 
{
    ui_act_id_call_main, ui_act_id_msg_list, ui_act_id_null, \
    ui_act_id_null, ui_act_id_prayer_time_main, ui_act_id_azkar_list, \
    ui_act_id_tasbih_main, ui_act_id_al_name_list, ui_act_id_Gcalendar_main, \
    ui_act_id_null, ui_act_id_sleep_main, ui_act_id_weather_data, \
    ui_act_id_hr_sample, ui_act_id_bo_sample, ui_act_id_alarm_main, \
    ui_act_id_more_menu, ui_act_id_set_main, 
};

/****************元素容器点击索引****************/
static const uint16_t common_list2_elem_container_idx[\
    Common_List2_Elem_Num] =
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
    10, 11, 12, 13, 14, 15, 16 
};

/****************通用列表2滚动参数****************/
static int16_t common_list2_scroll_dela = 0;
static int16_t common_list2_scroll_offset = 0;

/****************通用列表2是否滚动****************/
static bool common_list2_ver_scroll = false;

/****************通用列表2按压点相关****************/
static lv_point_t common_list2_min_point = {0};
static lv_point_t common_list2_max_point = {0};
static lv_point_t common_list2_now_point = {0};
static lv_point_t common_list2_start_point = {0};

/****************通用列表2参数内容****************/
static common_list2_ctx_t common_list2_ctx = \
    {0};

/****************通用列表2元素总数****************/
static const uint16_t common_list2_elem_num = \
    Common_List2_Elem_Num;

/****************通用列表2可视化行****************/
static const uint8_t common_list2_visual_line = \
    3;
    
/****************通用列表2元素容器sx****************/
static const int16_t common_list2_elem_container_sx = \
    22;

/****************通用列表2元素容器sy****************/
static const int16_t common_list2_elem_container_sy = \
    23;

/****************通用列表2元素容器宽****************/
static const int16_t common_list2_elem_container_width = \
    108;

/****************通用列表2元素容器高****************/
static const int16_t common_list2_elem_container_height = \
    134;


/****************函数声明定义****************/
static void common_list2_elem_container_scroll(void);
static void common_list2_container_event_cb(lv_event_t *e);


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
                                  通用列表2纵向滚动判断                             
*********************************************************************************/
static void common_list2_ver_scroll_judge(void)
{
    lv_indev_t *indev_act = lv_indev_get_act();

    lv_indev_get_point(indev_act, &common_list2_now_point);

    if(common_list2_now_point.x > common_list2_max_point.x)
        common_list2_max_point.x = common_list2_now_point.x;

    if(common_list2_now_point.x < common_list2_min_point.x)
        common_list2_min_point.x = common_list2_now_point.x;

    if(common_list2_now_point.y > common_list2_max_point.y)
        common_list2_max_point.y = common_list2_now_point.y;

    if(common_list2_now_point.y < common_list2_min_point.y)
        common_list2_min_point.y = common_list2_now_point.y;

    int16_t common_list2_x_max = common_list2_max_point.x - \
        common_list2_min_point.x;
    int16_t common_list2_y_max = common_list2_max_point.y - \
        common_list2_min_point.y;

    if(LV_ABS(common_list2_y_max) >= LV_ABS(common_list2_x_max) && \
        LV_ABS(common_list2_y_max) >= 10)
        common_list2_ver_scroll = true;
    else
        common_list2_ver_scroll = false;

    return;
}

/*********************************************************************************
                                  通用列表2计算纵向抛出距离                         
*********************************************************************************/
static int16_t common_list2_calc_throw_sum(int16_t throw_vert)
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
                                  通用列表2计算纵向抛出动画                         
*********************************************************************************/
static void common_list2_throw_anim_cb(void *var, int32_t val)
{
    common_list2_scroll_offset = val;

    common_list2_elem_container_scroll();

    common_scrollbar_press_handle(\
        common_list2_scroll_offset);

    return;
}

/*********************************************************************************
                                  通用列表2纵向抛出动画结束                       
*********************************************************************************/
static void common_list2_throw_anim_ready_cb(lv_anim_t *anim)
{
    common_scrollbar_released_handle();

    return;
}

/*********************************************************************************
                                  创建通用列表2容器                                 
*********************************************************************************/
static void common_list2_container_create(lv_obj_t *obj)
{
    lv_obj_t **common_list2_container = \
        &(common_list2_ctx.common_list2_container);

    widget_obj_para.obj_parent = obj;
    widget_obj_para.obj_x = 0;
    widget_obj_para.obj_y = \
        LCD_UI_Y_OFFSET;
    widget_obj_para.obj_width = \
        Common_List2_Container_W;
    widget_obj_para.obj_height = \
        Common_List2_Container_H;
    widget_obj_para.obj_bg_opax = \
        LV_OPA_0;
    widget_obj_para.obj_bg_color = \
        lv_color_hex(0x000000);
    widget_obj_para.obj_border_opax = \
        LV_OPA_0;
    widget_obj_para.obj_border_width = 0;
    widget_obj_para.obj_border_color = \
        lv_color_hex(0x000000);
    widget_obj_para.obj_radius = 0;
    widget_obj_para.obj_is_scrollable = false;
    *common_list2_container = \
        common_widget_obj_create(&widget_obj_para);
    lv_obj_add_event_cb(*common_list2_container, \
        common_list2_container_event_cb, LV_EVENT_ALL, NULL);

    return;
}

/*********************************************************************************
                                  通用列表2元素容器点击回调                          
*********************************************************************************/
static void common_list2_elem_container_click_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *common_list2_container = \
        common_list2_ctx.common_list2_container;

    bool anim_progress = \
        anim_progress_with_var(common_list2_container);

    if(common_list2_ver_scroll || anim_progress)
        return;

    uint16_t idx = *(uint16_t *)lv_event_get_user_data(e);

    if(idx == 2)
    {
        bool cali_succ = \
            GetSensorGmCaliSucc();
        if(cali_succ == false)
            ui_menu_jump(ui_act_id_gm_cali);
        else
        {
            if(!(ll_info.position_valid))
                ui_menu_jump(ui_act_id_kaaba_position);   
            else
                ui_menu_jump(ui_act_id_kaaba_qibla);
        }
    }else
    {
        ui_menu_jump(\
            common_list2_act_id[idx]);
    }

    return;
}

/*********************************************************************************
                                  通用列表2元素容器创建                             
*********************************************************************************/
static void common_list2_elem_container_create(\
    menu_align_t menu_align)
{
    lv_obj_t **common_list2_elem_container = \
        common_list2_ctx.common_list2_elem_container;
    lv_obj_t *common_list2_container = \
        common_list2_ctx.common_list2_container;

    widget_obj_para.obj_parent = \
        common_list2_container;
    widget_obj_para.obj_width = \
        common_list2_elem_container_width;
    widget_obj_para.obj_height = \
        common_list2_elem_container_height;
    widget_obj_para.obj_bg_opax = \
        LV_OPA_0;
    widget_obj_para.obj_bg_color = \
        lv_color_hex(0x000000);
    widget_obj_para.obj_border_opax = \
        LV_OPA_0;
    widget_obj_para.obj_border_width = 0;
    widget_obj_para.obj_border_color = \
        lv_color_hex(0x000000);
    widget_obj_para.obj_radius = 0;
    widget_obj_para.obj_is_scrollable = false;

    for(uint16_t idx = 0; idx < common_list2_elem_num; idx++)
    {
        widget_obj_para.obj_x = \
            common_list2_elem_container_sx + \
                common_list2_elem_container_width*(idx%3);
        widget_obj_para.obj_y = \
            common_list2_elem_container_sy + \
                common_list2_elem_container_height*(idx/3) + \
                    common_list2_scroll_offset + common_list2_scroll_dela;
        common_list2_elem_container[idx] = \
            common_widget_obj_create(&widget_obj_para);
        lv_obj_add_flag(common_list2_elem_container[idx], \
            LV_OBJ_FLAG_EVENT_BUBBLE);
        lv_obj_add_event_cb(common_list2_elem_container[idx], \
            common_list2_elem_container_click_cb, LV_EVENT_SHORT_CLICKED, \
                (void *)&common_list2_elem_container_idx[idx]);

        if(widget_obj_para.obj_y >= Common_List2_Container_H || \
            (widget_obj_para.obj_y + common_list2_elem_container_height) < 0)
        {
            lv_obj_add_flag(common_list2_elem_container[idx], \
                LV_OBJ_FLAG_HIDDEN);
        }
    }

    return;
}

/*********************************************************************************
                                  通用列表2元素容器滚动                             
*********************************************************************************/
static void common_list2_elem_container_scroll(void)
{
    int16_t obj_y = 0;
    lv_obj_t **common_list2_elem_container = \
        common_list2_ctx.common_list2_elem_container;
 
    for(uint16_t idx = 0; idx < common_list2_elem_num; idx++)
    {
        obj_y = common_list2_elem_container_sy + \
                common_list2_elem_container_height*(idx/3) + \
                    common_list2_scroll_offset + common_list2_scroll_dela;

        if(obj_y >= Common_List2_Container_H || \
            (obj_y + common_list2_elem_container_height) < 0)
        {
            lv_obj_add_flag(common_list2_elem_container[idx], \
                LV_OBJ_FLAG_HIDDEN);
            continue;
        }
            
        lv_obj_clear_flag(common_list2_elem_container[idx], \
                LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_y(common_list2_elem_container[idx], obj_y);
    }

    return;
}

/*********************************************************************************
                                  通用列表2元素图标创建                             
*********************************************************************************/
static void common_list2_elem_icon_create(\
    menu_align_t menu_align)
{
    lv_obj_t **common_list2_icon = \
        common_list2_ctx.common_list2_icon;
    lv_obj_t **common_list2_elem_container = \
        common_list2_ctx.common_list2_elem_container;

    widget_img_para.img_x = 0;
    widget_img_para.img_y = 0;
    widget_img_para.img_click_attr = false;
    widget_img_para.event_cb = NULL;
    widget_img_para.user_data = NULL;

    for(uint16_t idx = 0; idx < common_list2_elem_num; idx++)
    {
        widget_img_para.img_parent = \
            common_list2_elem_container[idx];
        widget_img_para.file_img_dat = \
            menu_88_88_icon_00_index + idx;
        common_list2_icon[idx] = \
            common_widget_img_create(&widget_img_para, NULL);
        lv_obj_align(common_list2_icon[idx], \
            LV_ALIGN_CENTER, 0, 0);
    }

    return;
}

/*********************************************************************************
                                  通用列表2容器事件回调                             
*********************************************************************************/
static void common_list2_container_pressed_cb(lv_event_t *e)
{
    common_list2_scroll_dela = 0;

    common_list2_ver_scroll = false;

    lv_indev_t *indev_act = lv_indev_get_act();

    lv_indev_get_point(indev_act, &common_list2_start_point);

    memcpy(&common_list2_now_point, &common_list2_start_point, \
        sizeof(lv_point_t));
    memcpy(&common_list2_min_point, &common_list2_start_point, \
        sizeof(lv_point_t));
    memcpy(&common_list2_max_point, &common_list2_start_point, \
        sizeof(lv_point_t));

    return;
}

static void common_list2_container_pressing_cb(lv_event_t *e)
{
    if(!common_list2_ver_scroll)
    {
        common_list2_ver_scroll_judge();

        if(common_list2_ver_scroll)
        {
            lv_obj_t *common_list2_container = \
                common_list2_ctx.common_list2_container;
            del_anim_with_var(common_list2_container);
        }
    }else
    {
        lv_point_t common_list2_scroll_vert;
        lv_indev_t *indev_act = lv_indev_get_act();
        lv_indev_get_vect(indev_act, &common_list2_scroll_vert);
        common_list2_scroll_dela += common_list2_scroll_vert.y;

        int16_t scroll_top_val = 0;
        int16_t scroll_bottom_val = \
            (-1)*((common_list2_elem_num+2)/3 - common_list2_visual_line) * \
                common_list2_elem_container_height;

        if(common_list2_scroll_offset + common_list2_scroll_dela > \
            scroll_top_val + common_list2_elem_container_height)
        {
            common_list2_scroll_dela = \
                (scroll_top_val + common_list2_elem_container_height) - \
                    common_list2_scroll_offset;
        }else if(common_list2_scroll_offset + common_list2_scroll_dela < \
            scroll_bottom_val - common_list2_elem_container_height)
        {
            common_list2_scroll_dela = \
                (scroll_bottom_val - common_list2_elem_container_height) - \
                    common_list2_scroll_offset;
        }
        
        common_list2_elem_container_scroll();

        common_scrollbar_press_handle(\
            common_list2_scroll_offset \
                + common_list2_scroll_dela);
    }

    return;
}

static void common_list2_container_release_cb(lv_event_t *e)
{
    if(!common_list2_ver_scroll)
        return;

    lv_point_t common_list2_throw_vert;
    lv_indev_t *indev_act = lv_indev_get_act();
    lv_indev_get_throw(indev_act, &common_list2_throw_vert);

    int16_t throw_sum = \
        common_list2_calc_throw_sum(common_list2_throw_vert.y);

    common_list2_scroll_offset += \
        common_list2_scroll_dela;
    common_list2_scroll_dela = 0;

    int16_t scroll_top_val = 0;
    int16_t scroll_bottom_val = \
        (-1)*((common_list2_elem_num+2)/3 - \
            common_list2_visual_line)* \
                common_list2_elem_container_height;

    int16_t throw_start = \
        common_list2_scroll_offset;
    int16_t throw_end = \
        common_list2_scroll_offset + throw_sum;

    int16_t throw_adjust = 0;
    uint32_t anim_duration = 0;
    uint32_t anim_min_duration = 300;
    uint32_t anim_max_duration = 700;

    if(throw_end > scroll_bottom_val && throw_end < scroll_top_val)
    {
        throw_adjust = \
            throw_end%common_list2_elem_container_height;
		if(throw_adjust <= (-1)*(common_list2_elem_container_height/2))
            throw_end -= \
                (common_list2_elem_container_height + throw_adjust);	
		else
            throw_end -= throw_adjust;

        anim_duration = LV_ABS(throw_sum)*2;    
    }else if(throw_end > scroll_top_val)
    {
        throw_end = scroll_top_val;

        if(throw_start != scroll_top_val)
            anim_duration = \
                LV_ABS(scroll_top_val - throw_start)*2;
        else
            anim_duration = anim_min_duration;
    }else if(throw_end < scroll_bottom_val)
    {
        throw_end = scroll_bottom_val;

        if(throw_start != scroll_top_val)
            anim_duration = \
                LV_ABS(scroll_bottom_val - throw_start)*2;
        else
            anim_duration = anim_min_duration;
    }

    if(anim_duration < anim_min_duration) \
        anim_duration = anim_min_duration;
    if(anim_duration > anim_max_duration) \
        anim_duration = anim_max_duration;

    lv_anim_t throw_anim;
    lv_obj_t *common_list2_container = \
        common_list2_ctx.common_list2_container;

    widget_anim_para.anim = &throw_anim;
    widget_anim_para.anim_obj = \
        common_list2_container;
    widget_anim_para.anim_exec_xcb = \
        common_list2_throw_anim_cb; 
    widget_anim_para.anim_duration = anim_duration;
    widget_anim_para.anim_start_val = throw_start;
    widget_anim_para.anim_end_val = throw_end;
    widget_anim_para.is_start_anim = false;
    common_widget_anim_create(&widget_anim_para);
    lv_anim_set_path_cb(widget_anim_para.anim, \
        lv_anim_path_ease_out);
    lv_anim_set_ready_cb(widget_anim_para.anim, \
        common_list2_throw_anim_ready_cb);
    lv_anim_start(widget_anim_para.anim);

    return;
}

static void common_list2_container_event_cb(lv_event_t *e)
{
    if(!e) return;

    lv_event_code_t event_code = \
        lv_event_get_code(e);

    if(event_code == LV_EVENT_PRESSED)
        common_list2_container_pressed_cb(e);
    else if(event_code == LV_EVENT_PRESSING)
        common_list2_container_pressing_cb(e);
    else if(event_code == LV_EVENT_RELEASED)
        common_list2_container_release_cb(e);

    return;
}

/*********************************************************************************
                                  通用列表2布局创建                                 
*********************************************************************************/
static void common_list2_layout_create(void)
{
    menu_align_t menu_align = \
        menu_align_left;
    if(lang_txt_is_arabic())
        menu_align = \
            menu_align_right;

    common_list2_elem_container_create(\
        menu_align);

    common_list2_elem_icon_create(\
        menu_align);

    lv_obj_t *common_list2_container = \
        common_list2_ctx.common_list2_container;
    int16_t scroll_bottom_val = \
        (-1)*((common_list2_elem_num+2)/3 - common_list2_visual_line) * \
            common_list2_elem_container_height;
    common_scrollbar_create(common_list2_container, \
        common_list2_scroll_offset, scroll_bottom_val, \
            menu_align);

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_null, \
            ui_act_id_menu);

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    common_scrollbar_destroy();

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

    memset(&common_list2_ctx, 0, \
        sizeof(common_list2_ctx_t));

    common_list2_container_create(obj);

    common_list2_layout_create();

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_common_list2) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_menu,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
