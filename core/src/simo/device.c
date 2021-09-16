/**
  @file device.h  (simplificado)
  @brief Estructura asociada a un dispositivo que envia y recibe data mediante buffer.
  @author German Velardez
  @date 12/2021
*/
#include "simo/device.h"
#include  "simo/uart.h"
#include <stdlib.h>



device_t* create_device(uint8_t bcomm_len,uint8_t bresp_len,device_init_func_t init_function,device_function_t write_function, device_function_t read_function)
{
    //Verificacion de parametros
    if(write_function == NULL || read_function == NULL || init_function == NULL) return NULL; //ERROR en funciones;
    if(bcomm_len == 0 || bresp_len == 0) return NULL; //buffer vacios

    device_t* device = (device_t*) malloc(sizeof(device_t));
    if(device == NULL) return NULL;

    //asignacion de memoria dinamica
    device->b_comm = (char*) malloc(bcomm_len*sizeof(char));
    device->b_resp = (char*) malloc(bresp_len*sizeof(char));
    if( device->b_comm == NULL || device->b_resp == NULL) return NULL; //ERROR en asignacion de memoria

    //asignacion de funciones
    device->init_fun = init_function;
    device->write_fun = write_function;
    device->read_fun  = read_function;

   
    //llamo a la funcion de inicio
    device->init_fun();
    // retorno
    return device;
}

void delete_device(device_t* device)
{
    //Verificacion de parametros
    if(device == NULL) return;

    //libero memoria
    free(device->b_comm);
    free(device->b_resp);
    device->init_fun = NULL;
    device->read_fun = NULL;
    device->write_fun = NULL,
    free(device); 
    return; 

}