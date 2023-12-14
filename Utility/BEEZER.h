#ifndef __BEEZER_H
#define __BEEZER_H
void BEEZER_Init(uint16_t, uint16_t);
void BEEZER_Play(uint16_t, uint8_t);
void BEEZER_Stop(void);
#endif
/*https://blog.csdn.net/weixin_59681811/article/details/124520449


    uint8_t i;
    const uint8_t maxNum = 16;



    while(1) {
        uint16_t state = 0x0001;

        for(i = 1; i < maxNum; i++) {

            if(i == 1) {
                LEDS_Write(~(0x0001));
                continue;
            }

            if(i <= maxNum / 2) {
                state <<= 1;
                LEDS_Write(~(state));
            } else {
                state >>= 1;
                LEDS_Write(~(state));
            }

            uint8_t t = i;

            if(t > maxNum / 2) {
                t = maxNum / 2 - (t - maxNum / 2);
            }

            BEEZER_Play(t - 1, 0); //蜂鸣器播放
            Delay_ms(100);
            BEEZER_Stop();//蜂鸣器停止播放

            Delay_ms(100);

            while(1) {
                if(Key_GetNum(GPIO_Pin_15) != 0) {
                    break;
                }
            }
        }


    }
*/
