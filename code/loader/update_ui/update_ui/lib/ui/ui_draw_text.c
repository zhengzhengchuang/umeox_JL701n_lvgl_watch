
#include "ui/lcd_spi/lcd_drive.h"
#include "ui/text_matrix.h"
#include "typedef.h"
#include "ui/ui_mask.h"
#include "ui/ui_basic.h"


const u8 update_text_buf[9][20]={
    /*0*/   "�ȴ�����",
    /*1*/   "�ȴ�����",
    /*2*/   "�볢��ʹ������",
    /*3*/   "����ֶ���������",
    /*4*/   "��ַ:",
    /*5*/   "����",
    /*6*/   ".",
    /*7*/   "��������",
    /*8*/   "����ǿ������",
};
/* disp_lcd_init(&ui_cfg_data); */
void bt_addr_to_str(u8*str_buf,u8*addr)
{
    int offset = 0;
    for(int i =0;i<6;i++){
        sprintf(&str_buf[offset], "%02X", addr[i]);
        offset += 2;
        if(i != 5){
            sprintf(&str_buf[offset], ":", addr[i]);
            offset += 1;
        }
    }
}

AT_UI_SIM_RAM
void ui_draw_text(int x, int y,int width,int height,int color, u8 *str,u8 str_len)
{
	struct rect draw;
	struct rect rect={x,y,width,height};
	int i;
	memcpy(&draw, &rect, sizeof(struct rect));
	 //printf("rect (%d, %d, %d, %d)\n", rect.left, rect.left + rect.width - 1, rect.top, rect.top + rect.height - 1);
	int block = disp_get_buffer_line(rect.width);
	 //printf("block : %d\n", block);
	for (i = 0; i < (rect.height + block - 1) / block; i++) {
		draw.top = rect.top + block * i;
		draw.height = (rect.top + rect.height - draw.top) > block ? block : (rect.top + rect.height - draw.top);
        //printf("draw : (%d %d %d %d)\n",draw.left,draw.top,draw.width,draw.height );
		disp_set_buffer_rect(&draw);
		disp_buffer_clear(&draw, 0x0000);
        draw_text(&draw, x, y, str,str_len, color);
		disp_buffer_flush(&draw, disp_get_buffer_addr());
	}
}
AT_UI_SIM_RAM
void ui_draw_rect(int x, int y,int width,int height,int color)
{
	struct rect draw;
	struct rect rect={x,y,width,height};
	int i;
	memcpy(&draw, &rect, sizeof(struct rect));
//	 printf("rect (%d, %d, %d, %d)\n", rect.left, rect.left + rect.width - 1, rect.top, rect.top + rect.height - 1);
	int block = disp_get_buffer_line(rect.width);
//	 printf("block : %d\n", block);
	for (i = 0; i < (rect.height + block - 1) / block; i++) {
		draw.top = rect.top + block * i;
		draw.height = (rect.top + rect.height - draw.top) > block ? block : (rect.top + rect.height - draw.top);
//        printf("draw : (%d %d %d %d)\n",draw.left,draw.top,draw.width,draw.height );
		disp_set_buffer_rect(&draw);
		disp_buffer_clear(&draw, color);
		disp_buffer_flush(&draw, disp_get_buffer_addr());
	}
}


