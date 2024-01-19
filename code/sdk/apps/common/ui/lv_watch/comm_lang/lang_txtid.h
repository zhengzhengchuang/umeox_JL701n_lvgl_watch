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
    lang_txtid_screen_sleep, //屏幕休眠
    lang_txtid_distance, //距离
    lang_txtid_temperature, //温度
    lang_txtid_kilometer, //千米
    lang_txtid_mile, //英里
    lang_txtid_unit_C, //摄氏度℃
    lang_txtid_unit_F, //华摄氏度℉
    lang_txtid_quran_watch, //Quran Watch
    lang_txtid_bluetooth_name, //蓝牙名称
    lang_txtid_bluetooth_mac,//蓝牙 MAC
    lang_txtid_version,//版本
    lang_txtid_QR_code,//二维码
    lang_txtid_factory_reset,//恢复出厂设置
    lang_txtid_factory_reset_tip,//恢复出厂设置将清除手表数据。
    lang_txtid_today,//今天
    lang_txtid_tomorrow,//明天
    lang_txtid_thunderstorm,//雷雨
    lang_txtid_drizzle,//细雨
    lang_txtid_light_rain,//小雨
    lang_txtid_moderate_rain,//中雨
    lang_txtid_heavy_intensity_rain,//强降雨
    lang_txtid_extreme_rain,//极端雨
    lang_txtid_freezing_rain,//冻雨
    lang_txtid_shower_rain,//阵雨
    lang_txtid_light_snow,//小雪
    lang_txtid_heavy_snow,//大雪
    lang_txtid_rain_and_snow,//雨雪
    lang_txtid_haze,//阴霾
    lang_txtid_dust,//灰尘
    lang_txtid_squall,//旋风
    lang_txtid_clear_sky,//晴天
    lang_txtid_few_clouds,//少云
    lang_txtid_scattered_clouds,//散云
    lang_txtid_overcast_clouds,//多云
    lang_txtid_cloudy,//阴天
    lang_txtid_no_data,//无数据
    lang_txtid_sunday,//周日
    lang_txtid_monday,//周一
    lang_txtid_tuesday,//周二
    lang_txtid_wednesday,//周三
    lang_txtid_thursday,//周四
    lang_txtid_friday,//周五
    lang_txtid_saturday,//周六
    
    lang_txtid_max,
};
typedef uint32_t comm_lang_txtid_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
