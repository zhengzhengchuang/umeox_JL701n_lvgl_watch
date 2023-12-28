#include "common_hr.h"
#include "../lv_watch.h"

/*********************************************************************************
                                  心率数据参数                                       
*********************************************************************************/
static uint8_t hr_group_num = 0;
static uint16_t hr_dsc_idx[Hr_Group_Max*Hr_Obj_Max] = {0xffff};
static comm_data_para_t comm_hr_para_cache[Hr_Group_Max] = {0};
static comm_data_para_t *p_comm_hr_para[Hr_Group_Max] = {NULL};
static lv_obj_t *common_widget_hr[Hr_Group_Max*Hr_Obj_Max] = {NULL};
static common_data_type_t hr_data_type[Hr_Group_Max] = {Comm_Data_Type___};


static int16_t common_hr_widget_sx(uint8_t idx, \
    uint8_t data_bit_num, uint16_t num_width, 
        uint16_t *hr_data_width)
{
    int16_t hr_data_sx = 0;

    if(!hr_data_width)
        return \
            (p_comm_hr_para[idx]->data_x);

    uint16_t width_sum = 0;
    for(uint8_t i = 0; i < data_bit_num; i++)
        width_sum += hr_data_width[i];

    common_data_align_t data_align = \
        p_comm_hr_para[idx]->data_align;

    if(data_align == Comm_Data_Align_Left)
        hr_data_sx = \
            p_comm_hr_para[idx]->data_x;
    else if(data_align == Comm_Data_Align_Right)
        hr_data_sx = \
            p_comm_hr_para[idx]->data_x + \
                ((Hr_Obj_Max*num_width) - \
                    width_sum);
    else if(data_align == Comm_Data_Align_Center)
        hr_data_sx = \
            p_comm_hr_para[idx]->data_x + \
                ((Hr_Obj_Max*num_width) - \
                    width_sum)/2;
    else
        hr_data_sx = \
            p_comm_hr_para[idx]->data_x;

    return hr_data_sx;
}

void common_hr_widget_init(void)
{
    if(!hr_group_num)
        return;

    hr_group_num = 0;

    memset(hr_dsc_idx, 0xffff, \
        sizeof(hr_dsc_idx));

    memset(common_widget_hr, 0, \
        sizeof(common_widget_hr));

    memset(hr_data_type, Comm_Data_Type___, \
        sizeof(hr_data_type));

    return;
}

void common_hr_refresh(void)
{
    if(!hr_group_num)
        return;

    for(uint8_t i = 0; i < hr_group_num; i++)
    {
        uint16_t vm_label_type = \
            vm_label_none;

        if(hr_data_type[i] == \
            Comm_Data_Type_Hr)
            vm_label_type = vm_label_hr;
        else if(hr_data_type[i] == \
            Comm_Data_Type_Min_Hr)
            vm_label_type = vm_label_min_hr;
        else if(hr_data_type[i] == \
            Comm_Data_Type_Max_Hr)
            vm_label_type = vm_label_max_hr;
        else
            continue;

        int16_t __data = \
            get_vm_para_cache_with_label(vm_label_type); 

        uint32_t num_addr_index = \
            p_comm_hr_para[i]->num_addr_index;

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

        char hr_num_str[Hr_Obj_Max + 1];
        memset(hr_num_str, 0, \
            sizeof(hr_num_str));

        if(!__data)
            memcpy(hr_num_str, (void *)"__", 2);
        else
            sprintf(hr_num_str, "%d", __data);

        uint8_t data_bit_num = \
            strlen((const char *)hr_num_str); 

        uint32_t hr_num_index[Hr_Obj_Max];
        uint16_t hr_data_width[Hr_Obj_Max] = {0};
        for(uint8_t j = 0; j < data_bit_num; j++)
        {
            if(hr_num_str[j] == '_')
            {
                hr_data_width[j] = \
                    symb_19_width;
                hr_num_index[j] = \
                    symb_19_addr_index;
            }else
            {
                hr_data_width[j] = \
                    num_width;
                hr_num_index[j] = \
                    num_addr_index + \
                        (hr_num_str[j] - '0');
            }
        }

        int16_t hr_data_sx = 0;
        hr_data_sx = common_hr_widget_sx(i, \
            data_bit_num, num_width, \
                hr_data_width);

        uint8_t obj_idx = \
            (Hr_Obj_Max - data_bit_num) + \
                Hr_Obj_Max*i;

        uint16_t width_sum = 0;
        int16_t refresh_x, refresh_y;
        for(uint8_t j = 0; j < data_bit_num; j++)
        {
            if(!common_widget_hr[j + obj_idx] || \
                hr_dsc_idx[j + obj_idx] == 0xffff)
                continue;

            if(j)
               width_sum += \
                hr_data_width[j - 1];

            refresh_x = hr_data_sx + width_sum + \
                p_comm_hr_para[i]->num_inv*j;
            refresh_y = p_comm_hr_para[i]->data_y;
            lv_obj_set_pos(common_widget_hr[j + obj_idx], \
                refresh_x, refresh_y);
            
            common_widget_img_replace_src(common_widget_hr[j + obj_idx], \
                hr_num_index[j], hr_dsc_idx[j + obj_idx]);
            lv_obj_clear_flag(common_widget_hr[j + obj_idx], \
                LV_OBJ_FLAG_HIDDEN);
        }

        width_sum = 0;

        obj_idx = Hr_Obj_Max*i;
        for(uint8_t j = 0; j < (Hr_Obj_Max - data_bit_num); j++)
           lv_obj_add_flag(common_widget_hr[j + obj_idx], \
                LV_OBJ_FLAG_HIDDEN); 
    }

    return;
}

