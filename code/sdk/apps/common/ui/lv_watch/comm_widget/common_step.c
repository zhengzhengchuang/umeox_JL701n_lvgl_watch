#include "common_step.h"
#include "../lv_watch.h"


/*********************************************************************************
                                  步数数据参数                                       
*********************************************************************************/
static uint8_t step_group_num = 0;
static comm_data_para_t comm_step_para_cache[Step_Group_Max] = {0};
static comm_data_para_t *p_comm_step_para[Step_Group_Max] = {NULL};
static uint16_t step_dsc_idx[Step_Group_Max*Step_Obj_Max] = {0xffff};
static lv_obj_t *common_widget_step[Step_Group_Max*Step_Obj_Max] = {NULL};
static common_data_type_t step_data_type[Step_Group_Max] = {Comm_Data_Type___};


static int16_t common_step_widget_sx(uint8_t idx, \
    uint8_t data_bit_num, uint16_t num_width, 
        uint16_t *step_data_width)
{
    int16_t step_data_sx = 0;

    if(!step_data_width)
        return \
            (p_comm_step_para[idx]->data_x);

    uint16_t width_sum = 0;
    for(uint8_t i = 0; i < data_bit_num; i++)
        width_sum += step_data_width[i];

    common_data_align_t data_align = \
        p_comm_step_para[idx]->data_align;

    if(data_align == Comm_Data_Align_Left)
        step_data_sx = \
            p_comm_step_para[idx]->data_x;
    else if(data_align == Comm_Data_Align_Right)
        step_data_sx = \
            p_comm_step_para[idx]->data_x + \
                ((Step_Obj_Max*num_width) - \
                    width_sum);
    else if(data_align == Comm_Data_Align_Center)
        step_data_sx = \
            p_comm_step_para[idx]->data_x + \
                ((Step_Obj_Max*num_width) - \
                    width_sum)/2;
    else
        step_data_sx = \
            p_comm_step_para[idx]->data_x;

    return step_data_sx;
}

void common_step_widget_init(void)
{
    if(!step_group_num)
        return;

    step_group_num = 0;

    memset(step_dsc_idx, 0xffff, \
        sizeof(step_dsc_idx));

    memset(common_widget_step, 0, \
        sizeof(common_widget_step));

    memset(step_data_type, Comm_Data_Type___, \
        sizeof(step_data_type));

    return;
}

void common_step_refresh(void)
{
    if(!step_group_num)
        return;

    for(uint8_t i = 0; i < step_group_num; i++)
    {
        uint16_t vm_label_type = \
            vm_label_none;

        if(step_data_type[i] == \
            Comm_Data_Type_Step)
            vm_label_type = vm_label_daily_step;
        else
            continue;

        int __data = \
            get_vm_para_cache_with_label(\
                vm_label_type); 

        if(__data > Step_Disp_Max)
            __data = Step_Disp_Max;

        uint32_t num_addr_index = \
            p_comm_step_para[i]->num_addr_index;

        lv_img_dsc_t *data_img_dsc = \
            common_widget_img_open_res(\
                num_addr_index);
        uint16_t num_width = \
            data_img_dsc->header.w;

        uint32_t symb_19_addr_index = \
            num_addr_index + \
                Comm_Symbol_19;
        data_img_dsc = \
            common_widget_img_open_res(\
                symb_19_addr_index);
        uint16_t symb_19_width = \
            data_img_dsc->header.w;

        char step_num_str[Step_Obj_Max + 1];
        memset(step_num_str, 0, \
            sizeof(step_num_str));

        if(!__data)
            memcpy(step_num_str, (void *)"__", 2);
        else
            sprintf(step_num_str, "%d", __data);

        uint8_t data_bit_num = \
            strlen((const char *)step_num_str);

        uint32_t step_num_index[Step_Obj_Max];
        uint16_t step_data_width[Step_Obj_Max];
        for(uint8_t j = 0; j < data_bit_num; j++)
        {
            if(step_num_str[j] == '_')
            {
                step_data_width[j] = \
                    symb_19_width;
                step_num_index[j] = \
                    symb_19_addr_index;
            }else
            {
                step_data_width[j] = \
                    num_width;
                step_num_index[j] = \
                    num_addr_index + \
                        (step_num_str[j] - '0');
            }
        }

        int16_t step_data_sx = 0;
        step_data_sx = common_step_widget_sx(i, \
            data_bit_num, num_width, \
                step_data_width);

        uint8_t obj_idx = \
        (Step_Obj_Max - data_bit_num) + \
            Step_Obj_Max*i;

        uint16_t width_sum = 0;
        int16_t refresh_x, refresh_y;
        for(uint8_t j = 0; j < data_bit_num; j++)
        {
            if(j)
               width_sum += \
                step_data_width[j - 1];

            if(!common_widget_step[j + obj_idx] || \
                step_dsc_idx[j + obj_idx] == 0xffff)
                continue;

            refresh_x = step_data_sx + width_sum + \
                p_comm_step_para[i]->num_inv*j;
            refresh_y = p_comm_step_para[i]->data_y;
            lv_obj_set_pos(common_widget_step[j + obj_idx], \
                refresh_x, refresh_y);
            
            common_widget_img_replace_src(common_widget_step[j + obj_idx], \
                step_num_index[j], step_dsc_idx[j + obj_idx]);
            lv_obj_clear_flag(common_widget_step[j + obj_idx], \
                LV_OBJ_FLAG_HIDDEN);
        }

        width_sum = 0;

        obj_idx = Step_Obj_Max*i;
        for(uint8_t j = 0; j < (Step_Obj_Max - data_bit_num); j++)
           lv_obj_add_flag(common_widget_step[j + obj_idx], \
                LV_OBJ_FLAG_HIDDEN); 
    }

    return;
}

