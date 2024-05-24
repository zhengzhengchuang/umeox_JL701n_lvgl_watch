#ifndef __AZKAR_TABLE_H__
#define __AZKAR_TABLE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

#define AzkarTitleNone "NULL"

#define Azkar_Table_MR_Sec   (25)
#define Azkar_Table_ER_Sec   (14)
#define Azkar_Table_APR_Sec  (14)
#define Azkar_Table_HAU_Sec  (5)
#define Azkar_Table_Fas_Sec  (4)
#define Azkar_Table_WWU_Sec  (3)
#define Azkar_Table_Gar_Sec  (3)
#define Azkar_Table_Abu_Sec  (3)
#define Azkar_Table_Home_Sec (7)
#define Azkar_Table_Mos_Sec  (3)
#define Azkar_Table_Ath_Sec  (2)
#define Azkar_Table_Food_Sec (3)
#define Azkar_Table_Tra_Sec  (3)
#define Azkar_Table_OR_Sec   (15)
#define Azkar_Table_Pra_Sec  (9)

#define Azkar_Sec_Max (Azkar_Table_MR_Sec)

enum
{
    AzkarTxtLangEn = 0x00,
    AzkarTxtLangTr,
    AzkarTxtLangAr,

    AzkarTxtLangNum,
};
typedef uint8_t AzkarTxtLang_t;

enum
{
    AzkarEnumTypeMR = 0x00,
    AzkarEnumTypeER,
    AzkarEnumTypeAPR,
    AzkarEnumTypeHAU,
    AzkarEnumTypeFas,
    AzkarEnumTypeWWU,
    AzkarEnumTypeGar,
    AzkarEnumTypeAbu,
    AzkarEnumTypeHome,
    AzkarEnumTypeMos,
    AzkarEnumTypeAth,
    AzkarEnumTypeFood,
    AzkarEnumTypeTra,
    AzkarEnumTypeOR,
    AzkarEnumTypePra,

    AzkarEnumTypeNum,
};
typedef uint8_t AzkarEnumType_t;

extern const char azkar_table_MR_en[\
    Azkar_Table_MR_Sec][600];
extern const char azkar_table_ER_en[\
    Azkar_Table_ER_Sec][600];
extern const char azkar_table_Apr_en[\
    Azkar_Table_APR_Sec][550];
extern const char azkar_table_Hau_en[\
    Azkar_Table_HAU_Sec][370];
extern const char azkar_table_Fas_en[\
    Azkar_Table_Fas_Sec][200];
extern const char azkar_table_Wwu_en[\
    Azkar_Table_WWU_Sec][370];
extern const char azkar_table_Gar_en[\
    Azkar_Table_Gar_Sec][230];
extern const char azkar_table_Abu_en[\
    Azkar_Table_Abu_Sec][160];
extern const char azkar_table_Home_en[\
    Azkar_Table_Home_Sec][160];
extern const char azkar_table_Mos_en[\
    Azkar_Table_Mos_Sec][250];
extern const char azkar_table_Ath_en[\
    Azkar_Table_Ath_Sec][280];
extern const char azkar_table_Food_en[\
    Azkar_Table_Food_Sec][110];
extern const char azkar_table_Tra_en[\
    Azkar_Table_Tra_Sec][850];
extern const char azkar_table_OR_en[\
    Azkar_Table_OR_Sec][560];
extern const char azkar_table_Pra_en[\
    Azkar_Table_Pra_Sec][720];

extern const char azkar_table_MR_tr[\
    Azkar_Table_MR_Sec][410];
extern const char azkar_table_ER_tr[\
    Azkar_Table_ER_Sec][410];
extern const char azkar_table_Apr_tr[\
    Azkar_Table_APR_Sec][420];
extern const char azkar_table_Hau_tr[\
    Azkar_Table_HAU_Sec][250];
extern const char azkar_table_Fas_tr[\
    Azkar_Table_Fas_Sec][150];
extern const char azkar_table_Wwu_tr[\
    Azkar_Table_WWU_Sec][240];
extern const char azkar_table_Gar_tr[\
    Azkar_Table_Gar_Sec][150];
extern const char azkar_table_Abu_tr[\
    Azkar_Table_Abu_Sec][120];
extern const char azkar_table_Home_tr[\
    Azkar_Table_Home_Sec][120];
extern const char azkar_table_Mos_tr[\
    Azkar_Table_Mos_Sec][240];
extern const char azkar_table_Ath_tr[\
    Azkar_Table_Ath_Sec][250];
extern const char azkar_table_Food_tr[\
    Azkar_Table_Food_Sec][100];
extern const char azkar_table_Tra_tr[\
    Azkar_Table_Tra_Sec][610];
extern const char azkar_table_OR_tr[\
    Azkar_Table_OR_Sec][490];
extern const char azkar_table_Pra_tr[\
    Azkar_Table_Pra_Sec][510];

extern const char azkar_table_MR_ar[\
    Azkar_Table_MR_Sec][900];
extern const char azkar_table_ER_ar[\
    Azkar_Table_ER_Sec][900];
extern const char azkar_table_Apr_ar[\
    Azkar_Table_APR_Sec][900];
extern const char azkar_table_Hau_ar[\
    Azkar_Table_HAU_Sec][520];
extern const char azkar_table_Fas_ar[\
    Azkar_Table_Fas_Sec][400];
extern const char azkar_table_Wwu_ar[\
    Azkar_Table_WWU_Sec][450];
