#include "../lv_watch.h"

static uint8_t azkar_sec_idx = 0;
static AzkarTxtLang_t azkar_lang = \
    AzkarTxtLangNum;
static AzkarEnumType_t azkar_type = \
    AzkarEnumTypeNum;

uint8_t GetAzkarSecIdx(void)
{
    return azkar_sec_idx;
}

void SetAzkarSecIdx(uint8_t sec_idx)
{
    azkar_sec_idx = sec_idx;

    return;
}

AzkarTxtLang_t GetAzkarTxtLang(void)
{
    return azkar_lang;
}

void SetAzkarTxtLang(AzkarTxtLang_t lang)
{
    azkar_lang = lang;

    return;
}

AzkarEnumType_t GetAzkarType(void)
{
    return azkar_type;
}

void SetAzkarType(AzkarEnumType_t type)
{
    azkar_type = type;

    return;
}

const char *GetAzkarPrayerTxtContent(uint8_t sec_idx)
{
    if(azkar_type >= \
        AzkarEnumTypeNum)
        return NULL;

    if(azkar_lang >= \
        AzkarTxtLangNum)
        return NULL;

    static const char *zakar_table_ctx;

    zakar_table_ctx = NULL;

    if(azkar_type == AzkarEnumTypeMR)
    {
        if(sec_idx >= \
            Azkar_Table_MR_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangEn)
            zakar_table_ctx = \
                azkar_table_MR_en[sec_idx];
        else if(azkar_lang == AzkarTxtLangTr)
            zakar_table_ctx = \
                azkar_table_MR_tr[sec_idx];
        else if(azkar_lang == AzkarTxtLangAr)
            zakar_table_ctx = \
                azkar_table_MR_ar[sec_idx];
    }else if(azkar_type == AzkarEnumTypeER)
    {
        if(sec_idx >= \
            Azkar_Table_ER_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangEn)
            zakar_table_ctx = \
                azkar_table_ER_en[sec_idx];
        else if(azkar_lang == AzkarTxtLangTr)
            zakar_table_ctx = \
                azkar_table_ER_tr[sec_idx];
        else if(azkar_lang == AzkarTxtLangAr)
            zakar_table_ctx = \
                azkar_table_ER_ar[sec_idx];
    }else if(azkar_type == AzkarEnumTypeAPR)
    {
        if(sec_idx >= \
            Azkar_Table_APR_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangEn)
            zakar_table_ctx = \
                azkar_table_Apr_en[sec_idx];
        else if(azkar_lang == AzkarTxtLangTr)
            zakar_table_ctx = \
                azkar_table_Apr_tr[sec_idx];
        else if(azkar_lang == AzkarTxtLangAr)
            zakar_table_ctx = \
                azkar_table_Apr_ar[sec_idx];
    }else if(azkar_type == AzkarEnumTypeHAU)
    {
        if(sec_idx >= \
            Azkar_Table_HAU_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangEn)
            zakar_table_ctx = \
                azkar_table_Hau_en[sec_idx];
        else if(azkar_lang == AzkarTxtLangTr)
            zakar_table_ctx = \
                azkar_table_Hau_tr[sec_idx];
        else if(azkar_lang == AzkarTxtLangAr)
            zakar_table_ctx = \
                azkar_table_Hau_ar[sec_idx];
    }else if(azkar_type == AzkarEnumTypeFas)
    {
        if(sec_idx >= \
            Azkar_Table_Fas_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangEn)
            zakar_table_ctx = \
                azkar_table_Fas_en[sec_idx];
        else if(azkar_lang == AzkarTxtLangTr)
            zakar_table_ctx = \
                azkar_table_Fas_tr[sec_idx];
        else if(azkar_lang == AzkarTxtLangAr)
            zakar_table_ctx = \
                azkar_table_Fas_ar[sec_idx];
    }else if(azkar_type == AzkarEnumTypeWWU)
    {
        if(sec_idx >= \
            Azkar_Table_WWU_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangEn)
            zakar_table_ctx = \
                azkar_table_Wwu_en[sec_idx];
        else if(azkar_lang == AzkarTxtLangTr)
            zakar_table_ctx = \
                azkar_table_Wwu_tr[sec_idx];
        else if(azkar_lang == AzkarTxtLangAr)
            zakar_table_ctx = \
                azkar_table_Wwu_ar[sec_idx];
    }else if(azkar_type == AzkarEnumTypeGar)
    {
        if(sec_idx >= \
            Azkar_Table_Gar_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangEn)
            zakar_table_ctx = \
                azkar_table_Gar_en[sec_idx];
        else if(azkar_lang == AzkarTxtLangTr)
            zakar_table_ctx = \
                azkar_table_Gar_tr[sec_idx];
        else if(azkar_lang == AzkarTxtLangAr)
            zakar_table_ctx = \
                azkar_table_Gar_ar[sec_idx];
    }else if(azkar_type == AzkarEnumTypeAbu)
    {
        if(sec_idx >= \
            Azkar_Table_Abu_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangEn)
            zakar_table_ctx = \
                azkar_table_Abu_en[sec_idx];
        else if(azkar_lang == AzkarTxtLangTr)
            zakar_table_ctx = \
                azkar_table_Abu_tr[sec_idx];
        else if(azkar_lang == AzkarTxtLangAr)
            zakar_table_ctx = \
                azkar_table_Abu_ar[sec_idx];
    }else if(azkar_type == AzkarEnumTypeHome)
    {
        if(sec_idx >= \
            Azkar_Table_Home_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangEn)
            zakar_table_ctx = \
                azkar_table_Home_en[sec_idx];
        else if(azkar_lang == AzkarTxtLangTr)
            zakar_table_ctx = \
                azkar_table_Home_tr[sec_idx];
        else if(azkar_lang == AzkarTxtLangAr)
            zakar_table_ctx = \
                azkar_table_Home_ar[sec_idx];
    }else if(azkar_type == AzkarEnumTypeMos)
    {
        if(sec_idx >= \
            Azkar_Table_Mos_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangEn)
            zakar_table_ctx = \
                azkar_table_Mos_en[sec_idx];
        else if(azkar_lang == AzkarTxtLangTr)
            zakar_table_ctx = \
                azkar_table_Mos_tr[sec_idx];
        else if(azkar_lang == AzkarTxtLangAr)
            zakar_table_ctx = \
                azkar_table_Mos_ar[sec_idx];
    }else if(azkar_type == AzkarEnumTypeAth)
    {
        if(sec_idx >= \
            Azkar_Table_Ath_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangEn)
            zakar_table_ctx = \
                azkar_table_Ath_en[sec_idx];
        else if(azkar_lang == AzkarTxtLangTr)
            zakar_table_ctx = \
                azkar_table_Ath_tr[sec_idx];
        else if(azkar_lang == AzkarTxtLangAr)
            zakar_table_ctx = \
                azkar_table_Ath_ar[sec_idx];
    }else if(azkar_type == AzkarEnumTypeFood)
    {
        if(sec_idx >= \
            Azkar_Table_Food_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangEn)
            zakar_table_ctx = \
                azkar_table_Food_en[sec_idx];
        else if(azkar_lang == AzkarTxtLangTr)
            zakar_table_ctx = \
                azkar_table_Food_tr[sec_idx];
        else if(azkar_lang == AzkarTxtLangAr)
            zakar_table_ctx = \
                azkar_table_Food_ar[sec_idx];
    }else if(azkar_type == AzkarEnumTypeTra)
    {
        if(sec_idx >= \
            Azkar_Table_Tra_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangEn)
            zakar_table_ctx = \
                azkar_table_Tra_en[sec_idx];
        else if(azkar_lang == AzkarTxtLangTr)
            zakar_table_ctx = \
                azkar_table_Tra_tr[sec_idx];
        else if(azkar_lang == AzkarTxtLangAr)
            zakar_table_ctx = \
                azkar_table_Tra_ar[sec_idx];
    }else if(azkar_type == AzkarEnumTypeOR)
    {
        if(sec_idx >= \
            Azkar_Table_OR_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangEn)
            zakar_table_ctx = \
                azkar_table_OR_en[sec_idx];
        else if(azkar_lang == AzkarTxtLangTr)
            zakar_table_ctx = \
                azkar_table_OR_tr[sec_idx];
        else if(azkar_lang == AzkarTxtLangAr)
            zakar_table_ctx = \
                azkar_table_OR_ar[sec_idx];
    }else if(azkar_type == AzkarEnumTypePra)
    {
        if(sec_idx >= \
            Azkar_Table_Pra_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangEn)
            zakar_table_ctx = \
                azkar_table_Pra_en[sec_idx];
        else if(azkar_lang == AzkarTxtLangTr)
            zakar_table_ctx = \
                azkar_table_Pra_tr[sec_idx];
        else if(azkar_lang == AzkarTxtLangAr)
            zakar_table_ctx = \
                azkar_table_Pra_ar[sec_idx];
    }

    return zakar_table_ctx;
}

