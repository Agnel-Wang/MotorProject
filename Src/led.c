#include "led.h"

uint16_t gpio_pin_leds[4] = {GPIO_Pin_GREEN, GPIO_Pin_BLUE, GPIO_Pin_YELLOW, GPIO_Pin_RED};

void ledInit(void) {
    GPIO_Set(GPIOA,PIN4|PIN5|PIN6|PIN7,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_2M,GPIO_PUPD_NONE);
}

void ledShiftingON(uint8_t dir) {
    if (dir) {
        for (uint8_t i = 0; i < GPIO_Pin_LEDs_Num; ++i) {
            LED_ON(GPIO_LEDs, gpio_pin_leds[i]);
            delayms(500);
        }
    } else {
        for (uint8_t i = GPIO_Pin_LEDs_Num; i > 0; --i) {
            LED_ON(GPIO_LEDs, gpio_pin_leds[i - 1]);
            delayms(500);
        }
    }
}

void ledShiftingOFF(uint8_t dir) {
    if (dir) {
        for (uint8_t i = 0; i < GPIO_Pin_LEDs_Num; ++i) {
            LED_OFF(GPIO_LEDs, gpio_pin_leds[i]);
            delayms(500);
        }
    } else {
        for (uint8_t i = GPIO_Pin_LEDs_Num; i > 0; --i) {
            LED_OFF(GPIO_LEDs, gpio_pin_leds[i - 1]);
            delayms(500);
        }
    }
}

void ledShowCPUUsage() {
    LED_ALL_OFF();
    if (OSCPUUsage < 25) {
        LED_GREEN_ON();
    } else if (OSCPUUsage < 50) {
        LED_GREEN_ON();
        LED_BLUE_ON();
    } else if (OSCPUUsage < 75) {
        LED_GREEN_ON();
        LED_BLUE_ON();
        LED_RED_ON();
    } else {
        LED_ALL_ON();
    }
}

void ledShow() {
	LED_RED_ON();delayms(200);
	LED_YELLOW_ON();delayms(200);
	LED_BLUE_ON();delayms(200);
	LED_GREEN_ON();delayms(200);
	LED_RED_OFF();delayms(200);
	LED_YELLOW_OFF();delayms(200);
	LED_BLUE_OFF();delayms(200);
	LED_GREEN_OFF();delayms(200);
}

void ledTask(void *pdata) {
    ledInit();
    LED_ALL_OFF();
    while (1) {
        ledShow();
        delayms(10);
    }
}