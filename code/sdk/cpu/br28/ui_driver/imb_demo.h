#ifndef __IMB_DEMO_H__
#define __IMB_DEMO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ui/ui/jl_images/FILE_index.h"
#include "ui/lvgl/src/draw/lv_draw_img.h"

void close_fd(void);
void *get_res_fd(void);
void open_fd(char *name);

void lv_close_res(lv_img_dsc_t*img_dst);
void lv_open_res(void *fd, int phyaddr, int offset, struct FileIndex res, lv_img_dsc_t*img_dst);
#ifdef __cplusplus
}
#endif

#endif
