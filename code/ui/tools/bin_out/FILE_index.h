#ifndef __FILE_INDEX_H__ 
#define __FILE_INDEX_H__ 

#ifdef __cplusplus
extern "C" {
#endif

struct file_index_t {
    char *name;
    int addr;
    int len;
};

extern const struct file_index_t file_index[];

#define font_common_32_address (0x00000000)

#define compass_bg_index (0x00000000)
#define compass_clock_index (0x00000001)
#define menu_icon_00_index (0x00000002)
#define menu_icon_01_index (0x00000003)
#define menu_icon_02_index (0x00000004)
#define menu_icon_03_index (0x00000005)
#define menu_icon_04_index (0x00000006)
#define menu_icon_05_index (0x00000007)
#define menu_icon_06_index (0x00000008)
#define menu_icon_07_index (0x00000009)
#define menu_icon_08_index (0x0000000A)
#define menu_icon_09_index (0x0000000B)
#define menu_icon_10_index (0x0000000C)
#define menu_icon_11_index (0x0000000D)
#define menu_icon_12_index (0x0000000E)
#define menu_icon_13_index (0x0000000F)
#define menu_icon_14_index (0x00000010)
#define menu_icon_15_index (0x00000011)
#define menu_icon_16_index (0x00000012)
#define menu_icon_17_index (0x00000013)
#define menu_icon_18_index (0x00000014)
#define menu_icon_19_index (0x00000015)
#define menu_icon_20_index (0x00000016)
#define menu_icon_21_index (0x00000017)
#define menu_icon_22_index (0x00000018)
#define menu_icon_23_index (0x00000019)
#define menu_icon_24_index (0x0000001A)
#define menu_icon_25_index (0x0000001B)
#define menu_icon_26_index (0x0000001C)
#define menu_icon_27_index (0x0000001D)
#define menu_icon_28_index (0x0000001E)
#define menu_icon_29_index (0x0000001F)
#define menu_icon_30_index (0x00000020)
#define menu_icon_31_index (0x00000021)
#define menu_icon_32_index (0x00000022)
#define menu_icon_33_index (0x00000023)
#define menu_icon_34_index (0x00000024)
#define menu_icon_35_index (0x00000025)
#define menu_icon_36_index (0x00000026)
#define watchface_00_bg_index (0x00000027)
#define watchface_00_hour_index (0x00000028)
#define watchface_00_min_index (0x00000029)
#define watchface_00_sec_index (0x0000002A)
#define weather_bg_index (0x0000002B)

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif