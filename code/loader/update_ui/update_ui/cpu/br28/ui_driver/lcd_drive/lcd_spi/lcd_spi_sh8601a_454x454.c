/*
** ����board��ͷ�ļ���ȷ��baord���濪�ص�������
*/
#include "app_config.h"
#include "clock_cfg.h"
#include "ui/lcd_spi/lcd_drive.h"


/*
** ��������ĺ꿪��
*/
//<<<[qspi�� 454x454]>>>//
#if TCFG_LCD_SPI_SH8601A_ENABLE

// #define LCD_DRIVE_CONFIG                    QSPI_RGB565_SUBMODE0_1T8B
/* #define LCD_DRIVE_CONFIG                    QSPI_RGB565_SUBMODE1_1T2B */
#define LCD_DRIVE_CONFIG                    QSPI_RGB565_SUBMODE2_1T2B

/*
** ����imdͷ�ļ���������صı����ͽṹ�嶼������imd.h
*/
#include "asm/imd.h"
#include "asm/imb.h"
#include "includes.h"
#include "ui/ui_api.h"


#if 0
#define SCR_X 120
#define SCR_Y 110
#define SCR_W 240
#define SCR_H 240
#define LCD_W 240
#define LCD_H 240
#define LCD_BLOCK_W 240
#define LCD_BLOCK_H 60
#define BUF_NUM 2
#else
#define SCR_X 0
#define SCR_Y 0
#define SCR_W 454
#define SCR_H 454
#define LCD_W 454
#define LCD_H 454
#define LCD_BLOCK_W 454
#define LCD_BLOCK_H 80
#define BUF_NUM 2
#endif

#define LCD_FORMAT OUTPUT_FORMAT_RGB565

/*
** ��ʼ������
*/
static const u8 lcd_spi_sh8601a_cmd_list_poweron[] ALIGNED(4) = {
	_BEGIN_, 0xc0, 0x5a, 0x5a, _END_,
	_BEGIN_, 0xc1, 0x5a, 0x5a, _END_,
	_BEGIN_, 0x11, _END_,
	_BEGIN_, REGFLAG_DELAY, 100, _END_,

#if (OUT_FORMAT(LCD_DRIVE_CONFIG) == FORMAT_RGB565)
	_BEGIN_, 0x3A, 0x55, _END_,
#elif (OUT_FORMAT(LCD_DRIVE_CONFIG) == FORMAT_RGB666)
	_BEGIN_, 0x3A, 0x66, _END_,
#elif (OUT_FORMAT(LCD_DRIVE_CONFIG) == FORMAT_RGB888)
	_BEGIN_, 0x3A, 0x77, _END_,
#endif

	_BEGIN_, 0x44, 0, 0, _END_,
	_BEGIN_, 0x35, 0x00, _END_,
	_BEGIN_, 0xb0, 0x16, _END_,
	_BEGIN_, 0xb1, 0x01, 0x05, 0x00, 0xa2, 0x00, 0xa7, 0x00, 0xa7, 0x00, _END_,
	_BEGIN_, 0x53, 0x28, _END_,
	_BEGIN_, 0xc4, 0x80, _END_,

	_BEGIN_, REGFLAG_DELAY, 25, _END_,
	_BEGIN_, 0x29, _END_,
	_BEGIN_, REGFLAG_DELAY, 20, _END_,
	_BEGIN_, 0xb1, 0xc0, _END_,

	_BEGIN_, 0xc0, 0xa5, 0xa5, _END_,
	_BEGIN_, 0xc1, 0xa5, 0xa5, _END_,
};


static const u8 lcd_cmd_list_sleepout[] ALIGNED(4) = {
	_BEGIN_, 0xc0, 0x5a, 0x5a, _END_,
	_BEGIN_, 0xc1, 0x5a, 0x5a, _END_,

#if (OUT_FORMAT(LCD_DRIVE_CONFIG) == FORMAT_RGB565)
	_BEGIN_, 0x3A, 0x55, _END_,
#elif (OUT_FORMAT(LCD_DRIVE_CONFIG) == FORMAT_RGB666)
	_BEGIN_, 0x3A, 0x66, _END_,
#elif (OUT_FORMAT(LCD_DRIVE_CONFIG) == FORMAT_RGB888)
	_BEGIN_, 0x3A, 0x77, _END_,
#endif

	_BEGIN_, 0x44, 0, 0, _END_,
	_BEGIN_, 0x35, 0x00, _END_,
	_BEGIN_, 0xb0, 0x16, _END_,
	_BEGIN_, 0xb1, 0x01, 0x05, 0x00, 0xa2, 0x00, 0xa7, 0x00, 0xa7, 0x00, _END_,
	_BEGIN_, 0x53, 0x28, _END_,
	_BEGIN_, 0xc4, 0x80, _END_,

	_BEGIN_, 0xb1, 0xc0, _END_,

	_BEGIN_, 0xc0, 0xa5, 0xa5, _END_,
	_BEGIN_, 0xc1, 0xa5, 0xa5, _END_,
};


extern struct lcd_spi_platform_data *lcd_get_platform_data();

void lcd_send_cmd_enable()
{
	u8 para[2];
	para[0] = 0x5a;
	para[1] = 0x5a;
	lcd_write_cmd(0xc0, para, 2);
	lcd_write_cmd(0xc1, para, 2);
}

void lcd_send_cmd_disable()
{
	u8 para[2];
	para[0] = 0xa5;
	para[1] = 0xa5;
	lcd_write_cmd(0xc0, para, 2);
	lcd_write_cmd(0xc1, para, 2);
}

