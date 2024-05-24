#include "al_name_list.h"

static bool load_comp;
static uint8_t load_idx;
static uint8_t load_num;
static bool load_comp_op;
static bool load_comp_pressed;
static lv_timer_t \
    *load_comp_timer;

al_name_list_ctx_t al_name_list_ctx;

static bool al_name_list_ver_scroll = \
    false;
static int16_t al_name_list_scroll_dela = 0;
static int16_t al_name_list_scroll_offset = 0;

static lv_point_t al_name_list_min_point = {0};
static lv_point_t al_name_list_max_point = {0};
static lv_point_t al_name_list_now_point = {0};
static lv_point_t al_name_list_start_point = {0};

static const uint8_t al_name_list_elem_num = \
    Al_Name_Elem_Num;

static const uint16_t al_name_list_ec_w = 270;
static const uint16_t al_name_list_ec_h = 310;
static const uint16_t al_name_list_ec_sx = 49;
static const uint16_t al_name_list_ec_sy = 10;

static const uint8_t al_name_list_visual_line = 1;

const uint8_t al_name_ec_idx[Al_Name_Elem_Num] = {
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

static void al_name_list_container_cb(\
    lv_event_t *e);
static void al_name_list_elem_container_scroll(void);

static uint8_t AlNameExId;
uint8_t GetAlNameExId(void)
{
    return AlNameExId;
}

void SetAlNameExId(uint8_t id)
{
    AlNameExId = id;

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

static int16_t al_name_list_throw_sum(\
    int16_t throwv)
{
    int16_t throw_vert_sum = 0;
    int16_t throw_vert_tmp = throwv;
    
    while(throw_vert_tmp)
    {
        throw_vert_sum += throw_vert_tmp;
        throw_vert_tmp = throw_vert_tmp * 90 / 100;
    }
    
    return throw_vert_sum;
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

static void al_name_list_container_create(\
    lv_obj_t *obj)
{
    lv_obj_t **al_name_container = \
        &(al_name_list_ctx.al_name_container);

    widget_obj_para.obj_parent = \
        obj;
    widget_obj_para.obj_x = 0;
    widget_obj_para.obj_y = \
        LCD_UI_Y_OFFSET;
    widget_obj_para.obj_width = \
        Al_Name_Container_W;
    widget_obj_para.obj_height = \
        Al_Name_Container_H;
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
    *al_name_container = \
        common_widget_obj_create(&widget_obj_para);
    lv_obj_add_event_cb(*al_name_container, \
        al_name_list_container_cb, LV_EVENT_ALL, NULL);

    return;
}

static void al_name_list_elem_container_cb(\
    lv_event_t *e)
{
    if(!e) return;

    if(!load_comp_pressed)
        return;

    lv_obj_t *al_name_container = \
        al_name_list_ctx.al_name_container;

    bool anim_progress = \
        anim_progress_with_var(al_name_container);

    if(al_name_list_ver_scroll || anim_progress)
        return;

    menu_align_t menu_align = \
        menu_align_left;
    if(AllahNameIsArabic())
        menu_align = \
            menu_align_right;

    lv_point_t p_act;
    lv_indev_get_point(\
        lv_indev_get_act(), &p_act);

    int16_t sx, ex;
    if(menu_align == menu_align_right)
    {
        sx = \
            al_name_list_ec_sx + \
                al_name_list_ec_w/2;
        ex = \
            al_name_list_ec_sx + \
                al_name_list_ec_w;
    }else
    {
        sx = \
            al_name_list_ec_sx;
        ex = \
            al_name_list_ec_sx + \
                al_name_list_ec_w/2;
    }
    
    int16_t sy = \
        LCD_UI_Y_OFFSET;
    int16_t ey = \
        LCD_UI_Y_OFFSET + 80;
    int16_t height = \
        al_name_list_ec_h;

    if((p_act.x >= sx && p_act.x < ex) &&
        ((p_act.y >= sy) && (p_act.y < ey) || \
            (p_act.y >= sy + height) && (p_act.y < ey + height)))
    {
        SetVmParaCacheByLabel(\
            vm_label_al_name_list_mode, al_name_list_mode1);

        ui_menu_jump(ui_act_id_al_name_list);

        return;
    }

    uint8_t idx = \
        *(uint8_t *)lv_event_get_user_data(e);

    printf("idx = %d\n", idx);

    SetAlNameExId(idx);

    ui_menu_jump(ui_act_id_al_name_ex);

    return;
}

static void al_name_list_elem_container_create(\
    menu_align_t menu_align, uint8_t load_idx, uint8_t load_num)
{
    lv_obj_t *al_name_container = \
        al_name_list_ctx.al_name_container;
    lv_obj_t **al_name_elem_container = \
        al_name_list_ctx.al_name_elem_container;
    
    widget_obj_para.obj_parent = \
        al_name_container;
    widget_obj_para.obj_width = \
        al_name_list_ec_w;
    widget_obj_para.obj_height = \
        al_name_list_ec_h;
    widget_obj_para.obj_bg_opax = \
        LV_OPA_0;
    widget_obj_para.obj_bg_color = \
        lv_color_hex(0x000000);
    widget_obj_para.obj_border_opax = \
        LV_OPA_0;
    widget_obj_para.obj_border_width = \
        0;
    widget_obj_para.obj_border_color = \
        lv_color_hex(0x000000);
    widget_obj_para.obj_radius = 0;
    widget_obj_para.obj_is_scrollable = \
        false;

    for(uint8_t i = load_idx; i < load_idx + load_num; i++)
    {
        widget_obj_para.obj_x = \
            al_name_list_ec_sx;
        widget_obj_para.obj_y = \
            al_name_list_ec_sy + \
                al_name_list_ec_h*i + \
                    al_name_list_scroll_offset + al_name_list_scroll_dela;
        al_name_elem_container[i] = \
            common_widget_obj_create(&widget_obj_para);
        lv_obj_add_flag(al_name_elem_container[i], \
            LV_OBJ_FLAG_EVENT_BUBBLE);
        lv_obj_add_event_cb(al_name_elem_container[i], \
            al_name_list_elem_container_cb, LV_EVENT_SHORT_CLICKED, \
                (void *)&al_name_ec_idx[i]);

        if(widget_obj_para.obj_y >= Al_Name_Container_H || \
            (widget_obj_para.obj_y + al_name_list_ec_h - 1) < 0)
        {
            lv_obj_add_flag(al_name_elem_container[i], \
                LV_OBJ_FLAG_HIDDEN);
        }
    }

    return;
}

static void al_name_list_elem_container_scroll(void)
{
    int16_t obj_y = 0;
    lv_obj_t **al_name_elem_container = \
        al_name_list_ctx.al_name_elem_container;
 
    for(uint8_t i = 0; i < al_name_list_elem_num; i++)
    {
        obj_y = al_name_list_ec_sy + al_name_list_ec_h*i + \
            al_name_list_scroll_offset + al_name_list_scroll_dela;

        if(obj_y >= Al_Name_Container_H || \
            (obj_y + al_name_list_ec_h - 1) < 0)
        {
            lv_obj_add_flag(al_name_elem_container[i], \
                LV_OBJ_FLAG_HIDDEN);

            continue;
        }
            
        lv_obj_clear_flag(al_name_elem_container[i], \
            LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_y(al_name_elem_container[i], obj_y);
    }

    return;
}

static void al_name_list_throw_anim_cb(\
    void *var, int32_t val)
{
    al_name_list_scroll_offset = val;

    al_name_list_elem_container_scroll();

    return;
}

static void al_name_list_throw_ready_cb(\
    lv_anim_t *anim)
{
    lv_obj_t *tileview_obj = \
        tileview_obj_container();
    lv_obj_add_flag(tileview_obj, \
        LV_OBJ_FLAG_SCROLLABLE);

    return;
}

static void al_name_list_elem_00_create(\
    menu_align_t menu_align, uint8_t load_idx, uint8_t load_num)
{
    lv_obj_t **al_name_elem_container = \
        al_name_list_ctx.al_name_elem_container;

    widget_img_para.event_cb = \
        NULL;
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.file_img_dat = \
        comm_icon_31_index;

    widget_label_para.label_w = \
        50;
    widget_label_para.label_h = \
        37;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_CLIP;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.user_text_font = \
        &font_common_num_32;
    widget_label_para.label_text_color = \
        lv_color_hex(0x000000);
    widget_label_para.label_ver_center = \
        false;

    char elem_00_str[3];
    lv_obj_t *al_name_seq_label;
    lv_obj_t *al_name_seq_container;
    for(uint8_t i = load_idx; i < load_idx + load_num; i++)
    {
        widget_img_para.img_parent = \
            al_name_elem_container[i];
        al_name_seq_container = \
            common_widget_img_create(&widget_img_para, NULL);
        if(menu_align == menu_align_right)
            lv_obj_align(al_name_seq_container, LV_ALIGN_TOP_RIGHT, \
                0, 10);
        else
            lv_obj_align(al_name_seq_container, LV_ALIGN_TOP_LEFT, \
                0, 10);

        memset(elem_00_str, 0, \
            sizeof(elem_00_str));
        sprintf(elem_00_str, "%02d", \
            i + 1);
        widget_label_para.label_parent = \
            al_name_seq_container;
        widget_label_para.label_text = \
            elem_00_str;
        al_name_seq_label = \
            common_widget_label_create(&widget_label_para);
        lv_obj_align(al_name_seq_label, LV_ALIGN_CENTER, \
            0, 0);
    }

    return;
}

static void al_name_list_elem_01_create(\
    menu_align_t menu_align, uint8_t load_idx, uint8_t load_num)
{
    lv_obj_t **al_name_elem_container = \
        al_name_list_ctx.al_name_elem_container;
 
    widget_img_para.img_click_attr = \
        false;
    widget_img_para.event_cb = \
        NULL;

    lv_obj_t *elem_01_obj;
    for(uint8_t i = load_idx; i < load_idx + load_num; i++)
    {
        widget_img_para.img_parent = \
            al_name_elem_container[i];
        widget_img_para.file_img_dat = \
            al_name_99_icon_00_index + i;
        elem_01_obj = \
            common_widget_img_create(&widget_img_para, NULL);
        lv_obj_align(elem_01_obj, LV_ALIGN_TOP_MID, \
            0, 40);
    }

    return;
}

static void al_name_list_elem_02_create(\
    menu_align_t menu_align, uint8_t load_idx)
{
    lv_obj_t **al_name_elem_container = \
        al_name_list_ctx.al_name_elem_container;

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

    lv_obj_t *elem_02_obj;
    for(uint8_t i = load_idx; i < load_idx + 1; i++)
    {
        widget_label_para.label_parent = \
            al_name_elem_container[i];
        widget_label_para.label_text = \
            GetAllahNameTableFollowLang(\
                lang_txt_al_name_00 + i);
        elem_02_obj = \
            common_widget_label_create(&widget_label_para);
        lv_obj_align(elem_02_obj, LV_ALIGN_TOP_MID, \
            0, 260);
    }

    return;
}

static void al_name_list_container_pressed_cb(\
    lv_event_t *e)
{
    if(!load_comp_op)
    {
        load_comp_pressed = \
            false;
        return;
    }

    load_comp_pressed = true;

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

static void al_name_list_container_pressing_cb(\
    lv_event_t *e)
{
    if(!load_comp_pressed)
        return;

    if(!al_name_list_ver_scroll)
    {
        al_name_list_ver_scroll_judge();

        if(al_name_list_ver_scroll)
        {
            lv_obj_t *al_name_container = \
                al_name_list_ctx.al_name_container;
            del_anim_with_var(al_name_container);
        }
    }else
    {
        lv_point_t al_name_list_sv;
        lv_indev_t *indev_act = \
            lv_indev_get_act();
        lv_indev_get_vect(indev_act, \
            &al_name_list_sv);
        al_name_list_scroll_dela += \
            al_name_list_sv.y;

        int16_t scroll_top_val = 0;
        int16_t scroll_bottom_val = \
            (-1)*(al_name_list_elem_num - al_name_list_visual_line) * \
                al_name_list_ec_h;

        if(al_name_list_scroll_offset + al_name_list_scroll_dela > \
            scroll_top_val + al_name_list_ec_h)
        {
            al_name_list_scroll_dela = \
                (scroll_top_val + al_name_list_ec_h) - \
                    al_name_list_scroll_offset;
        }else if(al_name_list_scroll_offset + al_name_list_scroll_dela < \
            scroll_bottom_val - al_name_list_ec_h)
        {
            al_name_list_scroll_dela = \
                (scroll_bottom_val - al_name_list_ec_h) - \
                    al_name_list_scroll_offset;
        }
        
        al_name_list_elem_container_scroll();
    }

    return;
}

static void al_name_list_container_release_cb(\
    lv_event_t *e)
{
    if(!load_comp_pressed)
        return;

    if(!al_name_list_ver_scroll)
        return;

    lv_point_t al_name_list_throwv;
    lv_indev_t *indev_act = \
        lv_indev_get_act();
    lv_indev_get_throw(indev_act, \
        &al_name_list_throwv);

    int16_t throw_sum = \
        al_name_list_throw_sum(al_name_list_throwv.y);

    al_name_list_scroll_offset += \
        al_name_list_scroll_dela;
    al_name_list_scroll_dela = 0;

    int16_t scroll_top_val = 0;
    int16_t scroll_bottom_val = \
        (-1)*(al_name_list_elem_num - al_name_list_visual_line)* \
            al_name_list_ec_h;

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
            throw_end%al_name_list_ec_h;
		if(throw_adjust <= (-1)*(al_name_list_ec_h/2))
            throw_end -= \
                (al_name_list_ec_h + throw_adjust);	
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
    lv_obj_t *al_name_container = \
        al_name_list_ctx.al_name_container;
    lv_obj_t *tileview_obj = \
        tileview_obj_container();
    lv_obj_clear_flag(tileview_obj, \
        LV_OBJ_FLAG_SCROLLABLE);

    widget_anim_para.anim = &throw_anim;
    widget_anim_para.anim_obj = \
        al_name_container;
    widget_anim_para.anim_exec_xcb = \
        al_name_list_throw_anim_cb; 
    widget_anim_para.anim_duration = anim_duration;
    widget_anim_para.anim_start_val = throw_start;
    widget_anim_para.anim_end_val = throw_end;
    widget_anim_para.is_start_anim = false;
    common_widget_anim_create(&widget_anim_para);
    lv_anim_set_path_cb(widget_anim_para.anim, \
        lv_anim_path_ease_out);
    lv_anim_set_ready_cb(widget_anim_para.anim, \
        al_name_list_throw_ready_cb);
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
    if(AllahNameIsArabic())
        menu_align = \
            menu_align_right;

    int16_t scroll = \
        al_name_list_scroll_offset + \
            al_name_list_scroll_dela;
    uint16_t ec_h = \
        al_name_list_ec_h;
    load_idx = LV_ABS(scroll/ec_h);
    if(load_idx < Al_Name_Elem_Num - 1)
        load_num = 2;
    else
        load_num = 1;

    al_name_list_elem_container_create(\
        menu_align, load_idx, load_num);

    al_name_list_elem_01_create(menu_align, \
        load_idx, load_num);

    al_name_list_elem_00_create(menu_align, \
        load_idx, load_num);

    al_name_list_elem_02_create(menu_align, \
        load_idx);

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;

    ui_act_id_t prev_act_id = \
        ui_act_id_menu;
    if(!lang_txt_is_arabic())
        tileview_register_all_menu(obj, ui_act_id_null, ui_act_id_null, \
            prev_act_id, ui_act_id_null, ui_act_id_al_name_list);
    else
        tileview_register_all_menu(obj, ui_act_id_null, ui_act_id_null, \
            ui_act_id_null, prev_act_id, ui_act_id_al_name_list);

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    if(load_comp_timer)
    {
        lv_timer_del(\
            load_comp_timer);
        load_comp_timer = NULL;
    }

    return;
}

static void load_comp_op_timeout_cb(\
    lv_timer_t *timer)
{
    if(load_comp_timer)
    {
        lv_timer_del(\
            load_comp_timer);
        load_comp_timer = NULL;
    }

    load_comp_op = true;

    return;
}

static void menu_refresh_cb(lv_obj_t *obj)
{
    if(!obj) return;

    if(load_comp)
        goto __load_comp;

    menu_align_t menu_align = \
        menu_align_left;
    if(AllahNameIsArabic())
        menu_align = \
            menu_align_right;

    lv_obj_t *al_name_container = \
        al_name_list_ctx.al_name_container;
    lv_obj_t **al_name_elem_container = \
        al_name_list_ctx.al_name_elem_container;

    widget_obj_para.obj_parent = \
        al_name_container;
    widget_obj_para.obj_width = \
        al_name_list_ec_w;
    widget_obj_para.obj_height = \
        al_name_list_ec_h;
    widget_obj_para.obj_bg_opax = \
        LV_OPA_0;
    widget_obj_para.obj_bg_color = \
        lv_color_hex(0x000000);
    widget_obj_para.obj_border_opax = \
        LV_OPA_0;
    widget_obj_para.obj_border_width = \
        0;
    widget_obj_para.obj_border_color = \
        lv_color_hex(0x000000);
    widget_obj_para.obj_radius = 0;
    widget_obj_para.obj_is_scrollable = \
        false;

    for(uint8_t i = 0; i < load_idx; i++)
    {
        widget_obj_para.obj_x = \
            al_name_list_ec_sx;
        widget_obj_para.obj_y = \
            al_name_list_ec_sy + \
                al_name_list_ec_h*i + \
                    al_name_list_scroll_offset + al_name_list_scroll_dela;
        al_name_elem_container[i] = \
            common_widget_obj_create(&widget_obj_para);
        lv_obj_add_flag(al_name_elem_container[i], \
            LV_OBJ_FLAG_EVENT_BUBBLE);
        lv_obj_add_event_cb(al_name_elem_container[i], \
            al_name_list_elem_container_cb, LV_EVENT_SHORT_CLICKED, \
                (void *)&al_name_ec_idx[i]);

        if(widget_obj_para.obj_y >= Al_Name_Container_H || \
            (widget_obj_para.obj_y + al_name_list_ec_h - 1) < 0)
        {
            lv_obj_add_flag(al_name_elem_container[i], \
                LV_OBJ_FLAG_HIDDEN);
        }
    }

    for(uint8_t i = load_idx + load_num; i < al_name_list_elem_num; \
        i++)
    {
        widget_obj_para.obj_x = \
            al_name_list_ec_sx;
        widget_obj_para.obj_y = \
            al_name_list_ec_sy + \
                al_name_list_ec_h*i + \
                    al_name_list_scroll_offset + al_name_list_scroll_dela;
        al_name_elem_container[i] = \
            common_widget_obj_create(&widget_obj_para);
        lv_obj_add_flag(al_name_elem_container[i], \
            LV_OBJ_FLAG_EVENT_BUBBLE);
        lv_obj_add_event_cb(al_name_elem_container[i], \
            al_name_list_elem_container_cb, LV_EVENT_SHORT_CLICKED, \
                (void *)&al_name_ec_idx[i]);

        if(widget_obj_para.obj_y >= Al_Name_Container_H || \
            (widget_obj_para.obj_y + al_name_list_ec_h - 1) < 0)
        {
            lv_obj_add_flag(al_name_elem_container[i], \
                LV_OBJ_FLAG_HIDDEN);
        }
    }
 
    widget_img_para.event_cb = \
        NULL;
    widget_img_para.img_click_attr = \
        false;
    
    lv_obj_t *elem_01_obj;
    for(uint8_t i = 0; i < load_idx; i++)
    {
        widget_img_para.img_parent = \
            al_name_elem_container[i];
        widget_img_para.file_img_dat = \
            al_name_99_icon_00_index + i;
        elem_01_obj = \
            common_widget_img_create(&widget_img_para, NULL);
        lv_obj_align(elem_01_obj, LV_ALIGN_TOP_MID, \
            0, 40);
    }

    for(uint8_t i = load_idx + load_num; i < al_name_list_elem_num; \
        i++)
    {
        widget_img_para.img_parent = \
            al_name_elem_container[i];
        widget_img_para.file_img_dat = \
            al_name_99_icon_00_index + i;
        elem_01_obj = \
            common_widget_img_create(&widget_img_para, NULL);
        lv_obj_align(elem_01_obj, LV_ALIGN_TOP_MID, \
            0, 40);
    }

    widget_img_para.file_img_dat = \
        comm_icon_31_index;

    widget_label_para.label_w = \
        50;
    widget_label_para.label_h = \
        37;
    widget_label_para.long_mode = \
        LV_LABEL_LONG_CLIP;
    widget_label_para.text_align = \
        LV_TEXT_ALIGN_CENTER;
    widget_label_para.user_text_font = \
        &font_common_num_32;
    widget_label_para.label_text_color = \
        lv_color_hex(0x000000);
    widget_label_para.label_ver_center = \
        false;

    char elem_00_str[3];
    lv_obj_t *al_name_seq_label;
    lv_obj_t *al_name_seq_container;
    for(uint8_t i = 0; i < load_idx; i++)
    {
        widget_img_para.img_parent = \
            al_name_elem_container[i];
        al_name_seq_container = \
            common_widget_img_create(&widget_img_para, NULL);
        if(menu_align == menu_align_right)
            lv_obj_align(al_name_seq_container, LV_ALIGN_TOP_RIGHT, \
                0, 10);
        else
            lv_obj_align(al_name_seq_container, LV_ALIGN_TOP_LEFT, \
                0, 10);

        memset(elem_00_str, 0, \
            sizeof(elem_00_str));
        sprintf(elem_00_str, "%02d", \
            i + 1);
        widget_label_para.label_parent = \
            al_name_seq_container;
        widget_label_para.label_text = \
            elem_00_str;
        al_name_seq_label = \
            common_widget_label_create(&widget_label_para);
        lv_obj_align(al_name_seq_label, LV_ALIGN_CENTER, \
            0, 0);
    }

    for(uint8_t i = load_idx + load_num; i < al_name_list_elem_num; \
        i++)
    {
        widget_img_para.img_parent = \
            al_name_elem_container[i];
        al_name_seq_container = \
            common_widget_img_create(&widget_img_para, NULL);
        if(menu_align == menu_align_right)
            lv_obj_align(al_name_seq_container, LV_ALIGN_TOP_RIGHT, \
                0, 10);
        else
            lv_obj_align(al_name_seq_container, LV_ALIGN_TOP_LEFT, \
                0, 10);

        memset(elem_00_str, 0, \
            sizeof(elem_00_str));
        sprintf(elem_00_str, "%02d", \
            i + 1);
        widget_label_para.label_parent = \
            al_name_seq_container;
        widget_label_para.label_text = \
            elem_00_str;
        al_name_seq_label = \
            common_widget_label_create(&widget_label_para);
        lv_obj_align(al_name_seq_label, LV_ALIGN_CENTER, \
            0, 0);
    }

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
    widget_label_para.user_text_font = \
        NULL;
    lv_obj_t *elem_02_obj;
    for(uint8_t i = 0; i < load_idx; i++)
    {
        widget_label_para.label_parent = \
            al_name_elem_container[i];
        widget_label_para.label_text = \
            GetAllahNameTableFollowLang(\
                lang_txt_al_name_00 + i);
        elem_02_obj = \
            common_widget_label_create(&widget_label_para);
        lv_obj_align(elem_02_obj, LV_ALIGN_TOP_MID, \
            0, 260);
    }

    for(uint8_t i = load_idx + 1; i < al_name_list_elem_num; \
        i++)
    {
        widget_label_para.label_parent = \
            al_name_elem_container[i];
        widget_label_para.label_text = \
            GetAllahNameTableFollowLang(\
                lang_txt_al_name_00 + i);
        elem_02_obj = \
            common_widget_label_create(&widget_label_para);
        lv_obj_align(elem_02_obj, LV_ALIGN_TOP_MID, \
            0, 260);
    }

    load_comp = true;

    if(!load_comp_timer)
        load_comp_timer = \
            lv_timer_create(load_comp_op_timeout_cb, 40, NULL);

    common_refresh_timer_destroy();

__load_comp:

    printf("%s\n", __func__);
    
    return;
}

static void menu_display_cb(lv_obj_t *obj)
{
    if(!obj) return;

    load_comp = false;
    load_comp_op = false;
    load_comp_pressed = false;

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
    .user_refresh_time_inv = 10,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
