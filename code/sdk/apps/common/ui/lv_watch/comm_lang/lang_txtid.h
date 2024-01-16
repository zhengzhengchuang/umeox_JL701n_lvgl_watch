#ifndef __LANG_TXTID_H__
#define __LANG_TXTID_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

/*********************************************************************************
                                  文本id枚举                                       
*********************************************************************************/
enum
{
    lang_txtid_phone,  //电话
    lang_txtid_notify, //消息通知
    lang_txtid_quran_player, //古兰经播放器
    lang_txtid_prayer_times, //礼拜时间
    lang_txtid_azkar, //祈祷词
    lang_txtid_tasbih_reminder, //赞念提醒
    lang_txtid_allah_99_name, //阿拉的 99 个尊名
    lang_txtid_hijri_calendar, //回历
    lang_txtid_sleep, //睡眠
    lang_txtid_heart_rate, //心率
    lang_txtid_spo2, //血氧
    lang_txtid_sports, //运动
    lang_txtid_alarm, //闹钟
    lang_txtid_more, //更多
    lang_txtid_settings, //设置
    lang_txtid_pedometer, //计步
    lang_txtid_menu_view, //菜单视图
    lang_txtid_sound, //声音
    lang_txtid_display, //展示
    lang_txtid_language, //语言
    lang_txtid_unit, //计量单位
    lang_txtid_shortcuts, //快捷方式
    lang_txtid_about, //关于
    lang_txtid_sound_on, //声音 - 开启
    lang_txtid_view_list, //列表
    lang_txtid_view_grid_1, //网格1
    lang_txtid_view_grid_2, //网格2

    lang_txtid_max,
};
typedef uint32_t comm_lang_txtid_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
