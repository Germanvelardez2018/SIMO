/**
 * @file comm.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */




#ifndef   COMM_COMM_H
#define   COMM_COMM_H

    #include "utils/utils.h"
    #include "comm/interface.h"

    typedef struct
    {
        char*         buffer;
        uint16_t      buffer_len;
        interface_t*  interface;
    } comm_t;





    comm_t* comm_create(uint16_t buffer_len, interface_t* interface);

#endif