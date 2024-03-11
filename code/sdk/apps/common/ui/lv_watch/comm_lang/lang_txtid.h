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
    lang_txtid_sunny,//晴
    lang_txtid_snow,//雪
    lang_txtid_thunderstorm,//雷阵雨
    lang_txtid_wind,//风
    lang_txtid_misthaze,//雾霾
    lang_txtid_sandstorm,//沙尘暴
    lang_txtid_cloudy,//多云
    lang_txtid_rain_snow,//雨夹雪
    lang_txtid_shower,//阵雨
    lang_txtid_overcast,//阴天
    lang_txtid_pouring,//大雨
    lang_txtid_light_rain,//小雨
    lang_txtid_no_data,//无数据
    lang_txtid_every_day,//每天
    lang_txtid_sunday,//周日
    lang_txtid_monday,//周一
    lang_txtid_tuesday,//周二
    lang_txtid_wednesday,//周三
    lang_txtid_thursday,//周四
    lang_txtid_friday,//周五
    lang_txtid_saturday,//周六
    lang_txtid_call_log,//通话记录
    lang_txtid_contacts,//联系人
    lang_txtid_call_disc_tips,//电话未连接，请在连接电话后重试。
    lang_txtid_no_record,//无记录
    lang_txtid_call_end,//通话结束
    lang_txtid_connect_and_open,//请连接手机，并打开播放器。
    lang_txtid_not_connected_phone,//未连接到手机
    lang_txtid_searching_for_phone,//正在寻找附近的手机...
    lang_txtid_dnd_enable,//勿扰模式 - 开启
    lang_txtid_dnd_disable,//勿扰模式 - 关闭
    lang_txtid_no_reminder,//无提醒
    lang_txtid_no_message,//无消息
    
    lang_txtid_max,
};
typedef uint32_t comm_lang_txtid_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
