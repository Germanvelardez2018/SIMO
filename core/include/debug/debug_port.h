/**
 * @file debug_interface.h
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "simo/uart.h"


#define DEBUG_ON            true        //!  Must be true to activate the interface
#define DEBUG_UART          S_UART1     //! Uart used by the interface
#define DEBUG_BAUDRATE      115200      
#define DEBUG_PRIORITY      1           //! Priority of the task involved
#define DEBUG_QUEUE_SIZE    5
#define DEBUG_ELEMENT       sizeof(char*)





//---------------------------SIM DEVICES------------------------------------------------//

/**
 * @brief 
 * 
 * @param string 
 * @return ** void 
 */
void debug_printf(char* string);










/**
 * @brief 
 * 
 * @return ** void 
 */
void debug_init(void);


//--------------------------------SIM DEVICES END -------------------------------------//