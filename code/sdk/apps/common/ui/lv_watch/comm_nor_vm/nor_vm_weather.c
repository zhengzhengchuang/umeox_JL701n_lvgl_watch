#include "nor_vm_main.h"

static vm_weather_ctx_t vm_weather_ctx;
static const nor_vm_type_t nor_vm_type = \
    nor_vm_type_weather;

/*********************************************************************************
                                  摄氏度转华氏度                                       
*********************************************************************************/
static int16_t temper_ctof(int16_t c_temper)
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
                              清除                                         
*********************************************************************************/
void vm_weather_ctx_clear(void)
{
    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);

    if(!nor_vm_file)
        return;

    uint8_t weather_num = \
        vm_weather_item_num();

    if(!weather_num) 
        return;

    while(weather_num)
    {
        flash_common_delete_by_index(\
            nor_vm_file, 0);

        weather_num--;
    }
    
    return;
}

/*********************************************************************************
                              存储数量                                         
*********************************************************************************/
uint8_t vm_weather_item_num(void)
{
    uint8_t weather_num = 0;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);

    if(!nor_vm_file)
        return weather_num;

    weather_num = \
        flash_common_get_total(nor_vm_file);

    if(weather_num > Weather_Sync_Days)
        weather_num = Weather_Sync_Days;

    return weather_num;
}

/*********************************************************************************
                              数据是否有效                                         
*********************************************************************************/
bool vm_whether_data_is_valid(void)
{
    bool is_valid = false;

    uint8_t weather_num = \
        vm_weather_item_num();

    if(weather_num)
        is_valid = true;

    return is_valid;
}

/*********************************************************************************
                              实时温度                                        
*********************************************************************************/
int16_t vm_weather_data_real_temper(void)
{
    int16_t real_temper = 0;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);
    int weather_ctx_len = \
        sizeof(vm_weather_ctx_t);
    
    if(!nor_vm_file)
        return real_temper;

    memset(&vm_weather_ctx, 0, \
        weather_ctx_len);
    flash_common_read_by_index(nor_vm_file, 0, 0, \
        weather_ctx_len, (uint8_t *)&vm_weather_ctx);

    if(vm_weather_ctx.check_code != \
        Nor_Vm_Check_Code)
        return real_temper;

    real_temper = \
        vm_weather_ctx.weather_real_temper;

    int cur_unit_temperature = \
        get_vm_para_cache_with_label(\
            vm_label_unit_temperature);

    if(cur_unit_temperature == \
        unit_temperature_F)
        real_temper = \
            temper_ctof(\
                real_temper);

    return real_temper;
}

/*********************************************************************************
                              指定哪天的最小温度                                        
*********************************************************************************/
int16_t vm_weather_data_min_temper(uint8_t day)
{
    int16_t min_temper = 0;

    uint8_t weather_num = \
        vm_weather_item_num();
    if(day >= weather_num)
        return min_temper;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);
    int weather_ctx_len = \
        sizeof(vm_weather_ctx_t); 
    if(!nor_vm_file)
        return min_temper;
    
    memset(&vm_weather_ctx, 0, \
        weather_ctx_len);
    flash_common_read_by_index(nor_vm_file, day, 0, \
        weather_ctx_len, (uint8_t *)&vm_weather_ctx);

    if(vm_weather_ctx.check_code != \
        Nor_Vm_Check_Code)
        return min_temper;

    min_temper = \
        vm_weather_ctx.weather_min_temper;

    int cur_unit_temperature = \
        get_vm_para_cache_with_label(\
            vm_label_unit_temperature);

    if(cur_unit_temperature == \
        unit_temperature_F)
        min_temper = \
            temper_ctof(\
                min_temper);

    return min_temper;
}

