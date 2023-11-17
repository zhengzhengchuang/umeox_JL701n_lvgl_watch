#include "sensor_iic.h"

#if TCFG_SENSOR_IIC_TYPE
#define iic_init(iic)                       hw_iic_init(iic)
#define iic_uninit(iic)                     hw_iic_uninit(iic)
#define iic_start(iic)                      hw_iic_start(iic)
#define iic_stop(iic)                       hw_iic_stop(iic)
#define iic_tx_byte(iic, byte)              hw_iic_tx_byte(iic, byte)
#define iic_rx_byte(iic, ack)               hw_iic_rx_byte(iic, ack)
#define iic_read_buf(iic, buf, len)         hw_iic_read_buf(iic, buf, len)
#define iic_write_buf(iic, buf, len)        hw_iic_write_buf(iic, buf, len)
#define iic_suspend(iic)                    hw_iic_suspend(iic)
#define iic_resume(iic)                     hw_iic_resume(iic)
#else
#define iic_init(iic)                       soft_iic_init(iic)
#define iic_uninit(iic)                     soft_iic_uninit(iic)
#define iic_start(iic)                      soft_iic_start(iic)
#define iic_stop(iic)                       soft_iic_stop(iic)
#define iic_tx_byte(iic, byte)              soft_iic_tx_byte(iic, byte)
#define iic_rx_byte(iic, ack)               soft_iic_rx_byte(iic, ack)
#define iic_read_buf(iic, buf, len)         soft_iic_read_buf(iic, buf, len)
#define iic_write_buf(iic, buf, len)        soft_iic_write_buf(iic, buf, len)
#define iic_suspend(iic)                    soft_iic_suspend(iic)
#define iic_resume(iic)                     soft_iic_resume(iic)
#endif

static spinlock_t sensor_iic_lock;
static const u8 sensor_iic_delay = 1;
static bool sensor_iic_init_flag = false;
static const soft_iic_dev sensor_iic_hdl = TCFG_SENOR_IIC_INDEX;

void sensor_iic_init(void)
{
    if(sensor_iic_init_flag)
        return;

    iic_init(sensor_iic_hdl);

    spin_lock_init(&sensor_iic_lock);

    sensor_iic_init_flag = true;

    return;
}

bool sensor_iic_tx_byte(u8 slave_addr, u8 reg_addr, u8 data)
{
    bool error_flag = false;

    spin_lock(&sensor_iic_lock);

    iic_start(sensor_iic_hdl);

    if(!iic_tx_byte(sensor_iic_hdl, slave_addr << 1))
    {
        error_flag = true;
        goto __gcend;
    }      
    delay(sensor_iic_delay);

    if(!iic_tx_byte(sensor_iic_hdl, reg_addr))
    {
        error_flag = true;
        goto __gcend;
    }
    delay(sensor_iic_delay);

    if(!iic_tx_byte(sensor_iic_hdl, data))
    {
        error_flag = true;
        goto __gcend;
    }

__gcend:
    iic_stop(sensor_iic_hdl);
    spin_unlock(&sensor_iic_lock);
    return (!error_flag);
}

bool sensor_iic_tx_buf(u8 slave_addr, u8 reg_addr, u8 *buf, u8 len)
{
    bool error_flag = false;

    if(!buf || len == 0)
        return error_flag;

    spin_lock(&sensor_iic_lock);

    iic_start(sensor_iic_hdl);

    if(!iic_tx_byte(sensor_iic_hdl, slave_addr << 1))
    {
        error_flag = true;
        goto __gcend;
    }
    delay(sensor_iic_delay);

    if(!iic_tx_byte(sensor_iic_hdl, reg_addr)) 
    {
        error_flag = true;
        goto __gcend;
    }
    delay(sensor_iic_delay);

    for(u8 i = 0; i < len; i++)
    {
        if(!iic_tx_byte(sensor_iic_hdl, buf[i])) 
        {
            error_flag = true;
            goto __gcend;
        }
        delay(sensor_iic_delay);
    }
    
 __gcend:
    iic_stop(sensor_iic_hdl);
    spin_unlock(&sensor_iic_lock);
    return (!error_flag);
}

bool sensor_iic_rx_buf(u8 slave_addr, u8 reg_addr, u8 *buf, u8 len)
{
    u8 r_len = 0;
    bool error_flag = false;

    if(!buf || len == 0)
        return error_flag;

    spin_lock(&sensor_iic_lock);

    iic_start(sensor_iic_hdl);

    if(!iic_tx_byte(sensor_iic_hdl, slave_addr << 1)) 
    {
        error_flag = true;
        goto __gcend;
    }
    delay(sensor_iic_delay);

    if(!iic_tx_byte(sensor_iic_hdl, reg_addr))
    {
        error_flag = true;
        goto __gcend;
    }
    delay(sensor_iic_delay);

    iic_start(sensor_iic_hdl);

    if(!iic_tx_byte(sensor_iic_hdl, (slave_addr << 1) | 0x01))
    {
        error_flag = true;
        goto __gcend;
    }
    delay(sensor_iic_delay);

    for(; len > 1; len--)
        buf[r_len++] = iic_rx_byte(sensor_iic_hdl, 1);

    buf[r_len++] = iic_rx_byte(sensor_iic_hdl, 0);

 __gcend:
    iic_stop(sensor_iic_hdl);
    spin_unlock(&sensor_iic_lock);
    return (!error_flag);
}