uint8_t GetAzkarPrayerReadFreq(uint8_t sec_idx)
{
    if(azkar_type >= \
        AzkarEnumTypeNum)
        return 1;

    if(azkar_type == AzkarEnumTypeMR)
    {
        if(sec_idx >= \
            Azkar_Table_MR_Sec)
            return 1;

        return azkar_read_freq_MR[sec_idx];
    }else if(azkar_type == AzkarEnumTypeER)
    {
        if(sec_idx >= \
            Azkar_Table_ER_Sec)
            return 1;

        return azkar_read_freq_ER[sec_idx];
    }else if(azkar_type == AzkarEnumTypeAPR)
    {
        if(sec_idx >= \
            Azkar_Table_APR_Sec)
            return 1;

        return azkar_read_freq_Apr[sec_idx];
    }else if(azkar_type == AzkarEnumTypeHAU)
    {
        if(sec_idx >= \
            Azkar_Table_HAU_Sec)
            return 1;

        return azkar_read_freq_Hau[sec_idx];
    }else if(azkar_type == AzkarEnumTypeFas)
    {
        if(sec_idx >= \
            Azkar_Table_Fas_Sec)
            return 1;

        return azkar_read_freq_Fas[sec_idx];
    }else if(azkar_type == AzkarEnumTypeWWU)
    {
        if(sec_idx >= \
            Azkar_Table_WWU_Sec)
            return 1;

        return azkar_read_freq_Wwu[sec_idx];
    }else if(azkar_type == AzkarEnumTypeGar)
    {
        if(sec_idx >= \
            Azkar_Table_Gar_Sec)
            return 1;

        return azkar_read_freq_Gar[sec_idx];
    }else if(azkar_type == AzkarEnumTypeAbu)
    {
        if(sec_idx >= \
            Azkar_Table_Abu_Sec)
            return 1;

        return azkar_read_freq_Abu[sec_idx];
    }else if(azkar_type == AzkarEnumTypeHome)
    {
        if(sec_idx >= \
            Azkar_Table_Home_Sec)
            return 1;

        return azkar_read_freq_Home[sec_idx];
    }else if(azkar_type == AzkarEnumTypeMos)
    {
        if(sec_idx >= \
            Azkar_Table_Mos_Sec)
            return 1;

        return azkar_read_freq_Mos[sec_idx];
    }else if(azkar_type == AzkarEnumTypeAth)
    {
        if(sec_idx >= \
            Azkar_Table_Ath_Sec)
            return 1;

        return azkar_read_freq_Ath[sec_idx];
    }else if(azkar_type == AzkarEnumTypeFood)
    {
        if(sec_idx >= \
            Azkar_Table_Food_Sec)
            return 1;

        return azkar_read_freq_Food[sec_idx];
    }else if(azkar_type == AzkarEnumTypeTra)
    {
        if(sec_idx >= \
            Azkar_Table_Tra_Sec)
            return 1;

        return azkar_read_freq_Tra[sec_idx];
    }else if(azkar_type == AzkarEnumTypeOR)
    {
        if(sec_idx >= \
            Azkar_Table_OR_Sec)
            return 1;

        return azkar_read_freq_OR[sec_idx];
    }else if(azkar_type == AzkarEnumTypePra)
    {
        if(sec_idx >= \
            Azkar_Table_Pra_Sec)
            return 1;

        return azkar_read_freq_Pra[sec_idx];
    }

    return 1;
}

