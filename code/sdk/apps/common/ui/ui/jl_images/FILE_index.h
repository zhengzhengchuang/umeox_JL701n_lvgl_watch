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
#define menu_100_100_icon_00_index (0x00000002)
#define menu_100_100_icon_01_index (0x00000003)
#define menu_100_100_icon_02_index (0x00000004)
#define menu_100_100_icon_03_index (0x00000005)
#define menu_100_100_icon_04_index (0x00000006)
#define menu_100_100_icon_05_index (0x00000007)
#define menu_100_100_icon_06_index (0x00000008)
#define menu_100_100_icon_07_index (0x00000009)
#define menu_100_100_icon_08_index (0x0000000A)
#define menu_100_100_icon_09_index (0x0000000B)
#define menu_100_100_icon_10_index (0x0000000C)
#define menu_100_100_icon_11_index (0x0000000D)
#define menu_100_100_icon_12_index (0x0000000E)
#define menu_100_100_icon_13_index (0x0000000F)
#define menu_100_100_icon_14_index (0x00000010)
#define menu_100_100_icon_15_index (0x00000011)
#define menu_100_100_icon_16_index (0x00000012)
#define menu_100_100_icon_17_index (0x00000013)
#define menu_100_100_icon_18_index (0x00000014)
#define menu_100_100_icon_19_index (0x00000015)
#define menu_100_100_icon_20_index (0x00000016)
#define menu_100_100_icon_21_index (0x00000017)
#define menu_100_100_icon_22_index (0x00000018)
#define menu_100_100_icon_23_index (0x00000019)
#define menu_100_100_icon_24_index (0x0000001A)
#define menu_100_100_icon_25_index (0x0000001B)
#define menu_100_100_icon_26_index (0x0000001C)
#define menu_100_100_icon_27_index (0x0000001D)
#define menu_100_100_icon_28_index (0x0000001E)
#define menu_100_100_icon_29_index (0x0000001F)
#define menu_100_100_icon_30_index (0x00000020)
#define menu_100_100_icon_31_index (0x00000021)
#define menu_100_100_icon_32_index (0x00000022)
#define menu_100_100_icon_33_index (0x00000023)
#define menu_100_100_icon_34_index (0x00000024)
#define menu_100_100_icon_35_index (0x00000025)
#define menu_100_100_icon_36_index (0x00000026)
#define menu_96_96_icon_00_index (0x00000027)
#define menu_96_96_icon_01_index (0x00000028)
#define menu_96_96_icon_02_index (0x00000029)
#define menu_96_96_icon_03_index (0x0000002A)
#define menu_96_96_icon_04_index (0x0000002B)
#define menu_96_96_icon_05_index (0x0000002C)
#define menu_96_96_icon_06_index (0x0000002D)
#define menu_96_96_icon_07_index (0x0000002E)
#define menu_96_96_icon_08_index (0x0000002F)
#define menu_96_96_icon_09_index (0x00000030)
#define menu_96_96_icon_10_index (0x00000031)
#define menu_96_96_icon_11_index (0x00000032)
#define menu_96_96_icon_12_index (0x00000033)
#define menu_96_96_icon_13_index (0x00000034)
#define menu_96_96_icon_14_index (0x00000035)
#define menu_96_96_icon_15_index (0x00000036)
#define menu_96_96_icon_16_index (0x00000037)
#define menu_96_96_icon_17_index (0x00000038)
#define menu_96_96_icon_18_index (0x00000039)
#define menu_96_96_icon_19_index (0x0000003A)
#define menu_96_96_icon_20_index (0x0000003B)
#define menu_96_96_icon_21_index (0x0000003C)
#define menu_96_96_icon_22_index (0x0000003D)
#define menu_96_96_icon_23_index (0x0000003E)
#define menu_96_96_icon_24_index (0x0000003F)
#define menu_96_96_icon_25_index (0x00000040)
#define menu_96_96_icon_26_index (0x00000041)
#define menu_96_96_icon_27_index (0x00000042)
#define menu_96_96_icon_28_index (0x00000043)
#define menu_96_96_icon_29_index (0x00000044)
#define menu_96_96_icon_30_index (0x00000045)
#define menu_96_96_icon_31_index (0x00000046)
#define menu_96_96_icon_32_index (0x00000047)
#define menu_96_96_icon_33_index (0x00000048)
#define menu_96_96_icon_34_index (0x00000049)
#define menu_96_96_icon_35_index (0x0000004A)
#define menu_96_96_icon_36_index (0x0000004B)
#define watchface_00_bg_index (0x0000004C)
#define watchface_00_hour_index (0x0000004D)
#define watchface_00_min_index (0x0000004E)
#define watchface_00_sec_index (0x0000004F)
#define weather_bg_index (0x00000050)

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif