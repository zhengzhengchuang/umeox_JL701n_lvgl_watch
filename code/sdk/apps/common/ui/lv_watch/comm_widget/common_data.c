#include "common_hr.h"
#include "common_bo.h"
#include "common_step.h"
#include "common_pace.h"
#include "common_data.h"
#include "../lv_watch.h"
#include "common_calorie.h"
#include "common_distance.h"

/*********************************************************************************
                                  数据参数                                       
*********************************************************************************/
comm_data_para_t comm_data_para = {0};


void common_data_widget_init(void)
{
    common_hr_widget_init();
    common_bo_widget_init();
    common_step_widget_init();
    common_pace_widget_init();
    common_calorie_widget_init();
    common_distance_widget_init();
    
    return;
}

void common_data_refresh(void)
{
    common_hr_refresh();
    common_bo_refresh();
    common_step_refresh();
    common_pace_refresh();
    common_calorie_refresh();
    common_distance_refresh();
    
    return;
}

void common_data_widget_create(comm_data_para_t *data_para, \
    common_data_type_t type, void *data_val)
{
    if(!data_para || !data_val)
        return;

    if(type == Comm_Data_Type_Hr || \
        type == Comm_Data_Type_Min_Hr || \
            type == Comm_Data_Type_Max_Hr)
    {
        common_hr_widget_create(data_para, \
            type, data_val);
    }else if(type == Comm_Data_Type_Bo || \
        type == Comm_Data_Type_Min_Bo || \
            type == Comm_Data_Type_Max_Bo)
    {
        common_bo_widget_create(data_para, \
            type, data_val);
    }else if(type == Comm_Data_Type_Step)
    {
        common_step_widget_create(data_para, \
            type, data_val);
    }else if(type == Comm_Data_Type_Calorie)
    {
        common_calorie_widget_create(data_para, \
            type, data_val);
    }else if(type == Comm_Data_Type_Pace)
    {
        common_pace_widget_create(data_para, \
            type, data_val);
    }else if(type == Comm_Data_Type_Distance)
    {
        common_distance_widget_create(data_para, \
            type, data_val);
    }

    return;
}
