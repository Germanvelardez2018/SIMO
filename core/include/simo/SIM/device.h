/**
 * @file device.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "stdint.h"
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "simo/request_command.h"
#include "simo/simo_utils.h"
#include "simo/uart.h"



typedef struct 
{
    uart_t uart;
    uint16_t baudrate;
    char* buffer;
    uint16_t buffer_len;
    task_function_t rx_task;
    task_function_t tx_task;
    callback_t    irq_rx;
    QueueHandle_t queue_cmd;
    QueueHandle_t queue_response;
    TaskHandle_t rx_handler;
    TaskHandle_t tx_handler;

} device_t;



device_t* create_device(
                        uart_t uart,
                        uint16_t baudrate,
                        uint16_t buffer_len,
                        task_function_t rx_task,
                        task_function_t tx_task,
                        callback_t    irq_rx
                        );

/**
 * @brief 
 * 
 * @param device 
 * @return ** void 
 */
void delete_device(device_t* device);



void init_device(device_t* device);

void deinit_device(device_t* device);








void send_command(device_t* device, request_command* req);


void send_response(device_t* device,char* response);












