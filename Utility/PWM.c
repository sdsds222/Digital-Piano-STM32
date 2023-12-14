#include "stm32f10x.h"                  // Device header

void PWM_Init(uint16_t arr, uint16_t psc)
{

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    // 使能RCC（复位和时钟控制）APB2外设的时钟。APB2总线主要负责GPIO、I2C、SPI、TIM等外设。
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 定义一个类型为GPIO_InitTypeDef的结构体变量，这个结构体主要用于初始化GPIO
    GPIO_InitTypeDef GPIO_InitStructure;

    // 设置GPIO的工作模式为复用推挽输出，输出数据寄存器将被断开，切换控制权到片上外设的TIM2的CH1，高电平有效，输出1，低电平有效，输出0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

    // 设置需要初始化的GPIO的引脚，这里设置的是GPIOB的第0脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;

    // 设置GPIO的频率为50MHz，这个设置是根据具体硬件的要求来的，频率越高，信号传输越快，但同时也会带来更多的噪声和功耗
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    // 初始化GPIOB，使用指定的初始化结构体
    GPIO_Init(GPIOB, &GPIO_InitStructure);





    // 将TIM2配置为使用内部时钟
    TIM_InternalClockConfig(TIM3);

    // 定义TIM_TimeBaseInitTypeDef结构体，该结构体用于设置TIM的时间基准参数
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    // 设置TIM的时钟分频因子为1，即没有分频
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

    // 设置TIM的计数模式为向上计数模式，即当计数器达到最大值时会回滚到0
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;

    // 设置ARR（自动重载寄存器）的值，该值决定了计数器的最大值，这里设置为100-1，即最大计数值为100
    //ARR
    TIM_TimeBaseInitStructure.TIM_Period = arr;

    // 设置PSC（预分频寄存器）的值，该值决定了时钟分频的因子，这里设置为720-1，即分频因子为720
    //PSC
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;

    // 设置重触发输出寄存器的值，这里设置为0，即不使用重触发输出功能
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;

    // 使用定义的初始化结构体来初始化TIM2的时间基准参数
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);






    // 定义TIM_OCInitTypeDef结构体，该结构体用于设置TIM的输出比较参数
    TIM_OCInitTypeDef TIM_OCInitStructure;

    //结构体赋初始值，否则会出现野指针
    TIM_OCStructInit(&TIM_OCInitStructure);

    //设置输出比较模式
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;

    //REF有效时输出高电平,有效电平为高电平，波形直接输出,设置有效电平为低电平则会翻转。
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    //设置输出使能
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

    //设置CCR捕获比较寄存器的值，值为50则占空比为50%
    //PWM频率：Freq=CK_PSC/(PSC+1)/(ARR+1)=计数器的更新频率 CK_PSC=72M
    //PWM占空比：Duty=CRR/(ARR+1)
    //PWM分辨率：Reso=1/(ARR+1)
    //ARR=100,PSC=720,CCR=50,则输出频率为1KHz，占空比为50%的PWM波形
    TIM_OCInitStructure.TIM_Pulse = 0;

    //初始化OC1。TIM2的CH1通道复用了PA0的引脚,输出PWM
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);

    //使能TIM2通用定时器
    TIM_Cmd(TIM3, ENABLE);
}


void PWM_SetCompare3(uint16_t Compare)
{

    //设置CCR捕获比较寄存器Capture/Compare Register的值
    TIM_SetCompare3(TIM3, Compare);
}

