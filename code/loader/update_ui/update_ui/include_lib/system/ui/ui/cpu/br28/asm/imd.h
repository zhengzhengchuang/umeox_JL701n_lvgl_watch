#ifndef __IMD_H__
#define __IMD_H__

#include "generic/typedef.h"


// ʹ���û���UI���
extern const int ENABLE_JL_UI_FRAME;

extern u8 curr_index;

extern volatile struct imd_variable imd_var;

typedef struct imd_driver {
	void (*init)(struct imd_variable *priv);
	void (*write)(u8, u8 *, u8);
	void (*read)(u8, u8 *, u8);
	void (*set_draw_area)(int, int, int, int);
	void (*draw)();
	void (*isr)();
};

enum {
	IMD_DRV_SPI,
	IMD_DRV_MCU,
	IMD_DRV_RGB,
	IMD_DRV_MAX,
};


//<<<[lcd�ӿ�����]>>>
#define SPI_MODE  (0<<4)
#define DSPI_MODE (1<<4)
#define QSPI_MODE (2<<4)

#define SPI_WIRE3  0
#define SPI_WIRE4  1

#define QSPI_SUBMODE0 0//0x02
#define QSPI_SUBMODE1 1//0x32
#define QSPI_SUBMODE2 2//0x12

#define PIXEL_1P1T (0<<5)
#define PIXEL_1P2T (1<<5)
#define PIXEL_1P3T (2<<5)
#define PIXEL_2P3T (3<<5)

#define PIXEL_1T2B  1
#define PIXEL_1T6B  5
#define PIXEL_1T8B  7
#define PIXEL_1T9B  8
#define PIXEL_1T12B 11
#define PIXEL_1T16B 15
#define PIXEL_1T18B 17
#define PIXEL_1T24B 23

#define FORMAT_RGB565 1//0//1P2T
#define FORMAT_RGB666 2//1//1P3T
#define FORMAT_RGB888 0//2//1P3T

#define SPI_PORTA 0
#define SPI_PORTB 1

#define IMD_SPI_PND_IE()    SFR(JL_IMD->IMDSPI_CON0, 29, 1, 1)
#define IMD_SPI_PND_DIS()   SFR(JL_IMD->IMDSPI_CON0, 29, 1, 0)

#define IMD_PAP_PND_IE()    SFR(JL_IMD->IMDPAP_CON0, 29, 1, 1)
#define IMD_PAP_PND_DIS()   SFR(JL_IMD->IMDPAP_CON0, 29, 1, 0)

#define IMD_RGB_PND_IE()    SFR(JL_IMD->IMDRGB_CON0, 29, 1, 1)
#define IMD_RGB_PND_DIS()   SFR(JL_IMD->IMDRGB_CON0, 29, 1, 0)


#define SPI_MODE_UNIDIR  0//��˫����d0��ʱ���ͽ���
#define SPI_MODE_BIDIR   1//ȫ˫����d0���͡�d1����

enum {
	PIN_NONE,
	PIN_SYNC0_PA4,
	PIN_SYNC1_PA5,
	PIN_SYNC2_PA6,
};

enum {
	SYNC0_SEL_NONE,
	SYNC0_SEL_RGB_SYNC0,
	SYNC0_SEL_PAP_WR,
	SYNC0_SEL_PAP_RD,
};

enum {
	SYNC1_SEL_NONE,
	SYNC1_SEL_RGB_SYNC1,
	SYNC1_SEL_PAP_WR,
	SYNC1_SEL_PAP_RD,
};

enum {
	SYNC2_SEL_NONE,
	SYNC2_SEL_RGB_SYNC2,
	SYNC2_SEL_PAP_WR,
	SYNC2_SEL_PAP_RD,
};

/*
** imd˽��ȫ�ֱ�������
*/
struct imd_variable {
	u8 imd_pnd;     // imd�жϱ�־
	u8 imd_busy;    // imdæµ��־
	u8 te_ext;      // te�жϱ�־
	u8 clock_init;  // imdʱ�ӳ�ʼ����־
	u8 sfr_save;    // �Ĵ��������־
	u32 imd_sfr[17];
	void (*dc_ctrl)(u8 val);
	void (*cs_ctrl)(u8 val);
	int (*te_stat)();
	struct imd_param *param;
	void (*imd_callback)(int err);//imd֡�ص�
};

// LCD��Ļ����
typedef enum lcd_type_cfg {
	LCD_TYPE_SPI,   // SPI��
	LCD_TYPE_MCU,   // MCU��
	LCD_TYPE_RGB,   // RGB��
} LCD_TYPE;

struct imd_param {
	// ��ʾ�������
	int scr_x;
	int scr_y;
	int scr_w;
	int scr_h;

	// lcd����
	int lcd_width;
	int lcd_height;
	LCD_TYPE lcd_type;

	// �Դ�����
	int buffer_num;
	int buffer_size;

	// imdģ������룬��imbģ��һ����ʱ��Ҳ��imbģ������
	int in_width;
	int in_height;
	int in_format;
	int in_stride;

	// debugģʽ
	int debug_mode_en;
	int debug_mode_color;

	// te����
	int te_en;      //TE�ź�ʹ��
	int te_port;    // te��io

	// ֡������
	int fps;

	// ����Ϊ������������ã�out_formatΪ��Ļ�����ظ�ʽ����
	struct spi_param {
		int spi_mode;
		int pixel_type;
		int out_format;
		int port;
		int spi_dat_mode;
	} spi;

	struct pap_param {
		int out_format;
		int right_shift_2bit;
		int dat_l2h_en;
		int wr_sel;
		int rd_sel;
	} pap;

	struct rgb_param {
		int dat_l2h;
		int dat_sf;
		int hv_mode;
		int xor_edge;
		int out_format;
		int continue_frames;

		int hsync_sel;
		int vsync_sel;
		int den_sel;

		int hpw_prd;
		int hbw_prd;
		int hfw_prd;
		int vpw_prd;
		int vbw_prd;
		int vfw_prd;
	} rgb;
};


enum {
	LCD_COLOR_MODE,
	LCD_DATA_MODE,
};

int  lcd_init(struct imd_param *param);
void lcd_write_cmd(u8 cmd, u8 *buf, u8 len);
void lcd_read_cmd(u8 cmd, u8 *buf, u8 len);
void lcd_set_draw_area(int xstart, int xend, int ystart, int yend);
void lcd_draw(u8 mode, u32 priv);
void lcd_full_clear(u32 color);
void lcd_clear(u16 xstart, u16 xend, u16 ystart, u16 yend, u32 color);
void lcd_set_ctrl_pin_func(void (*dc_ctrl)(u8), void (*cs_ctrl)(u8), int (*te_stat)());
void lcd_wait();
int  lcd_draw_set_callback(void (*callback)(int err));


u16 get_lcd_width_from_imd(void);
u16 get_lcd_height_from_imd(void);


#endif





