#include "../lv_watch.h"

#define BOND_CODE_VM_MASK (0x55aa)

DevBondCodeInfo_t BondCode_Info;

static const DevBondCodeInfo_t InitInfo = {
    .bc_valid = false,
    .bond_code = {0},
};

//设备绑定操作
void DevBondHandle(void)
{
    return;
}

//设备解绑操作
void DevUnBondHandle(void)
{
    //定个延时解绑

    return;
}

//相同返回true，不同返回false
bool BondCodeCompare(u8 *old_code, u8 *new_code, u8 len)
{
    for(u8 i = 0; i < len; i++)
    {
        if(old_code[i] != new_code[i])
            return false;
    }

    return true;
}

void BondCodeInfoParaRead(void)
{
    int vm_op_len = \
        sizeof(DevBondCodeInfo_t);

    int ret = syscfg_read(CFG_DEV_BOND_CODE_INFO, \
        &BondCode_Info, vm_op_len);
    if(ret != vm_op_len || \
        BondCode_Info.vm_mask != BOND_CODE_VM_MASK)
    {
        memcpy(&BondCode_Info, &InitInfo, \
            vm_op_len);

        BondCode_Info.vm_mask = \
            BOND_CODE_VM_MASK;

        BondCodeInfoParaUpdate();
    }

    return;
}

void BondCodeInfoParaWrite(void)
{
    int vm_op_len = \
        sizeof(DevBondCodeInfo_t);
    
    for(u8 i = 0; i < 3; i++)
    {
        int ret = syscfg_write(CFG_DEV_BOND_CODE_INFO, \
            &BondCode_Info, vm_op_len);
        if(ret == vm_op_len)
            break;
    }

    return;
}

void BondCodeInfoParaUpdate(void)
{
    BondCodeInfoParaWrite();

    return;
}
