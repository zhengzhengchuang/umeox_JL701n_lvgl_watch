#include "common_clock.h"

static uint8_t clk_p_num = 0;
static lv_obj_t *clk_p_obj[3] = {NULL};
static uint32_t clk_p_timer_id = 0xffffffff;
static struct sys_time clk_p_utc_time = {0};
static common_clock_pointer_para_t *clk_p_para = NULL;

void common_clock_pointer_para_init(void)
{
    clk_p_num = 0;

    clk_p_para = NULL; 

    for(uint8_t i = 0; i < 3; i++)
       clk_p_obj[i] = NULL;

    if(clk_p_timer_id != 0xffffffff)
        sys_timer_del(clk_p_timer_id);

    clk_p_timer_id = 0xffffffff;

    return;
}

void common_clock_pointer_refresh(int *refr_msg)
{
    if(!refr_msg) return;

    ui_get_sys_time(&clk_p_utc_time);

    uint8_t utc_time_hour = clk_p_utc_time.hour;
    uint8_t utc_time_minute = clk_p_utc_time.min;
    uint8_t utc_time_second = clk_p_utc_time.sec;

    int16_t clock_hour_angle = (utc_time_hour%12)*300 + (utc_time_minute%60)*5;
    int16_t clock_minute_angle = (utc_time_minute%60)*60 + utc_time_second%60;
    int16_t clock_second_angle = (utc_time_second%60)*60;

    for(uint8_t i = 0; i < clk_p_num; i++)
    {
        if(!clk_p_obj[i]) continue;

        if(clk_p_para[i].clk_p_type == Clk_Pointer_Type_Hour)
            lv_img_set_angle(clk_p_obj[i], clock_hour_angle);
        else if(clk_p_para[i].clk_p_type == Clk_Pointer_Type_Minute)
            lv_img_set_angle(clk_p_obj[i], clock_minute_angle);
        else if(clk_p_para[i].clk_p_type == Clk_Pointer_Type_Second)
            lv_img_set_angle(clk_p_obj[i], clock_second_angle);
    }

    return;
}

static void common_clock_pointer_timer_cb(void *priv)
{
    int clk_p_refr_img[1];
    clk_p_refr_img[0] = Ui_Msg_Clock_Pointer_refresh;\
    post_ui_msg(clk_p_refr_img, 1);

    return;
}

void common_clock_pointer_create(lv_obj_t *obj, const common_clock_pointer_para_t *para, uint8_t num)
{
    if(!obj || !para || !num) 
        return;

    clk_p_num = num;
    clk_p_para = para;
    clk_p_timer_id = 0xffffffff; 
    for(uint8_t i = 0; i < 3; i++)
       clk_p_obj[i] = NULL;

    ui_get_sys_time(&clk_p_utc_time);

    uint8_t utc_time_hour = clk_p_utc_time.hour;
    uint8_t utc_time_minute = clk_p_utc_time.min;
    uint8_t utc_time_second = clk_p_utc_time.sec;

    int16_t clock_hour_angle = (utc_time_hour%12)*300 + (utc_time_minute%60)*5;
    int16_t clock_minute_angle = (utc_time_minute%60)*60 + utc_time_second%60;
    int16_t clock_second_angle = (utc_time_second%60)*60;

    widget_img_para.img_x = 0;
    widget_img_para.img_y = 0;
    widget_img_para.img_parent = obj;

    for(uint8_t i = 0; i < clk_p_num; i++)
    {
        widget_img_para.file_img_dat = clk_p_para[i].clk_p_file_dat;
        clk_p_obj[i] = common_widget_img_create(&widget_img_para, NULL);
        lv_obj_align(clk_p_obj[i], LV_ALIGN_CENTER, 0, -clk_p_para[i].clk_p_height/2);
        lv_img_set_pivot(clk_p_obj[i], clk_p_para[i].clk_p_width/2, clk_p_para[i].clk_p_center);
        if(clk_p_para[i].clk_p_type == Clk_Pointer_Type_Hour)
            lv_img_set_angle(clk_p_obj[i], clock_hour_angle);
        else if(clk_p_para[i].clk_p_type == Clk_Pointer_Type_Minute)
            lv_img_set_angle(clk_p_obj[i], clock_minute_angle);
        else if(clk_p_para[i].clk_p_type == Clk_Pointer_Type_Second)
            lv_img_set_angle(clk_p_obj[i], clock_second_angle);
    }

    if(clk_p_timer_id == 0xffffffff)
        clk_p_timer_id = (uint32_t)sys_timer_add(NULL, common_clock_pointer_timer_cb, 100);

    return;
}
