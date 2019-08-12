#include "reg52.h"
#define GPRMC_TERM "$GPRMC,"    //定义要解析的指令，因为这条指令包含定位和时间信息
typedef unsigned int u16;    //对数据类型进行声明定义
typedef unsigned char u8;

//ToDo:
//    Define a struct to save data better, and use it better.
/*
struct rcvdata  {
    char position[];
    char 
};
*/

char receiveData[68] = {};



void UsartInit()
{
    SCON=0X50;          //设置为工作方式1
    TMOD=0X20;          //设置计数器工作方式2
    PCON=0X80;          //波特率加倍
    TH1=0XF3;           //计数器初始值设置，注意波特率是4800的
    TL1=0XF3;
    ES=1;               //打开接收中断
    EA=1;               //打开总中断
    TR1=1;              //打开计数器
}


void main()
{
    UsartInit();  //	串口初始化
    while(1);
}

void Usart() interrupt 4
{
    u8 receiveData;

    receiveData=SBUF;//出去接收到的数据
    RI = 0;//清除接收中断标志位
    SBUF=receiveData;//将接收到的数据放入到发送寄存器
    while(!TI);			 //等待发送数据完成
    TI=0;						 //清除发送完成标志位
}


/*  GPS显示示例:
        $GPRMC,115418.00,V,,,,,,,120819,,,N*76
        $GPVTG,,,,,,,,,N*30
        $GPGGA,115418.00,,,,,0,03,4.01,,,,,,*58
        $GPGSA,A,1,13,24,21,,,,,,,,,,4.14,4.01,1.00*02
        $GPGSV,1,1,03,13,09,052,26,21,61,261,27,24,73,099,34*43
        $GPGLL,,,,,115418.00,V,N*42
* */
