#ifndef __COMM_WEATHER_H__
#define __COMM_WEATHER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

/*********************************************************************************
                                  天气同步天数                                       
*********************************************************************************/
#define Weather_Sync_Days (7)

/*********************************************************************************
                                  天气无效值                                       
*********************************************************************************/
#define Weather_Invalid_Code (0x7fff)

/*********************************************************************************
                                  天气类型                                       
*********************************************************************************/
enum
{
    weather_type_thunderstorm = 0x00,  //雷雨
    weather_type_drizzle,              //细雨
    weather_type_light_rain,           //小雨
    weather_type_moderate_rain,        //中雨
    weather_type_heavy_intensity_rain, //强降雨
    weather_type_extreme_rain,         //极端雨
    weather_type_freezing_rain,        //冻雨
    weather_type_shower_rain,          //阵雨
    weather_type_light_snow,           //小雪
    weather_type_heavy_snow,           //大雪
    weather_type_rain_and_snow,        //雨雪
    weather_type_haze,                 //阴霾
    weather_type_dust,                 //灰尘
    weather_type_squall,               //旋风
    weather_type_clear_sky,            //晴天
    weather_type_few_clouds,           //少云
    weather_type_scattered_clouds,     //散云
    weather_type_overcast_clouds,      //多云
    weather_type_cloudy,               //阴天

    weather_type_unknown,              //未知
};
typedef uint8_t comm_weather_type_t;

/*********************************************************************************
                                  天气数据结构体                                       
*********************************************************************************/
typedef struct
{	
	int16_t weather_max_temper;
	int16_t weather_min_temper;
    int16_t weather_real_temper;
	comm_weather_type_t weather_type;
}comm_weather_data_t;

/*********************************************************************************
                                  天气管理参数                                       
*********************************************************************************/
typedef struct
{
    bool data_is_valid;
    comm_weather_data_t weather_data[\
        Weather_Sync_Days];
}weather_manage_para_t;

/*********************************************************************************
                                  天气数据接口                                       
*********************************************************************************/
bool comm_whether_data_is_valid(void);
int16_t comm_weather_get_min_temper(uint8_t day);
int16_t comm_weather_get_max_temper(uint8_t day);
int16_t comm_weather_get_real_temper(uint8_t day);
comm_weather_type_t comm_weather_get_type(uint8_t day);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