static bool AzkarPrayerTitleIsValid(const char *str)
{
    if(!str) return false;

    if(!strcmp(str, AzkarTitleNone))
        return false;
  
    return true;
}

const char *GetAzkarPrayerTxtTitle(uint8_t sec_idx)
{
    if(azkar_type >= \
        AzkarEnumTypeNum)
        return NULL;

    if(azkar_lang >= \
        AzkarTxtLangNum)
        return NULL;
    uint8_t title_lang_id;
    if(azkar_lang == \
        AzkarTxtLangAr)
        title_lang_id = 1;
    else
        title_lang_id = 0;

    static const char *azkar_title_ctx;

    azkar_title_ctx = NULL;

    if(azkar_type == AzkarEnumTypeMR)
    {
        if(sec_idx >= \
            Azkar_Table_MR_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangAr)
            azkar_title_ctx = \
                azkar_title_MR_ar[sec_idx];
        else
            azkar_title_ctx = \
                azkar_title_MR_en_tr[sec_idx];
    }else if(azkar_type == AzkarEnumTypeER)
    {
        if(sec_idx >= \
            Azkar_Table_ER_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangAr)
            azkar_title_ctx = \
                azkar_title_ER_ar[sec_idx];
        else
            azkar_title_ctx = \
                azkar_title_ER_en_tr[sec_idx];
    }else if(azkar_type == AzkarEnumTypeAPR)
    {
        if(sec_idx >= \
            Azkar_Table_APR_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangAr)
            azkar_title_ctx = \
                azkar_title_Apr_ar[sec_idx];
        else
            azkar_title_ctx = \
                azkar_title_Apr_en_tr[sec_idx];
    }else if(azkar_type == AzkarEnumTypeHAU)
    {
        if(sec_idx >= \
            Azkar_Table_HAU_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangAr)
            azkar_title_ctx = \
                azkar_title_Hau_ar[sec_idx];
        else
            azkar_title_ctx = \
                azkar_title_Hau_en_tr[sec_idx];
    }else if(azkar_type == AzkarEnumTypeFas)
    {
        if(sec_idx >= \
            Azkar_Table_Fas_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangAr)
            azkar_title_ctx = \
                azkar_title_Fas_ar[sec_idx];
        else
            azkar_title_ctx = \
                azkar_title_Fas_en_tr[sec_idx];
    }else if(azkar_type == AzkarEnumTypeWWU)
    {
        if(sec_idx >= \
            Azkar_Table_WWU_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangAr)
            azkar_title_ctx = \
                azkar_title_Wwu_ar[sec_idx];
        else
            azkar_title_ctx = \
                azkar_title_Wwu_en_tr[sec_idx];
    }else if(azkar_type == AzkarEnumTypeGar)
    {
        if(sec_idx >= \
            Azkar_Table_Gar_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangAr)
            azkar_title_ctx = \
                azkar_title_Gar_ar[sec_idx];
        else
            azkar_title_ctx = \
                azkar_title_Gar_en_tr[sec_idx];
    }else if(azkar_type == AzkarEnumTypeAbu)
    {
        if(sec_idx >= \
            Azkar_Table_Abu_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangAr)
            azkar_title_ctx = \
                azkar_title_Abu_ar[sec_idx];
        else
            azkar_title_ctx = \
                azkar_title_Abu_en_tr[sec_idx];
    }else if(azkar_type == AzkarEnumTypeHome)
    {
        if(sec_idx >= \
            Azkar_Table_Home_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangAr)
            azkar_title_ctx = \
                azkar_title_Home_ar[sec_idx];
        else
            azkar_title_ctx = \
                azkar_title_Home_en_tr[sec_idx];
    }else if(azkar_type == AzkarEnumTypeMos)
    {
        if(sec_idx >= \
            Azkar_Table_Mos_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangAr)
            azkar_title_ctx = \
                azkar_title_Mos_ar[sec_idx];
        else
            azkar_title_ctx = \
                azkar_title_Mos_en_tr[sec_idx];
    }else if(azkar_type == AzkarEnumTypeAth)
    {
        if(sec_idx >= \
            Azkar_Table_Ath_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangAr)
            azkar_title_ctx = \
                azkar_title_Ath_ar[sec_idx];
        else
            azkar_title_ctx = \
                azkar_title_Ath_en_tr[sec_idx];
    }else if(azkar_type == AzkarEnumTypeFood)
    {
        if(sec_idx >= \
            Azkar_Table_Food_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangAr)
            azkar_title_ctx = \
                azkar_title_Food_ar[sec_idx];
        else
            azkar_title_ctx = \
                azkar_title_Food_en_tr[sec_idx];
    }else if(azkar_type == AzkarEnumTypeTra)
    {
        if(sec_idx >= \
            Azkar_Table_Tra_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangAr)
            azkar_title_ctx = \
                azkar_title_Tra_ar[sec_idx];
        else
            azkar_title_ctx = \
                azkar_title_Tra_en_tr[sec_idx];
    }else if(azkar_type == AzkarEnumTypeOR)
    {
        if(sec_idx >= \
            Azkar_Table_OR_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangAr)
            azkar_title_ctx = \
                azkar_title_OR_ar[sec_idx];
        else
            azkar_title_ctx = \
                azkar_title_OR_en_tr[sec_idx];
    }else if(azkar_type == AzkarEnumTypePra)
    {
        if(sec_idx >= \
            Azkar_Table_Pra_Sec)
            return NULL;

        if(azkar_lang == AzkarTxtLangAr)
            azkar_title_ctx = \
                azkar_title_Pra_ar[sec_idx];
        else
            azkar_title_ctx = \
                azkar_title_Pra_en_tr[sec_idx];
    }

    if(!AzkarPrayerTitleIsValid(\
        azkar_title_ctx))
        return NULL;


    return azkar_title_ctx;
}

