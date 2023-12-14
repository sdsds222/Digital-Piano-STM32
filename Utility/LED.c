#include "stm32f10x.h"                  // Device header

void LED_Init()
{
    // 使能RCC（复位和时钟控制）APB2外设的时钟。APB2总线主要负责GPIO、I2C、SPI、TIM等外设。
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 定义一个类型为GPIO_InitTypeDef的结构体变量，这个结构体主要用于初始化GPIO
    GPIO_InitTypeDef GPIO_InitStructure;

    // 设置GPIO的工作模式为推挽输出，这是最常见的模式，即高电平有效，输出1，低电平有效，输出0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    // 设置需要初始化的GPIO的引脚，这里设置的是GPIOA的第0脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;

    // 设置GPIO的频率为50MHz，这个设置是根据具体硬件的要求来的，频率越高，信号传输越快，但同时也会带来更多的噪声和功耗
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    // 使用GPIO的初始化函数进行初始化，参数为GPIOA和刚才定义的结构体指针
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_Write(GPIOA, 0x00ff);
}

void LED_On(uint16_t pin)
{
    //重置PA0引脚的电平
    GPIO_ResetBits(GPIOA, pin);
}

void LED_Off(uint16_t pin)
{
    //设置PA0引脚的电平为高点平
    GPIO_SetBits(GPIOA, pin);
}

void LED_Write(uint16_t PortVal)
{
    //将值写入输出数据寄存器，例如：~0x0001
    GPIO_Write(GPIOA, PortVal);
}
