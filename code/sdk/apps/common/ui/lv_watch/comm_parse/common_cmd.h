#ifndef __COMMON_CMD_H__
#define __COMMON_CMD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

#define Le_Cmd_Max_Len (16)

enum
{
    le_cmd_get_dev_info = 0x01,            /******获取设备信息******/
    le_cmd_get_dev_support_func = 0x02,    /******获取设备支持的功能******/
    le_cmd_get_dev_func_state = 0x03,      /******获取设备功能状态******/ 
    le_cmd_set_dev_time = 0x04,            /******设置设备时间******/ 

    le_cmd_invalid = 0x80,                 /******无效命令******/ 
};
typedef uint8_t le_cmd_gather_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
