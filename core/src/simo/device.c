/**
 * @file device.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */



#include "simo/SIM/device.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "simo/debug_interface.h"

device_t* create_device(
                        uart_t uart,  //! uart to send commands
                        uint16_t baudrate, //!baudrate
                        uint16_t buffer_len, 
                        task_function_t rx_task,
                       
                        task_function_t tx_task,
                        
                        callback_t    irq_rx
                        )
    {

        debug_printf("iniciando device\r\n");
        //validate params
        if(buffer_len == 0 ||
          rx_task == NULL  ||
          tx_task == NULL  ||
          irq_rx  == NULL  )  return NULL;


          device_t* device = (device_t*) malloc(sizeof(device_t));
          if(device == NULL) return NULL ;
          device->buffer = malloc(sizeof(char)*buffer_len);
          if(device->buffer == NULL)
          {
              free(device);
              return NULL;
          }
          //assign functions
          device->rx_task = rx_task;
          device->tx_task = tx_task;
          device->irq_rx  = irq_rx;
          device->uart = uart;
          device->baudrate = baudrate;

          return device;        
        
    }

/**
 * @brief 
 * 
 * @param device 
 * @return ** void 
 */
void delete_device(device_t* device)
{
    //remove functions and params
    if (device == NULL)
    {
        device->irq_rx = NULL;
        device->rx_task = NULL;
        device->tx_task = NULL;
         //free memory
        free(device->buffer);
        free(device);
    }
   
   
}



void init_device(device_t* device)
{

    debug_printf("iniciamos device \n");
    if(device != NULL)
    {
        //INIT device. Create task
        BaseType_t ret =   xTaskCreate(device->tx_task,"TX DEVICE",2000,(void*)&(device->queue_cmd),3,&(device->rx_handler));
                   ret =   xTaskCreate(device->rx_task,"RX DEVICE",2000,(void*)&(device->queue_response),3,&(device->tx_handler));
        //init uart
        s_uart_init(device->uart,device->baudrate);
        s_set_interrupcion_handler(device->uart,true,false,device->irq_rx);


    }
}

void deinit_device(device_t* device);








void send_command(device_t* device, request_command* req)
{
    debug_printf("send request\r\n");
   xQueueSend( device->queue_cmd,req,10);
}


void send_response(device_t* device,char* response)
{   debug_printf("send response \r\n");
    xQueueSend(device->queue_response,&response,10);
}
