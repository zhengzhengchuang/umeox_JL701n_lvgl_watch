#include "settings_list.h"

/****************图标源****************/
static const uint32_t settings_list_icon_src[\
    Settings_List_Elem_Num] = 
{
    settings_00_index, settings_01_index, settings_02_index, \
    settings_03_index, settings_04_index, settings_06_index, 
};

/****************文本源id****************/
static const comm_lang_txtid_t settings_list_text_id[\
    Settings_List_Elem_Num] = 
{
    lang_txtid_menu_view, lang_txtid_sound, lang_txtid_display, \
    lang_txtid_language, lang_txtid_unit, lang_txtid_about,
};

/****************设置元素容器点击索引****************/
static const uint8_t settings_list_elem_container_idx[\
    Settings_List_Elem_Num] =
{
    0, 1, 2, 3, 4, 5, 
};

/****************设置元素页面跳转id****************/
static const ui_act_id_t settings_list_menu_id[\
    Settings_List_Elem_Num] = 
{
    ui_act_id_menu_view, ui_act_id_sound_ctrl, \
    ui_act_id_backlight, ui_act_id_lang_sel, \
    ui_act_id_unit_switch, ui_act_id_about,
};

/****************设置列表滚动参数****************/
static int16_t settings_list_scroll_dela = 0;
static int16_t settings_list_scroll_offset = 0;

/****************设置列表是否滚动****************/
static bool settings_list_ver_scroll = false;

/****************设置列表按压点相关****************/
static lv_point_t settings_list_min_point = {0};
static lv_point_t settings_list_max_point = {0};
static lv_point_t settings_list_now_point = {0};
static lv_point_t settings_list_start_point = {0};

/****************设置列表参数内容****************/
static settings_list_ctx_t settings_list_ctx = \
    {0};

/****************设置列表元素总数****************/
static const uint16_t settings_list_elem_num = \
    Settings_List_Elem_Num;

/****************设置列表可视化行****************/
static const uint8_t settings_list_visual_line = \
    3;

/****************设置列表元素容器sx****************/
static const int16_t settings_list_elem_container_sx = \
    0;

/****************设置列表元素容器起始y****************/
static const int16_t settings_list_elem_container_sy = \
    0;

/****************设置列表元素容器宽****************/
static const int16_t settings_list_elem_container_width = \
    Settings_List_Container_W;

/****************设置列表元素容器高****************/
static const int16_t settings_list_elem_container_height = \
    (112);

/****************函数声明****************/
static void settings_list_elem_container_scroll(void);
static void settings_list_container_event_cb(lv_event_t *e);


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
                                  设置列表纵向滚动判断                             
*********************************************************************************/
static void settings_list_ver_scroll_judge(void)
{
    lv_indev_t *indev_act = lv_indev_get_act();

    lv_indev_get_point(indev_act, &settings_list_now_point);

    if(settings_list_now_point.x > settings_list_max_point.x)
        settings_list_max_point.x = settings_list_now_point.x;

    if(settings_list_now_point.x < settings_list_min_point.x)
        settings_list_min_point.x = settings_list_now_point.x;

    if(settings_list_now_point.y > settings_list_max_point.y)
        settings_list_max_point.y = settings_list_now_point.y;

    if(settings_list_now_point.y < settings_list_min_point.y)
        settings_list_min_point.y = settings_list_now_point.y;

    int16_t settings_list_x_max = settings_list_max_point.x - \
        settings_list_min_point.x;
    int16_t settings_list_y_max = settings_list_max_point.y - \
        settings_list_min_point.y;

    if(LV_ABS(settings_list_y_max) >= LV_ABS(settings_list_x_max) && \
        LV_ABS(settings_list_y_max) >= 10)
        settings_list_ver_scroll = true;
    else
        settings_list_ver_scroll = false;

    return;
}

/*********************************************************************************
                                  设置列表计算纵向抛出距离                         
*********************************************************************************/
static int16_t settings_list_calc_throw_sum(int16_t throw_vert)
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
                                  设置列表纵向抛出动画                         
