#include "../lv_watch.h"

#define GM_ALGO_VM_MASK (0x55aa)

GMalgokeyInfo_t Galgo_info;

static const GMalgokeyInfo_t InitInfo = {
    .algo_key = {0},
};

void GalgoInfoParaRead(void)
{
    int vm_op_len = \
        sizeof(GMalgokeyInfo_t);

    int ret = syscfg_read(CFG_GM_ALGO_KEY_INFO, \
        &Galgo_info, vm_op_len);
    if(ret != vm_op_len || \
        Galgo_info.vm_mask != GM_ALGO_VM_MASK)
    {
        memcpy(&Galgo_info, &InitInfo, \
            vm_op_len);

        Galgo_info.vm_mask = \
            GM_ALGO_VM_MASK;

        GalgoInfoParaUpdate();
    }

    return;
}

void GalgoInfoParaWrite(void)
{
    int vm_op_len = \
        sizeof(GMalgokeyInfo_t);
    
    for(u8 i = 0; i < 3; i++)
    {
        int ret = syscfg_write(CFG_GM_ALGO_KEY_INFO, \
            &Galgo_info, vm_op_len);
        if(ret == vm_op_len)
            break;
    }

    return;
}

void GalgoInfoParaUpdate(void)
{
    GalgoInfoParaWrite();

    return;
}
