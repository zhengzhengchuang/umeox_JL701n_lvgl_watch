#include "common_list.h"

/****************图标源****************/
static const uint32_t common_list_icon_src[Common_List_Icon_Num] = 
{
    menu_100_100_icon_00_index, menu_100_100_icon_01_index, menu_100_100_icon_02_index, menu_100_100_icon_03_index, \
    menu_100_100_icon_04_index, menu_100_100_icon_05_index, menu_100_100_icon_06_index, menu_100_100_icon_07_index, \
    menu_100_100_icon_08_index, menu_100_100_icon_09_index, menu_100_100_icon_10_index, menu_100_100_icon_11_index, \
    menu_100_100_icon_12_index, menu_100_100_icon_13_index, menu_100_100_icon_14_index, menu_100_100_icon_15_index, \
    menu_100_100_icon_16_index, menu_100_100_icon_17_index, menu_100_100_icon_18_index, menu_100_100_icon_19_index, \
    menu_100_100_icon_20_index, menu_100_100_icon_21_index, menu_100_100_icon_22_index, menu_100_100_icon_23_index, \
    menu_100_100_icon_24_index, menu_100_100_icon_25_index, menu_100_100_icon_26_index, menu_100_100_icon_27_index, \
    menu_100_100_icon_28_index, menu_100_100_icon_29_index, menu_100_100_icon_30_index, menu_100_100_icon_31_index, \
    menu_100_100_icon_32_index, menu_100_100_icon_33_index, menu_100_100_icon_34_index, menu_100_100_icon_35_index, \
    menu_100_100_icon_36_index, 
};

/****************文本源****************/
static const char common_list_text_src[Common_List_Icon_Num][30] = 
{
    "Album", "Unknown", "Menu style", "Bedside lamp", "Call", "Notice", "Sports", "Unknown", \
    "About", "Activity records", "Countdown", "Calculator", "Do not disturb", "Stopwatch", "Alarm clock", "Unknown", \
    "Calendar", "Set up", "Sound and Vibration", "Flashlight", "Sleep", "Temperature", "Weather", "Unknown", \
    "Unknown", "Heart rate", "Blood sugar", "Blood pressure", "Blood oxygen", "Unknown", "Unknown", "Music", \
    "Game", "Language", "Exercise records", "Find phone", "Compass",
};

/****************元素容器点击索引****************/
static const uint16_t common_list_elem_container_idx[Common_List_Icon_Num] =
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29, \
    30, 31, 32, 33, 34, 35, 36,
};

/****************通用列表滚动参数****************/
static bool common_list_ver_scroll = false;
static int16_t common_list_scroll_dela = 0;
static int16_t common_list_scroll_offset = 0;

/****************通用列表按压点相关****************/
static lv_point_t common_list_min_point = {0};
static lv_point_t common_list_max_point = {0};
static lv_point_t common_list_now_point = {0};
static lv_point_t common_list_start_point = {0};

/****************通用列表图标半径****************/
static const uint16_t common_list_icon_r = 50;

/****************通用列表可视化个数****************/
static const uint8_t common_list_visual_num = 3;

/****************通用列表元素容器起始y****************/
static const int16_t common_list_elem_container_sy = 37;

/****************通用列表元素容器间隔****************/
static const int16_t common_list_elem_container_inv = 137;

/****************通用列表图标总数****************/
static const uint16_t common_list_icon_num = Common_List_Icon_Num;

/****************通用列表参数内容****************/
static common_list_ctx_t common_list_ctx = {0};

/****************函数声明定义****************/
static void common_list_elem_container_scroll(void);
static void common_list_container_event_cb(lv_event_t *e);



//*********************************************************************************//
//                                  通过对象删除正在进行的动画                        //
//*********************************************************************************//
static void del_anim_with_var(void *var)
{
    if(!var) return;

    if(lv_anim_get(var, NULL))
        lv_anim_del(var, NULL);
        
    return;
}

//*********************************************************************************//
//                                  通过对象获取正在进行的动画                        //
//*********************************************************************************//
static bool anim_progress_with_var(void *var)
{
    if(lv_anim_get(var, NULL))
        return true;

    return false;
}

