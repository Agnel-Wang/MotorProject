#include "beep.h"
#include "led.h"

const uint16_t musicArray[] = {
    263,163,163,264,265,
    1363,162,362,
    261,161,161,262,263,
    1363,157,457,
    256,263,462,
    256,263,462,
    256,263,362,161,
    661,260,
    263,163,163,264,265,
    1363,162,362,
    261,161,161,262,263,
    1363,157,457,
    256,263,462,
    256,263,462,
    256,263,362,161,
    661,260,
    163,162,465,
    164,1163,
    163,1162,462,165,164,
    263,164,365,263,
    462,160,161,
    255,1162,1161,461,
    164,163,164,163,461,
    164,163,361,162,
    661,260,440,440,440,440};

const uint16_t soundFrequ[7][7] = {
    // CDEFGAB
    {33,37,41,46,49,55,61              }, //C1    0
    {65,73,82,92,98,110,123            }, //C     1
    {130,146,164,185,196,220,246       }, //c     2
    {262,294,330,370,392,440,494       }, //c1    3    d
    {523,587,659,740,784,880,987       }, //c2    4	 e
    {1047,1175,1319,1480,1568,1760,1976}, //c3    5	 f
    {2093,2349,2637,2960,3136,3520,3951} //c4    6    g
};


void setPWMState(FunctionalState new_state) {
    TIM_Cmd(TIM1, new_state);
    TIM_CtrlPWMOutputs(TIM1, new_state);
}

void setPWM(uint16_t psc, uint32_t arr) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
     /* Timer clock = sysclock / (TIM_Prescaler + 1) */
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_Pulse = arr / 100;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
}

void setPWMFre(uint16_t fre) {
    /* pwm fre = clk / ((prescaler + 1) * (arr + 1))*/
    /* arr = (clk / (fre * (prescaler + 1))) - 1*/
   uint16_t psc = 16800;
   uint32_t arr = SystemCoreClock / (fre * (psc + 1)) - 1;
   setPWM(psc, arr);
}

void playNote(uint16_t fre) {
    setPWMState(DISABLE);
    setPWMFre(fre);
    setPWMState(ENABLE);
}


void playMusic() {
    uint16_t note_cnt = 0;
    uint16_t base_note_long = 1000 * 60 / 120 / 2;
    uint8_t main_scale = 5;
    uint16_t sound_time = 0, beat_time = 0;
    uint8_t note_scale;
    uint8_t note_degree;
    uint8_t note_long;
    uint8_t note_mode;
    for (note_cnt = 0; note_cnt < (sizeof(musicArray) >>1); ++note_cnt) {
        if (note_cnt % 2) LED_ALL_OFF();
        else LED_ALL_ON();
        note_scale = (musicArray[note_cnt] % 10);
        note_degree = (musicArray[note_cnt] / 10 % 10);
        note_long = (musicArray[note_cnt] / 100) % 10;
        note_mode = (musicArray[note_cnt] / 1000);
        note_degree = main_scale + note_degree - 5;
        beat_time = base_note_long * note_long;
        sound_time = (uint16_t)(beat_time * 0.8);
        if (note_scale)
            playNote(soundFrequ[note_degree][note_scale - 1]);
        delayms(sound_time);
        if (!note_mode)
            setPWMState(DISABLE);
        delayms(beat_time - sound_time);
    }
    setPWMState(DISABLE);
}

void tim1PWMInit(uint16_t psc, uint16_t arr, FunctionalState new_state) {
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource_BEEP, GPIO_AF_TIM1);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_BEEP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    setPWM(psc, arr);
    setPWMState(new_state);
}

void beepInit() {
    /* pwm fre = clk / ((prescaler + 1) * (arr + 1))*/
    /* arr = (clk / (fre * (prescaler + 1))) - 1*/
	tim1PWMInit(0, SystemCoreClock / 1000 - 1, DISABLE);
}

void beepShow(uint8_t num) {
	for(int i=0; i<num; i++)
	{
		setPWMState(ENABLE);delayms(100);
		setPWMState(DISABLE);delayms(100);
	}
}

void beepTask(void *pdata) {
    beepInit();
    beepShow(2);
    while (1) {
        //playMusic();
        delayms(20);
    }
}
