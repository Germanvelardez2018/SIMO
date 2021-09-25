/**
  @file sim_device.h  (simplificado)
  @brief dispositivo para el manejo de modulos SIM mediante puerto UART.
  @author German Velardez
  @date 12/2021
*/
#include "device.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/**
 * @brief   Inicio un dispositivo SIM a manejarse mediante puerto UART
 * 
* @param  bcomm_len: tamaño del buffer de salida
* @param  bresp_len: tamaño del baffer de entrada
* @param  init_function : FUncion para inciar dependencia, por ejemplo el puerto UART
* @param  write_funtion: funcion asociada a interfaz de hardware
* @param  read_function: funcion asociada a interfaz de hardware
* @return  device_t*: Puntero a el elemento, utiliza memoria dinamica
* 
* **/

device_t* create_sim_device(QueueHandle_t* QUEUE_RESPONSES);




