#ifndef __LANG_TABLE_H__
#define __LANG_TABLE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "lang_conf.h"
#include "lang_txtid.h"
#include "../include/ui_menu.h"

/*********************************************************************************
                                  语言字符串长度                                       
*********************************************************************************/
#define Comm_Lang_Str_Len (100)

/*********************************************************************************
                                  语言字符串数量                                       
*********************************************************************************/
#define Comm_Lang_Str_Num (lang_txtid_max)

extern const uint8_t lang_str_table[Comm_Lang_Num]\
    [Comm_Lang_Str_Num][Comm_Lang_Str_Len];
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
