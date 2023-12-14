#ifndef __Key_H
#define __Key_H
typedef enum{ KEY_UP = 0, KEY_DOWN = 1 } KeyState ;
typedef void (*KeyCallback)(KeyState,u16 Time);
void Key_Init(void);
u8 Key_GetNum(u16);
void Key_Listen(u16,KeyCallback);
KeyState Key_GetState(u16 key);
#endif
