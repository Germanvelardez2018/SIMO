#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "simo/wdt/wdt.h"

#include "simo/uart/uart.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#include "simo/timer/timer.h"
#include "simo/comm/comm.h"
#include <string.h>



/**
 * @brief   Funcion asociada a timer
 * 
 * @param   void* params: No se usa, es parte de la estructura de puntero a funcion que se asocia al timer 
 * @return  None
 * 
 * **/

static void blink_funcion(void *param)  //funcion testigo, ya no hace blink
{

   
    vTaskDelay(10);
  
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

    


     static soft_timer_t timer_led;

    status_t res = simo_timer_create(&timer_led, blink_funcion, 1000, 1);

    simo_timer_start(&timer_led);

    static comm_config_t comm_cfg;

    simo_comm_init(&(comm_cfg));

    simo_wdt_init();

    vTaskStartScheduler();

    for (;;)
    {
        //should never get here
    }

    return 0;
}
