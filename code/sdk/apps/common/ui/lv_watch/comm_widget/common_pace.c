#include "common_pace.h"
#include "../lv_watch.h"

/*********************************************************************************
                                  配速数据参数                                       
*********************************************************************************/
static uint8_t pace_group_num = 0;
static comm_data_para_t comm_pace_para_cache[Pace_Group_Max] = {0};
static comm_data_para_t *p_comm_pace_para[Pace_Group_Max] = {NULL};
static uint16_t pace_dsc_idx[Pace_Group_Max*Pace_Obj_Max] = {0xffff};
static lv_obj_t *common_widget_pace[Pace_Group_Max*Pace_Obj_Max] = {NULL};
static common_data_type_t pace_data_type[Pace_Group_Max] = {Comm_Data_Type___};


static int16_t common_pace_widget_sx(uint8_t idx, \
    uint8_t data_bit_num, uint16_t num_width, 
        uint16_t symb_20_width, uint16_t symb_21_width, \
            uint16_t *pace_data_width)
{
    int16_t pace_data_sx = 0;

    if(!pace_data_width)
        return \
            (p_comm_pace_para[idx]->data_x);

    uint16_t width_sum = 0;
    for(uint8_t i = 0; i < data_bit_num; i++)
        width_sum += pace_data_width[i];

    common_data_align_t data_align = \
        p_comm_pace_para[idx]->data_align;

    if(data_align == Comm_Data_Align_Left)
        pace_data_sx = \
            p_comm_pace_para[idx]->data_x;
    else if(data_align == Comm_Data_Align_Right)
        pace_data_sx = \
            p_comm_pace_para[idx]->data_x + \
                (((Pace_Obj_Max-2)*num_width) + symb_20_width + \
                    symb_21_width - width_sum);
    else if(data_align == Comm_Data_Align_Center)
        pace_data_sx = \
            p_comm_pace_para[idx]->data_x + \
                (((Pace_Obj_Max-2)*num_width) + symb_20_width + \
                    symb_21_width - width_sum)/2;
    else
        pace_data_sx = \
            p_comm_pace_para[idx]->data_x;

    return pace_data_sx;
}

void common_pace_widget_init(void)
{
    if(!pace_group_num)
        return;

    pace_group_num = 0;

    memset(pace_dsc_idx, 0xffff, \
        sizeof(pace_dsc_idx));

    memset(common_widget_pace, 0, \
        sizeof(common_widget_pace));

    memset(pace_data_type, Comm_Data_Type___, \
        sizeof(pace_data_type));

    return;
}

void common_pace_refresh(void)
{
    if(!pace_group_num)
        return;

    for(uint8_t i = 0; i < pace_group_num; i++)
    {
        uint16_t vm_label_type = \
            vm_label_none;

        if(pace_data_type[i] == \
            Comm_Data_Type_Pace)
            vm_label_type = vm_label_daily_pace;
        else
            continue;

        int __data = \
            get_vm_para_cache_with_label(\
                vm_label_type); 

        if(__data > Pace_Disp_Max)
            __data = Pace_Disp_Max;
  
        uint32_t num_addr_index = \
            p_comm_pace_para[i]->num_addr_index;

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

        uint32_t symb_20_addr_index = \
            num_addr_index + \
                Comm_Symbol_20;
        data_img_dsc = \
            common_widget_img_open_res(\
                symb_20_addr_index);
        uint16_t symb_20_width = \
            data_img_dsc->header.w;

        uint32_t symb_21_addr_index = \
            num_addr_index + \
                Comm_Symbol_21;
        data_img_dsc = \
            common_widget_img_open_res(\
                symb_21_addr_index);
        uint16_t symb_21_width = \
            data_img_dsc->header.w;

        char pace_num_str[Pace_Obj_Max + 1];
        memset(pace_num_str, 0, \
            sizeof(pace_num_str));

        if(!__data)
            memcpy(pace_num_str, (void *)"__", 2);
        else
            sprintf(pace_num_str, "%d,%d;", \
                __data/60, __data%60);
        
        uint8_t data_bit_num = \
            strlen((const char *)pace_num_str);

        uint32_t pace_num_index[Pace_Obj_Max];
        uint16_t pace_data_width[Pace_Obj_Max];
        for(uint8_t j = 0; j < data_bit_num; j++)
        {
            if(pace_num_str[j] == '_')
            {
                pace_data_width[j] = \
                    symb_19_width;
                pace_num_index[j] = \
                    symb_19_addr_index;
            }else if(pace_num_str[j] == ',')
            {
                pace_data_width[j] = \
                    symb_20_width;
                pace_num_index[j] = \
                    symb_20_addr_index;
            }else if(pace_num_str[j] == ';')
            {
                pace_data_width[j] = \
                    symb_21_width;
                pace_num_index[j] = \
                    symb_21_addr_index;
            }else
            {
                pace_data_width[j] = \
                    num_width;
                pace_num_index[j] = \
                    num_addr_index + \
                        (pace_num_str[j] - '0');
            }
        }

        int16_t pace_data_sx = 0;
        pace_data_sx = common_pace_widget_sx(i, \
            data_bit_num, num_width, symb_20_width, \
                symb_21_width, pace_data_width);

        uint8_t obj_idx = \
            (Pace_Obj_Max - data_bit_num) + \
                Pace_Obj_Max*i;

        uint16_t width_sum = 0;
        int16_t refresh_x, refresh_y;
        for(uint8_t j = 0; j < data_bit_num; j++)
        {
            if(j)
                width_sum += \
                    pace_data_width[j - 1];

            if(!common_widget_pace[j + obj_idx] || \
                pace_dsc_idx[j + obj_idx] == 0xffff)
                    continue;

            refresh_x = pace_data_sx + width_sum + \
                p_comm_pace_para[i]->num_inv*j;
            refresh_y = p_comm_pace_para[i]->data_y;
            lv_obj_set_pos(common_widget_pace[j + obj_idx], \
                refresh_x, refresh_y);
            
            common_widget_img_replace_src(common_widget_pace[j + obj_idx], \
                pace_num_index[j], pace_dsc_idx[j + obj_idx]);
            lv_obj_clear_flag(common_widget_pace[j + obj_idx], \
                LV_OBJ_FLAG_HIDDEN);
        }

        width_sum = 0;

        obj_idx = Pace_Obj_Max*i;
        for(uint8_t j = 0; j < (Pace_Obj_Max - data_bit_num); j++)
           lv_obj_add_flag(common_widget_pace[j + obj_idx], \
                LV_OBJ_FLAG_HIDDEN);
    }

    return;
}

