/**
 * @file cmd_request.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */




#ifndef   _SIMO_REQUEST_H
#define   _SIMO_REQUEST_H


    #include <stdint.h>
    #include <stdbool.h>
    typedef struct 
    {
        char* cmd;
        uint16_t cmd_size;    
        char* expected_res;
        bool check;
    } request_command;




    bool check_response(char* response,request_command* req);

    request_command* create_request(char* cmd, char* expected_res);


#endif






