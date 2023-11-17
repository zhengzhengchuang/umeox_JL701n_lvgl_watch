#include "qmi8658.h"

#if TCFG_QMI8658_EN

#define QMI8658_DATA_DEBUG (0)

static const u8 qmi8658_chip_id = 0x05;
static const u8 qmi8658_slave_addr[2] = {0x6A, 0x6B};
static qmi8658_drive_info_t qmi8658_drive_info = {0};

static bool qmi8658_write_reg(u8 reg_addr, u8 data)
{
    u8 retry = 5;
    bool succ_ret = false;

	u8 slave_addr = qmi8658_drive_info.slave_addr;

    succ_ret = sensor_iic_tx_byte(slave_addr, reg_addr, data);

    while(retry && !succ_ret)
    {
        succ_ret = sensor_iic_tx_byte(slave_addr, reg_addr, data);

        retry--;

        printf("%s:retry = %d\n", __func__, retry);
    }

    return succ_ret;
}

static bool qmi8658_write_regs(u8 reg_addr, u8 *buf, u8 len)
{
    if(!buf || len == 0)
        return false;

    u8 retry = 5;
    bool succ_ret = false;

	u8 slave_addr = qmi8658_drive_info.slave_addr;

    succ_ret = sensor_iic_tx_buf(slave_addr, reg_addr, buf, len);

    while(retry && !succ_ret)
    {
        succ_ret = sensor_iic_tx_buf(slave_addr, reg_addr, buf, len);

        retry--;

        printf("%s:retry = %d\n", __func__, retry);
    }

    return succ_ret;
}

static bool qmi8658_read_reg(u8 reg_addr, u8 *buf, u8 len)
{
    if(!buf || len == 0)
        return false;

    u8 retry = 5;
    bool succ_ret = false;

	u8 slave_addr = qmi8658_drive_info.slave_addr;

    succ_ret = sensor_iic_rx_buf(slave_addr, reg_addr, buf, len);

    while(retry && !succ_ret)
    {
        succ_ret = sensor_iic_rx_buf(slave_addr, reg_addr, buf, len);

        retry--;

        printf("%s:retry = %d\n", __func__, retry);
    }

    return succ_ret;
}

static void qmi8658_delay_ms(u32 ms)
{
	delay(ms);

    return;
}

static void qmi8658_delay_us(u32 us)
{
	delay_us(us);

    return;
}

static void qmi8658_chip_reset(void)
{
	u8 retry = 50;
	bool succ_ret = false;
	u8 reset_done_value = 0xff;

	succ_ret = qmi8658_write_reg(qmi8658_register_reset, 0xb0);

	if(succ_ret)
	{
		qmi8658_delay_ms(15);

		qmi8658_read_reg(qmi8658_register_reset_done, &reset_done_value, 1);

		while(retry && reset_done_value != 0x80)
		{
			qmi8658_delay_ms(15);

			qmi8658_read_reg(qmi8658_register_reset_done, &reset_done_value, 1);

			retry--;
		}
		
	}

	if(retry && succ_ret)
		printf("chip reset success!!!!!!!!!!!!!!!!\n");
	else
		printf("chip reset error!!!!!!!!!!!!!!!!!!\n");
	
	return;
}

static u8 qmi8658_read_chip_id(void)
{
	u8 chip_id = 0xff;
	u8 addr_sel_idx = 0;
	bool succ_ret = false;

	while(addr_sel_idx < sizeof(qmi8658_slave_addr))
	{
		qmi8658_drive_info.slave_addr = qmi8658_slave_addr[addr_sel_idx];

		succ_ret = qmi8658_read_reg(qmi8658_register_chip_id, &chip_id, 1);
		if(succ_ret) break;

		addr_sel_idx++;
	}
	
	return chip_id;
}

