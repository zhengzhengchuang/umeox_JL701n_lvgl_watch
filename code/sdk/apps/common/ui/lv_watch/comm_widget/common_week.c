#include "common_week.h"
#include "../lv_watch.h"

comm_week_para_t comm_week_para = {0};

/*********************************************************************************
                                  星期参数                                       
*********************************************************************************/
static uint8_t week_group_num = 0;
static comm_week_para_t *p_comm_week_para[Week_Group_Max] = {NULL};
static comm_week_para_t comm_week_para_cache[Week_Group_Max] = {0};
static uint16_t week_dsc_idx[Week_Group_Max*Week_Obj_Max] = {0xffff};
static lv_obj_t *common_widget_week[Week_Group_Max*Week_Obj_Max] = {NULL};


void common_week_widget_init(void)
{
    if(!week_group_num)
        return;

    week_group_num = 0;

    memset(week_dsc_idx, 0xffff, \
        sizeof(week_dsc_idx));

    memset(common_widget_week, 0, \
        sizeof(common_widget_week));

    return;
}


void common_week_refresh(void)
{
    if(!week_group_num)
        return;

    struct sys_time utc_time;
    ui_get_sys_time(&utc_time);

    comm_enum_week_t enum_week = \
        ui_get_sys_week(&utc_time);

    uint32_t week_addr_index[Week_Obj_Max];
    for(uint8_t i = 0; i < week_group_num; i++)
    {
        for(uint8_t j = 0; j < Week_Obj_Max; j++)
        {
            week_addr_index[j] = \
                p_comm_week_para[i]->week_addr_index + \
                    enum_week;

            if(!common_widget_week[j + i*Week_Obj_Max] || \
                week_dsc_idx[j + i*Week_Obj_Max] == 0xffff)
                continue;

            common_widget_img_replace_src(common_widget_week[j + i*Week_Obj_Max], \
                week_addr_index[j], week_dsc_idx[j + i*Week_Obj_Max]);
        }
    }

    return;
}

void common_week_widget_create(comm_week_para_t *week_para) 
{
    if(!week_para)
        return;

    if(week_group_num >= \
        Week_Group_Max)
        return;

    struct sys_time utc_time;
    ui_get_sys_time(&utc_time);

    comm_enum_week_t enum_week = \
        ui_get_sys_week(&utc_time);

    memcpy(&comm_week_para_cache[week_group_num], \
        week_para, sizeof(comm_week_para_t));

    p_comm_week_para[week_group_num] = \
        &comm_week_para_cache[week_group_num];

    uint32_t week_addr_index[Week_Obj_Max];
    for(uint8_t i = 0; i < Week_Obj_Max; i++)
        week_addr_index[i] = \
            p_comm_week_para[week_group_num]->week_addr_index + \
                enum_week;

    widget_img_para.event_cb = NULL;
    widget_img_para.user_data = NULL;
    widget_img_para.img_click_attr = false;
    widget_img_para.img_parent = \
        p_comm_week_para[week_group_num]->week_parent;

    uint8_t obj_num = Week_Obj_Max;
    uint8_t obj_idx = 0 + \
        week_group_num*Week_Obj_Max;
    

    for(uint8_t i = 0; i < obj_num; i++)
    {
        widget_img_para.img_x = \
            p_comm_week_para[week_group_num]->week_x;
        widget_img_para.img_y = \
            p_comm_week_para[week_group_num]->week_y;
        widget_img_para.file_img_dat = \
            week_addr_index[obj_idx%Week_Obj_Max + i];
        common_widget_week[obj_idx + i] = \
            common_widget_img_create(&widget_img_para, \
                &week_dsc_idx[obj_idx + i]);
    }

    week_group_num++;

    return;
}