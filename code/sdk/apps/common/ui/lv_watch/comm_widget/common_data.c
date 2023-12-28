#include "common_hr.h"
#include "common_bo.h"
#include "common_data.h"
#include "../lv_watch.h"

/*********************************************************************************
                                  数据参数                                       
*********************************************************************************/
comm_data_para_t comm_data_para = {0};


void common_data_widget_init(void)
{
    common_hr_widget_init();
    common_bo_widget_init();

    return;
}

void common_data_refresh(void)
{
    common_hr_refresh();
    common_bo_refresh();
    
    return;
}

void common_data_widget_create(comm_data_para_t *data_para, \
    common_data_type_t type, void *data_val)
{
    if(!data_para)
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
    }

    return;
}
