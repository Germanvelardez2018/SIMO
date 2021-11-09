/**
 * @file main.c
 * @author German Velardez (germanvelardez@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"

#include "simo/uart.h"
#include <stdio.h>
#include "pico/time.h"
#include <string.h>

#include "device/SIM_device.h"
#include "debug/debug_port.h"




void device_test(void* params)
{
    int counter= 0;
    char buffer[200];
    comm_t* device = create_sim_device();
    init_sim_device(device);
    
    vTaskDelay(5000);


    

    while(1)
    {
        sprintf(buffer,"AT\r\n",counter);
        send_and_check(device,buffer,1000);
        vTaskDelay(2000);
        counter+=1;

    }

}


int main(void)
{
   
    debug_init();
    BaseType_t ret =   xTaskCreate(device_test,"debug test",5000,0,3,0);
  
    vTaskStartScheduler();


    
}



