#include "../lv_watch.h"

void FindDevEnableHandle(void)
{
#if !Vm_Debug_En
    int DevBondFlag = \
        GetVmParaCacheByLabel(\
            vm_label_dev_bond);
    if(!DevBondFlag)
        return;
#endif

    //判断当前是否符合弹出的条件
    if(!MenuSupportPopup())
        return;

    /*勿扰模是否考虑*/
    //......
    
    /*震动、响铃*/
    //......

    /*弹窗*/
    ui_menu_jump(ui_act_id_find_dev);

    return;
}

void FindDevDisableHandle(void)
{
    return;
}

void FindPhoneHandle(void)
{
#if !Vm_Debug_En
    int DevBondFlag = \
        GetVmParaCacheByLabel(\
            vm_label_dev_bond);
    if(!DevBondFlag)
        return;
#endif

    RemoteGetDevEvents(Le_Event_Find_Phone);

    return;
}