static void qmi8568_config_acc_ssvt(qmi8658_accrange_t accrange)
{
	switch(accrange)
	{
		case qmi8658_accrange_2g:
			qmi8658_drive_info.acc_ssvt = 16384;
			break;

		case qmi8658_accrange_4g:
			qmi8658_drive_info.acc_ssvt = 8192;
			break;

		case qmi8658_accrange_8g:
			qmi8658_drive_info.acc_ssvt = 4096;
			break;

		case qmi8658_accrange_16g:
			qmi8658_drive_info.acc_ssvt = 2048;
			break;
		
		default:
			qmi8658_drive_info.acc_ssvt = 4096;
			break;
	}

	printf("%s:acc_ssvt=%d\n", __func__, qmi8658_drive_info.acc_ssvt);

	return;
}

static void qmi8568_config_gyro_ssvt(qmi8658_gyrorange_t gyrorange)
{
	switch(gyrorange)
	{
		case qmi8658_gyrorange_16dps:
			qmi8658_drive_info.gyro_ssvt = 2048;
			break;

		case qmi8658_gyrorange_32dps:
			qmi8658_drive_info.gyro_ssvt = 1024;
			break;

		case qmi8658_gyrorange_64dps:
			qmi8658_drive_info.gyro_ssvt = 512;
			break;

		case qmi8658_gyrorange_128dps:
			qmi8658_drive_info.gyro_ssvt = 256;
			break;

		case qmi8658_gyrorange_256dps:
			qmi8658_drive_info.gyro_ssvt = 128;
			break;

		case qmi8658_gyrorange_512dps:
			qmi8658_drive_info.gyro_ssvt = 64;
			break;

		case qmi8658_gyrorange_1024dps:
			qmi8658_drive_info.gyro_ssvt = 32;
			break;

		case qmi8658_gyrorange_2048dps:
			qmi8658_drive_info.gyro_ssvt = 16;
			break;
		
		default:
			qmi8658_drive_info.gyro_ssvt = 32;
			break;
	}

	printf("%s:gyro_ssvt=%d\n", __func__, qmi8658_drive_info.gyro_ssvt);

	return;
}

static void qmi8658_read_ctrl_register(void)
{
	u8 register_data[8] = {0xff};

	qmi8658_read_reg(qmi8658_register_ctrl_1, register_data, 8);

	for(u8 i = 0; i < 8; i++)
		printf("%s:data=0x%x\n", __func__, register_data[i]);

	return;
}

static void qmi8658_read_sensor_data(float acc_axis[3], float gyro_axis[3])
{
	u8 data_buf[12] = {0};
	s16 raw_acc_axis[3] = {0};
	s16 raw_gyro_axis[3] = {0};

	qmi8658_read_reg(qmi8658_register_acc_xl, data_buf, 12);

	raw_acc_axis[0] = (s16)((u16)(data_buf[1]<<8)|(data_buf[0]));
	raw_acc_axis[1] = (s16)((u16)(data_buf[3]<<8)|(data_buf[2]));
	raw_acc_axis[2] = (s16)((u16)(data_buf[5]<<8)|(data_buf[4]));

	raw_gyro_axis[0] = (s16)((u16)(data_buf[7]<<8)|(data_buf[6]));
	raw_gyro_axis[1] = (s16)((u16)(data_buf[9]<<8)|(data_buf[8]));
	raw_gyro_axis[2] = (s16)((u16)(data_buf[11]<<8)|(data_buf[10]));

	acc_axis[0] = (float)(raw_acc_axis[0]*(9.807f))/(qmi8658_drive_info.acc_ssvt);
	acc_axis[1] = (float)(raw_acc_axis[1]*(9.807f))/(qmi8658_drive_info.acc_ssvt);
	acc_axis[2] = (float)(raw_acc_axis[2]*(9.807f))/(qmi8658_drive_info.acc_ssvt);

	gyro_axis[0] = (float)(raw_gyro_axis[0]*(3.141592f))/((qmi8658_drive_info.gyro_ssvt)*180);
	gyro_axis[1] = (float)(raw_gyro_axis[1]*(3.141592f))/((qmi8658_drive_info.gyro_ssvt)*180);
	gyro_axis[2] = (float)(raw_gyro_axis[2]*(3.141592f))/((qmi8658_drive_info.gyro_ssvt)*180);

	return;
}

