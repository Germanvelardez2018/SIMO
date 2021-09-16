/**
  @file device.h  (simplificado)
  @brief Estructuras y funciones asociadas al manejo de un flujo de datos.
  @author German Velardez
  @date 12/2021
*/



#include <stdio.h>
#include <string.h>


typedef void (*device_function_t)(char*,uint32_t); //  funcion para escribir el buffer en la interfaz de salida

typedef void (*device_init_func_t)();    // funcion de incio


typedef struct
{
 char* b_comm;      //BUFFER COMANDOS
 char* b_resp;      //BUFFER RESPUESTAS
 uint8_t bcomm_len; //tamaño maximo comandos
 uint8_t bresp_len; //tamaño maximo respuestas
 uint8_t bcomm_c;  // contadores
 uint8_t bresp_c;  // contadores
 uint8_t is_started; //esta inicializado?  0: NO , 1:SI
 device_init_func_t init_fun;  // funcion para iniciar dependencias
 device_function_t write_fun;      // funcion para enviar datos
 device_function_t read_fun;  //funcion para recibir datos


}device_t;




/**
 * @brief   Inicio un dispositivo
 * 
 * @param  uint8_t bcomm_len: tamaño del buffer de salida
 * @param  uint8_t bresp_len: tamaño del baffer de entrada
 * @param device_init_func_t init_function : FUncion para inciar dependencia, por ejemplo el puerto UART
 * @param device_function_t write_funtion: funcion asociada a interfaz de hardware
 * @param device_function_t read_function: funcion asociada a interfaz de hardware
 * @return  device_t*: Puntero a el elemento, utiliza memoria dinamica
 * 
 * **/
device_t* create_device(uint8_t bcomm_len,uint8_t bresp_len,device_init_func_t init_function,device_function_t write_function, device_function_t read_function);


/**
 * @brief   Libera los recursos asociados al dispositivo
 * 
 * @param   device_t* device : Dispositivo a eliminar y liberar recursos
 
 * @return  None
 * 
 * **/
void delete_device(device_t* device);

