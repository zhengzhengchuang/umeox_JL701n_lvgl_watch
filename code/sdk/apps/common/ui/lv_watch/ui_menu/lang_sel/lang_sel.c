#include "lang_sel.h"

/****************语言列表文本源****************/
static const char *lang_sel_text_src[\
    Lang_List_Elem_Num] = 
{
    "العربية",
    "English",
    "Français",
    "اردو",
    "Türk",
    "简体中文",
    "Bahasa Indonesia",
    "فارسی",
    "Deutsch",
    "Pусский",
    "Melayu",
    "o'zbek",
};

/****************语言容器点击索引****************/
static const uint8_t lang_list_elem_container_idx[\
    Lang_List_Elem_Num] =
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
};

/****************语言列表滚动参数****************/
static int16_t lang_list_scroll_dela = 0;
static int16_t lang_list_scroll_offset = 0;

/****************语言列表是否滚动****************/
static bool lang_list_ver_scroll = false;

/****************语言列表按压点相关****************/
static lv_point_t lang_list_min_point = {0};
static lv_point_t lang_list_max_point = {0};
static lv_point_t lang_list_now_point = {0};
static lv_point_t lang_list_start_point = {0};

/****************语言列表参数内容****************/
static lang_list_ctx_t lang_list_ctx = \
    {0};

/****************语言列表元素总数****************/
static const uint16_t lang_list_elem_num = \
    Lang_List_Elem_Num;

/****************语言列表可视化行****************/
static const uint8_t lang_list_visual_line = \
    3;

/****************语言列表元素容器sx****************/
static const int16_t lang_list_elem_container_sx = \
    0;

/****************语言列表元素容器起始y****************/
static const int16_t lang_list_elem_container_sy = \
    0;

/****************语言列表元素容器宽****************/
static const int16_t lang_list_elem_container_width = \
    Lang_List_Container_W;

/****************语言列表元素容器高****************/
static const int16_t lang_list_elem_container_height = \
    (112);


/****************函数声明****************/
static void lang_list_elem_container_scroll(void);
static void lang_list_container_event_cb(lv_event_t *e);


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
                                  语言列表纵向滚动判断                             
*********************************************************************************/
static void lang_list_ver_scroll_judge(void)
{
    lv_indev_t *indev_act = lv_indev_get_act();

    lv_indev_get_point(indev_act, &lang_list_now_point);

    if(lang_list_now_point.x > lang_list_max_point.x)
        lang_list_max_point.x = lang_list_now_point.x;

    if(lang_list_now_point.x < lang_list_min_point.x)
        lang_list_min_point.x = lang_list_now_point.x;

    if(lang_list_now_point.y > lang_list_max_point.y)
        lang_list_max_point.y = lang_list_now_point.y;

    if(lang_list_now_point.y < lang_list_min_point.y)
        lang_list_min_point.y = lang_list_now_point.y;

    int16_t lang_list_x_max = lang_list_max_point.x - \
        lang_list_min_point.x;
    int16_t lang_list_y_max = lang_list_max_point.y - \
        lang_list_min_point.y;

    if(LV_ABS(lang_list_y_max) >= LV_ABS(lang_list_x_max) && \
        LV_ABS(lang_list_y_max) >= 10)
        lang_list_ver_scroll = true;
    else
        lang_list_ver_scroll = false;

    return;
}

/*********************************************************************************
                                  语言列表计算纵向抛出距离                         
*********************************************************************************/
static int16_t lang_list_calc_throw_sum(int16_t throw_vert)
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
                                  语言列表纵向抛出动画                         
*********************************************************************************/
static void lang_list_throw_anim_cb(void *var, int32_t val)
{
    lang_list_scroll_offset = val;

    lang_list_elem_container_scroll();

    common_scrollbar_press_handle(\
        lang_list_scroll_offset);

    return;
}

/*********************************************************************************
                                  语言列表纵向抛出动画结束                       
*********************************************************************************/
static void lang_list_throw_anim_ready_cb(lv_anim_t *anim)
{
    common_scrollbar_released_handle();

    return;
}