*********************************************************************************/
static void settings_list_throw_anim_cb(void *var, int32_t val)
{
    settings_list_scroll_offset = val;

    settings_list_elem_container_scroll();

    common_scrollbar_press_handle(\
        settings_list_scroll_offset);

    return;
}

/*********************************************************************************
                                  设置列表纵向抛出动画结束                       
*********************************************************************************/
static void settings_list_throw_anim_ready_cb(lv_anim_t *anim)
{
    common_scrollbar_released_handle();

    return;
}

/*********************************************************************************
                                  创建设置标题容器                                 
*********************************************************************************/
static void settings_list_title_container_create(lv_obj_t *obj)
{
    lv_obj_t **settings_list_title = \
        &(settings_list_ctx.settings_list_title);

    widget_obj_para.obj_parent = obj;
    widget_obj_para.obj_x = 0;
    widget_obj_para.obj_y = \
        LCD_UI_Y_OFFSET;
    widget_obj_para.obj_width = \
        Settings_List_Title_W;
    widget_obj_para.obj_height = \
        Settings_List_Title_H;
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
    *settings_list_title = \
        common_widget_obj_create(&widget_obj_para);
  
    return;
}

/*********************************************************************************
                                  创建设置标题标签                                 
*********************************************************************************/
static void settings_list_title_label_create(\
    menu_align_t menu_align)
{
    lv_obj_t **settings_list_title_label = \
        &(settings_list_ctx.settings_list_title_label);
    lv_obj_t *settings_list_title = \
        settings_list_ctx.settings_list_title;

    widget_label_para.label_x = 0;
    widget_label_para.label_y = 0;
    widget_label_para.label_w = \
        (Settings_List_Title_W - 30);
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
        settings_list_title;
    widget_label_para.label_text = \
        get_lang_txt_with_id(lang_txtid_settings);
    *settings_list_title_label = \
        common_widget_label_create(&widget_label_para);
    lv_obj_center(*settings_list_title_label);

    return;
}

/*********************************************************************************
                                  创建设置列表容器                                 
*********************************************************************************/
static void settings_list_container_create(lv_obj_t *obj)
{
    lv_obj_t **settings_list_container = \
        &(settings_list_ctx.settings_list_container);

    widget_obj_para.obj_parent = obj;
    widget_obj_para.obj_x = 0;
    widget_obj_para.obj_y = \
        Settings_List_Title_H + \
            LCD_UI_Y_OFFSET;
    widget_obj_para.obj_width = \
        Settings_List_Container_W;
    widget_obj_para.obj_height = \
        Settings_List_Container_H;
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
    *settings_list_container = \
        common_widget_obj_create(&widget_obj_para);
    lv_obj_add_event_cb(*settings_list_container, \
        settings_list_container_event_cb, LV_EVENT_ALL, NULL);

    return;
}

/*********************************************************************************
                                  设置列表元素容器点击回调                          
*********************************************************************************/
static void settings_list_elem_container_click_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *settings_list_container = \
        settings_list_ctx.settings_list_container;

    bool anim_progress = \
        anim_progress_with_var(settings_list_container);

    if(settings_list_ver_scroll || anim_progress)
        return;

    uint8_t idx = \
        *(uint8_t *)lv_event_get_user_data(e);

    ui_menu_jump(settings_list_menu_id[idx]);

    return;
}

