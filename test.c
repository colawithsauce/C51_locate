#include <reg52.h>
#include <uart.h>

sbit Key = P1^0;
sbit LED = P0^0;

void delay(unsigned int i);

void main(){
    Uart_Init();
    delay(1000);
    while (1){
        if (!Key){
            LED = ~LED
            UartPrintf("Hello");
        }else{
            continue;
        }
    }
}

void delay(unsigned int i){
    while(i--);
}