//*********************************************************************************//
//                                  通用列表纵向滚动判断                             //
//*********************************************************************************//
static void common_list_ver_scroll_judge(void)
{
    lv_indev_t *indev_act = lv_indev_get_act();

    lv_indev_get_point(indev_act, &common_list_now_point);

    if(common_list_now_point.x > common_list_max_point.x)
        common_list_max_point.x = common_list_now_point.x;

    if(common_list_now_point.x < common_list_min_point.x)
        common_list_min_point.x = common_list_now_point.x;

    if(common_list_now_point.y > common_list_max_point.y)
        common_list_max_point.y = common_list_now_point.y;

    if(common_list_now_point.y < common_list_min_point.y)
        common_list_min_point.y = common_list_now_point.y;

    int16_t common_list_x_max = common_list_max_point.x - \
        common_list_min_point.x;
    int16_t common_list_y_max = common_list_max_point.y - \
        common_list_min_point.y;

    if(LV_ABS(common_list_y_max) >= LV_ABS(common_list_x_max) && \
        LV_ABS(common_list_y_max) >= 10)
        common_list_ver_scroll = true;
    else
        common_list_ver_scroll = false;

    return;
}

//*********************************************************************************//
//                                  通用列表计算纵向抛出距离                          //
//*********************************************************************************//
static int16_t common_list_calc_throw_sum(int16_t throw_vert)
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

//*********************************************************************************//
//                                  通用列表计算纵向抛出动画                          //
//*********************************************************************************//
static void common_list_throw_anim_cb(void *var, int32_t val)
{
    common_list_scroll_offset = val;

    common_list_elem_container_scroll();

    return;
}

//*********************************************************************************//
//                                  创建通用列表容器                                 //
//*********************************************************************************//
static void common_list_container_create(lv_obj_t *obj)
{
    lv_obj_t **common_list_container = \
        &(common_list_ctx.common_list_container);

    widget_obj_para.obj_parent = obj;
    widget_obj_para.obj_x = 0;
    widget_obj_para.obj_y = 0;
    widget_obj_para.obj_width = Common_List_Container_W;
    widget_obj_para.obj_height = Common_List_Container_H;
    widget_obj_para.obj_bg_opax = LV_OPA_100;
    widget_obj_para.obj_bg_color = lv_color_hex(0x000000);
    widget_obj_para.obj_border_opax = LV_OPA_0;
    widget_obj_para.obj_border_width = 0;
    widget_obj_para.obj_border_color = lv_color_hex(0x000000);
    widget_obj_para.obj_radius = 0;
    widget_obj_para.obj_is_scrollable = false;
    *common_list_container = common_widget_obj_create(&widget_obj_para);
    lv_obj_add_event_cb(*common_list_container, common_list_container_event_cb, \
        LV_EVENT_ALL, NULL);

    return;
}

//*********************************************************************************//
//                                  通用列表元素容器点击回调                          //
//*********************************************************************************//
static void common_list_elem_container_click_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *common_list_container = \
        common_list_ctx.common_list_container;

    bool anim_progress = \
        anim_progress_with_var(common_list_container);

    if(common_list_ver_scroll || anim_progress)
        return;

    uint16_t idx = *(uint16_t *)lv_event_get_user_data(e);

    printf("******%s:%d\n", __func__, idx);

    //ui_menu_jump(ui_act_id_watchface);

    return;
}

//*********************************************************************************//
//                                  通用列表元素容器创建                             //
//*********************************************************************************//
static void common_list_elem_container_create(void)
{
    lv_obj_t **common_list_elem_container = \
        common_list_ctx.common_list_elem_container;
    lv_obj_t *common_list_container = \
        common_list_ctx.common_list_container;

    widget_obj_para.obj_parent = common_list_container;
    widget_obj_para.obj_width = Common_List_Container_W;
    widget_obj_para.obj_height = common_list_icon_r*2;
    widget_obj_para.obj_bg_opax = LV_OPA_0;
    widget_obj_para.obj_bg_color = lv_color_hex(0x000000);
    widget_obj_para.obj_border_opax = LV_OPA_0;
    widget_obj_para.obj_border_width = 0;
    widget_obj_para.obj_border_color = lv_color_hex(0x000000);
    widget_obj_para.obj_radius = 0;
    widget_obj_para.obj_is_scrollable = false;

    for(uint16_t idx = 0; idx < common_list_icon_num; idx++)
    {
        widget_obj_para.obj_x = 0;
        widget_obj_para.obj_y = common_list_elem_container_sy + \
            common_list_elem_container_inv*idx + common_list_scroll_offset + \
            common_list_scroll_dela;
        common_list_elem_container[idx] = common_widget_obj_create(&widget_obj_para);
        lv_obj_add_flag(common_list_elem_container[idx], LV_OBJ_FLAG_EVENT_BUBBLE);
        lv_obj_add_event_cb(common_list_elem_container[idx], common_list_elem_container_click_cb, \
            LV_EVENT_SHORT_CLICKED, (void *)&common_list_elem_container_idx[idx]);
    }

    return;
}