/*********************************************************************************
                                  设置列表元素容器创建                             
*********************************************************************************/
static void settings_list_elem_container_create(\
    menu_align_t menu_align)
{
    lv_obj_t **settings_list_elem_container = \
        settings_list_ctx.settings_list_elem_container;
    lv_obj_t *settings_list_container = \
        settings_list_ctx.settings_list_container;

    widget_obj_para.obj_parent = \
        settings_list_container;
    widget_obj_para.obj_width = \
        settings_list_elem_container_width;
    widget_obj_para.obj_height = \
        settings_list_elem_container_height;
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

    for(uint16_t idx = 0; idx < settings_list_elem_num; idx++)
    {
        widget_obj_para.obj_x = \
            settings_list_elem_container_sx;
        widget_obj_para.obj_y = \
            settings_list_elem_container_sy + \
                settings_list_elem_container_height*idx + \
                    settings_list_scroll_offset + settings_list_scroll_dela;
        settings_list_elem_container[idx] = \
            common_widget_obj_create(&widget_obj_para);
        lv_obj_add_flag(settings_list_elem_container[idx], \
            LV_OBJ_FLAG_EVENT_BUBBLE);
        lv_obj_add_event_cb(settings_list_elem_container[idx], \
            settings_list_elem_container_click_cb, LV_EVENT_SHORT_CLICKED, \
                (void *)&settings_list_elem_container_idx[idx]);

        if(widget_obj_para.obj_y >= Settings_List_Container_H || \
            (widget_obj_para.obj_y + settings_list_elem_container_height) < 0)
        {
            lv_obj_add_flag(settings_list_elem_container[idx], \
                LV_OBJ_FLAG_HIDDEN);
        }
    }

    return;
}

