#ifndef __file_index_h 
#define __file_index_h 


struct file_index_t {
    char *name;
    int addr;
    int len;
};

extern const struct file_index_t file_index[];

#define file_watchface_00_bg_dat             0x00000000
#define file_watchface_00_hour_dat             0x00000001
#define file_watchface_00_minute_dat             0x00000002
#define file_watchface_00_second_dat             0x00000003
#define file_watchface_00_sunny_dat             0x00000004
#define file_weather_bg_dat             0x00000005
#endif