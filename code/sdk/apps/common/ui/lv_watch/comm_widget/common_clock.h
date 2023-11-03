#ifndef __COMMON_CLOCK_H__
#define __COMMON_CLOCK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../lv_watch.h"

enum
{
    Clk_Pointer_Type_Hour = 0x00,
    Clk_Pointer_Type_Minute,
    Clk_Pointer_Type_Second,
};
typedef uint8_t clock_pointer_type_t;

typedef struct
{
    int16_t clk_p_width;
    int16_t clk_p_height;
    int16_t clk_p_center;

    uint32_t clk_p_file_dat;

    clock_pointer_type_t clk_p_type;
}common_clock_pointer_para_t;

void common_clock_pointer_para_init(void);
void common_clock_pointer_refresh(int *refr_msg);
void common_clock_pointer_create(lv_obj_t *obj, const common_clock_pointer_para_t *para, uint8_t num);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
