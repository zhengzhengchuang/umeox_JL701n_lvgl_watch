#include "al_name_list.h"

al_name_list_ctx_t al_name_list_ctx;

static int16_t al_name_list_scroll_dela = 0;
static int16_t al_name_list_scroll_offset = 0;

static bool al_name_list_ver_scroll = false;

static lv_point_t al_name_list_min_point = {0};
static lv_point_t al_name_list_max_point = {0};
static lv_point_t al_name_list_now_point = {0};
static lv_point_t al_name_list_start_point = {0};

static const uint16_t al_name_list_elem_num = \
    Al_Name_Elem_Num;

static const int16_t al_name_list_elem_container_sx = \
    49;

static const int16_t al_name_list_elem_container_sy = \
    10;

static const int16_t al_name_list_elem_container_width = \
    270;

static const int16_t al_name_list_elem_container_height = \
    310;

static const uint8_t al_name_list_visual_line = \
    1;

const uint8_t al_name_idx[Al_Name_Num] = 
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, \
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29, \
    30, 31, 32, 33, 34, 35, 36, 37, 38, 39, \
    40, 41, 42, 43, 44, 45, 46, 47, 48, 49, \
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59, \
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69, \
    70, 71, 72, 73, 74, 75, 76, 77, 78, 79, \
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, \
    90, 91, 92, 93, 94, 95, 96, 97, 98,
};

static void al_name_list_container_cb(lv_event_t *e);
static void al_name_list_elem_container_scroll(void);

static uint8_t al_name_ex_id;
uint8_t get_al_name_ex_id(void)
{
    return al_name_ex_id;
}

void set_al_name_ex_id(uint8_t id)
{
    al_name_ex_id = \
        id;

    return;
}

static void del_anim_with_var(void *var)
{
    if(!var) return;

    if(lv_anim_get(var, NULL))
        lv_anim_del(var, NULL);
        
    return;
}

static bool anim_progress_with_var(void *var)
{
    if(lv_anim_get(var, NULL))
        return true;

    return false;
}

static void al_name_list_ver_scroll_judge(void)
{
    lv_indev_t *indev_act = lv_indev_get_act();

    lv_indev_get_point(indev_act, &al_name_list_now_point);

    if(al_name_list_now_point.x > al_name_list_max_point.x)
        al_name_list_max_point.x = al_name_list_now_point.x;

    if(al_name_list_now_point.x < al_name_list_min_point.x)
        al_name_list_min_point.x = al_name_list_now_point.x;

    if(al_name_list_now_point.y > al_name_list_max_point.y)
        al_name_list_max_point.y = al_name_list_now_point.y;

    if(al_name_list_now_point.y < al_name_list_min_point.y)
        al_name_list_min_point.y = al_name_list_now_point.y;

    int16_t al_name_list_x_max = al_name_list_max_point.x - \
        al_name_list_min_point.x;
    int16_t al_name_list_y_max = al_name_list_max_point.y - \
        al_name_list_min_point.y;

    if(LV_ABS(al_name_list_y_max) >= LV_ABS(al_name_list_x_max) && \
        LV_ABS(al_name_list_y_max) >= 10)
        al_name_list_ver_scroll = true;
    else
        al_name_list_ver_scroll = false;

    return;
}

static int16_t al_name_list_calc_throw_sum(int16_t throw_vert)
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

static void al_name_list_throw_anim_cb(void *var, int32_t val)
{
    al_name_list_scroll_offset = val;

    al_name_list_elem_container_scroll();

    return;
}

static void al_name_list_container_create(lv_obj_t *obj)
{
    lv_obj_t **al_name_list_container = \
        &(al_name_list_ctx.al_name_list_container);

    widget_obj_para.obj_parent = \
        obj;
    widget_obj_para.obj_x = 0;
    widget_obj_para.obj_y = \
        LCD_UI_Y_OFFSET;
    widget_obj_para.obj_width = \
        Al_Name_List_Container_W;
    widget_obj_para.obj_height = \
        Al_Name_List_Container_H;
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
    widget_obj_para.obj_is_scrollable = \
        false;
    *al_name_list_container = \
        common_widget_obj_create(&widget_obj_para);
    lv_obj_add_event_cb(*al_name_list_container, \
        al_name_list_container_cb, LV_EVENT_ALL, NULL);

    return;
}

