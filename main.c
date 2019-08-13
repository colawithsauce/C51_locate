#include "reg51.h"
#include "uart.h"
#include "string.h"
#define GPRMC_TERM "$GPRMC,"    //����Ҫ������ָ���Ϊ����ָ�������λ��ʱ����Ϣ
#define MAX_DATA 68
typedef unsigned int u16;    //���������ͽ�����������
typedef unsigned char u8;

//ToDo:
//    Define a struct to save data better, and use it better.
/*
struct rcvdata  {
    char position[];
    char
    char
    char
    char
};
*/

char receiveData[MAX_DATA];



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
    u8 i;
    char identity[7] = GPRMC_TERM;
    
    for (i=0; i<MAX_DATA; i++){
        receiveData[i] = SBUF;
        RI = 0;
    }//����ȫ����

    if (strncmp(identity, receiveData, 7) == 0){ //������֤λ��ȷ
        while (1){
            i++;
            if (receiveData[i] != '\n'){
                SBUF = receiveData[i];
                while(!TI);
                TI=0;
            }else{
                break;
            }
        }
    }
}


/*  GPS��ʾʾ��:
        $GPRMC,115418.00,V,,,,,,,120819,,,N*76
        $GPVTG,,,,,,,,,N*30
        $GPGGA,115418.00,,,,,0,03,4.01,,,,,,*58
        $GPGSA,A,1,13,24,21,,,,,,,,,,4.14,4.01,1.00*02
        $GPGSV,1,1,03,13,09,052,26,21,61,261,27,24,73,099,34*43
        $GPGLL,,,,,115418.00,V,N*42
* */
