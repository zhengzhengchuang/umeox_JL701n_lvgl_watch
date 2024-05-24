#ifndef __AZKAR_PRAYER_FUNC_H__
#define __AZKAR_PRAYER_FUNC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

uint8_t GetAzkarSecIdx(void);
void SetAzkarSecIdx(uint8_t sec_idx);

uint8_t GetAzkarPrayerSecNum(void);

AzkarTxtLang_t GetAzkarTxtLang(void);
void SetAzkarTxtLang(AzkarTxtLang_t lang);

AzkarEnumType_t GetAzkarType(void);
void SetAzkarType(AzkarEnumType_t type);

uint8_t GetAzkarPrayerReadFreq(uint8_t sec_idx);
const char *GetAzkarPrayerTxtTitle(uint8_t sec_idx);
const char *GetAzkarPrayerTxtContent(uint8_t sec_idx);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
