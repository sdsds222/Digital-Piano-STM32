#ifndef __LEDS_H
#define __LEDS_H

void LEDS_Init(void);
void LEDS_On(uint16_t);
void LEDS_Off(uint16_t);
void LEDS_Write(uint16_t);

#endif
/*
重置PA0引脚的电平
LED_Off();
延时500毫秒
Delay_ms(500);
设置PA0引脚的电平为高点平
LED_On();
延时500毫秒
Delay_ms(500);
直接向ODR寄存器输出~0000 0000 0000 0001，16位二进制分别对应PA0到PA15共16个端口,低电平点亮，所以按位取反。
LED_Write(~0x0001);
*/

