#ifndef __LVGL_MAIN_H__
#define __LVGL_MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#define UI_TASK_NAME "ui"

/*自定义UI资源起始地址*/
#define RES_BASE_ADDR (0x0000000)

enum
{
    ui_msg_menu_jump = 0x00,
    ui_msg_menu_refresh,
    ui_msg_clock_pointer_refresh,
    ui_msg_key_handle,
};

int lvgl_test_init(void *param);
int post_ui_msg(int *msg, u8 len);
void ui_msg_handle(int *msg, u8 len);
void ui_key_msg_post(int key_value, int key_event);
#ifdef __cplusplus
}
#endif

#endif
