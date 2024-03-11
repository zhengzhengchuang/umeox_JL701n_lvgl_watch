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

#define font_common_num_32_address (0x001F5239)

#define font_common_num_36_address (0x001FDC2C)

#define font_common_num_42_address (0x00206744)

#define font_common_num_52_address (0x0020F50D)

#define font_common_num_64_address (0x002187B1)

#define about_00_index (0x00000000)
#define about_01_index (0x00000001)
#define about_02_index (0x00000002)
#define alarm_00_index (0x00000003)
#define alarm_01_index (0x00000004)
#define alarm_repeat_00_index (0x00000005)
#define alarm_repeat_01_index (0x00000006)
#define alarm_repeat_02_index (0x00000007)
#define alarm_repeat_03_index (0x00000008)
#define alarm_repeat_04_index (0x00000009)
#define alarm_repeat_05_index (0x0000000A)
#define alarm_repeat_06_index (0x0000000B)
#define alarm_repeat_07_index (0x0000000C)
#define alarm_repeat_08_index (0x0000000D)
#define alarm_repeat_09_index (0x0000000E)
#define alarm_repeat_10_index (0x0000000F)
#define alarm_repeat_11_index (0x00000010)
#define alarm_repeat_12_index (0x00000011)
#define alarm_repeat_13_index (0x00000012)
#define call_00_index (0x00000013)
#define call_01_index (0x00000014)
#define call_02_index (0x00000015)
#define call_03_index (0x00000016)
#define call_04_index (0x00000017)
#define call_05_index (0x00000018)
#define call_06_index (0x00000019)
#define call_07_index (0x0000001A)
#define call_08_index (0x0000001B)
#define call_09_index (0x0000001C)
#define call_10_index (0x0000001D)
#define call_11_index (0x0000001E)
#define call_12_index (0x0000001F)
#define call_13_index (0x00000020)
#define call_14_index (0x00000021)
#define call_15_index (0x00000022)
#define call_16_index (0x00000023)
#define call_18_index (0x00000024)
#define camera_00_index (0x00000025)
#define camera_01_index (0x00000026)
#define camera_02_index (0x00000027)
#define comm_icon_00_index (0x00000028)
#define comm_icon_01_index (0x00000029)
#define comm_icon_02_index (0x0000002A)
#define comm_icon_03_index (0x0000002B)
#define comm_icon_04_index (0x0000002C)
#define comm_icon_05_index (0x0000002D)
#define comm_icon_06_index (0x0000002E)
#define comm_icon_07_index (0x0000002F)
#define comm_icon_08_index (0x00000030)
#define comm_icon_09_index (0x00000031)
#define comm_icon_10_index (0x00000032)
#define comm_icon_11_index (0x00000033)
#define comm_icon_12_index (0x00000034)
#define comm_icon_13_index (0x00000035)
#define comm_icon_14_index (0x00000036)
#define comm_icon_15_index (0x00000037)
#define comm_icon_16_index (0x00000038)
#define comm_icon_17_index (0x00000039)
#define comm_icon_18_index (0x0000003A)
#define comm_icon_19_index (0x0000003B)
#define comm_icon_20_index (0x0000003C)
#define comm_icon_21_index (0x0000003D)
#define comm_icon_22_index (0x0000003E)
#define comm_icon_23_index (0x0000003F)
#define comm_icon_24_index (0x00000040)
#define comm_icon_25_index (0x00000041)
#define comm_icon_26_index (0x00000042)
#define comm_icon_27_index (0x00000043)
#define comm_icon_28_index (0x00000044)
#define comm_icon_29_index (0x00000045)
#define comm_num_14x22_gr_00_index (0x00000046)
#define comm_num_14x22_gr_01_index (0x00000047)
#define comm_num_14x22_gr_02_index (0x00000048)
#define comm_num_14x22_gr_03_index (0x00000049)
#define comm_num_14x22_gr_04_index (0x0000004A)
#define comm_num_14x22_gr_05_index (0x0000004B)
#define comm_num_14x22_gr_06_index (0x0000004C)
#define comm_num_14x22_gr_07_index (0x0000004D)
#define comm_num_14x22_gr_08_index (0x0000004E)
#define comm_num_14x22_gr_09_index (0x0000004F)
#define comm_num_14x22_gr_10_index (0x00000050)
#define comm_num_14x22_gr_11_index (0x00000051)
#define comm_num_14x22_gr_12_index (0x00000052)
#define comm_num_14x22_gr_13_index (0x00000053)
#define comm_num_14x22_gr_14_index (0x00000054)
#define comm_num_14x22_gr_15_index (0x00000055)
#define comm_num_14x22_gr_16_index (0x00000056)
#define comm_num_14x22_gr_17_index (0x00000057)
#define comm_num_14x22_gr_18_index (0x00000058)
#define comm_num_14x22_gr_19_index (0x00000059)
#define comm_num_14x22_gr_20_index (0x0000005A)
#define comm_num_14x22_gr_21_index (0x0000005B)
#define comm_num_14x22_wh_00_index (0x0000005C)
#define comm_num_14x22_wh_01_index (0x0000005D)
#define comm_num_14x22_wh_02_index (0x0000005E)
#define comm_num_14x22_wh_03_index (0x0000005F)
#define comm_num_14x22_wh_04_index (0x00000060)
#define comm_num_14x22_wh_05_index (0x00000061)
#define comm_num_14x22_wh_06_index (0x00000062)
#define comm_num_14x22_wh_07_index (0x00000063)
#define comm_num_14x22_wh_08_index (0x00000064)
#define comm_num_14x22_wh_09_index (0x00000065)
#define comm_num_14x22_wh_10_index (0x00000066)
#define comm_num_14x22_wh_11_index (0x00000067)
#define comm_num_14x22_wh_12_index (0x00000068)
#define comm_num_14x22_wh_13_index (0x00000069)
#define comm_num_14x22_wh_14_index (0x0000006A)
#define comm_num_14x22_wh_15_index (0x0000006B)
#define comm_num_14x22_wh_16_index (0x0000006C)
#define comm_num_14x22_wh_17_index (0x0000006D)
#define comm_num_14x22_wh_18_index (0x0000006E)
#define comm_num_14x22_wh_19_index (0x0000006F)
#define comm_num_14x22_wh_20_index (0x00000070)
#define comm_num_14x22_wh_21_index (0x00000071)
#define comm_num_16x28_ye_00_index (0x00000072)
#define comm_num_16x28_ye_01_index (0x00000073)
#define comm_num_16x28_ye_02_index (0x00000074)
#define comm_num_16x28_ye_03_index (0x00000075)
#define comm_num_16x28_ye_04_index (0x00000076)
#define comm_num_16x28_ye_05_index (0x00000077)
#define comm_num_16x28_ye_06_index (0x00000078)
#define comm_num_16x28_ye_07_index (0x00000079)
#define comm_num_16x28_ye_08_index (0x0000007A)
#define comm_num_16x28_ye_09_index (0x0000007B)
#define comm_num_16x28_ye_10_index (0x0000007C)
#define comm_num_16x28_ye_11_index (0x0000007D)
#define comm_num_16x28_ye_12_index (0x0000007E)
#define comm_num_16x28_ye_13_index (0x0000007F)
#define comm_num_16x28_ye_14_index (0x00000080)
#define comm_num_16x28_ye_15_index (0x00000081)
#define comm_num_16x28_ye_16_index (0x00000082)
#define comm_num_16x28_ye_17_index (0x00000083)
#define comm_num_16x28_ye_18_index (0x00000084)
#define comm_num_16x28_ye_19_index (0x00000085)
#define comm_num_16x28_ye_20_index (0x00000086)
#define comm_num_16x28_ye_21_index (0x00000087)
#define comm_num_20x32_wh_00_index (0x00000088)
#define comm_num_20x32_wh_01_index (0x00000089)
#define comm_num_20x32_wh_02_index (0x0000008A)
#define comm_num_20x32_wh_03_index (0x0000008B)
#define comm_num_20x32_wh_04_index (0x0000008C)
#define comm_num_20x32_wh_05_index (0x0000008D)
#define comm_num_20x32_wh_06_index (0x0000008E)
#define comm_num_20x32_wh_07_index (0x0000008F)
#define comm_num_20x32_wh_08_index (0x00000090)
#define comm_num_20x32_wh_09_index (0x00000091)
#define comm_num_20x32_wh_10_index (0x00000092)
#define comm_num_20x32_wh_11_index (0x00000093)
#define comm_num_20x32_wh_12_index (0x00000094)
#define comm_num_20x32_wh_13_index (0x00000095)
#define comm_num_20x32_wh_14_index (0x00000096)
#define comm_num_20x32_wh_15_index (0x00000097)
#define comm_num_20x32_wh_16_index (0x00000098)
#define comm_num_20x32_wh_17_index (0x00000099)
#define comm_num_20x32_wh_18_index (0x0000009A)
#define comm_num_20x32_wh_19_index (0x0000009B)
#define comm_num_20x32_wh_20_index (0x0000009C)
#define comm_num_20x32_wh_21_index (0x0000009D)
#define comm_num_30x40_wh_00_index (0x0000009E)
#define comm_num_30x40_wh_01_index (0x0000009F)
#define comm_num_30x40_wh_02_index (0x000000A0)
#define comm_num_30x40_wh_03_index (0x000000A1)
#define comm_num_30x40_wh_04_index (0x000000A2)
#define comm_num_30x40_wh_05_index (0x000000A3)
#define comm_num_30x40_wh_06_index (0x000000A4)
#define comm_num_30x40_wh_07_index (0x000000A5)
#define comm_num_30x40_wh_08_index (0x000000A6)
#define comm_num_30x40_wh_09_index (0x000000A7)
#define comm_num_30x40_wh_10_index (0x000000A8)
#define comm_num_30x40_wh_11_index (0x000000A9)
#define comm_num_30x40_wh_12_index (0x000000AA)
#define comm_num_30x40_wh_13_index (0x000000AB)
#define comm_num_30x40_wh_14_index (0x000000AC)
#define comm_num_30x40_wh_15_index (0x000000AD)
#define comm_num_30x40_wh_16_index (0x000000AE)
#define comm_num_30x40_wh_17_index (0x000000AF)
#define comm_num_30x40_wh_18_index (0x000000B0)
#define comm_num_30x40_wh_19_index (0x000000B1)
#define comm_num_30x40_wh_20_index (0x000000B2)
#define comm_num_30x40_wh_21_index (0x000000B3)
#define comm_num_30x50_wh_00_index (0x000000B4)
#define comm_num_30x50_wh_01_index (0x000000B5)
#define comm_num_30x50_wh_02_index (0x000000B6)
#define comm_num_30x50_wh_03_index (0x000000B7)
#define comm_num_30x50_wh_04_index (0x000000B8)
#define comm_num_30x50_wh_05_index (0x000000B9)
#define comm_num_30x50_wh_06_index (0x000000BA)
#define comm_num_30x50_wh_07_index (0x000000BB)
#define comm_num_30x50_wh_08_index (0x000000BC)
#define comm_num_30x50_wh_09_index (0x000000BD)
#define comm_num_30x50_wh_10_index (0x000000BE)
#define comm_num_30x50_wh_11_index (0x000000BF)
#define comm_num_30x50_wh_12_index (0x000000C0)
#define comm_num_30x50_wh_13_index (0x000000C1)
#define comm_num_30x50_wh_14_index (0x000000C2)
#define comm_num_30x50_wh_15_index (0x000000C3)
#define comm_num_30x50_wh_16_index (0x000000C4)
#define comm_num_30x50_wh_17_index (0x000000C5)
#define comm_num_30x50_wh_18_index (0x000000C6)
#define comm_num_30x50_wh_19_index (0x000000C7)
#define comm_num_30x50_wh_20_index (0x000000C8)
#define comm_num_30x50_wh_21_index (0x000000C9)
#define comm_num_30x50_ye_00_index (0x000000CA)
#define comm_num_30x50_ye_01_index (0x000000CB)
#define comm_num_30x50_ye_02_index (0x000000CC)
#define comm_num_30x50_ye_03_index (0x000000CD)
#define comm_num_30x50_ye_04_index (0x000000CE)
#define comm_num_30x50_ye_05_index (0x000000CF)
#define comm_num_30x50_ye_06_index (0x000000D0)
#define comm_num_30x50_ye_07_index (0x000000D1)
#define comm_num_30x50_ye_08_index (0x000000D2)
#define comm_num_30x50_ye_09_index (0x000000D3)
#define comm_num_30x50_ye_10_index (0x000000D4)
#define comm_num_30x50_ye_11_index (0x000000D5)
#define comm_num_30x50_ye_12_index (0x000000D6)
#define comm_num_30x50_ye_13_index (0x000000D7)
#define comm_num_30x50_ye_14_index (0x000000D8)
#define comm_num_30x50_ye_15_index (0x000000D9)
#define comm_num_30x50_ye_16_index (0x000000DA)
#define comm_num_30x50_ye_17_index (0x000000DB)
#define comm_num_30x50_ye_18_index (0x000000DC)
#define comm_num_30x50_ye_19_index (0x000000DD)
#define comm_num_30x50_ye_20_index (0x000000DE)
#define comm_num_30x50_ye_21_index (0x000000DF)
#define comm_num_36x56_wh_00_index (0x000000E0)
#define comm_num_36x56_wh_01_index (0x000000E1)
#define comm_num_36x56_wh_02_index (0x000000E2)
#define comm_num_36x56_wh_03_index (0x000000E3)
#define comm_num_36x56_wh_04_index (0x000000E4)
#define comm_num_36x56_wh_05_index (0x000000E5)
#define comm_num_36x56_wh_06_index (0x000000E6)
#define comm_num_36x56_wh_07_index (0x000000E7)
#define comm_num_36x56_wh_08_index (0x000000E8)
#define comm_num_36x56_wh_09_index (0x000000E9)
#define comm_num_36x56_wh_10_index (0x000000EA)
#define comm_num_36x56_wh_11_index (0x000000EB)
#define comm_num_36x56_wh_12_index (0x000000EC)
#define comm_num_36x56_wh_13_index (0x000000ED)
#define comm_num_36x56_wh_14_index (0x000000EE)
#define comm_num_36x56_wh_15_index (0x000000EF)
#define comm_num_36x56_wh_16_index (0x000000F0)
#define comm_num_36x56_wh_17_index (0x000000F1)
#define comm_num_36x56_wh_18_index (0x000000F2)
#define comm_num_36x56_wh_19_index (0x000000F3)
#define comm_num_36x56_wh_20_index (0x000000F4)
#define comm_num_36x56_wh_21_index (0x000000F5)
#define countdown_00_index (0x000000F6)
#define countdown_01_index (0x000000F7)
#define disp_ctrl_00_index (0x000000F8)
#define disp_ctrl_01_index (0x000000F9)
#define disp_ctrl_02_index (0x000000FA)
#define menu_100_100_icon_00_index (0x000000FB)
#define menu_100_100_icon_01_index (0x000000FC)
#define menu_100_100_icon_02_index (0x000000FD)
#define menu_100_100_icon_03_index (0x000000FE)
#define menu_100_100_icon_04_index (0x000000FF)
#define menu_100_100_icon_05_index (0x00000100)
#define menu_100_100_icon_06_index (0x00000101)
#define menu_100_100_icon_07_index (0x00000102)
#define menu_100_100_icon_08_index (0x00000103)
#define menu_100_100_icon_09_index (0x00000104)
#define menu_100_100_icon_10_index (0x00000105)
#define menu_100_100_icon_11_index (0x00000106)
#define menu_100_100_icon_12_index (0x00000107)
#define menu_100_100_icon_13_index (0x00000108)
#define menu_100_100_icon_14_index (0x00000109)
#define menu_100_100_icon_15_index (0x0000010A)
#define menu_88_88_icon_00_index (0x0000010B)
#define menu_88_88_icon_01_index (0x0000010C)
#define menu_88_88_icon_02_index (0x0000010D)
#define menu_88_88_icon_03_index (0x0000010E)
#define menu_88_88_icon_04_index (0x0000010F)
#define menu_88_88_icon_05_index (0x00000110)
#define menu_88_88_icon_06_index (0x00000111)
#define menu_88_88_icon_07_index (0x00000112)
#define menu_88_88_icon_08_index (0x00000113)
#define menu_88_88_icon_09_index (0x00000114)
#define menu_88_88_icon_10_index (0x00000115)
#define menu_88_88_icon_11_index (0x00000116)
#define menu_88_88_icon_12_index (0x00000117)
#define menu_88_88_icon_13_index (0x00000118)
#define menu_88_88_icon_14_index (0x00000119)
#define menu_88_88_icon_15_index (0x0000011A)
#define menu_view_00_index (0x0000011B)
#define menu_view_01_index (0x0000011C)
#define menu_view_02_index (0x0000011D)
#define message_icon_00_index (0x0000011E)
#define message_icon_02_index (0x0000011F)
#define message_icon_03_index (0x00000120)
#define message_type_00_index (0x00000121)
#define message_type_01_index (0x00000122)
#define message_type_02_index (0x00000123)
#define message_type_03_index (0x00000124)
#define message_type_04_index (0x00000125)
#define message_type_05_index (0x00000126)
#define message_type_06_index (0x00000127)
#define message_type_07_index (0x00000128)
#define message_type_08_index (0x00000129)
#define message_type_09_index (0x0000012A)
#define message_type_10_index (0x0000012B)
#define message_type_11_index (0x0000012C)
#define message_type_12_index (0x0000012D)
#define message_type_13_index (0x0000012E)
#define remind_hr_warn_00_index (0x0000012F)
#define remind_low_bat_00_index (0x00000130)
#define remind_off_wrist_00_index (0x00000131)
#define remind_ota_update_00_index (0x00000132)
#define remind_ota_update_01_index (0x00000133)
#define remind_ota_update_02_index (0x00000134)
#define remind_sedentary_00_index (0x00000135)
#define remind_wf_transp_00_index (0x00000136)
#define remote_music_00_index (0x00000137)
#define remote_music_01_index (0x00000138)
#define remote_music_02_index (0x00000139)
#define remote_music_03_index (0x0000013A)
#define remote_music_04_index (0x0000013B)
#define restore_00_index (0x0000013C)
#define settings_00_index (0x0000013D)
#define settings_01_index (0x0000013E)
#define settings_02_index (0x0000013F)
#define settings_03_index (0x00000140)
#define settings_04_index (0x00000141)
#define settings_05_index (0x00000142)
#define settings_06_index (0x00000143)
#define settings_07_index (0x00000144)
#define shutdown_00_index (0x00000145)
#define sound_ctrl_01_index (0x00000146)
#define sound_ctrl_02_index (0x00000147)
#define tool_box_camera_00_index (0x00000148)
#define tool_box_dnd_00_index (0x00000149)
#define tool_box_dnd_01_index (0x0000014A)
#define tool_box_ear_00_index (0x0000014B)
#define tool_box_ear_01_index (0x0000014C)
#define tool_box_find_00_index (0x0000014D)
#define tool_box_light_00_index (0x0000014E)
#define tool_box_light_01_index (0x0000014F)
#define tool_box_light_02_index (0x00000150)
#define tool_box_light_03_index (0x00000151)
#define tool_box_light_04_index (0x00000152)
#define tool_box_light_05_index (0x00000153)
#define tool_box_other_00_index (0x00000154)
#define tool_box_other_01_index (0x00000155)
#define tool_box_setting_00_index (0x00000156)
#define watchface_00_12x20_00_index (0x00000157)
#define watchface_00_12x20_01_index (0x00000158)
#define watchface_00_12x20_02_index (0x00000159)
#define watchface_00_12x20_03_index (0x0000015A)
#define watchface_00_12x20_04_index (0x0000015B)
#define watchface_00_12x20_05_index (0x0000015C)
#define watchface_00_12x20_06_index (0x0000015D)
#define watchface_00_12x20_07_index (0x0000015E)
#define watchface_00_12x20_08_index (0x0000015F)
#define watchface_00_12x20_09_index (0x00000160)
#define watchface_00_12x20_10_index (0x00000161)
#define watchface_00_12x20_11_index (0x00000162)
#define watchface_00_12x20_12_index (0x00000163)
#define watchface_00_52x78_00_index (0x00000164)
#define watchface_00_52x78_01_index (0x00000165)
#define watchface_00_52x78_02_index (0x00000166)
#define watchface_00_52x78_03_index (0x00000167)
#define watchface_00_52x78_04_index (0x00000168)
#define watchface_00_52x78_05_index (0x00000169)
#define watchface_00_52x78_06_index (0x0000016A)
#define watchface_00_52x78_07_index (0x0000016B)
#define watchface_00_52x78_08_index (0x0000016C)
#define watchface_00_52x78_09_index (0x0000016D)
#define watchface_00_bg_index (0x0000016E)
#define watchface_00_week_ar_00_index (0x0000016F)
#define watchface_00_week_ar_01_index (0x00000170)
#define watchface_00_week_ar_02_index (0x00000171)
#define watchface_00_week_ar_03_index (0x00000172)
#define watchface_00_week_ar_04_index (0x00000173)
#define watchface_00_week_ar_05_index (0x00000174)
#define watchface_00_week_ar_06_index (0x00000175)
#define watchface_00_week_en_00_index (0x00000176)
#define watchface_00_week_en_01_index (0x00000177)
#define watchface_00_week_en_02_index (0x00000178)
#define watchface_00_week_en_03_index (0x00000179)
#define watchface_00_week_en_04_index (0x0000017A)
#define watchface_00_week_en_05_index (0x0000017B)
#define watchface_00_week_en_06_index (0x0000017C)
#define watchface_00_week_fr_00_index (0x0000017D)
#define watchface_00_week_fr_01_index (0x0000017E)
#define watchface_00_week_fr_02_index (0x0000017F)
#define watchface_00_week_fr_03_index (0x00000180)
#define watchface_00_week_fr_04_index (0x00000181)
#define watchface_00_week_fr_05_index (0x00000182)
#define watchface_00_week_fr_06_index (0x00000183)
#define watchface_01_bg_index (0x00000184)
#define watchface_01_clock_hour_index (0x00000185)
#define watchface_01_clock_min_index (0x00000186)
#define watchface_01_clock_sec_index (0x00000187)
#define watchface_02_14x22_00_index (0x00000188)
#define watchface_02_14x22_01_index (0x00000189)
#define watchface_02_14x22_02_index (0x0000018A)
#define watchface_02_14x22_03_index (0x0000018B)
#define watchface_02_14x22_04_index (0x0000018C)
#define watchface_02_14x22_05_index (0x0000018D)
#define watchface_02_14x22_06_index (0x0000018E)
#define watchface_02_14x22_07_index (0x0000018F)
#define watchface_02_14x22_08_index (0x00000190)
#define watchface_02_14x22_09_index (0x00000191)
#define watchface_02_14x22_10_index (0x00000192)
#define watchface_02_14x22_11_index (0x00000193)
#define watchface_02_14x22_12_index (0x00000194)
#define watchface_02_52x78_00_index (0x00000195)
#define watchface_02_52x78_01_index (0x00000196)
#define watchface_02_52x78_02_index (0x00000197)
#define watchface_02_52x78_03_index (0x00000198)
#define watchface_02_52x78_04_index (0x00000199)
#define watchface_02_52x78_05_index (0x0000019A)
#define watchface_02_52x78_06_index (0x0000019B)
#define watchface_02_52x78_07_index (0x0000019C)
#define watchface_02_52x78_08_index (0x0000019D)
#define watchface_02_52x78_09_index (0x0000019E)
#define watchface_02_52x78_10_index (0x0000019F)
#define watchface_02_bg_index (0x000001A0)
#define watchface_02_week_ar_00_index (0x000001A1)
#define watchface_02_week_ar_01_index (0x000001A2)
#define watchface_02_week_ar_02_index (0x000001A3)
#define watchface_02_week_ar_03_index (0x000001A4)
#define watchface_02_week_ar_04_index (0x000001A5)
#define watchface_02_week_ar_05_index (0x000001A6)
#define watchface_02_week_ar_06_index (0x000001A7)
#define watchface_02_week_en_00_index (0x000001A8)
#define watchface_02_week_en_01_index (0x000001A9)
#define watchface_02_week_en_02_index (0x000001AA)
#define watchface_02_week_en_03_index (0x000001AB)
#define watchface_02_week_en_04_index (0x000001AC)
#define watchface_02_week_en_05_index (0x000001AD)
#define watchface_02_week_en_06_index (0x000001AE)
#define watchface_02_week_fr_00_index (0x000001AF)
#define watchface_02_week_fr_01_index (0x000001B0)
#define watchface_02_week_fr_02_index (0x000001B1)
#define watchface_02_week_fr_03_index (0x000001B2)
#define watchface_02_week_fr_04_index (0x000001B3)
#define watchface_02_week_fr_05_index (0x000001B4)
#define watchface_02_week_fr_06_index (0x000001B5)
#define watchface_03_bg_index (0x000001B6)
#define watchface_04_bg_index (0x000001B7)
#define watchface_04_clock_hour_index (0x000001B8)
#define watchface_04_clock_min_index (0x000001B9)
#define watchface_04_clock_sec_index (0x000001BA)
#define watchface_05_bg_index (0x000001BB)
#define watchface_05_clock_hour_index (0x000001BC)
#define watchface_05_clock_min_index (0x000001BD)
#define watchface_05_clock_sec_index (0x000001BE)
#define watchface_06_10x16_00_index (0x000001BF)
#define watchface_06_10x16_01_index (0x000001C0)
#define watchface_06_10x16_02_index (0x000001C1)
#define watchface_06_10x16_03_index (0x000001C2)
#define watchface_06_10x16_04_index (0x000001C3)
#define watchface_06_10x16_05_index (0x000001C4)
#define watchface_06_10x16_06_index (0x000001C5)
#define watchface_06_10x16_07_index (0x000001C6)
#define watchface_06_10x16_08_index (0x000001C7)
#define watchface_06_10x16_09_index (0x000001C8)
#define watchface_06_10x16_10_index (0x000001C9)
#define watchface_06_12x20_00_index (0x000001CA)
#define watchface_06_12x20_01_index (0x000001CB)
#define watchface_06_12x20_02_index (0x000001CC)
#define watchface_06_12x20_03_index (0x000001CD)
#define watchface_06_12x20_04_index (0x000001CE)
#define watchface_06_12x20_05_index (0x000001CF)
#define watchface_06_12x20_06_index (0x000001D0)
#define watchface_06_12x20_07_index (0x000001D1)
#define watchface_06_12x20_08_index (0x000001D2)
#define watchface_06_12x20_09_index (0x000001D3)
#define watchface_06_12x20_10_index (0x000001D4)
#define watchface_06_14x22_00_index (0x000001D5)
#define watchface_06_14x22_01_index (0x000001D6)
#define watchface_06_14x22_02_index (0x000001D7)
#define watchface_06_14x22_03_index (0x000001D8)
#define watchface_06_14x22_04_index (0x000001D9)
#define watchface_06_14x22_05_index (0x000001DA)
#define watchface_06_14x22_06_index (0x000001DB)
#define watchface_06_14x22_07_index (0x000001DC)
#define watchface_06_14x22_08_index (0x000001DD)
#define watchface_06_14x22_09_index (0x000001DE)
#define watchface_06_14x22_10_index (0x000001DF)
#define watchface_06_14x22_11_index (0x000001E0)
#define watchface_06_14x22_12_index (0x000001E1)
#define watchface_06_14x22_13_index (0x000001E2)
#define watchface_06_14x22_14_index (0x000001E3)
#define watchface_06_14x22_15_index (0x000001E4)
#define watchface_06_14x22_16_index (0x000001E5)
#define watchface_06_14x22_17_index (0x000001E6)
#define watchface_06_14x22_18_index (0x000001E7)
#define watchface_06_14x22_19_index (0x000001E8)
#define watchface_06_14x22_20_index (0x000001E9)
#define watchface_06_14x22_21_index (0x000001EA)
#define watchface_06_52x78_00_index (0x000001EB)
#define watchface_06_52x78_01_index (0x000001EC)
#define watchface_06_52x78_02_index (0x000001ED)
#define watchface_06_52x78_03_index (0x000001EE)
#define watchface_06_52x78_04_index (0x000001EF)
#define watchface_06_52x78_05_index (0x000001F0)
#define watchface_06_52x78_06_index (0x000001F1)
#define watchface_06_52x78_07_index (0x000001F2)
#define watchface_06_52x78_08_index (0x000001F3)
#define watchface_06_52x78_09_index (0x000001F4)
#define watchface_06_52x78_10_index (0x000001F5)
#define watchface_06_bg_index (0x000001F6)
#define watchface_06_etime_ar_00_index (0x000001F7)
#define watchface_06_etime_en_00_index (0x000001F8)
#define watchface_06_etime_fr_00_index (0x000001F9)
#define watchface_06_prayer_ar_00_index (0x000001FA)
#define watchface_06_prayer_ar_01_index (0x000001FB)
#define watchface_06_prayer_ar_02_index (0x000001FC)
#define watchface_06_prayer_ar_03_index (0x000001FD)
#define watchface_06_prayer_ar_04_index (0x000001FE)
#define watchface_06_prayer_ar_05_index (0x000001FF)
#define watchface_06_prayer_ar_06_index (0x00000200)
#define watchface_06_prayer_en_00_index (0x00000201)
#define watchface_06_prayer_en_01_index (0x00000202)
#define watchface_06_prayer_en_02_index (0x00000203)
#define watchface_06_prayer_en_03_index (0x00000204)
#define watchface_06_prayer_en_04_index (0x00000205)
#define watchface_06_prayer_en_05_index (0x00000206)
#define watchface_06_prayer_en_06_index (0x00000207)
#define watchface_06_prayer_fr_00_index (0x00000208)
#define watchface_06_prayer_fr_01_index (0x00000209)
#define watchface_06_prayer_fr_02_index (0x0000020A)
#define watchface_06_prayer_fr_03_index (0x0000020B)
#define watchface_06_prayer_fr_04_index (0x0000020C)
#define watchface_06_prayer_fr_05_index (0x0000020D)
#define watchface_06_prayer_fr_06_index (0x0000020E)
#define watchface_06_rtime_ar_00_index (0x0000020F)
#define watchface_06_rtime_en_00_index (0x00000210)
#define watchface_06_rtime_fr_00_index (0x00000211)
#define watchface_06_week_ar_00_index (0x00000212)
#define watchface_06_week_ar_01_index (0x00000213)
#define watchface_06_week_ar_02_index (0x00000214)
#define watchface_06_week_ar_03_index (0x00000215)
#define watchface_06_week_ar_04_index (0x00000216)
#define watchface_06_week_ar_05_index (0x00000217)
#define watchface_06_week_ar_06_index (0x00000218)
#define watchface_06_week_en_00_index (0x00000219)
#define watchface_06_week_en_01_index (0x0000021A)
#define watchface_06_week_en_02_index (0x0000021B)
#define watchface_06_week_en_03_index (0x0000021C)
#define watchface_06_week_en_04_index (0x0000021D)
#define watchface_06_week_en_05_index (0x0000021E)
#define watchface_06_week_en_06_index (0x0000021F)
#define watchface_06_week_fr_00_index (0x00000220)
#define watchface_06_week_fr_01_index (0x00000221)
#define watchface_06_week_fr_02_index (0x00000222)
#define watchface_06_week_fr_03_index (0x00000223)
#define watchface_06_week_fr_04_index (0x00000224)
#define watchface_06_week_fr_05_index (0x00000225)
#define watchface_06_week_fr_06_index (0x00000226)
#define watchface_07_14x22_00_index (0x00000227)
#define watchface_07_14x22_01_index (0x00000228)
#define watchface_07_14x22_02_index (0x00000229)
#define watchface_07_14x22_03_index (0x0000022A)
#define watchface_07_14x22_04_index (0x0000022B)
#define watchface_07_14x22_05_index (0x0000022C)
#define watchface_07_14x22_06_index (0x0000022D)
#define watchface_07_14x22_07_index (0x0000022E)
#define watchface_07_14x22_08_index (0x0000022F)
#define watchface_07_14x22_09_index (0x00000230)
#define watchface_07_14x22_10_index (0x00000231)
#define watchface_07_14x22_11_index (0x00000232)
#define watchface_07_14x22_12_index (0x00000233)
#define watchface_07_52x78_00_index (0x00000234)
#define watchface_07_52x78_01_index (0x00000235)
#define watchface_07_52x78_02_index (0x00000236)
#define watchface_07_52x78_03_index (0x00000237)
#define watchface_07_52x78_04_index (0x00000238)
#define watchface_07_52x78_05_index (0x00000239)
#define watchface_07_52x78_06_index (0x0000023A)
#define watchface_07_52x78_07_index (0x0000023B)
#define watchface_07_52x78_08_index (0x0000023C)
#define watchface_07_52x78_09_index (0x0000023D)
#define watchface_07_bg_index (0x0000023E)
#define watchface_08_bg_index (0x0000023F)
#define watchface_09_16x28_00_index (0x00000240)
#define watchface_09_16x28_01_index (0x00000241)
#define watchface_09_16x28_02_index (0x00000242)
#define watchface_09_16x28_03_index (0x00000243)
#define watchface_09_16x28_04_index (0x00000244)
#define watchface_09_16x28_05_index (0x00000245)
#define watchface_09_16x28_06_index (0x00000246)
#define watchface_09_16x28_07_index (0x00000247)
#define watchface_09_16x28_08_index (0x00000248)
#define watchface_09_16x28_09_index (0x00000249)
#define watchface_09_bg_index (0x0000024A)
#define watchface_10_52x78_00_index (0x0000024B)
#define watchface_10_52x78_01_index (0x0000024C)
#define watchface_10_52x78_02_index (0x0000024D)
#define watchface_10_52x78_03_index (0x0000024E)
#define watchface_10_52x78_04_index (0x0000024F)
#define watchface_10_52x78_05_index (0x00000250)
#define watchface_10_52x78_06_index (0x00000251)
#define watchface_10_52x78_07_index (0x00000252)
#define watchface_10_52x78_08_index (0x00000253)
#define watchface_10_52x78_09_index (0x00000254)
#define watchface_10_bg_index (0x00000255)
#define watchface_11_12x20_dark_00_index (0x00000256)
#define watchface_11_12x20_dark_01_index (0x00000257)
#define watchface_11_12x20_dark_02_index (0x00000258)
#define watchface_11_12x20_dark_03_index (0x00000259)
#define watchface_11_12x20_dark_04_index (0x0000025A)
#define watchface_11_12x20_dark_05_index (0x0000025B)
#define watchface_11_12x20_dark_06_index (0x0000025C)
#define watchface_11_12x20_dark_07_index (0x0000025D)
#define watchface_11_12x20_dark_08_index (0x0000025E)
#define watchface_11_12x20_dark_09_index (0x0000025F)
#define watchface_11_12x20_dark_10_index (0x00000260)
#define watchface_11_12x20_dark_11_index (0x00000261)
#define watchface_11_12x20_dark_12_index (0x00000262)
#define watchface_11_12x20_dark_13_index (0x00000263)
#define watchface_11_12x20_dark_14_index (0x00000264)
#define watchface_11_12x20_dark_15_index (0x00000265)
#define watchface_11_12x20_dark_16_index (0x00000266)
#define watchface_11_12x20_dark_17_index (0x00000267)
#define watchface_11_12x20_dark_18_index (0x00000268)
#define watchface_11_12x20_dark_19_index (0x00000269)
#define watchface_11_12x20_light_00_index (0x0000026A)
#define watchface_11_12x20_light_01_index (0x0000026B)
#define watchface_11_12x20_light_02_index (0x0000026C)
#define watchface_11_12x20_light_03_index (0x0000026D)
#define watchface_11_12x20_light_04_index (0x0000026E)
#define watchface_11_12x20_light_05_index (0x0000026F)
#define watchface_11_12x20_light_06_index (0x00000270)
#define watchface_11_12x20_light_07_index (0x00000271)
#define watchface_11_12x20_light_08_index (0x00000272)
#define watchface_11_12x20_light_09_index (0x00000273)
#define watchface_11_12x20_light_10_index (0x00000274)
#define watchface_11_12x20_light_11_index (0x00000275)
#define watchface_11_12x20_light_12_index (0x00000276)
#define watchface_11_12x20_light_13_index (0x00000277)
#define watchface_11_12x20_light_14_index (0x00000278)
#define watchface_11_12x20_light_15_index (0x00000279)
#define watchface_11_12x20_light_16_index (0x0000027A)
#define watchface_11_12x20_light_17_index (0x0000027B)
#define watchface_11_12x20_light_18_index (0x0000027C)
#define watchface_11_12x20_light_19_index (0x0000027D)
#define watchface_11_12x20_light_20_index (0x0000027E)
#define watchface_11_12x20_light_21_index (0x0000027F)
#define watchface_11_52x78_00_index (0x00000280)
#define watchface_11_52x78_01_index (0x00000281)
#define watchface_11_52x78_02_index (0x00000282)
#define watchface_11_52x78_03_index (0x00000283)
#define watchface_11_52x78_04_index (0x00000284)
#define watchface_11_52x78_05_index (0x00000285)
#define watchface_11_52x78_06_index (0x00000286)
#define watchface_11_52x78_07_index (0x00000287)
#define watchface_11_52x78_08_index (0x00000288)
#define watchface_11_52x78_09_index (0x00000289)
#define watchface_11_bg_index (0x0000028A)
#define watchface_11_weather_00_index (0x0000028B)
#define watchface_11_weather_01_index (0x0000028C)
#define watchface_11_weather_02_index (0x0000028D)
#define watchface_11_weather_03_index (0x0000028E)
#define watchface_11_weather_04_index (0x0000028F)
#define watchface_11_weather_05_index (0x00000290)
#define watchface_11_weather_06_index (0x00000291)
#define watchface_11_weather_07_index (0x00000292)
#define watchface_11_weather_08_index (0x00000293)
#define watchface_11_weather_09_index (0x00000294)
#define watchface_11_weather_10_index (0x00000295)
#define watchface_11_weather_11_index (0x00000296)
#define watchface_11_weather_12_index (0x00000297)
#define watchface_11_week_ar_00_index (0x00000298)
#define watchface_11_week_ar_01_index (0x00000299)
#define watchface_11_week_ar_02_index (0x0000029A)
#define watchface_11_week_ar_03_index (0x0000029B)
#define watchface_11_week_ar_04_index (0x0000029C)
#define watchface_11_week_ar_05_index (0x0000029D)
#define watchface_11_week_ar_06_index (0x0000029E)
#define watchface_11_week_en_00_index (0x0000029F)
#define watchface_11_week_en_01_index (0x000002A0)
#define watchface_11_week_en_02_index (0x000002A1)
#define watchface_11_week_en_03_index (0x000002A2)
#define watchface_11_week_en_04_index (0x000002A3)
#define watchface_11_week_en_05_index (0x000002A4)
#define watchface_11_week_en_06_index (0x000002A5)
#define watchface_11_week_fr_00_index (0x000002A6)
#define watchface_11_week_fr_01_index (0x000002A7)
#define watchface_11_week_fr_02_index (0x000002A8)
#define watchface_11_week_fr_03_index (0x000002A9)
#define watchface_11_week_fr_04_index (0x000002AA)
#define watchface_11_week_fr_05_index (0x000002AB)
#define watchface_11_week_fr_06_index (0x000002AC)
#define weather_148x140_00_index (0x000002AD)
#define weather_148x140_01_index (0x000002AE)
#define weather_148x140_02_index (0x000002AF)
#define weather_148x140_03_index (0x000002B0)
#define weather_148x140_04_index (0x000002B1)
#define weather_148x140_05_index (0x000002B2)
#define weather_148x140_06_index (0x000002B3)
#define weather_148x140_07_index (0x000002B4)
#define weather_148x140_08_index (0x000002B5)
#define weather_148x140_09_index (0x000002B6)
#define weather_148x140_10_index (0x000002B7)
#define weather_148x140_11_index (0x000002B8)
#define weather_72x68_00_index (0x000002B9)
#define weather_72x68_01_index (0x000002BA)
#define weather_72x68_02_index (0x000002BB)
#define weather_72x68_03_index (0x000002BC)
#define weather_72x68_04_index (0x000002BD)
#define weather_72x68_05_index (0x000002BE)
#define weather_72x68_06_index (0x000002BF)
#define weather_72x68_07_index (0x000002C0)
#define weather_72x68_08_index (0x000002C1)
#define weather_72x68_09_index (0x000002C2)
#define weather_72x68_10_index (0x000002C3)
#define weather_72x68_11_index (0x000002C4)
#define weather_no_data_00_index (0x000002C5)
#define weather_other_00_index (0x000002C6)
#define weather_other_01_index (0x000002C7)

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif