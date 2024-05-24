#ifndef __DEV_BOND_FUNC_H__
#define __DEV_BOND_FUNC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/ui_menu.h"

#define DevBondCodeLen (18)

typedef struct
{
    u16 vm_mask;

    bool bc_valid;
    u8 bond_code[DevBondCodeLen];
}DevBondCodeInfo_t;
extern DevBondCodeInfo_t BondCode_Info;

void BondCodeInfoParaRead(void);
void BondCodeInfoParaWrite(void);
void BondCodeInfoParaUpdate(void);

void DevBondHandle(void);
void DevUnBondHandle(void);
bool BondCodeCompare(u8 *old_code, u8 *new_code, u8 len);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
