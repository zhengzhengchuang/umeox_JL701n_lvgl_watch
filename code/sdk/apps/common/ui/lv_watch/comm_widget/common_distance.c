#include "../lv_watch.h"
#include "common_distance.h"

/*********************************************************************************
                                  距离数据参数                                       
*********************************************************************************/
static uint8_t distance_group_num = 0;
static comm_data_para_t comm_distance_para_cache[Distance_Group_Max] = {0};
static comm_data_para_t *p_comm_distance_para[Distance_Group_Max] = {NULL};
static uint16_t distance_dsc_idx[Distance_Group_Max*Distance_Obj_Max] = {0xffff};
static lv_obj_t *common_widget_distance[Distance_Group_Max*Distance_Obj_Max] = {NULL};
static common_data_type_t distance_data_type[Distance_Group_Max] = {Comm_Data_Type___};


static int16_t common_distance_widget_sx(uint8_t idx, \
    uint8_t data_bit_num, uint16_t num_width, 
        uint16_t symb_14_width, uint16_t *distance_data_width)
{
    int16_t distance_data_sx = 0;

    if(!distance_data_width)
        return \
            (p_comm_distance_para[idx]->data_x);

    uint16_t width_sum = 0;
    for(uint8_t i = 0; i < data_bit_num; i++)
        width_sum += distance_data_width[i];

    common_data_align_t data_align = \
        p_comm_distance_para[idx]->data_align;

    if(data_align == Comm_Data_Align_Left)
        distance_data_sx = \
            p_comm_distance_para[idx]->data_x;
    else if(data_align == Comm_Data_Align_Right)
        distance_data_sx = \
            p_comm_distance_para[idx]->data_x + \
                (((Distance_Obj_Max-1)*num_width) + \
                    symb_14_width - width_sum);
    else if(data_align == Comm_Data_Align_Center)
        distance_data_sx = \
            p_comm_distance_para[idx]->data_x + \
                (((Distance_Obj_Max-1)*num_width) + \
                    symb_14_width - width_sum)/2;
    else
        distance_data_sx = \
            p_comm_distance_para[idx]->data_x;

    return distance_data_sx;
}

void common_distance_widget_init(void)
{
    if(!distance_group_num)
        return;

    distance_group_num = 0;

    memset(distance_dsc_idx, 0xffff, \
        sizeof(distance_dsc_idx));

    memset(common_widget_distance, 0, \
        sizeof(common_widget_distance));

    memset(distance_data_type, Comm_Data_Type___, \
        sizeof(distance_data_type));

    return;
}

void common_distance_refresh(void)
{
    if(!distance_group_num)
        return;

    for(uint8_t i = 0; i < distance_group_num; i++)
    {
        uint16_t vm_label_type = \
            vm_label_none;

        if(distance_data_type[i] == \
            Comm_Data_Type_Distance)
            vm_label_type = vm_label_daily_distance;
        else
            continue;

        int __data = \
            get_vm_para_cache_with_label(\
                vm_label_type); 

        if(__data > Distance_Disp_Max)
            __data = Distance_Disp_Max;

        uint32_t num_addr_index = \
            p_comm_distance_para[i]->num_addr_index;

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

        uint32_t symb_14_addr_index = \
            num_addr_index + \
                Comm_Symbol_14;
        data_img_dsc = \
            common_widget_img_open_res(\
                symb_14_addr_index);
        uint16_t symb_14_width = \
            data_img_dsc->header.w;

        char distance_num_str[Distance_Obj_Max + 1];
        memset(distance_num_str, 0, \
            sizeof(distance_num_str));

        if(!__data)
            memcpy(distance_num_str, (void *)"__", 2);
        else
            sprintf(distance_num_str, "%d.%02d", \
                __data/1000, (__data%1000)/10);

        uint8_t data_bit_num = \
            strlen((const char *)distance_num_str);

        uint8_t reject_cnt = 0;
        for(int8_t i = (data_bit_num - 1); i >= 0; i--)
        {
            if(distance_num_str[i] != '0')
                break;

            reject_cnt++;
        }

        if(distance_num_str[data_bit_num - 1 - \
            reject_cnt] == '.')
            reject_cnt++;

        data_bit_num -= reject_cnt;

        uint32_t distance_num_index[Distance_Obj_Max];
        uint16_t distance_data_width[Distance_Obj_Max];
        for(uint8_t j = 0; j < data_bit_num; j++)
        {
            if(distance_num_str[j] == '_')
            {
                distance_data_width[j] = \
                    symb_19_width;
                distance_num_index[j] = \
                    symb_19_addr_index;
            }else if(distance_num_str[j] == '.')
            {
                distance_data_width[j] = \
                    symb_14_width;
                distance_num_index[j] = \
                    symb_14_addr_index;
            }else
            {
                distance_data_width[j] = \
                    num_width;
                distance_num_index[j] = \
                    num_addr_index + \
                        (distance_num_str[j] - '0');
            }
        }

        int16_t distance_data_sx = \
        common_distance_widget_sx(i, data_bit_num, num_width, \
            symb_14_width, distance_data_width);

        uint8_t obj_idx = \
            (Distance_Obj_Max - data_bit_num) + \
                Distance_Obj_Max*i;

        uint16_t width_sum = 0;
        int16_t refresh_x, refresh_y;
        for(uint8_t j = 0; j < data_bit_num; j++)
        {
            if(j)
                width_sum += \
                    distance_data_width[j - 1];

            if(!common_widget_distance[j + obj_idx] || \
                distance_dsc_idx[j + obj_idx] == 0xffff)
                    continue;

            refresh_x = distance_data_sx + width_sum + \
                p_comm_distance_para[i]->num_inv*j;
            refresh_y = p_comm_distance_para[i]->data_y;
            lv_obj_set_pos(common_widget_distance[j + obj_idx], \
                refresh_x, refresh_y);
            
            common_widget_img_replace_src(common_widget_distance[j + obj_idx], \
                distance_num_index[j], distance_dsc_idx[j + obj_idx]);
            lv_obj_clear_flag(common_widget_distance[j + obj_idx], \
                LV_OBJ_FLAG_HIDDEN);
        }

        width_sum = 0;

        obj_idx = Distance_Obj_Max*i;
        for(uint8_t j = 0; j < (Distance_Obj_Max - data_bit_num); j++)
           lv_obj_add_flag(common_widget_distance[j + obj_idx], \
                LV_OBJ_FLAG_HIDDEN);
    }

    return;
}

