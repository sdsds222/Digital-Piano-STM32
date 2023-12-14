#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "PWM.h"
#include "LEDS.h"
#include "BEEZER.h"
#include "Key.h"
#include "OLED.h"
#define MAX_SAVE_SIZE 2048

void KeyCallback1(KeyState, u16);
void KeyCallback2(KeyState, u16);
void KeyCallback3(KeyState, u16);
void KeyCallback4(KeyState, u16);
void KeyCallback5(KeyState, u16);
void KeyCallback6(KeyState, u16);
void KeyCallback7(KeyState, u16);
void clear_save_array(void);
void add_save_array(u16, u16, u16);
void Start_Interface(void);

u8 record_mode = 0;
u16 space_time = 0;
u8 musicMode = 0;
uint16_t save_array[MAX_SAVE_SIZE][3] = {200};
uint16_t save_index = 0;

int main()
{
    LED_Init();
    //PWM_Init();
    //LEDS_Init();
    Key_Init();
    OLED_Init();

    Start_Interface();

    while(1) {



        if(Key_GetState(GPIO_Pin_1) == KEY_DOWN) {
            space_time = 0;
            save_index = 0;
            record_mode = 0;
            Delay_ms(20);

            while(Key_GetState(GPIO_Pin_1) == KEY_DOWN) {}

            OLED_SetSystemMode("<Play Mode>", 20);

            for(u16 i = 0; i < MAX_SAVE_SIZE; i++) {
                u16 cmd = save_array[i][0];
                u16 play_mode = save_array[i][1];
                u16 wait_time = save_array[i][2];

                if(cmd == 200 || Key_GetState(GPIO_Pin_12) == KEY_DOWN) {
					OLED_ClearNowSystemMode();
                    Start_Interface();
                    break;
                } else if(cmd == 100) {
                    if(i != 0) {
                        while(wait_time--) {
                            Delay_ms(1);
                        }
                    }

                } else if(cmd == 0) {
                    BEEZER_Play(0, play_mode);
                    LED_On(GPIO_Pin_6);

                    if(play_mode == 0) {
                        OLED_PrintMusicChar('1');
                    } else {
                        OLED_PrintMusicChar('A');
                    }

                    while(wait_time--) {
                        Delay_ms(1);
                    }

                    BEEZER_Stop();
                    LED_Off(GPIO_Pin_6);

                } else if(cmd == 1) {
                    BEEZER_Play(1, play_mode);
                    LED_On(GPIO_Pin_5);

                    if(play_mode == 0) {
                        OLED_PrintMusicChar('2');
                    } else {
                        OLED_PrintMusicChar('B');
                    }

                    while(wait_time--) {
                        Delay_ms(1);
                    }

                    BEEZER_Stop();
                    LED_Off(GPIO_Pin_5);

                } else if(cmd == 2) {
                    BEEZER_Play(2, play_mode);
                    LED_On(GPIO_Pin_4);

                    if(play_mode == 0) {
                        OLED_PrintMusicChar('3');
                    } else {
                        OLED_PrintMusicChar('C');
                    }

                    while(wait_time--) {
                        Delay_ms(1);
                    }

                    BEEZER_Stop();
                    LED_Off(GPIO_Pin_4);

                } else if(cmd == 3) {
                    BEEZER_Play(3, play_mode);
                    LED_On(GPIO_Pin_3);

                    if(play_mode == 0) {
                        OLED_PrintMusicChar('4');
                    } else {
                        OLED_PrintMusicChar('D');
                    }

                    while(wait_time--) {
                        Delay_ms(1);
                    }

                    BEEZER_Stop();
                    LED_Off(GPIO_Pin_3);

                } else if(cmd == 4) {
                    BEEZER_Play(4, play_mode);
                    LED_On(GPIO_Pin_2);

                    if(play_mode == 0) {
                        OLED_PrintMusicChar('5');
                    } else {
                        OLED_PrintMusicChar('E');
                    }

                    while(wait_time--) {
                        Delay_ms(1);
                    }

                    BEEZER_Stop();
                    LED_Off(GPIO_Pin_2);

                } else if(cmd == 5) {
                    BEEZER_Play(5, play_mode);
                    LED_On(GPIO_Pin_1);

                    if(play_mode == 0) {
                        OLED_PrintMusicChar('6');
                    } else {
                        OLED_PrintMusicChar('F');
                    }

                    while(wait_time--) {
                        Delay_ms(1);
                    }

                    BEEZER_Stop();

                    LED_Off(GPIO_Pin_1);

                } else if(cmd == 6) {
                    BEEZER_Play(6, play_mode);
                    LED_On(GPIO_Pin_0);

                    if(play_mode == 0) {
                        OLED_PrintMusicChar('7');
                    } else {
                        OLED_PrintMusicChar('G');
                    }

                    while(wait_time--) {
                        Delay_ms(1);
                    }

                    BEEZER_Stop();
                    LED_Off(GPIO_Pin_0);

                }
            }
        }



        if(Key_GetState(GPIO_Pin_15) == KEY_DOWN) {
            Delay_ms(20);

            while(Key_GetState(GPIO_Pin_15) == KEY_DOWN) {}

            if(record_mode == 0) {

                OLED_SetSystemMode("<Record Mode>", 20);
                clear_save_array();
                space_time = 0;
                save_index = 0;
                record_mode = 1;
            } else {
				
                clear_save_array();

                space_time = 0;
                save_index = 0;
				record_mode =0;
				OLED_ClearNowSystemMode();
				Start_Interface();
            }
        }


        if(record_mode == 1) {
            space_time++;
            Delay_ms(1);
        }


        if(Key_GetState(GPIO_Pin_12) == KEY_DOWN) {
            musicMode = 1;
        } else {
            musicMode = 0;
        }

        Key_Listen(GPIO_Pin_4, KeyCallback1);
        Key_Listen(GPIO_Pin_5, KeyCallback2);
        Key_Listen(GPIO_Pin_6, KeyCallback3);
        Key_Listen(GPIO_Pin_7, KeyCallback4);
        Key_Listen(GPIO_Pin_8, KeyCallback5);
        Key_Listen(GPIO_Pin_9, KeyCallback6);
        Key_Listen(GPIO_Pin_14, KeyCallback7);


    }
}