void common_step_widget_create(comm_data_para_t *data_para, \
    common_data_type_t type, void *data_val)
{
    if(step_group_num >= \
        Step_Group_Max)
        return;

    int __data = *(int *)data_val;

    if(__data > Step_Disp_Max)
        __data = Step_Disp_Max;

    step_data_type[step_group_num] = type;

    memcpy(&comm_step_para_cache[step_group_num], \
        data_para, sizeof(comm_data_para_t));

    p_comm_step_para[step_group_num] = \
        &comm_step_para_cache[step_group_num];

    uint32_t num_addr_index = \
        p_comm_step_para[step_group_num]->num_addr_index;

    lv_img_dsc_t *data_img_dsc = \
        common_widget_img_open_res(\
            num_addr_index);
    uint16_t num_width = \
        data_img_dsc->header.w;

    uint32_t symb_19_addr_index = \
        num_addr_index + \
            Comm_Symbol_19;
    data_img_dsc = \
        common_widget_img_open_res(\
            symb_19_addr_index);
    uint16_t symb_19_width = \
        data_img_dsc->header.w;

    char step_num_str[Step_Obj_Max + 1];
    memset(step_num_str, 0, \
        sizeof(step_num_str));

    if(!__data)
        memcpy(step_num_str, (void *)"__", 2);
    else
        sprintf(step_num_str, "%d", __data);

    uint8_t data_bit_num = \
        strlen((const char *)step_num_str);

    uint32_t step_num_index[Step_Obj_Max];
    uint16_t step_data_width[Step_Obj_Max];
    for(uint8_t i = 0; i < data_bit_num; i++)
    {
        if(step_num_str[i] == '_')
        {
            step_data_width[i] = \
                symb_19_width;
            step_num_index[i] = \
                symb_19_addr_index;
        }else
        {
            step_data_width[i] = \
                num_width;
            step_num_index[i] = \
                num_addr_index + \
                    (step_num_str[i] - '0');
        }
    }

    int16_t step_data_sx = 0;
    step_data_sx = common_step_widget_sx(step_group_num, \
        data_bit_num, num_width, step_data_width);

    uint8_t obj_idx = \
        (Step_Obj_Max - data_bit_num) + \
            Step_Obj_Max*step_group_num;
    
    widget_img_para.event_cb = NULL;
    widget_img_para.user_data = NULL;
    widget_img_para.img_click_attr = false;
    widget_img_para.img_parent = \
        p_comm_step_para[step_group_num]->data_parent;

    uint16_t width_sum = 0;
    for(uint8_t i = 0; i < data_bit_num; i++)
    {
        if(i)
           width_sum += \
                step_data_width[i - 1];

        widget_img_para.img_x = \
            step_data_sx + width_sum + \
                p_comm_step_para[step_group_num]->num_inv*i;
        widget_img_para.img_y = \
            p_comm_step_para[step_group_num]->data_y;
        widget_img_para.file_img_dat = \
            step_num_index[i];

        common_widget_step[i + obj_idx] = \
            common_widget_img_create(&widget_img_para, \
                &step_dsc_idx[i + obj_idx]);
        lv_obj_clear_flag(common_widget_step[i + obj_idx], \
            LV_OBJ_FLAG_HIDDEN);
    }

    obj_idx = Step_Obj_Max*step_group_num;
    for(uint8_t i = 0; i < (Step_Obj_Max - data_bit_num); i++)
    {
        widget_img_para.file_img_dat = \
            num_addr_index;
        common_widget_step[i + obj_idx] = \
            common_widget_img_create(&widget_img_para, \
                &step_dsc_idx[i + obj_idx]);
        lv_obj_add_flag(common_widget_step[i + obj_idx], \
            LV_OBJ_FLAG_HIDDEN);
    }

    step_group_num++;

    return;
}
