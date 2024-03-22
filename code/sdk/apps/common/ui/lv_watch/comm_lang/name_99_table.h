#ifndef __NAME_99_TABLE_H__
#define __NAME_99_TABLE_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "lang_conf.h"
#include "../include/ui_menu.h"

/*********************************************************************************
                                  词条指令                                       
*********************************************************************************/
enum
{
    lang_txt_al_name_00 = 0x00,
    lang_txt_al_name_01,
    lang_txt_al_name_02,
    lang_txt_al_name_03,
    lang_txt_al_name_04,
    lang_txt_al_name_05,
    lang_txt_al_name_06,
    lang_txt_al_name_07,
    lang_txt_al_name_08,
    lang_txt_al_name_09,
    lang_txt_al_name_10,
    lang_txt_al_name_11,
    lang_txt_al_name_12,
    lang_txt_al_name_13,
    lang_txt_al_name_14,
    lang_txt_al_name_15,
    lang_txt_al_name_16,
    lang_txt_al_name_17,
    lang_txt_al_name_18,
    lang_txt_al_name_19,
    lang_txt_al_name_20,
    lang_txt_al_name_21,
    lang_txt_al_name_22,
    lang_txt_al_name_23,
    lang_txt_al_name_24,
    lang_txt_al_name_25,
    lang_txt_al_name_26,
    lang_txt_al_name_27,
    lang_txt_al_name_28,
    lang_txt_al_name_29,
    lang_txt_al_name_30,
    lang_txt_al_name_31,
    lang_txt_al_name_32,
    lang_txt_al_name_33,
    lang_txt_al_name_34,
    lang_txt_al_name_35,
    lang_txt_al_name_36,
    lang_txt_al_name_37,
    lang_txt_al_name_38,
    lang_txt_al_name_39,
    lang_txt_al_name_40,
    lang_txt_al_name_41,
    lang_txt_al_name_42,
    lang_txt_al_name_43,
    lang_txt_al_name_44,
    lang_txt_al_name_45,
    lang_txt_al_name_46,
    lang_txt_al_name_47,
    lang_txt_al_name_48,
    lang_txt_al_name_49,
    lang_txt_al_name_50,
    lang_txt_al_name_51,
    lang_txt_al_name_52,
    lang_txt_al_name_53,
    lang_txt_al_name_54,
    lang_txt_al_name_55,
    lang_txt_al_name_56,
    lang_txt_al_name_57,
    lang_txt_al_name_58,
    lang_txt_al_name_59,
    lang_txt_al_name_60,
    lang_txt_al_name_61,
    lang_txt_al_name_62,
    lang_txt_al_name_63,
    lang_txt_al_name_64,
    lang_txt_al_name_65,
    lang_txt_al_name_66,
    lang_txt_al_name_67,
    lang_txt_al_name_68,
    lang_txt_al_name_69,
    lang_txt_al_name_70,
    lang_txt_al_name_71,
    lang_txt_al_name_72,
    lang_txt_al_name_73,
    lang_txt_al_name_74,
    lang_txt_al_name_75,
    lang_txt_al_name_76,
    lang_txt_al_name_77,
    lang_txt_al_name_78,
    lang_txt_al_name_79,
    lang_txt_al_name_80,
    lang_txt_al_name_81,
    lang_txt_al_name_82,
    lang_txt_al_name_83,
    lang_txt_al_name_84,
    lang_txt_al_name_85,
    lang_txt_al_name_86,
    lang_txt_al_name_87,
    lang_txt_al_name_88,
    lang_txt_al_name_89,
    lang_txt_al_name_90,
    lang_txt_al_name_91,
    lang_txt_al_name_92,
    lang_txt_al_name_93,
    lang_txt_al_name_94,
    lang_txt_al_name_95,
    lang_txt_al_name_96,
    lang_txt_al_name_97,
    lang_txt_al_name_98,

    lang_txt_al_name_max,
};

/*********************************************************************************
                                  真主名数量                                       
*********************************************************************************/
#define Al_Name_Num \
    lang_txt_al_name_max

/*********************************************************************************
                                  真主名字符串长度                                       
*********************************************************************************/
#define Al_Name_Str_Len (30)

/*********************************************************************************
                                  真主名解释字符串长度                                       
*********************************************************************************/
#define Al_Name_Ex_Str_Len (300)

extern const char al_name_str_table[Comm_Lang_Num]\
    [Al_Name_Num][Al_Name_Str_Len];
extern const char al_name_ex_str_table[Comm_Lang_Num]\
    [Al_Name_Num][Al_Name_Ex_Str_Len];
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