void Start_Interface()
{
    OLED_ShowStringSlow(1, "<Digital Piano> ", 20);
    OLED_ShowStringSlow(2, "Version:1.0     ", 20);
    OLED_ShowStringSlow(3, "Dev by sdsds222 ", 20);
    OLED_ShowStringSlow(4, "2023/12/14      ", 20);
}

void KeyCallback1(KeyState keyState, u16 time)
{
    if(keyState == KEY_DOWN) {
        if(record_mode == 1) {
            add_save_array(100, 100, space_time);
        }

        BEEZER_Play(0, musicMode);
        LED_On(GPIO_Pin_6);

        if(musicMode == 0) {
            OLED_PrintMusicChar('1');
        } else {
            OLED_PrintMusicChar('A');
        }
    }

    if(keyState == KEY_UP) {
        BEEZER_Stop();
        LED_Off(GPIO_Pin_6);

        if(record_mode == 1) {
            add_save_array(0, musicMode, time);
        }
    }

}
void KeyCallback2(KeyState keyState, u16 time)
{
    if(keyState == KEY_DOWN) {
        if(record_mode == 1) {
            add_save_array(100, 100, space_time);
        }

        BEEZER_Play(1, musicMode);
        LED_On(GPIO_Pin_5);

        if(musicMode == 0) {
            OLED_PrintMusicChar('2');
        } else {
            OLED_PrintMusicChar('B');
        }
    }

    if(keyState == KEY_UP) {
        BEEZER_Stop();
        LED_Off(GPIO_Pin_5);

        if(record_mode == 1) {
            add_save_array(1, musicMode, time);
        }
    }

}

void KeyCallback3(KeyState keyState, u16 time)
{
    if(keyState == KEY_DOWN) {
        if(record_mode == 1) {
            add_save_array(100, 100, space_time);
        }

        BEEZER_Play(2, musicMode);
        LED_On(GPIO_Pin_4);

        if(musicMode == 0) {
            OLED_PrintMusicChar('3');
        } else {
            OLED_PrintMusicChar('C');
        }

    }

    if(keyState == KEY_UP) {
        BEEZER_Stop();
        LED_Off(GPIO_Pin_4);

        if(record_mode == 1) {
            add_save_array(2, musicMode, time);
        }
    }

}

void KeyCallback4(KeyState keyState, u16 time)
{
    if(keyState == KEY_DOWN) {
        if(record_mode == 1) {
            add_save_array(100, 100, space_time);
        }

        BEEZER_Play(3, musicMode);
        LED_On(GPIO_Pin_3);

        if(musicMode == 0) {
            OLED_PrintMusicChar('4');
        } else {
            OLED_PrintMusicChar('D');
        }
    }

    if(keyState == KEY_UP) {
        BEEZER_Stop();
        LED_Off(GPIO_Pin_3);

        if(record_mode == 1) {
            add_save_array(3, musicMode, time);
        }
    }

}

void KeyCallback5(KeyState keyState, u16 time)
{
    if(keyState == KEY_DOWN) {
        if(record_mode == 1) {
            add_save_array(100, 100, space_time);
        }

        BEEZER_Play(4, musicMode);
        LED_On(GPIO_Pin_2);

        if(musicMode == 0) {
            OLED_PrintMusicChar('5');
        } else {
            OLED_PrintMusicChar('E');
        }
    }

    if(keyState == KEY_UP) {
        BEEZER_Stop();
        LED_Off(GPIO_Pin_2);

        if(record_mode == 1) {
            add_save_array(4, musicMode, time);
        }
    }

}

void KeyCallback6(KeyState keyState, u16 time)
{
    if(keyState == KEY_DOWN) {
        if(record_mode == 1) {
            add_save_array(100, 100, space_time);
        }

        BEEZER_Play(5, musicMode);
        LED_On(GPIO_Pin_1);

        if(musicMode == 0) {
            OLED_PrintMusicChar('6');
        } else {
            OLED_PrintMusicChar('F');
        }
    }

    if(keyState == KEY_UP) {
        BEEZER_Stop();
        LED_Off(GPIO_Pin_1);

        if(record_mode == 1) {
            add_save_array(5, musicMode, time);
        }
    }

}

void KeyCallback7(KeyState keyState, u16 time)
{
    if(keyState == KEY_DOWN) {
        if(record_mode == 1) {
            add_save_array(100, 100, space_time);
        }

        BEEZER_Play(6, musicMode);
        LED_On(GPIO_Pin_0) ;

        if(musicMode == 0) {
            OLED_PrintMusicChar('7');
        } else {
            OLED_PrintMusicChar('G');
        }
    }

    if(keyState == KEY_UP) {
        BEEZER_Stop();
        LED_Off(GPIO_Pin_0);

        if(record_mode == 1) {
            add_save_array(6, musicMode, time);
        }
    }

}

void clear_save_array()
{
    for (u16 i = 0; i < MAX_SAVE_SIZE; i++) {
        for (u16 j = 0; j < 3; j++) {
            save_array[i][j] = 200;
        }
    }
}

void add_save_array(u16 cmd, u16 mode, u16 time)
{
    save_array[save_index][0] = cmd;
    save_array[save_index][1] = mode;
    save_array[save_index][2] = time;
    space_time = 0;
    save_index++;
}