static void qmi8658_axis_convert(float acc_axis[3], float gyro_axis[3], u8 layout)
{
	float raw_acc_axis[3];
	float raw_gyro_axis[3];

	raw_acc_axis[0] = acc_axis[0];
	raw_acc_axis[1] = acc_axis[1];

	raw_gyro_axis[0] = gyro_axis[0];
	raw_gyro_axis[1] = gyro_axis[1];

	/*z轴自己反向*/
	if(layout >= 4 && layout <= 7)
	{
		acc_axis[2] = -acc_axis[2];
		gyro_axis[2] = -gyro_axis[2];
	}

	if(layout%2)
	{
		/*x轴, y轴交换*/
		acc_axis[0] = raw_acc_axis[1];
		acc_axis[1] = raw_acc_axis[0];
		
		gyro_axis[0] = raw_gyro_axis[1];
		gyro_axis[1] = raw_gyro_axis[0];
	}

	if((layout == 1) || (layout == 2) || (layout == 4) || (layout == 7))
	{
		/*x轴自己反向*/
		acc_axis[0] = -acc_axis[0];
		gyro_axis[0] = -gyro_axis[0];
	}

	if((layout == 2) || (layout == 3) || (layout == 6) || (layout == 7))
	{
		/*y轴自己反向*/
		acc_axis[1] = -acc_axis[1];
		gyro_axis[1] = -gyro_axis[1];
	}

	return;
}

float qmi8658_read_tempearture(void)
{
	u8 tempearture_buf[2];
	s16 tempearture_i = 0;
	float tempearture_f = 0;

	qmi8658_read_reg(qmi8658_register_tempearture_l, tempearture_buf, 2);
	tempearture_i = ((s16)tempearture_buf[1]<<8)|tempearture_buf[0];
	tempearture_f = (float)tempearture_i/(256.0f);

	return tempearture_f;
}

void qmi8658_read_timestamp(u32 *timestamp)
{
	if(!timestamp) return;

	u32 timestamp_tmp = 0;
	u8 timestamp_buf[3] = {0};

	qmi8658_read_reg(qmi8658_register_timestamp_l, timestamp_buf, 3);
	timestamp_tmp = (u32)(((u32)timestamp_buf[2]<<16)|((u32)timestamp_buf[1]<<8)|timestamp_buf[0]);

	if(timestamp_tmp > qmi8658_drive_info.timestamp)
		qmi8658_drive_info.timestamp = timestamp_tmp;
	else
		qmi8658_drive_info.timestamp = (timestamp_tmp+0x1000000 - qmi8658_drive_info.timestamp);

	*timestamp = qmi8658_drive_info.timestamp;

	return;
}

void qmi8658_read_axis_xyz(float acc_axis[3], float gyro_axis[3])
{
	u8 data_state = 0x00;
	bool data_ready = false;

	qmi8658_read_reg(qmi8658_register_status_int, &data_state, 1);

	if((data_state&0x01) && (data_state&0x02))
		data_ready = true;

	if(data_ready)
	{
		qmi8658_read_sensor_data(acc_axis, gyro_axis);
		qmi8658_axis_convert(acc_axis, gyro_axis, 0);

#if QMI8658_DATA_DEBUG
		s16 acc_axis_x = (s16)acc_axis[0];
		s16 acc_axis_y = (s16)acc_axis[1];
		s16 acc_axis_z = (s16)acc_axis[2];

		s16 gyro_axis_x = (s16)gyro_axis[0];
		s16 gyro_axis_y = (s16)gyro_axis[1];
		s16 gyro_axis_z = (s16)gyro_axis[2];

		printf("*********acc axis:x=%d, y=%d, z=%d\n", \
			acc_axis_x, acc_axis_y, acc_axis_z);

		printf("*********gyro axis:x=%d, y=%d, z=%d\n", \
			gyro_axis_x, gyro_axis_y, gyro_axis_z);
#endif

		qmi8658_drive_info.acc_axis[0] = acc_axis[0];
		qmi8658_drive_info.acc_axis[1] = acc_axis[1];
		qmi8658_drive_info.acc_axis[2] = acc_axis[2];

		qmi8658_drive_info.gyro_axis[0] = gyro_axis[0];
		qmi8658_drive_info.gyro_axis[1] = gyro_axis[1];
		qmi8658_drive_info.gyro_axis[2] = gyro_axis[2];
	}else
	{
		acc_axis[0] = qmi8658_drive_info.acc_axis[0];
		acc_axis[1] = qmi8658_drive_info.acc_axis[1];
		acc_axis[2] = qmi8658_drive_info.acc_axis[2];

		gyro_axis[0] = qmi8658_drive_info.gyro_axis[0];
		gyro_axis[1] = qmi8658_drive_info.gyro_axis[1];
		gyro_axis[2] = qmi8658_drive_info.gyro_axis[2];
	}
		
	return;
}

