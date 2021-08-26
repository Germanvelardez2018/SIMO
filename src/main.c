#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#define LED_PIN PICO_DEFAULT_LED_PIN


#define GPIO_ON     1
#define GPIO_OFF    0

void GreenLEDTask(void *param)
{
    while(1)
    {
        gpio_put(LED_PIN, GPIO_ON);
        vTaskDelay(1000);
        gpio_put(LED_PIN, GPIO_OFF);
        vTaskDelay(1000);
    }
 
}


int main() 
{
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

 

    TaskHandle_t gLEDtask = NULL;
    TaskHandle_t rLEDtask = NULL;

    uint32_t status = xTaskCreate(
                    GreenLEDTask,
                    "Green LED",
                    1024,
                    NULL,
                    tskIDLE_PRIORITY,
                    &gLEDtask);


    vTaskStartScheduler();

    for( ;; )
    {
        //should never get here
    }

}