/*********************************************************************************
                                  设置列表元素容器滚动                             
*********************************************************************************/
static void settings_list_elem_container_scroll(void)
{
    int16_t obj_y = 0;
    lv_obj_t **settings_list_elem_container = \
        settings_list_ctx.settings_list_elem_container;
 
    for(uint16_t idx = 0; idx < settings_list_elem_num; idx++)
    {
        obj_y = settings_list_elem_container_sy + \
            settings_list_elem_container_height*idx + \
                settings_list_scroll_offset + settings_list_scroll_dela;

        if(obj_y >= Settings_List_Container_H || \
            (obj_y + settings_list_elem_container_height) < 0)
        {
            lv_obj_add_flag(settings_list_elem_container[idx], \
                LV_OBJ_FLAG_HIDDEN);
            continue;
        }
            
        lv_obj_clear_flag(settings_list_elem_container[idx], \
                LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_y(settings_list_elem_container[idx], obj_y);
    }

    return;
}

/*********************************************************************************
                                  设置列表元素图标创建                             
*********************************************************************************/
static void settings_list_elem_icon_create(\
    menu_align_t menu_align)
{
    lv_obj_t **settings_list_icon = \
        settings_list_ctx.settings_list_icon;
    lv_obj_t **settings_list_elem_container = \
        settings_list_ctx.settings_list_elem_container;

    widget_img_para.img_x = 0;
    widget_img_para.img_y = 0;
    widget_img_para.img_click_attr = false;
    widget_img_para.event_cb = NULL;
    widget_img_para.user_data = NULL;

    for(uint16_t idx = 0; idx < settings_list_elem_num; idx++)
    {
        widget_img_para.img_parent = \
            settings_list_elem_container[idx];
        widget_img_para.file_img_dat = \
            settings_list_icon_src[idx];
        settings_list_icon[idx] = \
            common_widget_img_create(&widget_img_para, NULL);

        if(menu_align == menu_align_right)
            lv_obj_align(settings_list_icon[idx], \
                LV_ALIGN_RIGHT_MID, -20, 0);
        else
            lv_obj_align(settings_list_icon[idx], \
                LV_ALIGN_LEFT_MID, 20, 0);
    }

    return;
}

/*********************************************************************************
                                  设置列表元素标签创建                             
*********************************************************************************/
static void settings_list_elem_label_create(\
    menu_align_t menu_align)
{
    lv_obj_t **settings_list_icon = \
        settings_list_ctx.settings_list_icon;
    lv_obj_t **settings_list_label = \
        settings_list_ctx.settings_list_label;
    lv_obj_t **settings_list_elem_container = \
        settings_list_ctx.settings_list_elem_container;

    widget_label_para.label_x = 0;
    widget_label_para.label_y = 0;
    widget_label_para.label_w = 200;
    widget_label_para.label_h = \
        Label_Line_Height*2;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_WRAP;
    if(menu_align == menu_align_right)
        widget_label_para.text_align = \
            LV_TEXT_ALIGN_RIGHT;
    else
        widget_label_para.text_align = \
            LV_TEXT_ALIGN_LEFT;
    widget_label_para.label_text_color = \
        lv_color_hex(0xffffff);
    widget_label_para.label_ver_center = \
        true;
    widget_label_para.user_text_font = NULL;

    for(uint16_t idx = 0; idx < settings_list_elem_num; idx++)
    {
        widget_label_para.label_parent = \
            settings_list_elem_container[idx];
        widget_label_para.label_text = \
            get_lang_txt_with_id(settings_list_text_id[idx]);
        settings_list_label[idx] = \
            common_widget_label_create(&widget_label_para);

        if(menu_align == menu_align_right)
            lv_obj_align_to(settings_list_label[idx], settings_list_icon[idx], \
                LV_ALIGN_OUT_LEFT_MID, -20, 0);
        else
            lv_obj_align_to(settings_list_label[idx], settings_list_icon[idx], \
                LV_ALIGN_OUT_RIGHT_MID, 20, 0);
    }

    return;
}

/*********************************************************************************
                                  设置列表元素箭头创建                             
*********************************************************************************/
static void setting_list_elem_arrow_create(\
    menu_align_t menu_align)
{
    lv_obj_t **settings_list_arrow = \
        settings_list_ctx.settings_list_arrow;
    lv_obj_t **settings_list_label = \
        settings_list_ctx.settings_list_label;
    lv_obj_t **settings_list_elem_container = \
        settings_list_ctx.settings_list_elem_container;

    widget_img_para.img_x = 0;
    widget_img_para.img_y = 0;
    widget_img_para.img_click_attr = false;
    widget_img_para.event_cb = NULL;
    widget_img_para.user_data = NULL;

    for(uint16_t idx = 0; idx < settings_list_elem_num; idx++)
    {
        widget_img_para.img_parent = \
            settings_list_elem_container[idx];
        widget_img_para.file_img_dat = \
            settings_07_index;
        settings_list_arrow[idx] = \
            common_widget_img_create(&widget_img_para, NULL);

        if(menu_align == menu_align_right)
            lv_obj_align_to(settings_list_arrow[idx], settings_list_label[idx], \
                LV_ALIGN_OUT_LEFT_MID, -10, 0);
        else
            lv_obj_align_to(settings_list_arrow[idx], settings_list_label[idx], \
                LV_ALIGN_OUT_RIGHT_MID, 10, 0);
    }

    return;
}

/*********************************************************************************
                                  设置列表容器事件回调                             
*********************************************************************************/
static void settings_list_container_pressed_cb(lv_event_t *e)
{
    settings_list_scroll_dela = 0;

    settings_list_ver_scroll = false;

    lv_indev_t *indev_act = lv_indev_get_act();

    lv_indev_get_point(indev_act, &settings_list_start_point);

    memcpy(&settings_list_now_point, &settings_list_start_point, \
        sizeof(lv_point_t));
    memcpy(&settings_list_min_point, &settings_list_start_point, \
        sizeof(lv_point_t));
    memcpy(&settings_list_max_point, &settings_list_start_point, \
        sizeof(lv_point_t));

    return;
}

static void settings_list_container_pressing_cb(lv_event_t *e)
{
    if(!settings_list_ver_scroll)
    {
        settings_list_ver_scroll_judge();

        if(settings_list_ver_scroll)
        {
            lv_obj_t *settings_list_container = \
                settings_list_ctx.settings_list_container;
            del_anim_with_var(settings_list_container);
        }
    }else
    {
        lv_point_t settings_list_scroll_vert;
        lv_indev_t *indev_act = lv_indev_get_act();
        lv_indev_get_vect(indev_act, &settings_list_scroll_vert);
        settings_list_scroll_dela += settings_list_scroll_vert.y;

        int16_t scroll_top_val = 0;
        int16_t scroll_bottom_val = \
            (-1)*(settings_list_elem_num - settings_list_visual_line) * \
                settings_list_elem_container_height;

        if(settings_list_scroll_offset + settings_list_scroll_dela > \
            scroll_top_val + settings_list_elem_container_height)
        {
            settings_list_scroll_dela = \
                (scroll_top_val + settings_list_elem_container_height) - \
                    settings_list_scroll_offset;
        }else if(settings_list_scroll_offset + settings_list_scroll_dela < \
            scroll_bottom_val - settings_list_elem_container_height)
        {
            settings_list_scroll_dela = \
                (scroll_bottom_val - settings_list_elem_container_height) - \
                    settings_list_scroll_offset;
        }
        
        settings_list_elem_container_scroll();

        common_scrollbar_press_handle(\
            settings_list_scroll_offset \
                + settings_list_scroll_dela);
    }

    return;
}

static void settings_list_container_release_cb(lv_event_t *e)
{
    if(!settings_list_ver_scroll)
        return;

    lv_point_t settings_list_throw_vert;
    lv_indev_t *indev_act = lv_indev_get_act();
    lv_indev_get_throw(indev_act, &settings_list_throw_vert);

    int16_t throw_sum = \
        settings_list_calc_throw_sum(settings_list_throw_vert.y);

    settings_list_scroll_offset += \
        settings_list_scroll_dela;
    settings_list_scroll_dela = 0;

    int16_t scroll_top_val = 0;
    int16_t scroll_bottom_val = \
        (-1)*(settings_list_elem_num - settings_list_visual_line)* \
        settings_list_elem_container_height;

    int16_t throw_start = settings_list_scroll_offset;
    int16_t throw_end = settings_list_scroll_offset + throw_sum;

    int16_t throw_adjust = 0;
    uint32_t anim_duration = 0;
    uint32_t anim_min_duration = 300;
    uint32_t anim_max_duration = 700;

    if(throw_end > scroll_bottom_val && throw_end < scroll_top_val)
    {
        throw_adjust = \
            throw_end%settings_list_elem_container_height;
		if(throw_adjust <= (-1)*(settings_list_elem_container_height/2))
            throw_end -= \
                (settings_list_elem_container_height + throw_adjust);	
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
    lv_obj_t *settings_list_container = \
        settings_list_ctx.settings_list_container;

    widget_anim_para.anim = &throw_anim;
    widget_anim_para.anim_obj = \
        settings_list_container;
    widget_anim_para.anim_exec_xcb = \
        settings_list_throw_anim_cb; 
    widget_anim_para.anim_duration = anim_duration;
    widget_anim_para.anim_start_val = throw_start;
    widget_anim_para.anim_end_val = throw_end;
    widget_anim_para.is_start_anim = false;
    common_widget_anim_create(&widget_anim_para);
    lv_anim_set_path_cb(widget_anim_para.anim, \
        lv_anim_path_ease_out);
    lv_anim_set_ready_cb(widget_anim_para.anim, \
        settings_list_throw_anim_ready_cb);
    lv_anim_start(widget_anim_para.anim);

    return;
}

static void settings_list_container_event_cb(lv_event_t *e)
{
    if(!e) return;

    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_PRESSED)
        settings_list_container_pressed_cb(e);
    else if(event_code == LV_EVENT_PRESSING)
        settings_list_container_pressing_cb(e);
    else if(event_code == LV_EVENT_RELEASED)
        settings_list_container_release_cb(e);

    return;
} 

/*********************************************************************************
                                  设置列表布局创建                                 
*********************************************************************************/
static void settings_list_layout_create(void)
{
    menu_align_t menu_align = \
        menu_align_left;
    if(lang_txt_is_arabic())
        menu_align = \
            menu_align_right;

    settings_list_title_label_create(\
        menu_align);

    settings_list_elem_container_create(\
        menu_align);

    settings_list_elem_icon_create(\
        menu_align);

    settings_list_elem_label_create(\
        menu_align);

    setting_list_elem_arrow_create(\
        menu_align);

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    ui_act_id_t prev_act_id = \
        read_menu_return_level_id();

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, prev_act_id, ui_act_id_null, \
            ui_act_id_settings_list);

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

    memset(&settings_list_ctx, 0, \
        sizeof(settings_list_ctx_t));

    settings_list_title_container_create(obj);

    settings_list_container_create(obj);

    settings_list_layout_create();

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_settings_list) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_settings_list,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
