#ifndef __NOR_VM_WEATHER_H__
#define __NOR_VM_WEATHER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

/*********************************************************************************
                                  同步最大天数                                       
*********************************************************************************/
#define Weather_Sync_Days (7)

/*********************************************************************************
                                  天气无效值                                       
*********************************************************************************/
#define Weather_Invalid_Code (0x7fff)

/*********************************************************************************
                                  天气类型(不要改枚举的顺序)                                    
*********************************************************************************/
enum
{
    weather_type_sunny,            //晴
    weather_type_snow,             //雪
    weather_type_thunderstorm,     //雷阵雨
    weather_type_wind,             //风
    weather_type_misthaze,         //雾霾
    weather_type_sandstorm,        //沙尘暴
    weather_type_cloudy,           //多云
    weather_type_rain_snow,        //雨夹雪
    weather_type_shower,           //阵雨
    weather_type_overcast,         //阴天
    weather_type_pouring,          //大雨
    weather_type_light_rain,       //小雨

    weather_type_unknown,          //未知
};
typedef uint8_t weather_type_t;

/*********************************************************************************
                                  天气数据内容                                       
*********************************************************************************/
typedef struct
{
    uint16_t check_code; 	

	int16_t weather_max_temper;
	int16_t weather_min_temper;
    int16_t weather_real_temper;
	weather_type_t weather_type;
}vm_weather_ctx_t;

/*********************************************************************************
                                  天气接口                                       
*********************************************************************************/
void vm_weather_ctx_clear(void);
uint8_t vm_weather_item_num(void);
bool vm_whether_data_is_valid(void);
int16_t vm_weather_data_real_temper(void);
int16_t vm_weather_data_min_temper(uint8_t day);
int16_t vm_weather_data_max_temper(uint8_t day);
weather_type_t vm_weather_data_weather_type(uint8_t day);
void vm_weather_ctx_falsh_save(uint8_t idx, vm_weather_ctx_t *p);
#ifdef __cplusplus
}
#endif

#endif
