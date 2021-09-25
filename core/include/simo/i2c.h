/**
  @file i2c.h  (simplificado)
  @brief Estructuras y funciones asociadas al manejo del harware .
  @author German Velardez
  @date 20/09/2021
*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum {
     S_I2C0,      //pins asociados 4,5
     S_I2C1
}i2c_t;



/**
 *  @brief inicia el puerto i2c
 *  @param i2c: interfaz i2c a utilizar
 *  @param baudrate: Baudrate en Hz (e.g 100kHz is 100000)
 * @return None:
 * 
 * **/

 void s_i2c_init(i2c_t i2c, uint32_t baudrate);



 /**
  * @brief deshabilita el puerto i2c
  * @param i2c: interfaz i2c a deshabilitar
  * @return None:
  * 
  * **/

 void s_i2c_deinit(i2c_t i2c);




 /**
  * @brief configuracion baudrate de dispositvo
  * @param i2c: interfaz i2c a deshabilitar
  * @return None:
  * 
  * **/

 void s_i2c_set_baudrate(i2c_t i2c, uint32_t baudrate);





/**
  * @brief configura el modo del i2c: esclavo o maestro
  * @param i2c: interfaz i2c
  * @param slave_mode: true si es esclavo y false si es maestro 
  * @param slave_address: la direccion del esclavo. En caso de modo master no se tiene en cuenta
  *  @return None:
  * 
  * **/

 void s_i2c_set_mode(i2c_t i2c, bool slave_mode,uint8_t slave_address);




/**
  * @brief Escribir un array de bytes en una direccion de un esclavo
  * @param i2c: interfaz i2c
  * @param slave_address: direccion del esclavo 
  * @param data: array de datos a escribir
  * @param data_len: cantidad de bytes a escribir
  * @param nostop: si es verdadero, el maestro comienza el siguiente bloque con un restart en vez de un start
  *  @return None:
  * 
  * **/

void s_i2c_write(i2c_t i2c,uint8_t slave_address, uint8_t* data, uint32_t data_len,bool nostop);






/**
  * @brief Leer un array de bytes en una direccion de un esclavo
  * @param i2c: interfaz i2c
  * @param slave_address: direccion del esclavo 
  * @param data: buffer de datos a leer
  * @param data_len: tamano del bauffer
  * @param nostop: si es verdadero, el maestro comienza el siguiente bloque con un restart en vez de un start
  *  @return None:
  * 
  * **/

void s_i2c_read(i2c_t i2c,uint8_t slave_address,  uint8_t* data, uint32_t data_len,bool nostop);