void common_distance_widget_create(comm_data_para_t *data_para, \
    common_data_type_t type, void *data_val)
{
    if(distance_group_num >= \
        Distance_Group_Max)
        return;

    int __data = *(int *)data_val;

    if(__data > Distance_Disp_Max)
        __data = Distance_Disp_Max;

    distance_data_type[distance_group_num] = type;

    memcpy(&comm_distance_para_cache[distance_group_num], \
        data_para, sizeof(comm_data_para_t));

    p_comm_distance_para[distance_group_num] = \
        &comm_distance_para_cache[distance_group_num];

    uint32_t num_addr_index = \
        p_comm_distance_para[distance_group_num]->num_addr_index;

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

    uint32_t symb_14_addr_index = \
        num_addr_index + \
            Comm_Symbol_14;
    data_img_dsc = \
        common_widget_img_open_res(\
            symb_14_addr_index);
    uint16_t symb_14_width = \
        data_img_dsc->header.w;

    char distance_num_str[Distance_Obj_Max + 1];
    memset(distance_num_str, 0, \
        sizeof(distance_num_str));

    if(!__data)
        memcpy(distance_num_str, (void *)"__", 2);
    else
        sprintf(distance_num_str, "%d.%02d", \
            __data/1000, (__data%1000)/10);

    uint8_t data_bit_num = \
        strlen((const char *)distance_num_str);

    uint8_t reject_cnt = 0;
    for(int8_t i = (data_bit_num - 1); i >= 0; i--)
    {
        if(distance_num_str[i] != '0')
            break;

        reject_cnt++;
    }

    if(distance_num_str[data_bit_num - 1 - \
        reject_cnt] == '.')
        reject_cnt++;

    data_bit_num -= reject_cnt;

    uint32_t distance_num_index[Distance_Obj_Max];
    uint16_t distance_data_width[Distance_Obj_Max];
    for(uint8_t i = 0; i < data_bit_num; i++)
    {   
        if(distance_num_str[i] == '_')
        {
            distance_data_width[i] = \
                symb_19_width;
            distance_num_index[i] = \
                symb_19_addr_index;
        }else if(distance_num_str[i] == '.')
        {
            distance_data_width[i] = \
                symb_14_width;
            distance_num_index[i] = \
                symb_14_addr_index;
        }else
        {
            distance_data_width[i] = \
                num_width;
            distance_num_index[i] = \
                num_addr_index + \
                    (distance_num_str[i] - '0');
        }
    }

    int16_t distance_data_sx = \
        common_distance_widget_sx(distance_group_num, \
            data_bit_num, num_width, symb_14_width, distance_data_width);

    uint8_t obj_idx = \
        (Distance_Obj_Max - data_bit_num) + \
            Distance_Obj_Max*distance_group_num;
    
    widget_img_para.event_cb = NULL;
    widget_img_para.user_data = NULL;
    widget_img_para.img_click_attr = false;
    widget_img_para.img_parent = \
        p_comm_distance_para[distance_group_num]->data_parent;

    uint16_t width_sum = 0;
    for(uint8_t i = 0; i < data_bit_num; i++)
    {
        if(i)
           width_sum += \
                distance_data_width[i - 1];

        widget_img_para.img_x = \
            distance_data_sx + width_sum + \
                p_comm_distance_para[distance_group_num]->num_inv*i;
        widget_img_para.img_y = \
            p_comm_distance_para[distance_group_num]->data_y;
        widget_img_para.file_img_dat = \
            distance_num_index[i];

        common_widget_distance[i + obj_idx] = \
            common_widget_img_create(&widget_img_para, \
                &distance_dsc_idx[i + obj_idx]);
        lv_obj_clear_flag(common_widget_distance[i + obj_idx], \
            LV_OBJ_FLAG_HIDDEN);
    }

    obj_idx = Distance_Obj_Max*distance_group_num;
    for(uint8_t i = 0; i < (Distance_Obj_Max - data_bit_num); i++)
    {
        widget_img_para.file_img_dat = \
            num_addr_index;
        common_widget_distance[i + obj_idx] = \
            common_widget_img_create(&widget_img_para, \
                &distance_dsc_idx[i + obj_idx]);
        lv_obj_add_flag(common_widget_distance[i + obj_idx], \
            LV_OBJ_FLAG_HIDDEN);
    }

    distance_group_num++;

    return;
}
