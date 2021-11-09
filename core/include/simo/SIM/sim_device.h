/**
 * @file sim_device.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "simo/uart.h"
#include "simo/SIM/device.h"







#define SIM_UART            S_UART1
#define SIM_BAUDRATE        (uint16_t)115200


#define SIM_BUFFER_SIZE       100

#define SIM_QUEUE_SIZE          5




device_t* create_sim_device();



void delete_sim_device(device_t* device);

