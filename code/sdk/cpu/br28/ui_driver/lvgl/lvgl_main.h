#ifndef __LVGL_MAIN_H__
#define __LVGL_MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#define UI_TASK_NAME "ui"

/*自定义UI资源起始地址*/
#define RES_BASE_ADDR (0x600000)

enum
{
    Ui_Msg_Menu_jump = 0x00,
    Ui_Msg_Menu_refresh,
    Ui_Msg_Clock_Pointer_refresh,
};

int lvgl_test_init(void *param);
int post_ui_msg(int *msg, u8 len);
void ui_msg_handle(int *msg, u8 len);
#ifdef __cplusplus
}
#endif

#endif
