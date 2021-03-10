#include "main.h"
#include "led.h"
#include "beep.h"

/**** Ucosii Tasks Set ****/
#define DEFALUT_TASK_STK_SIZE 128
#define START_TASK_PRIO 10
OS_STK OSStartTasksStk[DEFALUT_TASK_STK_SIZE];
#define LED_TASK_PRIO 7
OS_STK OSLedTasksStk[DEFALUT_TASK_STK_SIZE];
#define BEEP_TASK_PRIO 8
OS_STK OSBeepTasksStk[DEFALUT_TASK_STK_SIZE];

void startTasks(void *pdata) {
    OS_CPU_SR cpu_sr;

    OS_ENTER_CRITICAL();
    OS_CPU_SysTickInit(SystemCoreClock / OS_TICKS_PER_SEC);
    OS_EXIT_CRITICAL(); 

    OSStatInit();

    OSTaskCreate(ledTask, NULL, &OSLedTasksStk[DEFALUT_TASK_STK_SIZE - 1], LED_TASK_PRIO);
    //OSTaskCreate(beepTask, NULL, &OSBeepTasksStk[DEFALUT_TASK_STK_SIZE - 1], BEEP_TASK_PRIO);

    OSTaskDel(OS_PRIO_SELF);
}

int main()
{
	RCC->AHB1ENR |= 7<<0;//使能PORTA，PORTB, PORTC时钟
    OSInit();
    OSTaskCreate(startTasks, NULL, &OSStartTasksStk[DEFALUT_TASK_STK_SIZE - 1], START_TASK_PRIO);
    OSStart();
    return 0;
}