/*********************************************************************************
                                  创建语言标题                                 
*********************************************************************************/
static void lang_list_title_container_create(lv_obj_t *obj)
{
    lv_obj_t **lang_list_title = \
        &(lang_list_ctx.lang_list_title);

    widget_obj_para.obj_parent = obj;
    widget_obj_para.obj_x = 0;
    widget_obj_para.obj_y = \
        LCD_UI_Y_OFFSET;
    widget_obj_para.obj_width = \
        Lang_List_Title_W;
    widget_obj_para.obj_height = \
        Lang_List_Title_H;
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
    *lang_list_title = \
        common_widget_obj_create(&widget_obj_para);
  
    return;
}

/*********************************************************************************
                                  创建语言标题标签                                 
*********************************************************************************/
static void lang_list_title_label_create(void)
{
    lv_obj_t **lang_list_title_label = \
        &(lang_list_ctx.lang_list_title_label);
    lv_obj_t *lang_list_title = \
        lang_list_ctx.lang_list_title;

    widget_label_para.label_w = \
        (Lang_List_Title_W - 30);
    widget_label_para.label_h = \
        Label_Line_Height*2;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_WRAP;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_ver_center = \
        true;
    widget_label_para.user_text_font = NULL;
    widget_label_para.label_parent = \
        lang_list_title;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_language);
    *lang_list_title_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_center(*lang_list_title_label);

    return;
}

/*********************************************************************************
                                  创建语言列表容器                                 
*********************************************************************************/
static void lang_list_container_create(lv_obj_t *obj)
{
    lv_obj_t **lang_list_container = \
        &(lang_list_ctx.lang_list_container);

    widget_obj_para.obj_parent = obj;
    widget_obj_para.obj_x = 0;
    widget_obj_para.obj_y = \
        Lang_List_Title_H + \
            LCD_UI_Y_OFFSET;
    widget_obj_para.obj_width = \
        Lang_List_Container_W;
    widget_obj_para.obj_height = \
        Lang_List_Container_H;
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
    *lang_list_container = \
        common_widget_obj_create(&widget_obj_para);
    lv_obj_add_event_cb(*lang_list_container, \
        lang_list_container_event_cb, LV_EVENT_ALL, NULL);

    return;
}

/*********************************************************************************
                                  语言列表元素容器点击回调                          
*********************************************************************************/
static void lang_list_elem_container_click_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *lang_list_container = \
        lang_list_ctx.lang_list_container;

    bool anim_progress = \
        anim_progress_with_var(lang_list_container);

    if(lang_list_ver_scroll || anim_progress)
        return;

    uint16_t idx = \
        *(uint16_t *)lv_event_get_user_data(e);

    comm_language_id_t lang_id = \
        (comm_language_id_t)idx;

    set_vm_para_cache_with_label(\
        vm_label_sys_language, lang_id);

    ui_menu_jump(ui_act_id_lang_sel);

    return;
}

/*********************************************************************************
                                  语言列表元素容器创建                             
*********************************************************************************/
static void lang_list_elem_container_create(void)
{
    lv_obj_t **lang_list_elem_container = \
        lang_list_ctx.lang_list_elem_container;
    lv_obj_t *lang_list_container = \
        lang_list_ctx.lang_list_container;

    widget_obj_para.obj_parent = \
        lang_list_container;
    widget_obj_para.obj_width = \
        lang_list_elem_container_width;
    widget_obj_para.obj_height = \
        lang_list_elem_container_height;
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

    for(uint16_t idx = 0; idx < lang_list_elem_num; idx++)
    {
        widget_obj_para.obj_x = \
            lang_list_elem_container_sx;
        widget_obj_para.obj_y = \
            lang_list_elem_container_sy + \
                lang_list_elem_container_height*idx + \
                    lang_list_scroll_offset + lang_list_scroll_dela;
        lang_list_elem_container[idx] = \
            common_widget_obj_create(&widget_obj_para);
        lv_obj_add_flag(lang_list_elem_container[idx], \
            LV_OBJ_FLAG_EVENT_BUBBLE);
        lv_obj_add_event_cb(lang_list_elem_container[idx], \
            lang_list_elem_container_click_cb, LV_EVENT_SHORT_CLICKED, \
                (void *)&lang_list_elem_container_idx[idx]);

        if(widget_obj_para.obj_y >= Lang_List_Container_H || \
            (widget_obj_para.obj_y + lang_list_elem_container_height) < 0)
        {
            lv_obj_add_flag(lang_list_elem_container[idx], \
                LV_OBJ_FLAG_HIDDEN);
        }
    }

    return;
}

