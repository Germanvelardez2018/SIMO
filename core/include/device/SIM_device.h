/**
 * @file SIM_device.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */




#ifndef   DEVICE_SIM_DEVICE_H
#define   DEVICE_SIM_DEVICE_H

    #include "comm/comm.h"
    #include "simo/uart.h"




    #define SIM_DTR          4
    #define SIM_UART         S_UART0
    #define SIM_BAUDRATE     115200
    #define SIM_BUFFER_LEN      200



    comm_t* create_sim_device();


    void init_sim_device(comm_t* comm);

    void send_cmd(comm_t* comm,char* cmd);


    void read_response(comm_t* response,uint16_t timeout);


    void send_and_check(comm_t* comm, char* cmd,uint16_t timeout); 




#endif
        


