/**
 * @file interface.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "comm/interface.h"
#include <stddef.h>
#include <stdlib.h>

interface_t*  interface_create(init_function_t init,write_function_t write,read_function_t read)
{
    interface_t* interface = (interface_t*) malloc(sizeof(interface_t));
    if (interface == NULL ) return NULL;

    interface->init = init;
    interface->write= write;
    interface->read = read;

    return interface;
}

void interface_init(interface_t* interface)
{
    if (initstate != NULL) 
    {
         interface->init(NULL);
    }
   
}