//*********************************************************************************//
//                                  通用列表元素容器滚动                             //
//*********************************************************************************//
static void common_list_elem_container_scroll(void)
{
    int16_t scroll_offset_val = 0;
    lv_obj_t **common_list_elem_container = \
        common_list_ctx.common_list_elem_container;
 
    for(uint16_t idx = 0; idx < common_list_icon_num; idx++)
    {
        scroll_offset_val = common_list_elem_container_sy + \
            common_list_elem_container_inv*idx + common_list_scroll_offset + \
            common_list_scroll_dela;
        lv_obj_set_y(common_list_elem_container[idx], scroll_offset_val);
    }

    return;
}

//*********************************************************************************//
//                                  通用列表元素图标创建                             //
//*********************************************************************************//
static void common_list_elem_icon_create(void)
{
    lv_obj_t **common_list_icon = \
        common_list_ctx.common_list_icon;
    lv_obj_t **common_list_elem_container = \
        common_list_ctx.common_list_elem_container;

    widget_img_para.img_x = 0;
    widget_img_para.img_y = 0;
    widget_img_para.img_click_attr = false;
    widget_img_para.event_cb = NULL;
    widget_img_para.user_data = NULL;

    for(uint16_t idx = 0; idx < common_list_icon_num; idx++)
    {
        widget_img_para.img_parent = common_list_elem_container[idx];
        widget_img_para.file_img_dat = common_list_icon_src[idx];
        common_list_icon[idx] = common_widget_img_create(&widget_img_para, NULL);
        lv_obj_align(common_list_icon[idx], LV_ALIGN_LEFT_MID, 20, 0);
    }

    return;
}

//*********************************************************************************//
//                                  通用列表元素标签创建                             //
//*********************************************************************************//
static void common_list_elem_label_create(void)
{
    lv_obj_t **common_list_icon = \
        common_list_ctx.common_list_icon;
    lv_obj_t **common_list_label = \
        common_list_ctx.common_list_label;
    lv_obj_t **common_list_elem_container = \
        common_list_ctx.common_list_elem_container;

    widget_label_para.label_x = 0;
    widget_label_para.label_y = 0;
    widget_label_para.label_w = 200;
    widget_label_para.label_h = 37;
    widget_label_para.long_mode = LV_LABEL_LONG_SCROLL;
    widget_label_para.text_align = LV_TEXT_ALIGN_LEFT;
    widget_label_para.label_text_color = lv_color_hex(0xffffff);
    widget_label_para.user_text_font = NULL;

    for(uint16_t idx = 0; idx < common_list_icon_num; idx++)
    {
        widget_label_para.label_parent = common_list_elem_container[idx];
        widget_label_para.label_text = common_list_text_src[idx];
        common_list_label[idx] = common_widget_label_create(&widget_label_para);
        lv_obj_align_to(common_list_label[idx], common_list_icon[idx], \
            LV_ALIGN_OUT_RIGHT_MID, 20, 0);
    }

    return;
}

//*********************************************************************************//
//                                  通用列表容器事件回调                             //
//*********************************************************************************//
static void common_list_container_pressed_cb(lv_event_t *e)
{
    common_list_scroll_dela = 0;

    common_list_ver_scroll = false;

    lv_indev_t *indev_act = lv_indev_get_act();

    lv_indev_get_point(indev_act, &common_list_start_point);

    memcpy(&common_list_now_point, &common_list_start_point, \
        sizeof(lv_point_t));
    memcpy(&common_list_min_point, &common_list_start_point, \
        sizeof(lv_point_t));
    memcpy(&common_list_max_point, &common_list_start_point, \
        sizeof(lv_point_t));

    return;
}