void common_pace_widget_create(comm_data_para_t *data_para, \
    common_data_type_t type, void *data_val)
{
    if(pace_group_num >= \
        Pace_Group_Max)
        return;

    int __data = *(int *)data_val;

    if(__data > Pace_Disp_Max)
        __data = Pace_Disp_Max;

    pace_data_type[pace_group_num] = type;

    memcpy(&comm_pace_para_cache[pace_group_num], \
        data_para, sizeof(comm_data_para_t));

    p_comm_pace_para[pace_group_num] = \
        &comm_pace_para_cache[pace_group_num];

    uint32_t num_addr_index = \
        p_comm_pace_para[pace_group_num]->num_addr_index;

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

    uint32_t symb_20_addr_index = \
        num_addr_index + \
            Comm_Symbol_20;
    data_img_dsc = \
        common_widget_img_open_res(\
            symb_20_addr_index);
    uint16_t symb_20_width = \
        data_img_dsc->header.w;

    uint32_t symb_21_addr_index = \
        num_addr_index + \
            Comm_Symbol_21;
    data_img_dsc = \
        common_widget_img_open_res(\
            symb_21_addr_index);
    uint16_t symb_21_width = \
        data_img_dsc->header.w;

    char pace_num_str[Pace_Obj_Max + 1];
    memset(pace_num_str, 0, \
        sizeof(pace_num_str));

    if(!__data)
        memcpy(pace_num_str, (void *)"__", 2);
    else
        sprintf(pace_num_str, "%d,%d;", \
            __data/60, __data%60);

    uint8_t data_bit_num = \
        strlen((const char *)pace_num_str);

    uint32_t pace_num_index[Pace_Obj_Max];
    uint16_t pace_data_width[Pace_Obj_Max];
    for(uint8_t i = 0; i < data_bit_num; i++)
    {   
        if(pace_num_str[i] == '_')
        {
            pace_data_width[i] = \
                symb_19_width;
            pace_num_index[i] = \
                symb_19_addr_index;
        }else if(pace_num_str[i] == ',')
        {
            pace_data_width[i] = \
                symb_20_width;
            pace_num_index[i] = \
                symb_20_addr_index;
        }else if(pace_num_str[i] == ';')
        {
            pace_data_width[i] = \
                symb_21_width;
            pace_num_index[i] = \
                symb_21_addr_index;
        }else
        {
            pace_data_width[i] = \
                num_width;
            pace_num_index[i] = \
                num_addr_index + \
                    (pace_num_str[i] - '0');
        }
    }

    int16_t pace_data_sx = 0;
    pace_data_sx = common_pace_widget_sx(pace_group_num, \
        data_bit_num, num_width, symb_20_width, \
            symb_21_width, pace_data_width);

    uint8_t obj_idx = \
        (Pace_Obj_Max - data_bit_num) + \
            Pace_Obj_Max*pace_group_num;
    
    widget_img_para.event_cb = NULL;
    widget_img_para.user_data = NULL;
    widget_img_para.img_click_attr = false;
    widget_img_para.img_parent = \
        p_comm_pace_para[pace_group_num]->data_parent;

    uint16_t width_sum = 0;
    for(uint8_t i = 0; i < data_bit_num; i++)
    {
        if(i)
           width_sum += \
                pace_data_width[i - 1];

        widget_img_para.img_x = \
            pace_data_sx + width_sum + \
                p_comm_pace_para[pace_group_num]->num_inv*i;
        widget_img_para.img_y = \
            p_comm_pace_para[pace_group_num]->data_y;
        widget_img_para.file_img_dat = \
            pace_num_index[i];

        common_widget_pace[i + obj_idx] = \
            common_widget_img_create(&widget_img_para, \
                &pace_dsc_idx[i + obj_idx]);
        lv_obj_clear_flag(common_widget_pace[i + obj_idx], \
            LV_OBJ_FLAG_HIDDEN);
    }

    obj_idx = Pace_Obj_Max*pace_group_num;
    for(uint8_t i = 0; i < (Pace_Obj_Max - data_bit_num); i++)
    {
        widget_img_para.file_img_dat = \
            num_addr_index;
        common_widget_pace[i + obj_idx] = \
            common_widget_img_create(&widget_img_para, \
                &pace_dsc_idx[i + obj_idx]);
        lv_obj_add_flag(common_widget_pace[i + obj_idx], \
            LV_OBJ_FLAG_HIDDEN);
    }

    pace_group_num++;

    return;
}
