#include <reg52.h>
#include <uart.h>

sbit Key = P1^0;
sbit Parse = P1^2;
sbit LED = P0^0;

void delay(unsigned int i);
void Uart_Init();

void main(){
    Uart_Init();
    delay(1000);
    
    while (1){
        if (!Key){
            delay(10000);
            if(!Key){
                LED = ~LED;
                UartPrintf("hello!");
                }else{
                    continue;
                }
        }
    }
}

void delay(unsigned int i){
    while(i--);
}
