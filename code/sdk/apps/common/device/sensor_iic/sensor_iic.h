#ifndef __SENSOR_IIC_H__
#define __SENSOR_IIC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "app_config.h"
#include "asm/iic_hw.h"
#include "asm/iic_soft.h"
#include "system/includes.h"

void sensor_iic_init(void);
bool sensor_iic_tx_byte(u8 slave_addr, u8 reg_addr, u8 data);
bool sensor_iic_tx_buf(u8 slave_addr, u8 reg_addr, u8 *buf, u8 len);
bool sensor_iic_rx_buf(u8 slave_addr, u8 reg_addr, u8 *buf, u8 len);
#ifdef __cplusplus
}
#endif

#endif