static void al_name_list_elem_container_cb(lv_event_t *e)
{
    if(!e) return;

    lv_obj_t *al_name_list_container = \
        al_name_list_ctx.al_name_list_container;

    bool anim_progress = \
        anim_progress_with_var(al_name_list_container);

    if(al_name_list_ver_scroll || anim_progress)
        return;

    menu_align_t menu_align = \
        menu_align_left;
    if(lang_txt_is_arabic())
        menu_align = \
            menu_align_right;

    lv_point_t p_act;
    lv_indev_get_point(\
        lv_indev_get_act(), &p_act);

    int16_t sx, ex;
    if(menu_align == menu_align_right)
    {
        sx = \
            al_name_list_elem_container_sx + \
                al_name_list_elem_container_width/2;
        ex = \
            al_name_list_elem_container_sx + \
                al_name_list_elem_container_width;
    }else
    {
        sx = \
            al_name_list_elem_container_sx;
        ex = \
            al_name_list_elem_container_sx + \
                al_name_list_elem_container_width/2;
    }
    
    int16_t sy = \
        LCD_UI_Y_OFFSET;
    int16_t ey = \
        LCD_UI_Y_OFFSET + 80;
    int16_t height = \
        al_name_list_elem_container_height;

    if((p_act.x >= sx && p_act.x < ex) &&
        ((p_act.y >= sy) && (p_act.y < ey) || \
            (p_act.y >= sy + height) && (p_act.y < ey + height)))
    {
        set_vm_para_cache_with_label(\
            vm_label_al_name_list_mode, al_name_list_mode1);

        ui_menu_jump(ui_act_id_al_name_list);

        return;
    }

    uint8_t idx = \
        *(uint8_t *)lv_event_get_user_data(e);

    printf("%s:idx = %d\n", __func__, idx);

    set_al_name_ex_id(idx);

    ui_menu_jump(ui_act_id_al_name_ex);

    return;
}

static void al_name_list_elem_container_create(\
    menu_align_t menu_align)
{
    lv_obj_t **al_name_list_elem_container = \
        al_name_list_ctx.al_name_list_elem_container;
    lv_obj_t *al_name_list_container = \
        al_name_list_ctx.al_name_list_container;

    widget_obj_para.obj_parent = \
        al_name_list_container;
    widget_obj_para.obj_width = \
        al_name_list_elem_container_width;
    widget_obj_para.obj_height = \
        al_name_list_elem_container_height;
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
    widget_obj_para.obj_is_scrollable = \
        false;

    for(uint16_t idx = 0; idx < al_name_list_elem_num; idx++)
    {
        widget_obj_para.obj_x = \
            al_name_list_elem_container_sx;
        widget_obj_para.obj_y = \
            al_name_list_elem_container_sy + \
                al_name_list_elem_container_height*idx + \
                    al_name_list_scroll_offset + al_name_list_scroll_dela;
        al_name_list_elem_container[idx] = \
            common_widget_obj_create(&widget_obj_para);
        lv_obj_add_flag(al_name_list_elem_container[idx], \
            LV_OBJ_FLAG_EVENT_BUBBLE);
        lv_obj_add_event_cb(al_name_list_elem_container[idx], \
            al_name_list_elem_container_cb, LV_EVENT_SHORT_CLICKED, \
                (void *)&al_name_idx[idx]);

        if(widget_obj_para.obj_y >= Al_Name_List_Container_H || \
            (widget_obj_para.obj_y + al_name_list_elem_container_height) < 0)
        {
            lv_obj_add_flag(al_name_list_elem_container[idx], \
                LV_OBJ_FLAG_HIDDEN);
        }
    }

    return;
}

