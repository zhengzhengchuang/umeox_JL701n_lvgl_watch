#include "asm/includes.h"
#include "media/includes.h"

typedef struct func_op
{

    char index; // 0x1 int 0x2 char *s  0x03为 int char *s的参数的函数 这个可以自己去配置
    union overlay_text
    {
        /* data */

        int (*func_op_1)(int x);
        int (*func_op_2)(char *s);
        int (*func_op_3)(char *s, int x);
    };

} func_Type; // 注册函数的结构体
SEC_USED(.overlay_text_bss)
func_Type text_buf[10];
SEC_USED(.overlay_text_bss)
int (*inface_fun)(func_Type *buf, int func_num);
func_Type arry_fun_buf[10] = {
    {2,puts},
    {3,(put_buf)},
};//注册函数的结构体

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

SEC_USED(.overlay_text_data)//data段数据
u8 data_buf[] = "I DATA_BUF1:^V^";
SEC_USED(.overlay_text_data)
u8 data_buf2[] = "I DATA_BUF2:^V^";

SEC_USED(.demo3_code0)
volatile void demo3_code0(char *s, int put_num, int (*inface_fun_text)(func_Type *buf, int func_num), func_Type *buf_inface)
{
    // inface_fun_text=get_func;
    inface_fun = inface_fun_text;
    buf_inface = text_buf;
    // buf_inface[0].func_op_2=puts;
    // buf_inface[1].func_op_3=put_buf;
    inface_fun_text(buf_inface, 2);
    buf_inface[0].func_op_2(s);
    buf_inface[1].func_op_3(s, put_num);
}

/*防止编译器把函数优化 故在这加了一个函数在board_701n_demo.c里面调用了一下 没有实际意义*/
volatile void text_fun()
{
    printf("demo3_code0=0x%x", demo3_code0);
    put_buf(text_buf, sizeof(text_buf));
    put_buf(data_buf2, sizeof(data_buf2));
}

#if 0
SEC_USED(.demo3_code0)
volatile  void demo3_code0(int	(puts(const char *)),char *s)
{
    pus_text=puts;
    
    //u8 buf[32];
    //memset(buf, 0x22, sizeof(buf));
    pus_text(s);
    pus_text(data_buf);
    //put_buf(buf, 32);
}
#endif