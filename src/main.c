#include <stdio.h>





#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "simo/uart/uart.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include <string.h>

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



void PrintTask(void* params)
 {
     //init the uart 0 


    static simo_uart_instance  instance =
    {
        .uart = uart0,
        .rx_pin = 1,
        .tx_pin = 0,
        .baudrate = 115200,
        .irq_en = false
    };


    init_simo_uart(&instance);

    char msg[]="simo \r\n";

    int8_t buffer[250];
    write_simo_uart(&instance,msg,strlen(msg));
    while(1)
    {
        
    //    read_simo_uart(&instance,buffer,50);

        uint8_t counter =  read_simo_uart_until(&instance,buffer,250,'x');

        vTaskDelay(400);

        write_simo_uart(&instance,buffer,counter);

    }


     
 }




int main() 
{
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

 

    TaskHandle_t gLEDtask = NULL;
    TaskHandle_t printtask = NULL;

    uint32_t status = xTaskCreate(
                    GreenLEDTask,
                    "Green LED",
                    1024,
                    NULL,
                    tskIDLE_PRIORITY,
                    &gLEDtask);


            status = xTaskCreate(
                    PrintTask,
                    "print out",
                    4*1024,
                    NULL,
                    tskIDLE_PRIORITY,
                    &printtask);


    vTaskStartScheduler();

    for( ;; )
    {
        //should never get here
    }

}
