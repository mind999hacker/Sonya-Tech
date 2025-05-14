#ifndef rotary_h
#define rotary_h

#include "main.h"


// Disable this emit codes once per step instead of twice.
#define HALF_STEP

// Values returned by 'process'
// No complete step yet.
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Anti-clockwise step.
#define DIR_CCW 0x20
// Default start state
#define R_START 0x0

unsigned char Pin_process(unsigned int , unsigned int );


#endif


/**** SAMPLE CODE ****
 *
 *
pinb5 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5);   //digital read on STM32
pinb6 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6);   //digital read on STM32

result = Pin_process(pinb5,pinb6);
if (result == DIR_CW) {
      count++;
      HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    } else if (result == DIR_CCW) {
      --count;
      HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }
 */
