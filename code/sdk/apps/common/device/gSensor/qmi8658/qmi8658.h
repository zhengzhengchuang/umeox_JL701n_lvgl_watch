#ifndef __QMI8658_H__
#define __QMI8658_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../sensor_iic/sensor_iic.h"

#if TCFG_QMI8658_EN

//*********************************************************************************//
//                                  qmi8658寄存器地址                                //
//*********************************************************************************//
enum
{
	qmi8658_register_chip_id        = 0x00,
	qmi8658_register_ctrl_1         = 0x02,
	qmi8658_register_ctrl_2         = 0x03,
	qmi8658_register_ctrl_3         = 0x04,
	qmi8658_register_ctrl_5         = 0x06,
	qmi8658_register_ctrl_7         = 0x08,
	qmi8658_register_ctrl_8         = 0x09,
	qmi8658_register_ctrl_9         = 0x0A,

	qmi8658_register_status_int     = 0x2D,

	qmi8658_register_acc_xl         = 0x35,
	qmi8658_register_acc_xh,
	qmi8658_register_acc_yl,
	qmi8658_register_acc_yh,
	qmi8658_register_acc_zl,
	qmi8658_register_acc_zh,
	qmi8658_register_gyro_xl,     
	qmi8658_register_gyro_xh,
	qmi8658_register_gyro_yl,
	qmi8658_register_gyro_yh,
	qmi8658_register_gyro_zl,
	qmi8658_register_gyro_zh,

	qmi8658_register_timestamp_l    = 0x30,
	qmi8658_register_timestamp_m,
	qmi8658_register_timestamp_h,

	qmi8658_register_tempearture_l  = 0x33,
	qmi8658_register_tempearture_h,
	
	qmi8658_register_reset_done     = 0x4D,
	qmi8658_register_reset          = 0x60,
};

//*********************************************************************************//
//                                  qmi8658加速度计频率                              //
//*********************************************************************************//
typedef enum
{
	qmi8658_accodr_1000hz           = 0x03,
	qmi8658_accodr_500hz            = 0x04,
	qmi8658_accodr_250hz            = 0x05,
	qmi8658_accodr_125hz            = 0x06,
	qmi8658_accodr_62hz             = 0x07, //实际62.5hz
	qmi8658_accodr_31hz             = 0x08, //实际31.25hz
}qmi8658_accodr_t;

//*********************************************************************************//
//                                  qmi8658加速度计量程                              //
//*********************************************************************************//
typedef enum
{
	qmi8658_accrange_2g             = (0x00<<4),
	qmi8658_accrange_4g             = (0x01<<4),
	qmi8658_accrange_8g             = (0x02<<4),
	qmi8658_accrange_16g            = (0x03<<4),
}qmi8658_accrange_t;

enum
{
	qmi8658_accst_disable           = (0x00<<7),
	qmi8658_accst_enable            = (0x01<<7),
};



//*********************************************************************************//
//                                  qmi8658陀螺仪频率                                //
//*********************************************************************************//
typedef enum
{
	qmi8658_gyroodr_7174hz           = 0x00, //实际7174.4hz
	qmi8658_gyroodr_3587hz           = 0x01, //实际3587.2hz
	qmi8658_gyroodr_1793hz           = 0x02, //实际1793.6hz
	qmi8658_gyroodr_896hz            = 0x03, //实际896.8hz
	qmi8658_gyroodr_448hz            = 0x04, //实际448.4hz
	qmi8658_gyroodr_224hz            = 0x05, //实际224.2hz
	qmi8658_gyroodr_112hz            = 0x06, //实际112.1hz
	qmi8658_gyroodr_56hz             = 0x07, //实际56.05hz
	qmi8658_gyroodr_28hz             = 0x08, //实际28.025hz
}qmi8658_gyroodr_t;

//*********************************************************************************//
//                                  qmi8658陀螺仪量程                                //
//*********************************************************************************//
typedef enum
{
	qmi8658_gyrorange_16dps          = (0x00<<4),
	qmi8658_gyrorange_32dps          = (0x01<<4),
	qmi8658_gyrorange_64dps          = (0x02<<4),
	qmi8658_gyrorange_128dps         = (0x03<<4),
	qmi8658_gyrorange_256dps         = (0x04<<4),
	qmi8658_gyrorange_512dps         = (0x05<<4),
	qmi8658_gyrorange_1024dps        = (0x06<<4),
	qmi8658_gyrorange_2048dps        = (0x07<<4),
}qmi8658_gyrorange_t;

enum
{
	qmi8658_gyrost_disable           = (0x00<<7),
	qmi8658_gyrost_enable            = (0x01<<7),
};



//*********************************************************************************//
//                                  qmi8658低通滤波lsp                              //
//*********************************************************************************//
typedef enum
{
	qmi8658_lsp_disable              = (0x00),
	qmi8658_lsp_enable               = (0x01),
}qmi8658_lsp_state_t;

enum
{
	qmi8658_acc_lsp_mode_0           = (0x00<<1),
	qmi8658_acc_lsp_mode_1           = (0x01<<1),
	qmi8658_acc_lsp_mode_2           = (0x02<<1),
	qmi8658_acc_lsp_mode_3           = (0x03<<1),
	
	qmi8658_gyro_lsp_mode_0          = (0x00<<5),
	qmi8658_gyro_lsp_mode_1          = (0x01<<5),
	qmi8658_gyro_lsp_mode_2          = (0x02<<5),
	qmi8658_gyro_lsp_mode_3          = (0x03<<5),
};

typedef struct
{
	u16 acc_ssvt;
	u16 gyro_ssvt;
	u8 slave_addr;
	u32 timestamp;
	float acc_axis[3];
	float gyro_axis[3];	
	qmi8658_accodr_t accodr;
	qmi8658_accrange_t accrange;
	qmi8658_gyroodr_t gyroodr;
	qmi8658_gyrorange_t gyrorange;
	qmi8658_lsp_state_t acc_lsp_state;
	qmi8658_lsp_state_t gyro_lsp_state;
}qmi8658_drive_info_t;

void qmi8658_init(void);
float qmi8658_read_tempearture(void);
void qmi8658_read_timestamp(u32 *timestamp);
void qmi8658_read_axis_xyz(float acc_axis[3], float gyro_axis[3]);
#endif

#ifdef __cplusplus
}
#endif

#endif
