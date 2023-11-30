
#include "chsc6x_comp.h"
#include "chsc6x_platform.h"

#if TCFG_TOUCH_PANEL_ENABLE

#if TCFG_TP_CHSC6X_ENABLE

static const u8 iic_hdl = 0;

u8 tp_iic_hdl(void)
{
    return iic_hdl;
}

struct ts_event {
    unsigned short x; /*x coordinate */
    unsigned short y; /*y coordinate */
    int flag; /* touch event flag: 0 -- down; 1-- up; 2 -- contact */
    int id;   /*touch ID */
};

void chsc6x_read_touch_info()
{
    int ret;
    int rd_len = 0;
    unsigned char point_num;
    unsigned char read_buf[6];
    struct ts_event events[CHSC6X_MAX_POINTS_NUM];

    if(1 == CHSC6X_MAX_POINTS_NUM) {
        rd_len = 3;
    } else if(2 == CHSC6X_MAX_POINTS_NUM) {
        if ((CHSC6X_RES_MAX_X < 255) && (CHSC6X_RES_MAX_Y < 255) ) {
            rd_len = 5;
        } else {
            rd_len = 6;
        }
    } else {
        chsc6x_err("CHSC641X_MAX_POINTS_NUM more than two");
        return;
    }
    
    ret = chsc6x_i2c_read(CHSC6X_I2C_ID, read_buf, rd_len);
    if(rd_len == ret) {
        point_num = read_buf[0] & 0x03;
    
        if(1 == CHSC6X_MAX_POINTS_NUM) {               
            events[0].x = (unsigned short)(((read_buf[0] & 0x40) >> 6) << 8) | (unsigned short)read_buf[1];
            events[0].y = (unsigned short)(((read_buf[0] & 0x80) >> 7) << 8) | (unsigned short)read_buf[2];
    
            events[0].flag= (read_buf[0] >> 4) & 0x03;
            events[0].id = (read_buf[0] >>2) & 0x01;
            chsc6x_info("chsc6x:   000  X:%d, Y:%d, point_num:%d,flag:%d, id:%d \r\n", \
                events[0].x, events[0].y, point_num, events[0].flag, events[0].id);
    
        } else if(2 == CHSC6X_MAX_POINTS_NUM) {                
            if ((CHSC6X_RES_MAX_X > 255) || (CHSC6X_RES_MAX_Y > 255) ) {
                events[0].x = (unsigned short)((read_buf[5] & 0x01) << 8) | (unsigned short)read_buf[1];
                events[0].y = (unsigned short)((read_buf[5] & 0x02) << 7) | (unsigned short)read_buf[2];
    
                events[0].flag = (read_buf[0] >> 4) & 0x03;
                events[0].id = (read_buf[0] >>2) & 0x01;
                chsc6x_info("chsc6x:   111  X:%d, Y:%d, point_num:%d,flag:%d, id:%d \r\n", \
                    events[0].x, events[0].y, point_num, events[0].flag, events[0].id); 
    
                events[1].x = (unsigned short)((read_buf[5] & 0x04) << 6) | (unsigned short)read_buf[3];
                events[1].y = (unsigned short)((read_buf[5] & 0x08) << 5) | (unsigned short)read_buf[4];
    
                events[1].flag = (read_buf[0] >> 6) & 0x03;
                events[1].id = (read_buf[0] >>3) & 0x01;
                chsc6x_info("chsc6x:   222  X:%d, Y:%d, point_num:%d,flag:%d, id:%d \r\n", \
                    events[1].x, events[1].y, point_num, events[1].flag, events[1].id);             
            } else {
                events[0].x = read_buf[1];
                events[0].y = read_buf[2];
    
                events[0].flag = (read_buf[0] >> 4) & 0x03;
                events[0].id = (read_buf[0] >>2) & 0x01;
                chsc6x_info("chsc6x:   333  X:%d, Y:%d, point_num:%d,flag:%d, id:%d \r\n", \
                    events[0].x, events[0].y, point_num, events[0].flag, events[0].id);                 
    
                events[1].x = read_buf[3];
                events[1].y = read_buf[4];
    
                events[1].flag = (read_buf[0] >> 6) & 0x03;
                events[1].id = (read_buf[0] >>3) & 0x01;
                chsc6x_info("chsc6x:   444  X:%d, Y:%d, point_num:%d,flag:%d, id:%d \r\n", \
                    events[1].x, events[1].y, point_num, events[1].flag, events[1].id);             
            }   	           
        }   
    }
    else{
        chsc6x_err("chsc6x: chsc6x_read_touch_info iic err! rd_len=%d, ret=%d \r\n", rd_len, ret);
    }
}

void chsc6x_resume(void)
{
    chsc6x_info("touch_resume");
    chsc6x_tp_reset();
}

void chsc6x_suspend(void)
{
    unsigned char buft[1] = {0};
    int ret = -1;
    chsc6x_tp_reset();
    ret = chsc6x_write_bytes_u16addr_sub(CHSC6X_I2C_ID, 0xa503, buft, 0);
    if(ret == 0) {
        chsc6x_info("touch_suspend OK \r\n");
    }else{
        chsc6x_info("touch_suspend failed \r\n");
    }
}

void chsc6x_dbcheck(void)
{
    unsigned char buft[1] = {0};
    int ret = -1;
    chsc6x_tp_reset();
    ret = chsc6x_write_bytes_u16addr_sub(CHSC6X_I2C_ID, 0xd001, buft, 0);   //0xd001 close
    if(ret == 0) {
        chsc6x_info("Enable dbcheck OK \r\n");
    }else{
        chsc6x_info("Enable dbcheck failed \r\n");
    }
}

void chsc6x_palmcheck(void)
{
    unsigned char buft[1] = {0};
    int ret = -1;
    chsc6x_tp_reset();
    ret = chsc6x_write_bytes_u16addr_sub(CHSC6X_I2C_ID, 0xd101, buft, 0);   //0xd100 close
    if(ret == 0) {
        chsc6x_info("Enable palmcheck OK \r\n");
    }else{
        chsc6x_info("Enable palmcheck failed \r\n");
    }
}

void chsc6x_init(void)
{
    int i = 0;
    //int ret = 0;  
    struct ts_fw_infos fw_infos;
    //1:update OK, !0 fail
    unsigned char fw_update_ret_flag = 0; 

    chsc6x_iic_init(tp_iic_hdl());

    chsc6x_tp_reset();

    printf("%s:%d\n", __func__, tp_iic_hdl());

#if 0 
    u8 cnt = 5;
    int ret = -1;
    unsigned char data;
    while(cnt && ret == -1)
    {
        ret = chsc6x_read_bytes_u16addr_sub(CHSC6X_I2C_ID, 0x9FF8, &data, 1);
        cnt--;
    }
#endif

#if 0
    for(i = 0; i < 3; i++) 
    {
        ret = chsc6x_tp_dect(&fw_infos, &fw_update_ret_flag);
        if(1 == ret) {
          #if CHSC6X_AUTO_UPGRADE /* If need update FW */
            chsc6x_info("chsc6x_tp_dect succeed!\r\n");    
            if(1 == fw_update_ret_flag) {
                chsc6x_err("update fw succeed! \r\n"); 
                break;
            } else {
                chsc6x_err("update fw failed! \r\n"); 
            }
          #else
            break;
          #endif
        }else {
            chsc6x_err("chsc6x_tp_dect failed! i = %d \r\n", i);    
        }
    }
#endif
}
#endif

#endif