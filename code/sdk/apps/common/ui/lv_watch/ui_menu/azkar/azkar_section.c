#include "azkar_section.h"

static azkar_sec_ctx_t azkar_sec_ctx;

static const int16_t azkar_sec_ec_sx = \
    0;
static const int16_t azkar_sec_ec_sy = \
    0;
static const int16_t azkar_sec_ec_inv = \
    Azkar_Sec_Container_W;
static const uint16_t azkar_sec_ec_w = \
    Azkar_Sec_Container_W;
static const uint16_t azkar_sec_ec_h = \
    Azkar_Sec_Container_H;

static bool azkar_sec_hor_scroll = \
    false;
static int16_t azkar_sec_scroll_dela = \
    0;
static int16_t azkar_sec_scroll_offset = \
    0;

static bool azkar_sec_txt_load = \
    false;

static bool azkar_sec_scroll_lock = \
    false;

static lv_point_t azkar_sec_min_point = {0};
static lv_point_t azkar_sec_max_point = {0};
static lv_point_t azkar_sec_now_point = {0};
static lv_point_t azkar_sec_start_point = {0};

static void azkar_sec_all_obj_event_cb(\
    lv_event_t *e);
static void azkar_sec_elem_container_scroll(void);

void set_azkar_sec_scroll_offset(int16_t val)
{
    azkar_sec_scroll_offset = \
        val;

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

static void azkar_sec_hor_scroll_judge(void)
{
    menu_align_t menu_align = \
        menu_align_left;
    if(lang_txt_is_arabic())
        menu_align = \
            menu_align_right;

    lv_indev_t *indev_act = \
        lv_indev_get_act();
    lv_indev_get_point(indev_act, \
        &azkar_sec_now_point);

    if(azkar_sec_now_point.x > azkar_sec_max_point.x)
        azkar_sec_max_point.x = azkar_sec_now_point.x;

    if(azkar_sec_now_point.x < azkar_sec_min_point.x)
        azkar_sec_min_point.x = azkar_sec_now_point.x;

    if(azkar_sec_now_point.y > azkar_sec_max_point.y)
        azkar_sec_max_point.y = azkar_sec_now_point.y;

    if(azkar_sec_now_point.y < azkar_sec_min_point.y)
        azkar_sec_min_point.y = azkar_sec_now_point.y;

    int16_t azkar_sec_x_max = azkar_sec_max_point.x - \
        azkar_sec_min_point.x;
    int16_t azkar_sec_y_max = azkar_sec_max_point.y - \
        azkar_sec_min_point.y;

    if(LV_ABS(azkar_sec_x_max) >= LV_ABS(azkar_sec_y_max) && \
        LV_ABS(azkar_sec_x_max) >= 10)
        azkar_sec_hor_scroll = true;
    else
        azkar_sec_hor_scroll = false;

    return;
}

static void azkar_sec_throw_ready_cb(lv_anim_t *a)
{
    uint8_t SecIdx =\
        LV_ABS(azkar_sec_scroll_offset) / \
            Azkar_Sec_Container_W;
    uint8_t SecNum =\
        GetAzkarPrayerSecNum();
    SecIdx %= SecNum;
    SetAzkarSecIdx(SecIdx);

    lv_obj_t *tileview_obj = \
        tileview_obj_container();
    if(SecIdx == 0)
        lv_obj_add_flag(tileview_obj, \
            LV_OBJ_FLAG_SCROLLABLE);
    else
        lv_obj_clear_flag(tileview_obj, \
            LV_OBJ_FLAG_SCROLLABLE);

    return;
}

static void azkar_sec_throw_anim_cb(void *var, int32_t val)
{   
    azkar_sec_scroll_offset = \
        val;

    azkar_sec_elem_container_scroll();

    return;
}

static void azkar_sec_container_create(lv_obj_t *obj)
{
    lv_obj_t **azkar_sec_container = \
        &(azkar_sec_ctx.azkar_sec_container);

    widget_obj_para.obj_parent = \
        obj;
    widget_obj_para.obj_x = \
        0;
    widget_obj_para.obj_y = \
        LCD_UI_Y_OFFSET;
    widget_obj_para.obj_width = \
        Azkar_Sec_Container_W;
    widget_obj_para.obj_height = \
        Azkar_Sec_Container_H;
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
    *azkar_sec_container = \
        common_widget_obj_create(&widget_obj_para);
    lv_obj_add_event_cb(*azkar_sec_container, \
        azkar_sec_all_obj_event_cb, LV_EVENT_ALL, NULL);

    return;
}

static void azkar_sec_elem_container_create(\
    menu_align_t menu_align)
{
    lv_obj_t *azkar_sec_container = \
        azkar_sec_ctx.azkar_sec_container;
    lv_obj_t **azkar_sec_elem_container = \
        azkar_sec_ctx.azkar_sec_elem_container;

    widget_obj_para.obj_parent = \
        azkar_sec_container;
    widget_obj_para.obj_width = \
        azkar_sec_ec_w;
    widget_obj_para.obj_height = \
        azkar_sec_ec_h;
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

    uint8_t azkar_sec_num = \
        GetAzkarPrayerSecNum();
    for(uint8_t i = 0; i < azkar_sec_num; i++)
    {
        if(menu_align == menu_align_left)
            widget_obj_para.obj_x = \
                azkar_sec_ec_sx + \
                    azkar_sec_ec_inv*i + \
                        azkar_sec_scroll_offset + \
                            azkar_sec_scroll_dela;
        else
            widget_obj_para.obj_x = \
                azkar_sec_ec_sx - \
                    azkar_sec_ec_inv*i + \
                        azkar_sec_scroll_offset + \
                            azkar_sec_scroll_dela;
        widget_obj_para.obj_y = \
            azkar_sec_ec_sy;
        azkar_sec_elem_container[i] = \
            common_widget_obj_create(&widget_obj_para);
        lv_obj_add_event_cb(azkar_sec_elem_container[i], \
            azkar_sec_all_obj_event_cb, LV_EVENT_ALL, NULL);
 
        if(widget_obj_para.obj_x >= Azkar_Sec_Container_W || \
            (widget_obj_para.obj_x + azkar_sec_ec_w - 1) < 0)
        {
            lv_obj_add_flag(azkar_sec_elem_container[i], \
                LV_OBJ_FLAG_HIDDEN);
        }
    }

    return;
}

static void azkar_sec_elem_container_scroll(void)
{
    menu_align_t menu_align = \
        menu_align_left;
    if(lang_txt_is_arabic())
        menu_align = \
            menu_align_right;

    int16_t obj_x = 0;
    lv_obj_t **azkar_sec_elem_container = \
        azkar_sec_ctx.azkar_sec_elem_container;
 
    uint8_t SecNum = \
        GetAzkarPrayerSecNum();
    for(uint8_t i = 0; i < SecNum; i++)
    {
        if(menu_align == menu_align_right)
            obj_x = azkar_sec_ec_sx - azkar_sec_ec_inv*i + \
                azkar_sec_scroll_offset + azkar_sec_scroll_dela;
        else
            obj_x = azkar_sec_ec_sx + azkar_sec_ec_inv*i + \
                azkar_sec_scroll_offset + azkar_sec_scroll_dela;
            
        if(obj_x >= Azkar_Sec_Container_W || \
            (obj_x + azkar_sec_ec_w - 1) < 0)
        {
            lv_obj_add_flag(azkar_sec_elem_container[i], \
                LV_OBJ_FLAG_HIDDEN);

            continue;
        }

        lv_obj_clear_flag(azkar_sec_elem_container[i], \
                LV_OBJ_FLAG_HIDDEN);

        lv_obj_set_x(azkar_sec_elem_container[i], obj_x);
    }

    return;
}

static void azkar_sec_elem_ctx_label_create(\
    menu_align_t menu_align)
{
    lv_obj_t **azkar_sec_ctx_label = \
        azkar_sec_ctx.azkar_sec_ctx_label;
    lv_obj_t **azkar_sec_elem_container = \
        azkar_sec_ctx.azkar_sec_elem_container;
    
    int16_t azkar_cont_y;
    const char *azkar_title;
    uint8_t azkar_read_freq;
    char azkar_read_freq_str[10];

    uint8_t SecIdx = \
        GetAzkarSecIdx();
    uint8_t SecNum = \
        GetAzkarPrayerSecNum();
    AzkarTxtLang_t TxtLang = \
        GetAzkarTxtLang();
    for(uint8_t i = 0; i < SecNum; i++)
    {
        azkar_read_freq = \
            GetAzkarPrayerReadFreq(i);
        if(azkar_read_freq > 1) 
        {
            memset(azkar_read_freq_str, 0, \
                sizeof(azkar_read_freq_str));
            sprintf(azkar_read_freq_str, "[%d]", \
                azkar_read_freq);
            widget_label_para.label_w = \
                60;
            widget_label_para.label_h = \
                37;
            widget_label_para.long_mode = \
                LV_LABEL_LONG_CLIP;
            widget_label_para.text_align = \
                LV_TEXT_ALIGN_CENTER;
            widget_label_para.label_text_color = \
                lv_color_hex(0xf0d790);
            widget_label_para.label_ver_center = \
                false;
            widget_label_para.user_text_font = \
                &font_common_num_32;
            widget_label_para.label_parent = \
                azkar_sec_elem_container[i];
            widget_label_para.label_text = \
                azkar_read_freq_str;
            lv_obj_t *azkar_freq_label = \
                common_widget_label_create(&widget_label_para);
            lv_obj_align(azkar_freq_label, LV_ALIGN_TOP_MID, \
                0, 20);
        } 
        
        azkar_title = \
            GetAzkarPrayerTxtTitle(i);
        if(azkar_title)
        {
            widget_label_para.label_w = \
                320;
            widget_label_para.label_h = \
                36*2;
            widget_label_para.long_mode = \
                LV_LABEL_LONG_WRAP;
            widget_label_para.text_align = \
                LV_TEXT_ALIGN_CENTER;
            widget_label_para.label_text_color = \
                lv_color_hex(0xf0d790);
            widget_label_para.label_ver_center = \
                true;
            widget_label_para.user_text_font = \
                &font_common_26_no_ch;
            widget_label_para.label_parent = \
                azkar_sec_elem_container[i];
            widget_label_para.label_text = \
                GetAzkarPrayerTxtTitle(i);
            lv_obj_t *azkar_sec_title_label = \
                common_widget_label_create(&widget_label_para);
            if(azkar_read_freq > 1)
                lv_obj_align(azkar_sec_title_label, LV_ALIGN_TOP_MID, \
                    0, 60);
            else
                lv_obj_align(azkar_sec_title_label, LV_ALIGN_TOP_MID, \
                    0, 20);
        }
        
        widget_textarea_para.width = \
            320;
        if(azkar_read_freq > 1)
        {
            if(azkar_title)
                azkar_cont_y = 142;  
            else
                azkar_cont_y = 60;  
        }else
        {
            if(azkar_title)
                azkar_cont_y = 102;
            else
                azkar_cont_y = 20;     
        }
        widget_textarea_para.height = \
            Azkar_Sec_Container_H - \
                azkar_cont_y;
        widget_textarea_para.font = \
            &font_common_26_no_ch;
        widget_textarea_para.color = \
            lv_color_hex(0xffffff);
        if(menu_align == menu_align_right)
            widget_textarea_para.align = \
                LV_TEXT_ALIGN_RIGHT;
        else
            widget_textarea_para.align = \
                LV_TEXT_ALIGN_LEFT;
        widget_textarea_para.bg_opa_x = \
            LV_OPA_0;
        widget_textarea_para.bg_color = \
            lv_color_hex(0x000000);
        widget_textarea_para.border_width = \
            0;
        widget_textarea_para.border_opa_x = \
            LV_OPA_0;
        widget_textarea_para.border_color = \
            lv_color_hex(0x000000);
        widget_textarea_para.parent = \
            azkar_sec_elem_container[i];
        if(i == SecIdx)
            widget_textarea_para.txt = \
                GetAzkarPrayerTxtContent(i);
        else
            widget_textarea_para.txt = NULL;
        azkar_sec_ctx_label[i] = \
            common_widget_textarea_create(&widget_textarea_para);
        lv_obj_align(azkar_sec_ctx_label[i], LV_ALIGN_TOP_MID, \
            0, azkar_cont_y);
        lv_obj_set_style_pad_top(azkar_sec_ctx_label[i], \
                10, LV_PART_MAIN);
        if(TxtLang == AzkarTxtLangAr)
            lv_obj_set_style_pad_bottom(azkar_sec_ctx_label[i], \
                20, LV_PART_MAIN);
        else
            lv_obj_set_style_pad_bottom(azkar_sec_ctx_label[i], \
                60, LV_PART_MAIN);
        lv_obj_add_flag(azkar_sec_ctx_label[i], \
            LV_OBJ_FLAG_EVENT_BUBBLE);
    }

    return;
}

static void azkar_sec_elem_tr_icon_cb(\
    lv_event_t *e)
{
    if(!e) return;

    if(!azkar_sec_txt_load)
        return;

    AzkarTxtLang_t TxtLang = \
        GetAzkarTxtLang();
    if(TxtLang == AzkarTxtLangEn)
        TxtLang = AzkarTxtLangTr;
    else if(TxtLang == AzkarTxtLangTr)
        TxtLang = AzkarTxtLangEn;
    SetAzkarTxtLang(TxtLang);

    ui_menu_jump(\
        p_ui_info_cache->cur_act_id);

    return;
}

static void azkar_sec_elem_tr_icon_create(\
    menu_align_t menu_align)
{
    lv_obj_t **azkar_sec_elem_container = \
        azkar_sec_ctx.azkar_sec_elem_container;

    uint8_t azkar_sec_num = \
        GetAzkarPrayerSecNum();
    AzkarTxtLang_t azkar_lang = \
        GetAzkarTxtLang();
    for(uint8_t i = 0; i < azkar_sec_num; i++)
    {
        widget_img_para.img_parent = \
            azkar_sec_elem_container[i];
        if(azkar_lang == AzkarTxtLangEn)
            widget_img_para.file_img_dat = \
                azkar_tr_00_index;
        else
            widget_img_para.file_img_dat = \
                azkar_tr_01_index;
        widget_img_para.img_click_attr = \
            true;
        widget_img_para.event_cb = \
            azkar_sec_elem_tr_icon_cb;
        widget_img_para.user_data = \
            NULL;
        lv_obj_t *azkar_tr_icon = \
            common_widget_img_create(&widget_img_para, NULL);
        lv_obj_align(azkar_tr_icon, LV_ALIGN_BOTTOM_RIGHT, \
            -40, -30);
        lv_obj_set_ext_click_area(azkar_tr_icon, 30);
        lv_obj_add_flag(azkar_tr_icon, LV_OBJ_FLAG_EVENT_BUBBLE);
        if(azkar_lang == AzkarTxtLangAr)
            lv_obj_add_flag(azkar_tr_icon, LV_OBJ_FLAG_HIDDEN);
    }

    return;
}

static void azkar_sec_container_pressed_cb(lv_event_t *e)
{
    lv_obj_t *azkar_sec_container = \
        azkar_sec_ctx.azkar_sec_container;

    if(anim_progress_with_var(\
        azkar_sec_container))
    {
        azkar_sec_scroll_lock = \
            true;

        return;  
    }

    if(!azkar_sec_txt_load)
    {
        azkar_sec_scroll_lock = \
            true;

        return; 
    }

    azkar_sec_scroll_lock = \
        false; 

    azkar_sec_scroll_dela = 0;

    azkar_sec_hor_scroll = false;

    lv_indev_t *indev_act = lv_indev_get_act();

    lv_indev_get_point(indev_act, &azkar_sec_start_point);

    memcpy(&azkar_sec_now_point, &azkar_sec_start_point, \
        sizeof(lv_point_t));
    memcpy(&azkar_sec_min_point, &azkar_sec_start_point, \
        sizeof(lv_point_t));
    memcpy(&azkar_sec_max_point, &azkar_sec_start_point, \
        sizeof(lv_point_t));

    return;
}

static void azkar_sec_container_pressing_cb(lv_event_t *e)
{
    if(azkar_sec_scroll_lock)
        return;

    if(!azkar_sec_hor_scroll)
    {
        azkar_sec_hor_scroll_judge();

        if(azkar_sec_hor_scroll)
        {
            lv_obj_t *azkar_sec_container = \
                azkar_sec_ctx.azkar_sec_container;
            del_anim_with_var(\
                azkar_sec_container);

            uint8_t SecIdx = \
                GetAzkarSecIdx();
            lv_obj_t *azkar_sec_ctx_label = \
                azkar_sec_ctx.azkar_sec_ctx_label[SecIdx];
            lv_obj_clear_flag(azkar_sec_ctx_label, \
                LV_OBJ_FLAG_SCROLLABLE);
        }
    }

    return;
}

static void azkar_sec_container_release_cb(lv_event_t *e)
{
    if(azkar_sec_scroll_lock)
        return;

    if(!azkar_sec_hor_scroll)
        return;

    menu_align_t menu_align = \
        menu_align_left;
    if(lang_txt_is_arabic())
        menu_align = \
            menu_align_right;

    uint8_t SecIdx = \
        GetAzkarSecIdx();
    uint8_t SecNum = \
        GetAzkarPrayerSecNum();

    lv_point_t azkar_sec_throw;
    lv_indev_t *indev_act = \
        lv_indev_get_act();
    lv_indev_get_throw(indev_act, \
        &azkar_sec_throw);

    lv_obj_t *azkar_sec_ctx_label = \
        azkar_sec_ctx.azkar_sec_ctx_label[SecIdx];
    lv_obj_add_flag(azkar_sec_ctx_label, \
        LV_OBJ_FLAG_SCROLLABLE);

    int16_t scroll_abs_min;
    int16_t scroll_abs_max;
    if(menu_align == menu_align_right)
    {
        scroll_abs_min = 0;
        scroll_abs_max = \
            (SecNum - 1)*azkar_sec_ec_w;
    }else
    {
        scroll_abs_min = 0;
        scroll_abs_max = \
            (-1)*(SecNum - 1)*azkar_sec_ec_w;
    }

    int16_t throw_start;
    int16_t throw_end;
    throw_start = \
        azkar_sec_scroll_offset;
    if(LV_ABS(azkar_sec_throw.x) >= \
        10)
    {
        if(azkar_sec_throw.x < 0)   
            throw_end = \
                azkar_sec_scroll_offset - \
                    Azkar_Sec_Container_W;
        else
            throw_end = \
                azkar_sec_scroll_offset + \
                    Azkar_Sec_Container_W;
    }else
        return;

    if(menu_align == menu_align_right)
    {
        if(throw_end > scroll_abs_max || 
            throw_end < scroll_abs_min)
            return;
    }else
    {
        if(throw_end > scroll_abs_min || 
            throw_end < scroll_abs_max)
            return;
    }
    
    azkar_sec_scroll_dela = 0;

    uint32_t anim_duration = 300;

    lv_anim_t throw_anim;
    lv_obj_t *azkar_sec_container = \
        azkar_sec_ctx.azkar_sec_container;

    widget_anim_para.anim = \
        &throw_anim;
    widget_anim_para.anim_obj = \
        azkar_sec_container;
    widget_anim_para.anim_exec_xcb = \
        azkar_sec_throw_anim_cb; 
    widget_anim_para.anim_duration = \
        anim_duration;
    widget_anim_para.anim_start_val = \
        throw_start;
    widget_anim_para.anim_end_val = \
        throw_end;
    widget_anim_para.is_start_anim = false;
    common_widget_anim_create(&widget_anim_para);
    lv_anim_set_path_cb(widget_anim_para.anim, \
        lv_anim_path_ease_out);
    lv_anim_set_ready_cb(widget_anim_para.anim, \
        azkar_sec_throw_ready_cb);
    lv_anim_start(widget_anim_para.anim);

    return;
}

static void azkar_sec_all_obj_event_cb(lv_event_t *e)
{
    if(!e) return;

    lv_event_code_t event_code = \
        lv_event_get_code(e);

    if(event_code == LV_EVENT_PRESSED)
        azkar_sec_container_pressed_cb(e);
    else if(event_code == LV_EVENT_PRESSING)
        azkar_sec_container_pressing_cb(e);
    else if(event_code == LV_EVENT_RELEASED)
        azkar_sec_container_release_cb(e);

    return;
} 

static void azkar_sec_layout_create(\
    menu_align_t menu_align)
{
    azkar_sec_elem_container_create(\
        menu_align);

    azkar_sec_elem_ctx_label_create(\
        menu_align);

    azkar_sec_elem_tr_icon_create(\
        menu_align);

    return;
}

static void menu_create_cb(lv_obj_t *obj)
{
    if(!obj) return;
   
    ui_act_id_t prev_act_id = \
        ui_act_id_azkar_list;
    if(!lang_txt_is_arabic())
        tileview_register_all_menu(obj, ui_act_id_null, ui_act_id_null, \
            prev_act_id, ui_act_id_null, ui_act_id_azkar_section);
    else
        tileview_register_all_menu(obj, ui_act_id_null, ui_act_id_null, \
            ui_act_id_null, prev_act_id, ui_act_id_azkar_section);

    uint8_t azkar_sec_idx = \
        GetAzkarSecIdx();
    lv_obj_t *tileview_obj = \
        tileview_obj_container();
    if(azkar_sec_idx == 0)
        lv_obj_add_flag(tileview_obj, \
            LV_OBJ_FLAG_SCROLLABLE);
    else
        lv_obj_clear_flag(tileview_obj, \
            LV_OBJ_FLAG_SCROLLABLE);

    return;
}

static void menu_destory_cb(lv_obj_t *obj)
{
    return;
}

static void menu_refresh_cb(lv_obj_t *obj)
{
    if(!obj) return;

    if(azkar_sec_txt_load)
        return;

    lv_obj_t **azkar_sec_ctx_label = \
        azkar_sec_ctx.azkar_sec_ctx_label;

    uint8_t SecIdx = \
        GetAzkarSecIdx();
    uint8_t SecNum = \
        GetAzkarPrayerSecNum();
    for(uint8_t i = 0; i < SecNum; i++)
    {
        if(i == SecIdx)
            continue;

        lv_textarea_add_text(azkar_sec_ctx_label[i], \
            GetAzkarPrayerTxtContent(i));
    }
        
    azkar_sec_txt_load = true;

    return;
}

static void menu_display_cb(lv_obj_t *obj)
{
    if(!obj) return;

    menu_align_t menu_align = \
        menu_align_left;
    if(lang_txt_is_arabic())
        menu_align = \
            menu_align_right;

    azkar_sec_txt_load = \
        false;

    memset(&azkar_sec_ctx, 0, \
        sizeof(azkar_sec_ctx_t));

    azkar_sec_container_create(obj);

    azkar_sec_layout_create(menu_align);

    return;
}

static void menu_key_cb(lv_obj_t *obj, int key_value, \
    int key_event)
{
    if(!obj) return;

    return;
}

register_ui_menu_load_info(\
    menu_load_azkar_section) = 
{
    .menu_arg = NULL,
    .lock_flag = false,
    .return_flag = true,
    .menu_id = \
        ui_act_id_azkar_section,
    .user_offscreen_time = 0,
    .user_refresh_time_inv = 100,
    .key_func_cb = menu_key_cb,
    .create_func_cb = menu_create_cb,
    .destory_func_cb = menu_destory_cb,
    .refresh_func_cb = menu_refresh_cb,
    .display_func_cb = menu_display_cb,
};
