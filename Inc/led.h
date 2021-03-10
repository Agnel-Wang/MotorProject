#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "common.h"
#include "delay.h"
#include "sys.h"

#define GPIO_LEDs GPIOA
#define GPIO_Pin_GREEN      GPIO_Pin_7
#define GPIO_Pin_RED        GPIO_Pin_4
#define GPIO_Pin_YELLOW     GPIO_Pin_5
#define GPIO_Pin_BLUE       GPIO_Pin_6
#define GPIO_Pin_LEDs (GPIO_Pin_GREEN | GPIO_Pin_RED | GPIO_Pin_YELLOW | GPIO_Pin_BLUE)
#define GPIO_Pin_LEDs_Num 4

#define LED_ON(GPIO, GPIO_Pin) GPIO_ResetBits(GPIO, GPIO_Pin)
#define LED_OFF(GPIO, GPIO_Pin) GPIO_SetBits(GPIO, GPIO_Pin)
#define LED_TOGGLE(GPIO, GPIO_Pin) GPIO_ToggleBits(GPIO, GPIO_Pin)

#define LED_GREEN_ON() LED_ON(GPIO_LEDs, GPIO_Pin_GREEN)
#define LED_GREEN_OFF() LED_OFF(GPIO_LEDs, GPIO_Pin_GREEN)
#define LED_GREEN_TOGGLE() LED_TOGGLE(GPIO_LEDs, GPIO_Pin_GREEN)

#define LED_RED_ON() LED_ON(GPIO_LEDs, GPIO_Pin_RED)
#define LED_RED_OFF() LED_OFF(GPIO_LEDs, GPIO_Pin_RED)
#define LED_RED_TOGGLE() LED_TOGGLE(GPIO_LEDs, GPIO_Pin_RED)

#define LED_YELLOW_ON() LED_ON(GPIO_LEDs, GPIO_Pin_YELLOW)
#define LED_YELLOW_OFF() LED_OFF(GPIO_LEDs, GPIO_Pin_YELLOW)
#define LED_YELLOW_TOGGLE() LED_TOGGLE(GPIO_LEDs, GPIO_Pin_YELLOW)

#define LED_BLUE_ON() LED_ON(GPIO_LEDs, GPIO_Pin_BLUE)
#define LED_BLUE_OFF() LED_OFF(GPIO_LEDs, GPIO_Pin_BLUE)
#define LED_BLUE_TOGGLE() LED_TOGGLE(GPIO_LEDs, GPIO_Pin_BLUE)

#define LED_ALL_OFF() LED_OFF(GPIO_LEDs, GPIO_Pin_LEDs)
#define LED_ALL_ON() LED_ON(GPIO_LEDs, GPIO_Pin_LEDs)

struct LedType {
    GPIO_TypeDef *io_group;
    uint16_t pin;
};
void ledInit();
void ledShiftingON(uint8_t dir);
void ledShiftingOFF(uint8_t dir);
void ledTask(void *pdata);
void ledShowCPUUsage();

#ifdef __cplusplus
}
#endif

#endif