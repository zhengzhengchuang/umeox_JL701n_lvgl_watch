#ifndef __COMMON_TIME_H__
#define __COMMON_TIME_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

/*********************************************************************************
                                  一组时间占用的最大obj个数                                       
*********************************************************************************/
#define Time_Obj_Max (8)

/*********************************************************************************
                                  时间组数最大                                       
*********************************************************************************/
#define Time_Group_Max (3)

/*********************************************************************************
                                  时间小时制枚举                                      
*********************************************************************************/
enum
{
    comm_time_format_24 = 0x00,
    comm_time_format_12 = 0x01,
};
typedef uint8_t comm_time_format_t;

/*********************************************************************************
                                  时间显示模式枚举                                      
*********************************************************************************/
enum
{
    comm_time_mode___ = 0x00,           /*显示模式   无*/
    comm_time_mode_hh,           /*显示模式   时*/
    comm_time_mode_mm,           /*显示模式   分*/
    comm_time_mode_ss,           /*显示模式   秒*/
    comm_time_mode_hh_mm,        /*显示模式   时:分*/
    comm_time_mode_mm_ss,        /*显示模式   分:秒*/
    comm_time_mode_hh_mm_ss,     /*显示模式   时:分:秒*/
};
typedef uint8_t comm_time_mode_t;

/*********************************************************************************
                                  时间控件参数集合                                   
*********************************************************************************/
typedef struct
{  
    int16_t time_x;
    int16_t time_y;
    int16_t num_inv;
    lv_obj_t *time_parent;
    uint32_t num_addr_index;
}comm_time_para_t;
extern comm_time_para_t comm_time_para;

void common_time_refresh(void);
void common_time_widget_init(void);
void common_time_widget_create(comm_time_para_t *time_para, \
    comm_time_mode_t time_mode);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
