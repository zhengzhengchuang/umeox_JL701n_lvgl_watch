#include "FILE_index.h" 


//struct FileIndex {
//    char *name;
//    int addr;
//    int len;
//};
const struct FileIndex FILE_index[] = {
    { "FILE_watchface_00_bg_dat", 0x00000000 ,21628},
    { "FILE_watchface_00_hour_dat", 0x00005480 ,1888},
    { "FILE_watchface_00_minute_dat", 0x00005BE4 ,2680},
    { "FILE_watchface_00_second_dat", 0x00006660 ,2668},
    { "FILE_weather_bg_dat", 0x000070D0 ,22204},
};