static void lcd_adjust_display_brightness(u8 percent)
{
	u16 brightness;
	u8 para[2];

	brightness = percent * 0x3ff / 100;

	para[0] = brightness & 0xff;
	para[1] = (brightness >> 8) & 0x3;

	lcd_write_cmd(0x51, para, 2);
	/* lcd_write_cmd(0x4a, para, 2); //Brightness Value of AOD Mode, ��Ч�� */
	/* lcd_write_cmd(0x63, para, 2); //Brightness Value of HBM Mode, ��Ч�� */
}

/*
** lcd�������
** ���ǵ��ֱ�Ӧ��lcd���������Ҫ��������ɣ�������Ҫpwm���⣬��ʱ�����
** ����ڲ�������lcd���⣬ȫ�����ⲿ���п���
*/
static int lcd_spi_sh8601a_backlight_ctrl(u8 percent)
{
	if (percent) {
		lcd_write_cmd(0x29, NULL, 0);
		if (percent <= 20) {
			lcd_adjust_display_brightness(1);
		} else if (percent <= 40) {
			lcd_adjust_display_brightness(3);
		} else if (percent <= 60) {
			lcd_adjust_display_brightness(6);
		} else if (percent <= 80) {
			lcd_adjust_display_brightness(10);
		} else if (percent <= 100) {
			lcd_adjust_display_brightness(100);
		}
		/* g_printf("lcd backlight percent:%d",percent); */
	} else {
		lcd_write_cmd(0x28, NULL, 0);
	}

	return 0;
}


/*
** lcd��Դ����
*/
static int lcd_spi_sh8601a_power_ctrl(u8 onoff)
{
//    extern void wdt_clear();
//    wdt_clear();
	lcd_en_ctrl(onoff);
	return 0;
}


#define DEEP_STANDBY  1

/*
** ����lcd����˯��
*/
static void lcd_spi_sh8601a_entersleep(void)
{
	u8 dstb = 0x01;

	lcd_write_cmd(0x28, NULL, 0);
	lcd_write_cmd(0x10, NULL, 0);
	delay_2ms(120 / 2); // delay 120ms
#if DEEP_STANDBY
	lcd_write_cmd(0x4f, &dstb, sizeof(dstb));
	delay_2ms(102 / 2); // delay 120ms
	struct lcd_platform_data *lcd_dat = lcd_get_platform_data();
	if (lcd_dat->pin_te != NO_CONFIG_PORT) {
		gpio_set_pull_up(lcd_dat->pin_te, 0);
		gpio_set_pull_down(lcd_dat->pin_te, 0);
		gpio_direction_input(lcd_dat->pin_te);
		gpio_set_die(lcd_dat->pin_te, 0);
	}
#endif

}



/*
** ����lcd�˳�˯��
*/
static void lcd_spi_sh8601a_exitsleep(void)
{
#if DEEP_STANDBY
	struct lcd_platform_data *lcd_dat = lcd_get_platform_data();
	if (lcd_dat && lcd_dat->pin_reset) {
		gpio_direction_output(lcd_dat->pin_reset, 0);
		delay_2ms(4);   // delay >5ms
		gpio_direction_output(lcd_dat->pin_reset, 1);
		delay_2ms(4);   // delay >5ms
	}

	lcd_write_cmd(0x11, NULL, 0);
	delay_2ms(5);
	lcd_write_cmd(0x29, NULL, 0);
	delay_2ms(5);

	extern struct imd_param lcd_spi_sh8601a_param;
	lcd_init(&lcd_spi_sh8601a_param);
	lcd_drv_cmd_list(lcd_cmd_list_sleepout, sizeof(lcd_cmd_list_sleepout) / sizeof(lcd_cmd_list_sleepout[0]));
#else
	lcd_write_cmd(0x11, NULL, 0);
	delay_2ms(5);   // delay 120ms
	lcd_write_cmd(0x29, NULL, 0);
#endif
}


struct imd_param lcd_spi_sh8601a_param = {
	.scr_x    = SCR_X,
	.scr_y    = SCR_Y,
	.scr_w    = SCR_W,
	.scr_h    = SCR_H,

	.in_width  = SCR_W,
	.in_height = SCR_H,
	.in_format = LCD_FORMAT,

	.lcd_width  = LCD_W,
	.lcd_height = LCD_H,

	.lcd_type = LCD_TYPE_SPI,

	.buffer_num = BUF_NUM,
	.buffer_size = LCD_BLOCK_W * LCD_BLOCK_H * 2,

	.fps = 60,

	.spi = {
		.spi_mode = SPI_IF_MODE(LCD_DRIVE_CONFIG),
		.pixel_type = PIXEL_TYPE(LCD_DRIVE_CONFIG),
		.out_format = OUT_FORMAT(LCD_DRIVE_CONFIG),
		.port = SPI_PORTA,
		.spi_dat_mode = SPI_MODE_UNIDIR,
	},

	.debug_mode_en = false,
	.debug_mode_color = 0xff0000,
};


REGISTER_LCD_DEVICE() = {
	.logo = "sh8601",
	.row_addr_align    = 2,
	.column_addr_align = 2,

	.lcd_cmd = (void *) &lcd_spi_sh8601a_cmd_list_poweron,
	.cmd_cnt = sizeof(lcd_spi_sh8601a_cmd_list_poweron) / sizeof(lcd_spi_sh8601a_cmd_list_poweron[0]),
	.param   = (void *) &lcd_spi_sh8601a_param,

	.reset = NULL,  // û������ĸ�λ���������ڲ���ͨ��λ��������
	.backlight_ctrl = lcd_spi_sh8601a_backlight_ctrl,
	.power_ctrl = lcd_spi_sh8601a_power_ctrl,
	.entersleep = lcd_spi_sh8601a_entersleep,
	.exitsleep = lcd_spi_sh8601a_exitsleep,
};


#endif


