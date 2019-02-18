/* ADC2 Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "driver/dac.h"
#include "esp_system.h"
#include "esp_adc_cal.h"

// #define DAC_EXAMPLE_CHANNEL     CONFIG_DAC_EXAMPLE_CHANNEL
#define Channel_X	32 //gpio 13
#define Channel_Y	34 //gpio 12
#define Channel_Btn	35 //gpio 14



void app_main(void)
{
    int state[3];
	
	gpio_pad_select_gpio(Channel_X);
 	gpio_set_pull_mode(Channel_X,GPIO_PULLUP_ONLY);
    gpio_set_direction(Channel_X, GPIO_MODE_INPUT);
	
	gpio_pad_select_gpio(Channel_Y);
 	gpio_set_pull_mode(Channel_Y,GPIO_PULLUP_ONLY);
    gpio_set_direction(Channel_Y, GPIO_MODE_INPUT);
    
    gpio_pad_select_gpio(Channel_Btn);
 	gpio_set_pull_mode(Channel_Btn,GPIO_PULLUP_ONLY);
    gpio_set_direction(Channel_Btn, GPIO_MODE_INPUT);

    printf("start conversion.\n");
    while(1) {
	    state[0] = gpio_get_level(Channel_X);
	    state[1] = gpio_get_level(Channel_Y);
	    state[2] = gpio_get_level(Channel_Btn);
	
		printf("X : %d \n, Y : %d \n. Btn : %d \n",state[0],state[1],state[2]);

	 vTaskDelay( 2 * portTICK_PERIOD_MS );
}

}
