/**
 * @file interface.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */



#ifndef   COMM_INTERFACE_H
#define   COMM_INTERFACE_H


    #include "utils/utils.h"


    typedef struct
    {
        init_function_t init;
        read_function_t read;
        write_function_t write;

    } interface_t;




interface_t*  interface_create(init_function_t init,write_function_t write,read_function_t read);

void interface_init(interface_t* interface);
#endif