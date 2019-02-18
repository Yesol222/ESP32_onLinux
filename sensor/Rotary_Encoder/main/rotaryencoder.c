#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_adc_cal.h"
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <string.h>

#define CLK 21 //channel B
#define DT 14 //channel A
#define SW 15


void app_main(void)
{    
	int read_A;
	int read_B;
	int state;
	int counter = 0;
	int flag = 0;
	
    gpio_pad_select_gpio(CLK);
    gpio_set_pull_mode(CLK,GPIO_PULLUP_ONLY);
    gpio_set_direction(CLK, GPIO_MODE_INPUT);
    
    gpio_pad_select_gpio(DT);
//    gpio_set_pull_mode(DT,GPIO_PULLUP_ONLY);
    gpio_set_direction(DT, GPIO_MODE_INPUT);
    
    gpio_pad_select_gpio(SW);
//    gpio_set_pull_mode(SW,GPIO_PULLUP_ONLY);
    gpio_set_direction(SW, GPIO_MODE_INPUT);

	read_A = gpio_get_level(DT);
	read_B = gpio_get_level(CLK);
	state = gpio_get_level(DT);
	//when channel A changes from high to low, if B is high -> CW
	//if B is low ->CCW
	//when A is low if we read value of B -> know the direction
	
    while(1){
    	read_A = gpio_get_level(DT);
		while(!read_A){
			read_B = gpio_get_level(CLK);
			flag = 1;
		}
		if(flag == 1){
			flag = 0;
			if((state == 0)&&(read_B==1)){
				counter++;
				printf("%d \n",counter);
			}
			if((state == 1)&&(read_B==0)){
				counter--;
				printf("%d \n",counter);
			}
		}
		
		if(gpio_get_level(SW) != 1)
			counter = 0;
		printf("%d \n",counter);
		
		vTaskDelay(2*portTICK_PERIOD_MS);
	}	
}
