#ifndef __PWM_H
#define __PWM_H



void PWM_Init(uint16_t arr4,uint16_t psc);
void PWM_SetCompare3(uint16_t);


#endif
/*
for(i = 0; i < 200; i++) {
            uint8_t j = i;

            if(j > 100) {
                j = 100 - (j - 100);
            }

            PWM_SetCompare1(j);
            Delay_ms(20);
        }
*/
