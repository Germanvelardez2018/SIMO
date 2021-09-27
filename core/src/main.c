
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
#include "simo/lcd.h"

#include "simo/bluetooth/bluetooth.h"
 

static QueueSetHandle_t _QUEUE_RESPONSES_MAIN_;



static void _task_read_responses(void* params)
{
    _QUEUE_RESPONSES_MAIN_ = xQueueCreate(4,sizeof(char*));
    char* buff;
    
    while(1)
    {
         if (xQueueReceive(_QUEUE_RESPONSES_MAIN_, &buff, portMAX_DELAY) == pdPASS)
        {


            //En este bloque va la rutina que gestiona las respuestas
            s_uart_write(S_UART0, "[_task_read_responses]:", strlen("[_task_read_responses]:"));
            s_uart_write(S_UART0, (buff), strlen(buff));
            s_uart_write(S_UART0, "\n", 1);
        }

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

       
    s_bluetooth_init();
  simo_wdt_init();






    vTaskStartScheduler();

    for (;;)
    {
        
        //should never get here
    }

    return 0;
}
