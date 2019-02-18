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
#define REED_GPIO 34
#define ESP_INTR_FLAG_DEFAULT 0

void app_main(void)
{    
	int read;

    gpio_pad_select_gpio(REED_GPIO);
 	gpio_set_pull_mode(REED_GPIO,GPIO_PULLUP_ONLY);
    gpio_set_direction(REED_GPIO, GPIO_MODE_INPUT);
    
    while(1){
    	read = gpio_get_level(REED_GPIO);
    	if(read == 1)
    		printf("nothing\n");
    	else
    		printf("magnet detected\n");
    	vTaskDelay( 2 * portTICK_PERIOD_MS );	
	}
}
