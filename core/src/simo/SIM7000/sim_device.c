#include "simo/SIM/sim_device.h"
#include "simo/request_command.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "simo/debug_interface.h"

#include <stdio.h>
static device_t* _SIM_device;



static void _SIM_rx_task(void* params)
{
    QueueHandle_t* response_queue = (QueueHandle_t*)(params);
    //init queue
    (*response_queue) = xQueueCreate(SIM_QUEUE_SIZE,sizeof(char*));
    char* response;
    while(1)
    {
         xQueueReceive((*response_queue),&response,100);
         //checkear response
         char buff[100];
         sprintf(buff,"la respuesta es: %s\r\n",response);
        debug_printf(buff);
    }
}






static void _SIM_tx_task(void* params)
{
    QueueHandle_t* command_queue = (QueueHandle_t*)(params);
    //init queue
    (*command_queue) = xQueueCreate(SIM_QUEUE_SIZE,sizeof(request_command*));
    request_command* cmd;
    while(1)
    {
        xQueueReceive((*command_queue),&cmd,100);

        //send command from UART
          //checkear response
         char buff[100];
         sprintf(buff,"envio comando: %s\r\n",cmd->cmd);
         debug_printf(buff);

        
    }
}




static void _SIM_IRQ_RX(void)
{

    uint16_t counter= 0;
    while(s_uart_is_readable(SIM_UART,10) && counter <= SIM_BUFFER_SIZE )
    {
        (*_SIM_device).buffer[counter]= s_uart_getc(SIM_UART);
        counter+=1;

    }
         (*_SIM_device).buffer[counter] = 0; // close string

         send_response(_SIM_device,((*_SIM_device).buffer));
       

}






void init_sim_device(device_t* device)
{   
    init_device(device);
}

device_t* create_sim_device()
{
    
    debug_printf("creando sim device \r\n");
        _SIM_device = create_device(
                             SIM_UART,
                             SIM_BAUDRATE,
                             SIM_BUFFER_SIZE,
                            _SIM_rx_task,
                            _SIM_tx_task,
                            _SIM_IRQ_RX
                            );


        return _SIM_device;
}



void delete_sim_device(device_t* device)
{
    delete_device(device);
}

