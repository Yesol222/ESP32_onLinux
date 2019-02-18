#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_adc_cal.h"
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#define LEDC_HS_MODE       LEDC_HIGH_SPEED_MODE
#define BUZZER_TIMER      (LEDC_TIMER_1)
#define BUZZER_CHANNEL    (LEDC_CHANNEL_1)
#define BUZZER_GPIO       (5)
#define BUZZER_FREQ         (2200)  
#define BUZZER_DUTY       (4000)

void app_main(void)
{   
 ledc_timer_config_t buzzer_timer = {
		.speed_mode = LEDC_HS_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT,
        .timer_num = BUZZER_TIMER,
        .freq_hz = BUZZER_FREQ
    };
//    buzzer_timer.speed_mode = LEDC_LS_MODE;
//    buzzer_timer.timer_num = LEDC_LS_TIMER;
    ledc_timer_config(&buzzer_timer);
    
 ledc_channel_config_t buzzer_channel = {
		.gpio_num =BUZZER_GPIO,
        .speed_mode = LEDC_HS_MODE,
        .channel = BUZZER_CHANNEL,
        .hpoint = LEDC_INTR_DISABLE,
        .timer_sel = BUZZER_TIMER,
        .duty = 0x1fff}; 
        
    ledc_channel_config(&buzzer_channel);
    
    while(1){
    	ledc_set_duty(buzzer_channel.speed_mode,buzzer_channel.channel,0);
    	ledc_update_duty(buzzer_channel.speed_mode, buzzer_channel.channel);
    	vTaskDelay(1000 / portTICK_PERIOD_MS);
    	ledc_set_duty(buzzer_channel.speed_mode,buzzer_channel.channel,BUZZER_DUTY);
    	ledc_update_duty(buzzer_channel.speed_mode, buzzer_channel.channel);
    	vTaskDelay(1000 / portTICK_PERIOD_MS);
    	
	}
        
        
        

}
