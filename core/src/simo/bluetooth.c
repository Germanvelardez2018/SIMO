
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"

#include "simo/bluetooth/bluetooth.h"
#include "simo/sim_device.h"
#include "simo/uart.h"




static QueueSetHandle_t _QUEUE_BLE_INTERFACE_;

 device_t* sim_modulo ;  



static void _task_BLE_responses(void* params)
{
    _QUEUE_BLE_INTERFACE_ = xQueueCreate(4,sizeof(char*));
    char* buff;
    
    while(1)
    {
         if (xQueueReceive(_QUEUE_BLE_INTERFACE_, &buff, portMAX_DELAY) == pdPASS)
        {


            //En este bloque va la rutina que gestiona las respuestas
            s_uart_write(S_UART0, "[_BLE INTERFACE]:", strlen("[_BLE INTERFACE]:"));
            s_uart_write(S_UART0, (buff), strlen(buff));
            s_uart_write(S_UART0, "\n", 1);
        }

    }
   
    

}








void s_bluetooth_init(){



    /**
    * Los objetos sim_device utilizan el puerto UART0 para comunicarse a 115200 baudios.
    * **/
   device_t* sim_modulo = create_sim_device(&_QUEUE_BLE_INTERFACE_);  

    /**
     * Tarea encargada de  recibir las respuestar por UART y gestionarlas
     * **/

    xTaskCreate(_task_BLE_responses,"BLE INTERFACE",4*1024,NULL,3,NULL);
 
}