/*********************************************************************************
                                  语言列表元素容器滚动                             
*********************************************************************************/
static void lang_list_elem_container_scroll(void)
{
    int16_t obj_y = 0;
    lv_obj_t **lang_list_elem_container = \
        lang_list_ctx.lang_list_elem_container;
 
    for(uint16_t idx = 0; idx < lang_list_elem_num; idx++)
    {
        obj_y = lang_list_elem_container_sy + \
            lang_list_elem_container_height*idx + \
                lang_list_scroll_offset + lang_list_scroll_dela;

        if(obj_y >= Lang_List_Container_H || \
            (obj_y + lang_list_elem_container_height) < 0)
        {
            lv_obj_add_flag(lang_list_elem_container[idx], \
                LV_OBJ_FLAG_HIDDEN);
            continue;
        }
            
        lv_obj_clear_flag(lang_list_elem_container[idx], \
                LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_y(lang_list_elem_container[idx], obj_y);
    }

    return;
}

/*********************************************************************************
                                  语言列表元素图标创建                             
*********************************************************************************/
static void lang_list_elem_icon_create(void)
{
    lv_obj_t **lang_list_icon = \
        lang_list_ctx.lang_list_icon;
    lv_obj_t **lang_list_elem_container = \
        lang_list_ctx.lang_list_elem_container;

    int cur_lang = \
        get_vm_para_cache_with_label(\
            vm_label_sys_language); 

    widget_img_para.img_x = 0;
    widget_img_para.img_y = 0;
    widget_img_para.event_cb = NULL;
    widget_img_para.user_data = NULL;
    widget_img_para.img_click_attr = false;

    for(uint16_t idx = 0; idx < lang_list_elem_num; idx++)
    {
        widget_img_para.img_parent = \
            lang_list_elem_container[idx];
        if(idx == cur_lang)
            widget_img_para.file_img_dat = \
                comm_icon_06_index;
        else
            widget_img_para.file_img_dat = \
                comm_icon_05_index;
        lang_list_icon[idx] = \
            common_widget_img_create(&widget_img_para, NULL);
        lv_obj_center(lang_list_icon[idx]);
    }

    return;
}

/*********************************************************************************
                                  语言列表元素标签创建                             
*********************************************************************************/
static void lang_list_elem_label_create(void)
{
    lv_obj_t **lang_list_label = \
        lang_list_ctx.lang_list_label;
    lv_obj_t **lang_list_icon = \
        lang_list_ctx.lang_list_icon;

    widget_label_para.label_x = 0;
    widget_label_para.label_y = 0;
    widget_label_para.label_w = 240;
    widget_label_para.label_h = \
        Label_Line_Height;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_SCROLL;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_ver_center = \
        false;
    widget_label_para.user_text_font = NULL;

    for(uint16_t idx = 0; idx < lang_list_elem_num; idx++)
    {
        widget_label_para.label_parent = \
            lang_list_icon[idx];
        widget_label_para.label_text = \
            lang_sel_text_src[idx];
        lang_list_label[idx] = \
            common_widget_label_create(&widget_label_para);
        lv_obj_center(lang_list_label[idx]);
    }

    return;
}

/*********************************************************************************
                                  语言列表容器事件回调                             
*********************************************************************************/
static void lang_list_container_pressed_cb(lv_event_t *e)
{
    lang_list_scroll_dela = 0;

    lang_list_ver_scroll = false;

    lv_indev_t *indev_act = lv_indev_get_act();

    lv_indev_get_point(indev_act, &lang_list_start_point);

    memcpy(&lang_list_now_point, &lang_list_start_point, \
        sizeof(lv_point_t));
    memcpy(&lang_list_min_point, &lang_list_start_point, \
        sizeof(lv_point_t));
    memcpy(&lang_list_max_point, &lang_list_start_point, \
        sizeof(lv_point_t));

    return;
}

static void lang_list_container_pressing_cb(lv_event_t *e)
{
    if(!lang_list_ver_scroll)
    {
        lang_list_ver_scroll_judge();

        if(lang_list_ver_scroll)
        {
            lv_obj_t *lang_list_container = \
                lang_list_ctx.lang_list_container;
            del_anim_with_var(lang_list_container);
        }
    }else
    {
        lv_point_t lang_list_scroll_vert;
        lv_indev_t *indev_act = lv_indev_get_act();
        lv_indev_get_vect(indev_act, &lang_list_scroll_vert);
        lang_list_scroll_dela += lang_list_scroll_vert.y;

        int16_t scroll_top_val = 0;
        int16_t scroll_bottom_val = \
            (-1)*(lang_list_elem_num - lang_list_visual_line) * \
                lang_list_elem_container_height;

        if(lang_list_scroll_offset + lang_list_scroll_dela > \
            scroll_top_val + lang_list_elem_container_height)
        {
            lang_list_scroll_dela = \
                (scroll_top_val + lang_list_elem_container_height) - \
                    lang_list_scroll_offset;
        }else if(lang_list_scroll_offset + lang_list_scroll_dela < \
            scroll_bottom_val - lang_list_elem_container_height)
        {
            lang_list_scroll_dela = \
                (scroll_bottom_val - lang_list_elem_container_height) - \
                    lang_list_scroll_offset;
        }
        
        lang_list_elem_container_scroll();

        common_scrollbar_press_handle(\
            lang_list_scroll_offset \
                + lang_list_scroll_dela);
    }

    return;
}

static void lang_list_container_release_cb(lv_event_t *e)
{
    if(!lang_list_ver_scroll)
        return;

    lv_point_t lang_list_throw_vert;
    lv_indev_t *indev_act = lv_indev_get_act();
    lv_indev_get_throw(indev_act, &lang_list_throw_vert);

    int16_t throw_sum = \
        lang_list_calc_throw_sum(lang_list_throw_vert.y);

    lang_list_scroll_offset += \
        lang_list_scroll_dela;
    lang_list_scroll_dela = 0;

    int16_t scroll_top_val = 0;
    int16_t scroll_bottom_val = \
        (-1)*(lang_list_elem_num - lang_list_visual_line)* \
        lang_list_elem_container_height;

    int16_t throw_start = lang_list_scroll_offset;
    int16_t throw_end = lang_list_scroll_offset + throw_sum;

    int16_t throw_adjust = 0;
    uint32_t anim_duration = 0;
    uint32_t anim_min_duration = 300;
    uint32_t anim_max_duration = 700;

    if(throw_end > scroll_bottom_val && throw_end < scroll_top_val)
    {
        throw_adjust = \
            throw_end%lang_list_elem_container_height;
		if(throw_adjust <= (-1)*(lang_list_elem_container_height/2))
            throw_end -= \
                (lang_list_elem_container_height + throw_adjust);	
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
    lv_obj_t *lang_list_container = \
        lang_list_ctx.lang_list_container;

    widget_anim_para.anim = &throw_anim;
    widget_anim_para.anim_obj = \
        lang_list_container;
    widget_anim_para.anim_exec_xcb = \
        lang_list_throw_anim_cb; 
    widget_anim_para.anim_duration = anim_duration;
    widget_anim_para.anim_start_val = throw_start;
    widget_anim_para.anim_end_val = throw_end;
    widget_anim_para.is_start_anim = false;
    common_widget_anim_create(&widget_anim_para);
    lv_anim_set_path_cb(widget_anim_para.anim, \
        lv_anim_path_ease_out);
    lv_anim_set_ready_cb(widget_anim_para.anim, \
        lang_list_throw_anim_ready_cb);
    lv_anim_start(widget_anim_para.anim);

    return;
}

static void lang_list_container_event_cb(lv_event_t *e)
{
    if(!e) return;

    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_PRESSED)
        lang_list_container_pressed_cb(e);
    else if(event_code == LV_EVENT_PRESSING)
        lang_list_container_pressing_cb(e);
    else if(event_code == LV_EVENT_RELEASED)
        lang_list_container_release_cb(e);

    return;
} 

/*********************************************************************************
                                  语言列表布局创建                                 
*********************************************************************************/
static void lang_list_layout_create(void)
{
    lang_list_title_label_create();

    lang_list_elem_container_create();

    lang_list_elem_icon_create();

    lang_list_elem_label_create();

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    ui_act_id_t prev_act_id = \
        read_menu_return_level_id();

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, prev_act_id, ui_act_id_null, \
            ui_act_id_lang_sel);

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

    memset(&lang_list_ctx, 0, \
        sizeof(lang_list_ctx_t));

    lang_list_title_container_create(obj);

    lang_list_container_create(obj);

    lang_list_layout_create();

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_lang_sel) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_lang_sel,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