static void common_list_container_pressing_cb(lv_event_t *e)
{
    if(!common_list_ver_scroll)
    {
        common_list_ver_scroll_judge();

        if(common_list_ver_scroll)
        {
            lv_obj_t *common_list_container = \
                common_list_ctx.common_list_container;
            del_anim_with_var(common_list_container);
        }
    }else
    {
        lv_point_t common_list_scroll_vert;
        lv_indev_t *indev_act = lv_indev_get_act();
        lv_indev_get_vect(indev_act, &common_list_scroll_vert);
        common_list_scroll_dela += common_list_scroll_vert.y;

        int16_t scroll_top_val = 0;
        int16_t scroll_bottom_val = \
            (-1)*(common_list_icon_num - common_list_visual_num) * \
            common_list_elem_container_inv;

        if(common_list_scroll_offset + common_list_scroll_dela > \
            scroll_top_val + common_list_elem_container_inv)
        {
            common_list_scroll_dela = \
                (scroll_top_val + common_list_elem_container_inv) - \
                    common_list_scroll_offset;
        }else if(common_list_scroll_offset + common_list_scroll_dela < \
            scroll_bottom_val - common_list_elem_container_inv)
        {
            common_list_scroll_dela = \
                (scroll_bottom_val - common_list_elem_container_inv) - \
                    common_list_scroll_offset;
        }
        
        common_list_elem_container_scroll();
    }

    return;
}

static void common_list_container_release_cb(lv_event_t *e)
{
    if(!common_list_ver_scroll)
        return;

    lv_point_t common_list_throw_vert;
    lv_indev_t *indev_act = lv_indev_get_act();
    lv_indev_get_throw(indev_act, &common_list_throw_vert);

    int16_t throw_sum = common_list_calc_throw_sum(common_list_throw_vert.y);

    common_list_scroll_offset += common_list_scroll_dela;
    common_list_scroll_dela = 0;

    int16_t scroll_top_val = 0;
    int16_t scroll_bottom_val = \
        (-1)*(common_list_icon_num - common_list_visual_num)* \
        common_list_elem_container_inv;

    int16_t throw_start = common_list_scroll_offset;
    int16_t throw_end = common_list_scroll_offset + throw_sum;

    int16_t throw_adjust = 0;
    uint32_t anim_duration = 0;
    if(throw_end > scroll_bottom_val && throw_end < scroll_top_val)
    {
        throw_adjust = throw_end%common_list_elem_container_inv;
		if(throw_adjust <= (-1)*(common_list_elem_container_inv/2))
            throw_end -=(common_list_elem_container_inv + throw_adjust);	
		else
            throw_end -= throw_adjust;

        anim_duration = LV_ABS(throw_sum)*2;
        
    }else if(throw_end > scroll_top_val)
    {
        throw_end = scroll_top_val;

        if(throw_start != scroll_top_val)
            anim_duration = LV_ABS(scroll_top_val - throw_start)*2;
        else
            anim_duration = 300;
    }else if(throw_end < scroll_bottom_val)
    {
        throw_end = scroll_bottom_val;

        if(throw_start != scroll_top_val)
            anim_duration = LV_ABS(scroll_bottom_val - throw_start)*2;
        else
            anim_duration = 300;
    }

    if(anim_duration < 300) anim_duration = 300;
    if(anim_duration > 1500) anim_duration = 1500;

    lv_anim_t throw_anim;
    lv_obj_t *common_list_container = \
        common_list_ctx.common_list_container;

    widget_anim_para.anim = &throw_anim;
    widget_anim_para.anim_obj = common_list_container;
    widget_anim_para.anim_exec_xcb = common_list_throw_anim_cb; 
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

static void common_list_container_event_cb(lv_event_t *e)
{
    if(!e) return;

    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_PRESSED)
        common_list_container_pressed_cb(e);
    else if(event_code == LV_EVENT_PRESSING)
        common_list_container_pressing_cb(e);
    else if(event_code == LV_EVENT_RELEASED)
        common_list_container_release_cb(e);

    return;
} 

//*********************************************************************************//
//                                  通用列表布局创建                                 //
//*********************************************************************************//
static void common_list_layout_create(void)
{
    common_list_elem_container_create();

    common_list_elem_icon_create();

    common_list_elem_label_create();

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    tileview_register_all_menu(obj, ui_act_id_null, ui_act_id_null, \
        ui_act_id_null, ui_act_id_null, ui_act_id_menu);

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

    memset(&common_list_ctx, 0, sizeof(common_list_ctx_t));

    common_list_container_create(obj);

    common_list_layout_create();

    return;
}

static void menu_key_cb(int key_value, int key_event)
{
    return;
}

register_ui_menu_load_info(menu_load_common_list) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = ui_act_id_menu,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
