/*说明：A工程为生成bin文件的工程 B工程为被加载的工程
        这个文件为B工程
*/
#include "asm/includes.h"
#include "media/includes.h"
#include "overlay_code.h"
#define OVERLAY_IN_FLASH_NAME "OVERLAY"   //isd_config_rule 文件配置
#define SDFILE_INSIDE_OVERLAY_ROOT_PATH       	SDFILE_MOUNT_PATH"/app/"OVERLAY_IN_FLASH_NAME  //分区
typedef struct func_op{
    
    char index; //0x1 int 0x2 char *s  0x03为 int char *s的参数的函数
    union overlay_text
    {
        /* data */
        
        int  (*func_op_1)(int x);
        int  (*func_op_2)(char *s);
        int  (*func_op_3)(char *s,int x);
    };
    
    
}func_Type;//注册函数的结构体
 char func_flash[] =
{
    0x76, 0x04, 0x05, 0x16, 0xC0, 0xFF, 0x00, 0x00, 0x10, 0x00, 0x14, 0xD6, 0x82, 0x60, 0xC6, 0xFF, 
    0x04, 0x00, 0x10, 0x00, 0x41, 0x22, 0x60, 0x16, 0xC2, 0x00, 0x50, 0xD6, 0x61, 0x61, 0xC1, 0x00, 
    0x50, 0xD6, 0x62, 0x63, 0x41, 0x16, 0xC2, 0x00, 0x56, 0x04, 

};//加载到该工程函数的数组（由bin文件生成）
 char array_data[] =
{
    0x49, 0x20, 0x44, 0x41, 0x54, 0x41, 0x5F, 0x42, 0x55, 0x46, 0x31, 0x3A, 0x5E, 0x56, 0x5E, 0x00, 
    0x49, 0x20, 0x44, 0x41, 0x54, 0x41, 0x5F, 0x42, 0x55, 0x46, 0x32, 0x3A, 0x5E, 0x56, 0x5E, 0x00, 

};//这是A工程要加载到B工程的data段数据

func_Type arry_fun_buf[10] = {
    {2,puts},
    {3,(put_buf)},
};//放置要注册的函数，比如说A工程 函数下用到了puts 这里就要提供一个puts函数的接口
SEC_USED(.overlay_text_bss)
func_Type text_buf[10]; //做一个媒介作用，给A工程下的函数提供在函数里面使用到的函数 如上面的puts
SEC_USED(.overlay_text_bss)
int (*inface_fun)(func_Type *buf,int func_num); //注册函数的接口
AT(.overlay_text_data)
 u8 overlay_text_data[256];
 int Registering_Interface(func_Type *buf, int func_num)
 {

    int cnt = 0;
    for ((cnt) = 0; cnt < func_num; (cnt)++)
    {
        switch (arry_fun_buf[cnt].index)
        {
            // printf("switch");
        case 0x01:
            buf[cnt].func_op_1 = arry_fun_buf[cnt].func_op_1 ;
            break;
        case 0x02:
            buf[cnt].func_op_2 = arry_fun_buf[cnt].func_op_2;

            break;
        case 0x03:
            buf[cnt].func_op_3 = arry_fun_buf[cnt].func_op_2;

            break;
        }
    }
 }
 u32 org_addr_text;
 static void overlay_load_code_flash(u32 type)
 {
    /*为了获取存放的flash地址*/
    FILE *fd = fopen(SDFILE_INSIDE_OVERLAY_ROOT_PATH, "r");
    struct vfs_attr attr = {0};
    fget_attrs(fd, &attr);
    u32 part_addr = attr.sclust;
    printf("attr.sclust:0x%x", part_addr);
    u32 part_len = attr.fsize;
    part_addr = sdfile_cpu_addr2flash_addr(part_addr);
    fclose(fd);

    printf("part_addr at addr: 0x%x\n", part_addr);
    printf("array at addr: %d\n", sizeof(func_flash));
    printf("func_flash add:0x%x", func_flash);
    /*flash写操作 写擦除在写*/
    norflash_erase(IOCTL_ERASE_SECTOR, part_addr);

    norflash_write(NULL, func_flash, sizeof(func_flash), part_addr); // 将A工程的bin文件写入到flash
    org_addr_text = sdfile_flash_addr2cpu_addr(part_addr);           // 获取从flash启动的地址
    printf("org_addr=%x", (org_addr_text));
    put_buf(org_addr_text, sizeof(func_flash));
    memcpy(overlay_text_data, array_data, sizeof(array_data)); // 拷贝data段的数据
 }
 /*func_flash_demo
    char *s:要打印的数组
    int put_num：要打印数组的多少个数据
    (*inface_fun)(func_Type *buf,int func_num)：接口函数 这里是Registering_Interface
    func_Type *buf_inface :存放要注册函数的结构体
    */
 static void overlay_demo_timer_flash(void *p)
 {
    void (*flash_demo_func)(char *s, int put_num, int (*inface_fun)(func_Type *buf, int func_num), func_Type *buf_inface);
    inface_fun = Registering_Interface;     // 链接一下接口函数的地址
    overlay_load_code_flash(OVERLAY_DEMO3); // 下载函数到flash
    flash_demo_func = org_addr_text;        // 刚刚获取到的flash地址 让函数指针指向他
    flash_demo_func("array_data_flash", 5, Registering_Interface, text_buf);
 }

 void overlay_demo_init_demo(void)
 {
    sys_timer_add(NULL, overlay_demo_timer_flash, 1000);
 }