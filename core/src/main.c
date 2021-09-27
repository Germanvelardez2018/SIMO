
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"
#include "pico/stdlib.h"
#include "simo/wdt/wdt.h"
#include <string.h>
#include <stdio.h>

// pruebas

#include "simo/sim_device.h"
#include "simo/uart.h"
#include "simo/spi.h"

 

static QueueSetHandle_t _QUEUE_RESPONSES_MAIN_;

#define PIN_BLINK      16

static void _task_test_spi(void* params)
{
    
    //inicio el SP1

    uint8_t buffer[4]={5,0,7,1};
    s_uart_init(S_UART0,115200);
    s_uart_write(S_UART0,"iniciando pruebas de SPI\n",strlen("iniciando pruebas de SPI\n"));
    s_spi_init(S_SPI1,10*1000);


     gpio_put(PIN_BLINK, 1);
    gpio_set_dir(PIN_BLINK, 1);

    while(1)
    {
             gpio_put(PIN_BLINK, 1);

        s_uart_write(S_UART0,"enviando secuencia write spi\n",strlen("enviando secuencia write spi\n"));
        s_spi_write(S_SPI1,buffer,4);
        vTaskDelay(2000);
             gpio_put(PIN_BLINK, 0);


    }
   
    

}




/**
 * @brief   Inicio el programa principal del sistema
 * @param   None
 * @return  int 0: 
 * 
 * **/

int main()
{

    stdio_init_all();

   
    simo_wdt_init();

    xTaskCreate(_task_test_spi,"spi test",2000,0,3,0);
    vTaskStartScheduler();

    for (;;)
    {
        
        //should never get here
    }

    return 0;
}
