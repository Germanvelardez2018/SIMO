/**
 * @file utils.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdint.h>


#ifndef   _SIMO_UTILS_H
#define   _SIMO_UTILS_H

typedef void (*irq_callback_t)(void);     //callback funcion
typedef void (*task_function)(void*);



typedef void (*init_function_t)(void*);

typedef      void(*write_function_t)(char*,uint16_t len);
typedef void (*read_function_t)(char* buffer,uint16_t len,uint16_t timeout);


/**
 * @brief  struct to define a command request
 * 
 */





typedef struct 
{
    char* cmd;
    uint16_t cmd_len;
    char* response;
    uint16_t response_len;

}cmd_request;


#endif