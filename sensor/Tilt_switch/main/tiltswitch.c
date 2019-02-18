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
#define TILT_GPIO 34
#define ESP_INTR_FLAG_DEFAULT 0

void app_main(void)
{    
	int read;

    gpio_pad_select_gpio(TILT_GPIO);
 	gpio_set_pull_mode(TILT_GPIO,GPIO_PULLUP_ONLY);
    gpio_set_direction(TILT_GPIO, GPIO_MODE_INPUT);
    
    while(1){
    	read = gpio_get_level(TILT_GPIO);
    	if(read == 0)
    		printf("object tilted!!\n");
    	else
    		printf("object is still\n");
    	vTaskDelay( 2 * portTICK_PERIOD_MS );	
	}
}
