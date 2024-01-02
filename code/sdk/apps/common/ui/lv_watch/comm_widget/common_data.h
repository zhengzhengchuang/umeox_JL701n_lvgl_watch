#ifndef __COMMON_DATA_H__
#define __COMMON_DATA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

/*********************************************************************************
                                  心率  示例:102bmp                                
*********************************************************************************/
#define Hr_Obj_Max (3)
#define Hr_Group_Max (6)


/*********************************************************************************
                                  血氧  示例:100%                                      
*********************************************************************************/
#define Bo_Obj_Max (4)
#define Bo_Group_Max (6)


/*********************************************************************************
                                  步数  示例:88888steps                                    
*********************************************************************************/
#define Step_Obj_Max (5)
#define Step_Group_Max (3)


/*********************************************************************************
                                  卡路里(千卡)  示例:8888kcal                                 
*********************************************************************************/
#define Calorie_Obj_Max (4)
#define Calorie_Group_Max (3)


/*********************************************************************************
                                  配速  示例:99'99''                                    
*********************************************************************************/
#define Pace_Obj_Max (6)
#define Pace_Group_Max (3)


/*********************************************************************************
                                  距离  示例:99.99km                               
*********************************************************************************/
#define Distance_Obj_Max (5)
#define Distance_Group_Max (3)


/*********************************************************************************
                                  通用数据类型枚举                                       
*********************************************************************************/
enum
{
    Comm_Data_Type___ = 0x00,

    Comm_Data_Type_Hr,             /*数据类型：心率值*/
    Comm_Data_Type_Min_Hr,         /*数据类型：最小心率*/
    Comm_Data_Type_Max_Hr,         /*数据类型：最大心率*/

    Comm_Data_Type_Bo,             /*数据类型：血氧*/
    Comm_Data_Type_Min_Bo,         /*数据类型：最小血氧*/
    Comm_Data_Type_Max_Bo,         /*数据类型：最大血氧*/

    Comm_Data_Type_Step,           /*数据类型：步数*/
    Comm_Data_Type_Calorie,        /*数据类型：卡路里(千卡)*/
    Comm_Data_Type_Pace,           /*数据类型：配速*/
    Comm_Data_Type_Distance,       /*数据类型：距离*/
};
typedef uint8_t common_data_type_t;

/*********************************************************************************
                                  通用数据对齐枚举                                       
*********************************************************************************/
enum
{
    Comm_Data_Align____ = 0x00,
    Comm_Data_Align_Left,
    Comm_Data_Align_Right,
    Comm_Data_Align_Center,
};
typedef uint8_t common_data_align_t;

/*********************************************************************************
                                  通用数据参数集合                                      
*********************************************************************************/
typedef struct
{
    int16_t data_x;
    int16_t data_y;
    int16_t num_inv;
    lv_obj_t *data_parent;
    uint32_t num_addr_index;
    common_data_align_t data_align;
}comm_data_para_t;
extern comm_data_para_t comm_data_para;

void common_data_refresh(void);
void common_data_widget_init(void);
void common_data_widget_create(comm_data_para_t *data_para, \
    common_data_type_t type, void *data_val);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