static void al_name_list_elem_container_scroll(void)
{
    int16_t obj_y = 0;
    lv_obj_t **al_name_list_elem_container = \
        al_name_list_ctx.al_name_list_elem_container;
 
    for(uint16_t idx = 0; idx < al_name_list_elem_num; idx++)
    {
        obj_y = al_name_list_elem_container_sy + \
            al_name_list_elem_container_height*idx + \
            al_name_list_scroll_offset + al_name_list_scroll_dela;

        if(obj_y >= Al_Name_List_Container_H || \
            (obj_y + al_name_list_elem_container_height) < 0)
        {
            lv_obj_add_flag(al_name_list_elem_container[idx], \
                LV_OBJ_FLAG_HIDDEN);
            continue;
        }
            
        lv_obj_clear_flag(al_name_list_elem_container[idx], \
                LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_y(al_name_list_elem_container[idx], obj_y);
    }

    return;
}

static void al_name_list_elem_00_create(\
    menu_align_t menu_align)
{
    lv_obj_t **al_name_list_elem_container = \
        al_name_list_ctx.al_name_list_elem_container;

    widget_obj_para.obj_width = \
        60;
    widget_obj_para.obj_height = \
        60;
    widget_obj_para.obj_bg_opax = \
        LV_OPA_100;
    widget_obj_para.obj_bg_color = \
        lv_color_hex(0xF0D990);
    widget_obj_para.obj_border_width = \
        0;
    widget_obj_para.obj_border_opax = \
        LV_OPA_0;
    widget_obj_para.obj_border_color = \
        lv_color_hex(0x000000);
    widget_obj_para.obj_is_scrollable = \
        false;
    widget_obj_para.obj_radius = \
        60/2;

    widget_label_para.label_w = \
        50;
    widget_label_para.label_h = \
        37;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_CLIP;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.label_text_color = \
        lv_color_hex(0x000000);
    widget_label_para.label_ver_center = \
        false;
    widget_label_para.user_text_font = \
        &font_common_num_32;
    
    char elem_00_str[3];
    for(uint16_t idx = 0; idx < al_name_list_elem_num; idx++)
    {
        widget_obj_para.obj_parent = \
            al_name_list_elem_container[idx];
        lv_obj_t *elem_00_container = \
            common_widget_obj_create(&widget_obj_para);
        if(menu_align == menu_align_right)
            lv_obj_align(elem_00_container, LV_ALIGN_TOP_RIGHT, \
                0, 10);
        else
            lv_obj_align(elem_00_container, LV_ALIGN_TOP_LEFT, \
                0, 10);
        lv_obj_clear_flag(elem_00_container, LV_OBJ_FLAG_CLICKABLE);

        memset(elem_00_str, 0 , \
            sizeof(elem_00_str));
        sprintf(elem_00_str, "%02d", \
            idx + 1);
        widget_label_para.label_parent = \
            elem_00_container;
        widget_label_para.label_text = \
            elem_00_str;
        lv_obj_t *elem_00_label = \
            common_widget_label_create(&widget_label_para);
        lv_obj_align(elem_00_label, LV_ALIGN_CENTER, \
            0, 0);
    }

    return;
}


static void al_name_list_elem_01_create(\
    menu_align_t menu_align)
{
    lv_obj_t **al_name_list_elem_container = \
        al_name_list_ctx.al_name_list_elem_container;

    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = \
        NULL;
    for(uint16_t idx = 0; idx < al_name_list_elem_num; idx++)
    {
        widget_img_para.img_parent = \
            al_name_list_elem_container[idx];
        widget_img_para.file_img_dat = \
           al_name_99_icon_00_index + idx; 
        lv_obj_t *elem_01_icon = \
            common_widget_img_create(&widget_img_para, NULL);
        lv_obj_align(elem_01_icon, LV_ALIGN_TOP_MID, \
            0, 40);
    }

    return;
}

static void al_name_list_elem_02_create(\
    menu_align_t menu_align)
{
    lv_obj_t **al_name_list_elem_container = \
        al_name_list_ctx.al_name_list_elem_container;

    widget_label_para.label_w = \
        260;
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
    widget_label_para.user_text_font = \
        NULL;
    
    for(uint16_t idx = 0; idx < al_name_list_elem_num; idx++)
    {
        widget_label_para.label_parent = \
            al_name_list_elem_container[idx];
        widget_label_para.label_text = \
            al_name_lang_txt_with_id(\
                lang_txt_al_name_00 + idx);
        lv_obj_t *al_name_label = \
            common_widget_label_create(&widget_label_para);
        lv_obj_align(al_name_label, LV_ALIGN_TOP_MID, \
            0, 260);
    }

    return;
}

static void al_name_list_container_pressed_cb(lv_event_t *e)
{
    al_name_list_scroll_dela = 0;

    al_name_list_ver_scroll = false;

    lv_indev_t *indev_act = lv_indev_get_act();

    lv_indev_get_point(indev_act, &al_name_list_start_point);

    memcpy(&al_name_list_now_point, &al_name_list_start_point, \
        sizeof(lv_point_t));
    memcpy(&al_name_list_min_point, &al_name_list_start_point, \
        sizeof(lv_point_t));
    memcpy(&al_name_list_max_point, &al_name_list_start_point, \
        sizeof(lv_point_t));

    return;
}

static void al_name_list_container_pressing_cb(lv_event_t *e)
{
    if(!al_name_list_ver_scroll)
    {
        al_name_list_ver_scroll_judge();

        if(al_name_list_ver_scroll)
        {
            lv_obj_t *al_name_list_container = \
                al_name_list_ctx.al_name_list_container;
            del_anim_with_var(al_name_list_container);
        }
    }else
    {
        lv_point_t al_name_list_scroll_vert;
        lv_indev_t *indev_act = lv_indev_get_act();
        lv_indev_get_vect(indev_act, &al_name_list_scroll_vert);
        al_name_list_scroll_dela += al_name_list_scroll_vert.y;

        int16_t scroll_top_val = 0;
        int16_t scroll_bottom_val = \
            (-1)*(al_name_list_elem_num - al_name_list_visual_line) * \
                al_name_list_elem_container_height;

        if(al_name_list_scroll_offset + al_name_list_scroll_dela > \
            scroll_top_val + al_name_list_elem_container_height)
        {
            al_name_list_scroll_dela = \
                (scroll_top_val + al_name_list_elem_container_height) - \
                    al_name_list_scroll_offset;
        }else if(al_name_list_scroll_offset + al_name_list_scroll_dela < \
            scroll_bottom_val - al_name_list_elem_container_height)
        {
            al_name_list_scroll_dela = \
                (scroll_bottom_val - al_name_list_elem_container_height) - \
                    al_name_list_scroll_offset;
        }
        
        al_name_list_elem_container_scroll();
    }

    return;
}

static void al_name_list_container_release_cb(lv_event_t *e)
{
    if(!al_name_list_ver_scroll)
        return;

    lv_point_t al_name_list_throw_vert;
    lv_indev_t *indev_act = lv_indev_get_act();
    lv_indev_get_throw(indev_act, &al_name_list_throw_vert);

    int16_t throw_sum = \
        al_name_list_calc_throw_sum(al_name_list_throw_vert.y);

    al_name_list_scroll_offset += \
        al_name_list_scroll_dela;
    al_name_list_scroll_dela = 0;

    int16_t scroll_top_val = 0;
    int16_t scroll_bottom_val = \
        (-1)*(al_name_list_elem_num - al_name_list_visual_line)* \
        al_name_list_elem_container_height;

    int16_t throw_start = \
        al_name_list_scroll_offset;
    int32_t throw_end = \
        al_name_list_scroll_offset + throw_sum;

    int16_t throw_adjust = 0;
    uint32_t anim_duration = 0;
    uint32_t anim_min_duration = 300;
    uint32_t anim_max_duration = 700;

    if(throw_end > scroll_bottom_val && \
        throw_end < scroll_top_val)
    {
        throw_adjust = \
            throw_end%al_name_list_elem_container_height;
		if(throw_adjust <= (-1)*(al_name_list_elem_container_height/2))
            throw_end -= \
                (al_name_list_elem_container_height + throw_adjust);	
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
    lv_obj_t *al_name_list_container = \
        al_name_list_ctx.al_name_list_container;

    widget_anim_para.anim = &throw_anim;
    widget_anim_para.anim_obj = \
        al_name_list_container;
    widget_anim_para.anim_exec_xcb = \
        al_name_list_throw_anim_cb; 
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

static void al_name_list_container_cb(lv_event_t *e)
{
    if(!e) return;

    lv_event_code_t event_code = \
        lv_event_get_code(e);

    if(event_code == LV_EVENT_PRESSED)
        al_name_list_container_pressed_cb(e);
    else if(event_code == LV_EVENT_PRESSING)
        al_name_list_container_pressing_cb(e);
    else if(event_code == LV_EVENT_RELEASED)
        al_name_list_container_release_cb(e);

    return;
} 

static void al_name_list_layout_create(void)
{
    menu_align_t menu_align = \
        menu_align_left;
    if(lang_txt_is_arabic())
        menu_align = \
            menu_align_right;

    al_name_list_elem_container_create(\
        menu_align);

    al_name_list_elem_01_create(menu_align);

    al_name_list_elem_00_create(menu_align);

    al_name_list_elem_02_create(menu_align);

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    ui_act_id_t prev_act_id = \
        read_menu_return_level_id();

    tileview_register_all_menu(obj, ui_act_id_null, \
        ui_act_id_null, prev_act_id, ui_act_id_null, \
            ui_act_id_al_name_list);

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

    memset(&al_name_list_ctx, 0, \
        sizeof(al_name_list_ctx_t));

    al_name_list_container_create(obj);

    al_name_list_layout_create();

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_al_name_list0) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_al_name_list,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 0,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
