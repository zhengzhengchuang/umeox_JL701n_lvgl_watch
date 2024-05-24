#include "../lv_watch.h"

#define MSG_NOTIFY_VM_MASK (0x55ac)

MsgNotifyInfoPara_t Notify_Info;

static const MsgNotifyInfoPara_t InitInfo = {
    .sw_union.info = 0x00FF,
};

static uint8_t QueryId;
uint8_t GetQueryId(void)
{
    return QueryId;
}

void SetQueryId(uint8_t id)
{
    QueryId = id;
    return;
}

u8 GetMessageNum(void)
{
    u8 num = \
        VmMessageItemNum();

    return num;
}

bool GetVmFlashMessageCtx(u8 idx)
{
    bool ret = \
        VmMessageCtxByIdx(idx);
    
    return ret;
}

static void VmFlashMessageCtxWrite(\
    vm_message_ctx_t *w_ctx)
{
    VmMessageCtxFlashSave(w_ctx);
    
    return;
}

static void MessageNotifyIsOnHandle(void)
{
    int dnd_state = \
        GetVmParaCacheByLabel(vm_label_dnd_state);
    if(dnd_state == dnd_state_enable)
        return;

    //当前菜单是否支持弹窗
    if(!MenuSupportPopup())
        return;

    u8 num = GetMessageNum();
    if(num == 0)
        return;

    //震动
    motor_run(1, def_motor_duty);

    SetQueryId(num - 1);
    ui_menu_jump(ui_act_id_msg_detail);

    return;
}

void MsgNotifyProcess(vm_message_ctx_t *w_ctx)
{
#if !Vm_Debug_En
    int DevBondFlag = \
        GetVmParaCacheByLabel(\
            vm_label_dev_bond);
    if(!DevBondFlag)
        return;
#endif

    if(w_ctx == NULL) return;

    message_type_t type = \
        w_ctx->message_type;
    
    /*暂时屏蔽掉Ble通话*/
    if(type == \
        message_type_phone)
        return;

    if(type >= \
        message_type_unknown)
        return;

    /*消息推送开关*/
    uint32_t info = \
        Notify_Info.sw_union.info;
    if(!((info >> type) & 0x1))
        return;

    VmFlashMessageCtxWrite(w_ctx);

    MessageNotifyIsOnHandle();

    return;
}

void MsgNotifyInfoParaRead(void)
{
    int vm_op_len = \
        sizeof(MsgNotifyInfoPara_t);

    int ret = syscfg_read(CFG_MSG_NOTIFY_PARA_INFO, \
        &Notify_Info, vm_op_len);
    if(ret != vm_op_len || \
        Notify_Info.vm_mask != MSG_NOTIFY_VM_MASK)
    {
        memcpy(&Notify_Info, &InitInfo, \
            vm_op_len);

        Notify_Info.vm_mask = \
            MSG_NOTIFY_VM_MASK;

        MsgNotifyInfoParaUpdate();
    }

    return;
}

void MsgNotifyInfoParaWrite(void)
{
    int vm_op_len = \
        sizeof(MsgNotifyInfoPara_t);
    
    for(u8 i = 0; i < 3; i++)
    {
        int ret = syscfg_write(CFG_MSG_NOTIFY_PARA_INFO, \
            &Notify_Info, vm_op_len);
        if(ret == vm_op_len)
            break;
    }

    return;
}

void MsgNotifyInfoParaUpdate(void)
{
    MsgNotifyInfoParaWrite();

    return;
}

