#ifndef __FILE_index_h 
#define __FILE_index_h 

struct FileIndex {
    char *name;
    int addr;
    int len;
};
extern const struct FileIndex FILE_index[] ;
#define FILE_watchface_00_bg_dat             0x00000000
#define FILE_watchface_00_hour_dat             0x00000001
#define FILE_watchface_00_minute_dat             0x00000002
#define FILE_watchface_00_second_dat             0x00000003
#define FILE_weather_bg_dat             0x00000004
#endif