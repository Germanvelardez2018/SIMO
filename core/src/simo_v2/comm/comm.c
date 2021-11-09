/**
 * @file comm.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "comm/comm.h"

#include <stdlib.h>



comm_t* comm_create(uint16_t buffer_len, interface_t* interface)
{
    if(interface == NULL ||
       buffer_len == 0
      ) return NULL;
    comm_t* comm = (comm_t*)malloc(sizeof(comm_t));
    if (comm == NULL) return NULL;

    comm->buffer = (char*)malloc(sizeof(char)*buffer_len);
    comm->buffer_len = buffer_len;
    if( comm->buffer == NULL)
    {
        free(comm);
        return NULL;
    }
    comm->interface = interface;
    return comm;

}
