/**
  @file PCF8674.h  (simplificado)
  @brief Driver para el manejo de 8674.h.
  @author German Velardez
  @date 20/09/2021
*/

#include <stdint.h>

#define _INTERFAZ_ "I2C"

#define _INTERRUPCION 1

#define ADDRESS_DEVICE 0x27

typedef struct
{

    int8_t device_address; //direccion del dispositivo
    int8_t memory_port;    //memoria que representa los 8 pines del dispositivo
    int8_t pin_irq;        //pin conectado a la irq del PCF8674
} pin_extension_t;

/**
 * @brief   Inicio un dispositivo PCF8674 para expandir pines
 * 
 * @param device_address: La direccion del dispositivo  PCF8674 (I2C)
 * @param pin_irq: El pin del microcontrolador que se conectara con la interrupcion del PCF8674.
 * @return  pin_extension_t*: objeto que representa el dispositivo extensor de pines
 * 
 * **/

pin_extension_t *s_PCF8674_init(int8_t device_address, int8_t pin_irq);

/**
 * @brief   leo el valor del puerto del dispositivo PCF8674
 * 
 * @param device: objeto del que se desea leer puerto
 * @return  int8_t: valor del puerto
 * 
 * **/
int8_t read_port(pin_extension_t *device);







/**
 * @brief   Escribo el valor del puerto del dispositivo PCF8674
 * 
 * @param device: objeto del que se desea escribir su puerto
 * @return  None
 * 
 * **/
void write_prot(pin_extension_t *device, int8_t new_value);
