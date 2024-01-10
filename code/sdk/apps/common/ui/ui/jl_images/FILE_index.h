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

#define comm_num_30x40_ye_00_index (0x00000000)
#define comm_num_30x40_ye_01_index (0x00000001)
#define comm_num_30x40_ye_02_index (0x00000002)
#define comm_num_30x40_ye_03_index (0x00000003)
#define comm_num_30x40_ye_04_index (0x00000004)
#define comm_num_30x40_ye_05_index (0x00000005)
#define comm_num_30x40_ye_06_index (0x00000006)
#define comm_num_30x40_ye_07_index (0x00000007)
#define comm_num_30x40_ye_08_index (0x00000008)
#define comm_num_30x40_ye_09_index (0x00000009)
#define comm_num_30x40_ye_10_index (0x0000000A)
#define comm_num_30x40_ye_11_index (0x0000000B)
#define comm_num_30x40_ye_12_index (0x0000000C)
#define comm_num_30x40_ye_13_index (0x0000000D)
#define comm_num_30x40_ye_14_index (0x0000000E)
#define comm_num_30x40_ye_15_index (0x0000000F)
#define comm_num_30x40_ye_16_index (0x00000010)
#define comm_num_30x40_ye_17_index (0x00000011)
#define comm_num_30x40_ye_18_index (0x00000012)
#define comm_num_30x40_ye_19_index (0x00000013)
#define comm_num_30x40_ye_20_index (0x00000014)
#define comm_num_30x40_ye_21_index (0x00000015)
#define menu_100_100_icon_00_index (0x00000016)
#define menu_100_100_icon_01_index (0x00000017)
#define menu_100_100_icon_02_index (0x00000018)
#define menu_100_100_icon_03_index (0x00000019)
#define menu_100_100_icon_04_index (0x0000001A)
#define menu_100_100_icon_05_index (0x0000001B)
#define menu_100_100_icon_06_index (0x0000001C)
#define menu_100_100_icon_07_index (0x0000001D)
#define menu_100_100_icon_08_index (0x0000001E)
#define menu_100_100_icon_09_index (0x0000001F)
#define menu_100_100_icon_10_index (0x00000020)
#define menu_100_100_icon_11_index (0x00000021)
#define menu_100_100_icon_12_index (0x00000022)
#define menu_100_100_icon_13_index (0x00000023)
#define menu_100_100_icon_14_index (0x00000024)
#define menu_100_100_icon_15_index (0x00000025)
#define menu_88_88_icon_00_index (0x00000026)
#define menu_88_88_icon_01_index (0x00000027)
#define menu_88_88_icon_02_index (0x00000028)
#define menu_88_88_icon_03_index (0x00000029)
#define menu_88_88_icon_04_index (0x0000002A)
#define menu_88_88_icon_05_index (0x0000002B)
#define menu_88_88_icon_06_index (0x0000002C)
#define menu_88_88_icon_07_index (0x0000002D)
#define menu_88_88_icon_08_index (0x0000002E)
#define menu_88_88_icon_09_index (0x0000002F)
#define menu_88_88_icon_10_index (0x00000030)
#define menu_88_88_icon_11_index (0x00000031)
#define menu_88_88_icon_12_index (0x00000032)
#define menu_88_88_icon_13_index (0x00000033)
#define menu_88_88_icon_14_index (0x00000034)
#define menu_88_88_icon_15_index (0x00000035)
#define remind_hr_warn_00_index (0x00000036)
#define remind_low_bat_00_index (0x00000037)
#define remind_off_wrist_00_index (0x00000038)
#define remind_ota_update_00_index (0x00000039)
#define remind_ota_update_01_index (0x0000003A)
#define remind_ota_update_02_index (0x0000003B)
#define remind_sedentary_00_index (0x0000003C)
#define remind_wf_transp_00_index (0x0000003D)
#define restore_00_index (0x0000003E)
#define shutdown_00_index (0x0000003F)
#define watchface_00_bg_index (0x00000040)
#define watchface_00_clock_dot_index (0x00000041)
#define watchface_00_clock_hour_index (0x00000042)
#define watchface_00_clock_minute_index (0x00000043)
#define watchface_00_clock_second_index (0x00000044)

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif