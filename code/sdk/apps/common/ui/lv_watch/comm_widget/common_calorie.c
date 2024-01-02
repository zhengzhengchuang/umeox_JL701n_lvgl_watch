#include "../lv_watch.h"
#include "common_calorie.h"

/*********************************************************************************
                                  卡路里数据参数                                       
*********************************************************************************/
static uint8_t calorie_group_num = 0;
static comm_data_para_t comm_calorie_para_cache[Calorie_Group_Max] = {0};
static comm_data_para_t *p_comm_calorie_para[Calorie_Group_Max] = {NULL};
static uint16_t calorie_dsc_idx[Calorie_Group_Max*Calorie_Obj_Max] = {0xffff};
static lv_obj_t *common_widget_calorie[Calorie_Group_Max*Calorie_Obj_Max] = {NULL};
static common_data_type_t calorie_data_type[Calorie_Group_Max] = {Comm_Data_Type___};


static int16_t common_calorie_widget_sx(uint8_t idx, \
    uint8_t data_bit_num, uint16_t num_width, 
        uint16_t *calorie_data_width)
{
    int16_t calorie_data_sx = 0;

    if(!calorie_data_width)
        return \
            (p_comm_calorie_para[idx]->data_x);

    uint16_t width_sum = 0;
    for(uint8_t i = 0; i < data_bit_num; i++)
        width_sum += calorie_data_width[i];

    common_data_align_t data_align = \
        p_comm_calorie_para[idx]->data_align;

    if(data_align == Comm_Data_Align_Left)
        calorie_data_sx = \
            p_comm_calorie_para[idx]->data_x;
    else if(data_align == Comm_Data_Align_Right)
        calorie_data_sx = \
            p_comm_calorie_para[idx]->data_x + \
                ((Calorie_Obj_Max*num_width) - \
                    width_sum);
    else if(data_align == Comm_Data_Align_Center)
        calorie_data_sx = \
            p_comm_calorie_para[idx]->data_x + \
                ((Calorie_Obj_Max*num_width) - \
                    width_sum)/2;
    else
        calorie_data_sx = \
            p_comm_calorie_para[idx]->data_x;

    return calorie_data_sx;
}

void common_calorie_widget_init(void)
{
    if(!calorie_group_num)
        return;

    calorie_group_num = 0;

    memset(calorie_dsc_idx, 0xffff, \
        sizeof(calorie_dsc_idx));

    memset(common_widget_calorie, 0, \
        sizeof(common_widget_calorie));

    memset(calorie_data_type, Comm_Data_Type___, \
        sizeof(calorie_data_type));

    return;
}

void common_calorie_refresh(void)
{
    if(!calorie_group_num)
        return;

    for(uint8_t i = 0; i < calorie_group_num; i++)
    {
        uint16_t vm_label_type = \
            vm_label_none;

        if(calorie_data_type[i] == \
            Comm_Data_Type_Calorie)
            vm_label_type = vm_label_daily_calorie;
        else
            continue;

        int __data = \
            get_vm_para_cache_with_label(\
                vm_label_type); 

        if(__data > Calorie_Disp_Max)
            __data = Calorie_Disp_Max;

        uint32_t num_addr_index = \
            p_comm_calorie_para[i]->num_addr_index;

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

        char calorie_num_str[Calorie_Obj_Max + 1];
        memset(calorie_num_str, 0, \
            sizeof(calorie_num_str));

        if(!__data)
            memcpy(calorie_num_str, (void *)"__", 2);
        else
            sprintf(calorie_num_str, "%d", __data);

        uint8_t data_bit_num = \
            strlen((const char *)calorie_num_str);

        uint32_t calorie_num_index[Calorie_Obj_Max];
        uint16_t calorie_data_width[Calorie_Obj_Max];
        for(uint8_t j = 0; j < data_bit_num; j++)
        {
            if(calorie_num_str[j] == '_')
            {
                calorie_data_width[j] = \
                    symb_19_width;
                calorie_num_index[j] = \
                    symb_19_addr_index;
            }else
            {
                calorie_data_width[j] = \
                    num_width;
                calorie_num_index[j] = \
                    num_addr_index + \
                        (calorie_num_str[j] - '0');
            }
        }

        int16_t calorie_data_sx = 0;
        calorie_data_sx = common_calorie_widget_sx(i, \
            data_bit_num, num_width, \
                calorie_data_width);

        uint8_t obj_idx = \
        (Calorie_Obj_Max - data_bit_num) + \
            Calorie_Obj_Max*i;

        uint16_t width_sum = 0;
        int16_t refresh_x, refresh_y;
        for(uint8_t j = 0; j < data_bit_num; j++)
        {
            if(j)
               width_sum += \
                calorie_data_width[j - 1];

            if(!common_widget_calorie[j + obj_idx] || \
                calorie_dsc_idx[j + obj_idx] == 0xffff)
                continue;

            refresh_x = calorie_data_sx + width_sum + \
                p_comm_calorie_para[i]->num_inv*j;
            refresh_y = p_comm_calorie_para[i]->data_y;
            lv_obj_set_pos(common_widget_calorie[j + obj_idx], \
                refresh_x, refresh_y);
            
            common_widget_img_replace_src(common_widget_calorie[j + obj_idx], \
                calorie_num_index[j], calorie_dsc_idx[j + obj_idx]);
            lv_obj_clear_flag(common_widget_calorie[j + obj_idx], \
                LV_OBJ_FLAG_HIDDEN);
        }

        width_sum = 0;

        obj_idx = Calorie_Obj_Max*i;
        for(uint8_t j = 0; j < (Calorie_Obj_Max - data_bit_num); j++)
           lv_obj_add_flag(common_widget_calorie[j + obj_idx], \
                LV_OBJ_FLAG_HIDDEN); 
    }

    return;
}

void common_calorie_widget_create(comm_data_para_t *data_para, \
    common_data_type_t type, void *data_val)
{
    if(calorie_group_num >= \
        Calorie_Group_Max)
        return;

    int __data = *(int *)data_val;

    if(__data > Calorie_Disp_Max)
        __data = Calorie_Disp_Max;

    calorie_data_type[calorie_group_num] = type;

    memcpy(&comm_calorie_para_cache[calorie_group_num], \
        data_para, sizeof(comm_data_para_t));

    p_comm_calorie_para[calorie_group_num] = \
        &comm_calorie_para_cache[calorie_group_num];

    uint32_t num_addr_index = \
        p_comm_calorie_para[calorie_group_num]->num_addr_index;

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

    char calorie_num_str[Calorie_Obj_Max + 1];
    memset(calorie_num_str, 0, \
        sizeof(calorie_num_str));

    if(!__data)
        memcpy(calorie_num_str, (void *)"__", 2);
    else
        sprintf(calorie_num_str, "%d", __data);

    uint8_t data_bit_num = \
        strlen((const char *)calorie_num_str);

    uint32_t calorie_num_index[Calorie_Obj_Max];
    uint16_t calorie_data_width[Calorie_Obj_Max];
    for(uint8_t i = 0; i < data_bit_num; i++)
    {
        if(calorie_num_str[i] == '_')
        {
            calorie_data_width[i] = \
                symb_19_width;
            calorie_num_index[i] = \
                symb_19_addr_index;
        }else
        {
            calorie_data_width[i] = \
                num_width;
            calorie_num_index[i] = \
                num_addr_index + \
                    (calorie_num_str[i] - '0');
        }
    }

    int16_t calorie_data_sx = 0;
    calorie_data_sx = common_calorie_widget_sx(calorie_group_num, \
        data_bit_num, num_width, calorie_data_width);

    uint8_t obj_idx = \
        (Calorie_Obj_Max - data_bit_num) + \
            Calorie_Obj_Max*calorie_group_num;
    
    widget_img_para.event_cb = NULL;
    widget_img_para.user_data = NULL;
    widget_img_para.img_click_attr = false;
    widget_img_para.img_parent = \
        p_comm_calorie_para[calorie_group_num]->data_parent;

    uint16_t width_sum = 0;
    for(uint8_t i = 0; i < data_bit_num; i++)
    {
        if(i)
           width_sum += \
                calorie_data_width[i - 1];

        widget_img_para.img_x = \
            calorie_data_sx + width_sum + \
                p_comm_calorie_para[calorie_group_num]->num_inv*i;
        widget_img_para.img_y = \
            p_comm_calorie_para[calorie_group_num]->data_y;
        widget_img_para.file_img_dat = \
            calorie_num_index[i];

        common_widget_calorie[i + obj_idx] = \
            common_widget_img_create(&widget_img_para, \
                &calorie_dsc_idx[i + obj_idx]);
        lv_obj_clear_flag(common_widget_calorie[i + obj_idx], \
            LV_OBJ_FLAG_HIDDEN);
    }

    obj_idx = Calorie_Obj_Max*calorie_group_num;
    for(uint8_t i = 0; i < (Calorie_Obj_Max - data_bit_num); i++)
    {
        widget_img_para.file_img_dat = \
            num_addr_index;
        common_widget_calorie[i + obj_idx] = \
            common_widget_img_create(&widget_img_para, \
                &calorie_dsc_idx[i + obj_idx]);
        lv_obj_add_flag(common_widget_calorie[i + obj_idx], \
            LV_OBJ_FLAG_HIDDEN);
    }

    calorie_group_num++;

    return;
}