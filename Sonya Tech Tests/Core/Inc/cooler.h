#include "stm32f1xx_hal.h"
#include <stdbool.h>
#include "cmsis_os.h"
#include <math.h>


#define KP_COOLER 18.0f
#define KI_COOLER 1.0f
#define KD_COOLER 2.0f

#define SET_COOLER_TEMP -5

// Define PWM limits for cooling fan control
#define PWM_MIN_COOLER 0
#define PWM_MAX_COOLER 100

#define NUMSAMPLES 20                  //Number of ADC samples to average for better measurement accuracy
#define SERIESRESISTOR 10000          //Value of the series resistor in ohms
#define THERMISTORNOMINAL 10000       //Nominal resistance of the thermistor at 25°C in ohms
#define TEMPERATURENOMINAL 25           //Nominal temperature for the thermistor resistance in degrees Celsius
#define BCOEFFICIENT 3950              //Beta coefficient of the thermistor, typically between 3000 and 4000



uint16_t calculatePIDCooler(float current_temp, int target_temp);

void coolerOn(TIM_HandleTypeDef *htim2, ADC_HandleTypeDef *hadc1);
