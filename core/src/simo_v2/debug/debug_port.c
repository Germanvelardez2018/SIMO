/**
 * @file debug_port.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "simo/debug_interface.h"

#include <string.h>

static QueueHandle_t _queue_debug;

/**
 * @brief 
 * 
 * @param string 
 * @return ** void 
 */
void debug_printf(char* string)
{
    if(DEBUG_ON)
    {
        xQueueSend(_queue_debug,&string,10);
    }


}






static void _debug_task(void* params)
{

    _queue_debug = xQueueCreate(DEBUG_QUEUE_SIZE,DEBUG_ELEMENT);
    s_uart_init(DEBUG_UART,DEBUG_BAUDRATE);

    char* buff;
    while(1)
    {
        if( xQueueReceive(_queue_debug,&buff,(TickType_t) 10) == pdPASS)
        {
            // print out
            //
            s_uart_write(DEBUG_UART,(uint8_t*)(buff),strlen(buff));
            //s_uart_write(DEBUG_UART,"debug task",strlen("debug task"));

        }


        vTaskDelay(1000);
    }
}







/**
 * @brief 
 * 
 * @return ** void 
 */
void debug_init(void)
{
    if (DEBUG_ON)
    {
       
        BaseType_t ret =   xTaskCreate(_debug_task,"DEBUG ",3000,0,DEBUG_PRIORITY,0);


    }



}