void qmi8658_init(void)
{
	u8 chip_id = 0xff;

	chip_id = qmi8658_read_chip_id();

	if(chip_id != qmi8658_chip_id)
	{
		printf("qmi8658_init error!!!!!!!!!!!!!!!!!\n");
		return;
	}

	qmi8658_chip_reset();

	qmi8658_write_reg(qmi8658_register_ctrl_9, 0xA2);
	qmi8658_delay_ms(2000);
	qmi8658_write_reg(qmi8658_register_ctrl_1, 0x60);

	qmi8658_drive_info.accodr = qmi8658_accodr_125hz;
	qmi8658_drive_info.accrange = qmi8658_accrange_8g;
	u8 acc_conf_info = (qmi8658_drive_info.accodr)|(qmi8658_drive_info.accrange) \
		|qmi8658_accst_disable;
	qmi8568_config_acc_ssvt(qmi8658_drive_info.accrange);
	qmi8658_write_reg(qmi8658_register_ctrl_2, acc_conf_info);
	printf("%s:acc_conf=0x%x\n", __func__, acc_conf_info);

	qmi8658_drive_info.gyroodr = qmi8658_gyroodr_224hz;
	qmi8658_drive_info.gyrorange = qmi8658_gyrorange_1024dps;
	u8 gyro_conf_info = (qmi8658_drive_info.gyroodr)|(qmi8658_drive_info.gyrorange) \
		|qmi8658_gyrost_disable;
	qmi8568_config_gyro_ssvt(qmi8658_drive_info.gyrorange);
	qmi8658_write_reg(qmi8658_register_ctrl_3, gyro_conf_info);
	printf("%s:gyro_conf=0x%x\n", __func__, gyro_conf_info);

	u8 ctrl_acc_lsp_data = 0x00;
	qmi8658_drive_info.acc_lsp_state = qmi8658_lsp_disable;
	if(qmi8658_drive_info.acc_lsp_state == qmi8658_lsp_disable)
		ctrl_acc_lsp_data &= (~(0x01<<0));		
	else
	{
		ctrl_acc_lsp_data |= qmi8658_acc_lsp_mode_3;
		ctrl_acc_lsp_data |= (0x01<<0);
	}

	u8 ctrl_gyro_lsp_data = 0x00;
	qmi8658_drive_info.gyro_lsp_state = qmi8658_lsp_disable;
	if(qmi8658_drive_info.gyro_lsp_state == qmi8658_lsp_disable)
		ctrl_gyro_lsp_data &= (~(0x01<<4));		
	else
	{
		ctrl_gyro_lsp_data |= qmi8658_gyro_lsp_mode_3;
		ctrl_gyro_lsp_data |= (0x01<<4);
	}

	u8 ctrl_lsp_data = ctrl_acc_lsp_data|ctrl_gyro_lsp_data;
	qmi8658_write_reg(qmi8658_register_ctrl_5, ctrl_lsp_data);
	printf("%s:lsp_data=0x%x\n", __func__, ctrl_lsp_data);

	qmi8658_write_reg(qmi8658_register_ctrl_7, 0xA3);
	qmi8658_delay_ms(2);

	qmi8658_read_ctrl_register();

	printf("qmi8658_init success!!!!!!!!!!!!!!!!!\n");

	return;
}
#endif
