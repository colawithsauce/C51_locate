#include "reg52.h"
#define GPRMC_TERM "$GPRMC,"    //����Ҫ������ָ���Ϊ����ָ�������λ��ʱ����Ϣ
typedef unsigned int u16;    //���������ͽ�����������
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
    SCON=0X50;          //����Ϊ������ʽ1
    TMOD=0X20;          //���ü�����������ʽ2
    PCON=0X80;          //�����ʼӱ�
    TH1=0XF3;           //��������ʼֵ���ã�ע�Ⲩ������4800��
    TL1=0XF3;
    ES=1;               //�򿪽����ж�
    EA=1;               //�����ж�
    TR1=1;              //�򿪼�����
}


void main()
{
    UsartInit();  //	���ڳ�ʼ��
    while(1);
}

void Usart() interrupt 4
{
    u8 receiveData;

    receiveData=SBUF;//��ȥ���յ�������
    RI = 0;//��������жϱ�־λ
    SBUF=receiveData;//�����յ������ݷ��뵽���ͼĴ���
    while(!TI);			 //�ȴ������������
    TI=0;						 //���������ɱ�־λ
}


/*  GPS��ʾʾ��:
        $GPRMC,115418.00,V,,,,,,,120819,,,N*76
        $GPVTG,,,,,,,,,N*30
        $GPGGA,115418.00,,,,,0,03,4.01,,,,,,*58
        $GPGSA,A,1,13,24,21,,,,,,,,,,4.14,4.01,1.00*02
        $GPGSV,1,1,03,13,09,052,26,21,61,261,27,24,73,099,34*43
        $GPGLL,,,,,115418.00,V,N*42
* */