extern const char azkar_table_Gar_ar[\
    Azkar_Table_Gar_Sec][350];
extern const char azkar_table_Abu_ar[\
    Azkar_Table_Abu_Sec][250];
extern const char azkar_table_Home_ar[\
    Azkar_Table_Home_Sec][250];
extern const char azkar_table_Mos_ar[\
    Azkar_Table_Mos_Sec][500];
extern const char azkar_table_Ath_ar[\
    Azkar_Table_Ath_Sec][400];
extern const char azkar_table_Food_ar[\
    Azkar_Table_Food_Sec][200];
extern const char azkar_table_Tra_ar[\
    Azkar_Table_Tra_Sec][1150];
extern const char azkar_table_OR_ar[\
    Azkar_Table_OR_Sec][830];
extern const char azkar_table_Pra_ar[\
    Azkar_Table_Pra_Sec][1024];

extern const uint8_t azkar_read_freq_MR[\
    Azkar_Table_MR_Sec];
extern const uint8_t azkar_read_freq_ER[\
    Azkar_Table_ER_Sec];
extern const uint8_t azkar_read_freq_Apr[\
    Azkar_Table_APR_Sec];
extern const uint8_t azkar_read_freq_Hau[\
    Azkar_Table_HAU_Sec];
extern const uint8_t azkar_read_freq_Fas[\
    Azkar_Table_Fas_Sec];
extern const uint8_t azkar_read_freq_Wwu[\
    Azkar_Table_WWU_Sec];
extern const uint8_t azkar_read_freq_Gar[\
    Azkar_Table_Gar_Sec];
extern const uint8_t azkar_read_freq_Abu[\
    Azkar_Table_Abu_Sec];
extern const uint8_t azkar_read_freq_Home[\
    Azkar_Table_Home_Sec];
extern const uint8_t azkar_read_freq_Mos[\
    Azkar_Table_Mos_Sec];
extern const uint8_t azkar_read_freq_Ath[\
    Azkar_Table_Ath_Sec];
extern const uint8_t azkar_read_freq_Food[\
    Azkar_Table_Food_Sec];
extern const uint8_t azkar_read_freq_Tra[\
    Azkar_Table_Tra_Sec];
extern const uint8_t azkar_read_freq_OR[\
    Azkar_Table_OR_Sec];
extern const uint8_t azkar_read_freq_Pra[\
    Azkar_Table_Pra_Sec];

extern const char azkar_title_MR_en_tr[\
    Azkar_Table_MR_Sec][5];
extern const char azkar_title_ER_en_tr[\
    Azkar_Table_ER_Sec][5];
extern const char azkar_title_Apr_en_tr[\
    Azkar_Table_APR_Sec][5];
extern const char azkar_title_Hau_en_tr[\
    Azkar_Table_HAU_Sec][45];
extern const char azkar_title_Fas_en_tr[\
    Azkar_Table_Fas_Sec][40];
extern const char azkar_title_Wwu_en_tr[\
    Azkar_Table_WWU_Sec][5];
extern const char azkar_title_Gar_en_tr[\
    Azkar_Table_Gar_Sec][30];
extern const char azkar_title_Abu_en_tr[\
    Azkar_Table_Abu_Sec][30];
extern const char azkar_title_Home_en_tr[\
    Azkar_Table_Home_Sec][30];
extern const char azkar_title_Mos_en_tr[\
    Azkar_Table_Mos_Sec][40];
extern const char azkar_title_Ath_en_tr[\
    Azkar_Table_Ath_Sec][25];
extern const char azkar_title_Food_en_tr[\
    Azkar_Table_Food_Sec][40];
extern const char azkar_title_Tra_en_tr[\
    Azkar_Table_Tra_Sec][50];
extern const char azkar_title_OR_en_tr[\
    Azkar_Table_OR_Sec][55];
extern const char azkar_title_Pra_en_tr[\
    Azkar_Table_Pra_Sec][60];

extern const char azkar_title_MR_ar[\
    Azkar_Table_MR_Sec][5];
extern const char azkar_title_ER_ar[\
    Azkar_Table_ER_Sec][5];
extern const char azkar_title_Apr_ar[\
    Azkar_Table_APR_Sec][5];
extern const char azkar_title_Hau_ar[\
    Azkar_Table_HAU_Sec][65];
extern const char azkar_title_Fas_ar[\
    Azkar_Table_Fas_Sec][40];
extern const char azkar_title_Wwu_ar[\
    Azkar_Table_WWU_Sec][5];
extern const char azkar_title_Gar_ar[\
    Azkar_Table_Gar_Sec][30];
extern const char azkar_title_Abu_ar[\
    Azkar_Table_Abu_Sec][45];
extern const char azkar_title_Home_ar[\
    Azkar_Table_Home_Sec][50];
extern const char azkar_title_Mos_ar[\
    Azkar_Table_Mos_Sec][60];
extern const char azkar_title_Ath_ar[\
    Azkar_Table_Ath_Sec][45];
extern const char azkar_title_Food_ar[\
    Azkar_Table_Food_Sec][45];
extern const char azkar_title_Tra_ar[\
    Azkar_Table_Tra_Sec][45];
extern const char azkar_title_OR_ar[\
    Azkar_Table_OR_Sec][65];
extern const char azkar_title_Pra_ar[\
    Azkar_Table_Pra_Sec][80];
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
