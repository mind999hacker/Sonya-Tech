

#include "cooler.h"

float integral_cooler = 0.0f;
float previous_error_cooler = 0.0f;

float samples[NUMSAMPLES];          //Array to store ADC sample values
uint8_t i;                       //Loop counter for sampling


uint16_t calculatePIDCooler(float current_temp, int target_temp) {
    static uint32_t last_time = 0;
    uint32_t current_time = HAL_GetTick();
    float integral_cooler = 0.0f;
    float delta_time = (current_time - last_time) / 1000.0f; // Convert to seconds
    last_time = current_time;

    // Compute error (target - current)
    float error = current_temp - target_temp; // Reversed logic for cooling

    // Compute integral_cooler term
    integral_cooler += error * delta_time;

    // Compute derivative term
    float derivative = (error - previous_error_cooler) / delta_time;

    // PID formula (Negative sign because cooling increases as temperature rises)
    float output = (KP_COOLER * error + KI_COOLER * integral_cooler + KD_COOLER * derivative);

    // Clamp output to PWM limits
    if (output > PWM_MAX_COOLER) output = PWM_MAX_COOLER;
    if (output < PWM_MIN_COOLER) output = PWM_MIN_COOLER;

    // Update previous error
    previous_error_cooler = error;

    return (uint16_t)output;
}

void coolerOn(TIM_HandleTypeDef *htim2, ADC_HandleTypeDef *hadc1)
{
	float average = 0;               //Variable to store the average of ADC samples
	float cooler_temperature;                   //Variable to store the calculated temperature in Celsius

	for (i = 0; i < NUMSAMPLES; i++)
	{
		  HAL_ADC_Start(hadc1);                              //Start the ADC conversion
		  HAL_ADC_PollForConversion(hadc1, HAL_MAX_DELAY);   //Wait for the conversion to complete
		  samples[i] = HAL_ADC_GetValue(hadc1);              //Read the ADC conversion result
		  osDelay(10);                                      //Delay between samples to stabilize the ADC readings
	}

	for (i = 0; i < NUMSAMPLES; i++)
	{
		average += samples[i];  //Sum up all the ADC sample values
	}

    average /= NUMSAMPLES;  //Calculate the average of the ADC samples

    if (average > 0)
    {  // Ensure the average is not zero to avoid division errors
        average = 4094 / average - 1;  // Convert ADC reading to resistance using 12-bit ADC resolution
        average = SERIESRESISTOR / average;  // Calculate the thermistor resistance

        // Apply the cooler_temperature-Hart equation to convert resistance to temperature
        cooler_temperature = average / THERMISTORNOMINAL;  //Compute the ratio of thermistor resistance to nominal resistance
        cooler_temperature = log(cooler_temperature);  //Compute the natural logarithm of the resistance ratio
        cooler_temperature /= BCOEFFICIENT;  //Divide by the thermistor's Beta coefficient
        cooler_temperature += 1.0 / (TEMPERATURENOMINAL + 273.15);  //Add the reciprocal of the nominal temperature in Kelvin
        cooler_temperature = 1.0 / cooler_temperature;  //Compute the reciprocal to get the temperature in Kelvin
        cooler_temperature -= 273.15;  //Convert the temperature from Kelvin to Celsius


    }
    else
    {
        //HANDLE THE ERROR
    }

    osDelay(5000);


    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,1);   //PWM pin for cooler
    //TIM2->CCR2 = calculatePIDCooler(cooler_temperature, -18);
    //HAL_TIM_PWM_Start(htim2, TIM_CHANNEL_2);  //Select the write channel for pin

    if(cooler_temperature > (SET_COOLER_TEMP+5))
    {
    	TIM2->CCR2 = 100;
    	HAL_TIM_PWM_Start(htim2, TIM_CHANNEL_2);
    }
    else if (cooler_temperature > (SET_COOLER_TEMP+2))
    {
    	TIM2->CCR2 = 80;
    	HAL_TIM_PWM_Start(htim2, TIM_CHANNEL_2);
    }
    else
	{
		TIM2->CCR2 = 60;
		HAL_TIM_PWM_Start(htim2, TIM_CHANNEL_2);
	}
}







