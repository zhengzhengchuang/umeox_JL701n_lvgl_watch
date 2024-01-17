#ifndef __LANG_CONF_H__
#define __LANG_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "lang_txtid.h"
#include "../include/ui_menu.h"

/*********************************************************************************
                                  语言支持配置                                       
*********************************************************************************/
#define Comm_Conf_Lang_Ar  (1)  //阿拉伯语
#define Comm_Conf_Lang_En  (1)  //英文
#define Comm_Conf_Lang_Fr  (1)  //法语
#define Comm_Conf_Lang_Ur  (1)  //乌尔都语
#define Comm_Conf_Lang_Tu  (1)  //土耳其语
#define Comm_Conf_Lang_Ch  (1)  //简体中文
#define Comm_Conf_Lang_In  (1)  //印尼语
#define Comm_Conf_Lang_Pe  (1)  //波斯语
#define Comm_Conf_Lang_Ge  (1)  //德语
#define Comm_Conf_Lang_Th  (0)  //泰语 no use
#define Comm_Conf_Lang_Ru  (1)  //俄语
#define Comm_Conf_Lang_Hi  (0)  //印地语 no use
#define Comm_Conf_Lang_Ma  (0)  //马来西亚语
#define Comm_Conf_Lang_Uz  (0)  //乌兹别克斯坦语

/*********************************************************************************
                                  语言支持枚举                                       
*********************************************************************************/
enum
{
#if Comm_Conf_Lang_Ar
    comm_language_id_arabic = 0x00,
#endif

#if Comm_Conf_Lang_En
    comm_language_id_english,
#endif

#if Comm_Conf_Lang_Fr
    comm_language_id_french,
#endif

#if Comm_Conf_Lang_Ur
    comm_language_id_urdu,
#endif

#if Comm_Conf_Lang_Tu
    comm_language_id_turkish,
#endif

#if Comm_Conf_Lang_Ch
    comm_language_id_chinese,
#endif

#if Comm_Conf_Lang_In
    comm_language_id_indonesian,
#endif

#if Comm_Conf_Lang_Pe
    comm_language_id_persian,
#endif

#if Comm_Conf_Lang_Ge
    comm_language_id_german,
#endif

#if Comm_Conf_Lang_Th
    comm_language_id_thai,
#endif

#if Comm_Conf_Lang_Ru
    comm_language_id_russian,
#endif

#if Comm_Conf_Lang_Hi
    comm_language_id_hindi,
#endif

#if Comm_Conf_Lang_Ma
    comm_language_id_malaysian,
#endif

#if Comm_Conf_Lang_Uz
    comm_language_id_uzbek,
#endif

    comm_language_id_max,
};
typedef uint8_t comm_language_id_t;

/*********************************************************************************
                                  语言类型数量                                       
*********************************************************************************/
#define Comm_Lang_Num (comm_language_id_max)

comm_language_id_t get_comm_sys_language(void);
void set_comm_sys_language(comm_language_id_t lang_id);
const void *get_lang_txt_with_id(comm_lang_txtid_t txtid);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