/*********************************************************************************
                              指定哪天的最大温度                                        
*********************************************************************************/
int16_t vm_weather_data_max_temper(uint8_t day)
{
    int16_t max_temper = 0;

    uint8_t weather_num = \
        vm_weather_item_num();
    if(day >= weather_num)
        return max_temper;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);
    int weather_ctx_len = \
        sizeof(vm_weather_ctx_t); 
    if(!nor_vm_file)
        return max_temper;
    
    memset(&vm_weather_ctx, 0, \
        weather_ctx_len);
    flash_common_read_by_index(nor_vm_file, day, 0, \
        weather_ctx_len, (uint8_t *)&vm_weather_ctx);

    if(vm_weather_ctx.check_code != \
        Nor_Vm_Check_Code)
        return max_temper;

    max_temper = \
        vm_weather_ctx.weather_max_temper;

    int cur_unit_temperature = \
        get_vm_para_cache_with_label(\
            vm_label_unit_temperature);

    if(cur_unit_temperature == \
        unit_temperature_F)
        max_temper = \
            temper_ctof(\
                max_temper);

    return max_temper;
}


/*********************************************************************************
                              指定哪天的天气类型                                        
*********************************************************************************/
weather_type_t vm_weather_data_weather_type(uint8_t day)
{
    weather_type_t weather_type = \
        weather_type_unknown;

    uint8_t weather_num = \
        vm_weather_item_num();
    if(day >= weather_num)
        return weather_type;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);
    int weather_ctx_len = \
        sizeof(vm_weather_ctx_t); 
    if(!nor_vm_file)
        return weather_type;

    memset(&vm_weather_ctx, 0, \
        weather_ctx_len);
    flash_common_read_by_index(nor_vm_file, day, 0, \
        weather_ctx_len, (uint8_t *)&vm_weather_ctx);

    if(vm_weather_ctx.check_code != \
        Nor_Vm_Check_Code)
        return weather_type;

    weather_type = \
        vm_weather_ctx.weather_type;

    return weather_type;
}

/*********************************************************************************
                              天气数据存储                                        
*********************************************************************************/
void vm_weather_ctx_falsh_save(uint8_t idx, vm_weather_ctx_t *p)
{
    if(!p) return;

    void *nor_vm_file = \
        nor_flash_vm_file(nor_vm_type);
    int weather_ctx_len = \
        sizeof(vm_weather_ctx_t);

    if(!nor_vm_file)
        return;

    uint8_t weather_num = \
        vm_weather_item_num();
    if(idx < weather_num)
        vm_weather_ctx_clear();

    int file_id = \
        flash_common_open_id(nor_vm_file, 0, \
            weather_ctx_len);
    if(!file_id) return;

    flash_common_write_packet(nor_vm_file, file_id, \
        weather_ctx_len, (uint8_t *)p);

    return;
}

#if 0
static const vm_weather_ctx_t vm_weather_ctx_test[\
    Weather_Sync_Days] = 
{
    [0] = {
        .check_code = Nor_Vm_Check_Code, .weather_type = weather_type_sunny, \
        .weather_real_temper = 25, .weather_min_temper = 20, .weather_max_temper = 28, 
    },

    [1] = {
        .check_code = Nor_Vm_Check_Code, .weather_type = weather_type_snow, \
        .weather_real_temper = 26, .weather_min_temper = 21, .weather_max_temper = -29, 
    },

    [2] = {
        .check_code = Nor_Vm_Check_Code, .weather_type = weather_type_thunderstorm, \
        .weather_real_temper = 27, .weather_min_temper = 22, .weather_max_temper = 30, 
    },

    [3] = {
        .check_code = Nor_Vm_Check_Code, .weather_type = weather_type_wind, \
        .weather_real_temper = 28, .weather_min_temper = 23, .weather_max_temper = 31, 
    },

    [4] = {
        .check_code = Nor_Vm_Check_Code, .weather_type = weather_type_sunny, \
        .weather_real_temper = 29, .weather_min_temper = 24, .weather_max_temper = 32, 
    },

    [5] = {
        .check_code = Nor_Vm_Check_Code, .weather_type = weather_type_misthaze, \
        .weather_real_temper = 30, .weather_min_temper = 25, .weather_max_temper = 33, 
    },

    [6] = {
        .check_code = Nor_Vm_Check_Code, .weather_type = weather_type_sandstorm, \
        .weather_real_temper = 31, .weather_min_temper = 26, .weather_max_temper = 34, 
    },
};

void vm_weather_ctx_falsh_test(void)
{
    for(uint8_t i = 0; i < Weather_Sync_Days; i++)
    {
        vm_weather_ctx_falsh_save(i, \
            &vm_weather_ctx_test[i]);
    }

    return;
}
#endif