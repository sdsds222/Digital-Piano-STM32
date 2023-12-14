#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Key.h"

void Key_Init()
{

    // 使能RCC（复位和时钟控制）APB2外设的时钟。APB2总线主要负责GPIO、I2C、SPI、TIM等外设。
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 定义一个类型为GPIO_InitTypeDef的结构体变量，这个结构体主要用于初始化GPIO
    GPIO_InitTypeDef GPIO_InitStructure;

    // 设置GPIO的工作模式为上拉输入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

    // 设置需要初始化的GPIO的引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_15 |  GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_1;

    // 设置GPIO的频率为50MHz，这个设置是根据具体硬件的要求来的，频率越高，信号传输越快，但同时也会带来更多的噪声和功耗
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    // 初始化GPIOB，使用指定的初始化结构体
    GPIO_Init(GPIOB, &GPIO_InitStructure);

}


u8 Key_GetNum(u16 key)
{
    u8 keyNum = 0;

    if(GPIO_ReadInputDataBit(GPIOB, key) == 0) {
        Delay_ms(20);

        while(GPIO_ReadInputDataBit(GPIOB, key) == 0);

        Delay_ms(20);
        keyNum = 1;
    }

    return keyNum;
}

void Key_Listen(u16 key, KeyCallback callback)
{
    if(GPIO_ReadInputDataBit(GPIOB, key) == 0) {
        callback(KEY_DOWN, 0);
        Delay_ms(20);
        u16 deltaTime = 0;

        while(GPIO_ReadInputDataBit(GPIOB, key) == 0) {
            deltaTime++;
            Delay_ms(1);
        }

        callback(KEY_UP, deltaTime + 40);
        Delay_ms(20);
    }

}

KeyState Key_GetState(u16 key)
{
    u8 state = GPIO_ReadInputDataBit(GPIOB, key);

    if(state == 0) {
        return KEY_DOWN;
    } else {
        return KEY_UP;
    }
}
