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
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <string.h>

#define GPIO_INPUT_PIN_SEL  (1ULL<<GPIO_INPUT_IO_0)
#define OBSTACLE_GPIO 34
#define ESP_INTR_FLAG_DEFAULT 0

void app_main(void)
{    
	int read_raw;

    gpio_pad_select_gpio(OBSTACLE_GPIO);
 	gpio_set_pull_mode(OBSTACLE_GPIO,GPIO_PULLUP_ONLY);
    gpio_set_direction(OBSTACLE_GPIO, GPIO_MODE_INPUT);
    int n =GPIO_INPUT_GET(OBSTACLE_GPIO);
    
    while(1){
    	read_raw = gpio_get_level(OBSTACLE_GPIO);
    	if(read_raw == 1)
    		printf("obstacle detected! %d\n",n);
    	else
    		printf("nothing \n");
    	vTaskDelay( 2 * portTICK_PERIOD_MS );	
	}
}