uint8_t GetAzkarPrayerSecNum(void)
{
    uint8_t section_num = 0;

    if(azkar_type >= \
        AzkarEnumTypeNum)
        return section_num;

    if(azkar_type == AzkarEnumTypeMR)
    {
        section_num = \
            Azkar_Table_MR_Sec;
    }else if(azkar_type == AzkarEnumTypeER)
    {
        section_num = \
            Azkar_Table_ER_Sec;
    }else if(azkar_type == AzkarEnumTypeAPR)
    {
        section_num = \
            Azkar_Table_APR_Sec;
    }else if(azkar_type == AzkarEnumTypeHAU)
    {
        section_num = \
            Azkar_Table_HAU_Sec;
    }else if(azkar_type == AzkarEnumTypeFas)
    {
        section_num = \
            Azkar_Table_Fas_Sec;
    }else if(azkar_type == AzkarEnumTypeWWU)
    {
        section_num = \
            Azkar_Table_WWU_Sec;
    }else if(azkar_type == AzkarEnumTypeGar)
    {
        section_num = \
            Azkar_Table_Gar_Sec;
    }else if(azkar_type == AzkarEnumTypeAbu)
    {
        section_num = \
            Azkar_Table_Abu_Sec;
    }else if(azkar_type == AzkarEnumTypeHome)
    {
        section_num = \
            Azkar_Table_Home_Sec;
    }else if(azkar_type == AzkarEnumTypeMos)
    {
        section_num = \
            Azkar_Table_Mos_Sec;
    }else if(azkar_type == AzkarEnumTypeAth)
    {
        section_num = \
            Azkar_Table_Ath_Sec;
    }else if(azkar_type == AzkarEnumTypeFood)
    {
        section_num = \
            Azkar_Table_Food_Sec;
    }else if(azkar_type == AzkarEnumTypeTra)
    {
        section_num = \
            Azkar_Table_Tra_Sec;
    }else if(azkar_type == AzkarEnumTypeOR)
    {
        section_num = \
            Azkar_Table_OR_Sec;
    }else if(azkar_type == AzkarEnumTypePra)
    {
        section_num = \
            Azkar_Table_Pra_Sec;
    }

    return section_num;
}