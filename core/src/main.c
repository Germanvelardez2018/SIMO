#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "simo/wdt/wdt.h"

#include "simo/uart/uart.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#include "simo/timer/timer.h"

#include <string.h>
#include "simo/SIM/communication.h"




/**
 * @brief   Inicio el programa principal del sistema
 * @param   None
 * @return  int 0: 
 * 
 * **/

int main()
{
    stdio_init_all();

    //INICIO EL MODUILO
   simo_communication_init();



    simo_wdt_init();

    vTaskStartScheduler();

    for (;;)
    {
        //should never get here
    }

    return 0;
}
