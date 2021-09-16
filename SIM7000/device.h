/**
 * Comandos para el SIM7000
 * 
 * **/


#include <string.h>
#include <stdint.h>

typedef enum
{
    DEVICE_FAILED,
    DEVICE_SUCCESS
} device_status;


#define TIME_OUT_RESPONSE               1000    //Time out de espera para recibir mensaje




device_status  check_response(const char* response, const char* expected_response);







