#include "comm_weather.h"
#include "../poc_modem/poc_modem_vm.h"

/*********************************************************************************
                                  天气数据是否有效                                       
*********************************************************************************/
bool comm_whether_data_is_valid(void)
{
    bool data_is_valid = \
        p_vm_para_cache->weather_manage_para.data_is_valid;

    return data_is_valid;
}

/*********************************************************************************
                                  摄氏度转华氏度                                       
*********************************************************************************/
static int16_t comm_weather_convert_f_temper(int16_t c_temper)
{
	float f_temper = 0.0f;
	float f_temper_dec = 0.0f;
	
	f_temper = (((c_temper*(1.0f)) * 9 / 5) + 32); 
	f_temper_dec = (float)(f_temper - (int16_t)f_temper);
	if(f_temper_dec < 0.0f)
	{
		if(f_temper_dec + ((-1)*(0.5f)) <= ((-1)*(1.0f)))
            f_temper = f_temper + ((-1)*(0.5f));
	}else
	{
		if(f_temper_dec + (0.5f) >= 1.0f)
            f_temper = f_temper + (0.5f);
	}
	
	return (int16_t)f_temper;
}

/*********************************************************************************
                                  获取天气实时温度                                       
*********************************************************************************/
int16_t comm_weather_get_real_temper(void)
{
    int16_t weather_real_temper = \
        p_vm_para_cache->weather_manage_para.weather_real_temper;

    int cur_unit_temperature = \
        get_vm_para_cache_with_label(\
            vm_label_unit_temperature);

    if(cur_unit_temperature == \
        unit_temperature_F)
        weather_real_temper = \
            comm_weather_convert_f_temper(\
                weather_real_temper);

     return weather_real_temper;   
}

/*********************************************************************************
                                  获取天气最小温度                                       
*********************************************************************************/
int16_t comm_weather_get_min_temper(uint8_t day)
{
    if(day >= Weather_Sync_Days)
        return Weather_Invalid_Code;

    int16_t weather_min_temper = \
        p_vm_para_cache->weather_manage_para.weather_data[\
            day].weather_min_temper;

    int cur_unit_temperature = \
        get_vm_para_cache_with_label(\
            vm_label_unit_temperature);

    if(cur_unit_temperature == \
        unit_temperature_F)
        weather_min_temper = \
            comm_weather_convert_f_temper(\
                weather_min_temper);

     return weather_min_temper;   
}

/*********************************************************************************
                                  获取天气最大温度                                       
*********************************************************************************/
int16_t comm_weather_get_max_temper(uint8_t day)
{
    if(day >= Weather_Sync_Days)
        return Weather_Invalid_Code;

    int16_t weather_max_temper = \
        p_vm_para_cache->weather_manage_para.weather_data[\
            day].weather_max_temper;

    int cur_unit_temperature = \
        get_vm_para_cache_with_label(\
            vm_label_unit_temperature);

    if(cur_unit_temperature == \
        unit_temperature_F)
        weather_max_temper = \
            comm_weather_convert_f_temper(\
                weather_max_temper);

     return weather_max_temper;   
}

/*********************************************************************************
                                  获取天气类型                                       
*********************************************************************************/
comm_weather_type_t comm_weather_get_type(uint8_t day)
{
    if(day >= Weather_Sync_Days)
        return weather_type_unknown;

    comm_weather_type_t weather_type = \
        p_vm_para_cache->weather_manage_para.weather_data[\
            day].weather_type;

    return weather_type;
}