void common_hr_widget_create(comm_data_para_t *data_para, \
    common_data_type_t type, void *data_val)
{
    if(hr_group_num >= \
        Hr_Group_Max)
        return;

    int __data = *(int *)data_val;

    hr_data_type[hr_group_num] = type;

    memcpy(&comm_hr_para_cache[hr_group_num], \
        data_para, sizeof(comm_data_para_t));

    p_comm_hr_para[hr_group_num] = \
        &comm_hr_para_cache[hr_group_num];

    uint32_t num_addr_index = \
        p_comm_hr_para[hr_group_num]->num_addr_index;

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

    char hr_num_str[Hr_Obj_Max + 1];
    memset(hr_num_str, 0, \
        sizeof(hr_num_str));

    if(!__data)
        memcpy(hr_num_str, (void *)"__", 2);
    else
        sprintf(hr_num_str, "%d", __data);

    uint8_t data_bit_num = \
        strlen((const char *)hr_num_str);

    uint32_t hr_num_index[Hr_Obj_Max];
    uint16_t hr_data_width[Hr_Obj_Max] = {0};
    for(uint8_t i = 0; i < data_bit_num; i++)
    {
        if(hr_num_str[i] == '_')
        {
            hr_data_width[i] = \
                symb_19_width;
            hr_num_index[i] = \
                symb_19_addr_index;
        }else
        {
            hr_data_width[i] = \
                num_width;
            hr_num_index[i] = \
                num_addr_index + \
                    (hr_num_str[i] - '0');
        }
    }

    int16_t hr_data_sx = 0;
    hr_data_sx = common_hr_widget_sx(hr_group_num, \
        data_bit_num, num_width, hr_data_width);

    uint8_t obj_idx = \
        (Hr_Obj_Max - data_bit_num) + \
            Hr_Obj_Max*hr_group_num;
    
    widget_img_para.event_cb = NULL;
    widget_img_para.user_data = NULL;
    widget_img_para.img_click_attr = false;
    widget_img_para.img_parent = \
        p_comm_hr_para[hr_group_num]->data_parent;

    uint16_t width_sum = 0;
    for(uint8_t i = 0; i < data_bit_num; i++)
    {
        if(i)
           width_sum += \
                hr_data_width[i - 1];

        widget_img_para.img_x = \
            hr_data_sx + width_sum + \
                p_comm_hr_para[hr_group_num]->num_inv*i;
        widget_img_para.img_y = \
            p_comm_hr_para[hr_group_num]->data_y;
        widget_img_para.file_img_dat = \
            hr_num_index[i];

        common_widget_hr[i + obj_idx] = \
            common_widget_img_create(&widget_img_para, \
                &hr_dsc_idx[i + obj_idx]);
        lv_obj_clear_flag(common_widget_hr[i + obj_idx], \
            LV_OBJ_FLAG_HIDDEN);
    }

    obj_idx = Hr_Obj_Max*hr_group_num;
    for(uint8_t i = 0; i < (Hr_Obj_Max - data_bit_num); i++)
    {
        widget_img_para.file_img_dat = \
            num_addr_index;
        common_widget_hr[i + obj_idx] = \
            common_widget_img_create(&widget_img_para, \
                &hr_dsc_idx[i + obj_idx]);
        lv_obj_add_flag(common_widget_hr[i + obj_idx], \
            LV_OBJ_FLAG_HIDDEN);
    }

    hr_group_num++;

    return;
}
