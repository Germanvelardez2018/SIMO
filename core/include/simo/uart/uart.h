/**
  @file uart.h
  @brief Estructuras y funciones asociadas al manejo del harware uart.
  @author German Velardez
  @date 9/2021


*/

#include "simo/core.h"
#include "hardware/uart.h"
#include "hardware/irq.h"



#ifndef _SIMO_UART_H
#define _SIMO_UART_H

/*! Numero de UART del dispositivo */

#define N_UART 2         

/*!  UART0 GPIOS: TX: 1, RX: 2      opcionalmente    TX: 12, RX:13*/

#define UART0                   uart0
#define UART0_TX                1
#define UART0_TX_OPTIONAL       12
#define UART0_RX                2
#define UART0_RX_OPTIONAL       13



/*!  *    UART0 GPIOS: TX: 4, RX: 5      opcionalmente    TX: 8, RX: 9 */
#define UART1 uart1
#define UART1_TX                4
#define UART1_TX_OPTIONAL       8
#define UART1_RX                5
#define UART1_RX_OPTIONAL       9

/*! Buffer utilizado para lecturas mediante rutinas de interrupcion */

#define IRQ_BUFFER  256




/***
 *    UART0: TX: 1, RX: 2      opcionalmente    TX: 12, RX:13
 *    UART1: TX: 4, RX: 5      opcionalmente    TX: 8 , RX:9
 */





//! Estructura asociada a configuracion de hardware UART


typedef struct
{
    uart_inst_t*   uart;     /*!<  Uart fisica a configurar */
    uint8_t       rx_pin;    /*!<  Pin RX del UART */
    uint8_t       tx_pin;    /*!<  Pin TX del UART */
    uint          baudrate; /*!<   Baurate del puerto*/
    bool          irq_rx;   /*!<   Habilita las interrpciones cuando el bufer fifo contenda datos*/
    bool          irq_tx;  /*!<   Habilita las interrupciones cuando tenemos datos en el buffer fifo que necesitan ser enviados */
   
} simo_uart_instance;



typedef void (*irq_rx_callback_t)(void);


/*
    Functions
*/





/**
 * @brief   Inicia el hardware uart del sistema
 * 
 * @param   simo_uart_instance*: instance
 * @return  None
 * 
 * **/

void init_simo_uart(simo_uart_instance* instance);


/**
 * @brief   Desconfigura el hardware uart del sistema
 * 
 * @param   simo_uart_instance*: instance
 * @return  None
 * 
 * **/

void deinit_simo_uart(simo_uart_instance* instance);



/**
 * @brief   Envia por uart la cantidad  buffer_len de bytes almacenado en buffer
 * 
 * @param   simo_uart_instance*: instance
 * @param   int8* buffer: Array de bytes a enviar
 * @param   uint16_t buffer_len: tamaño de buffer a enviar
 * @return  None
 * 
 * **/

void write_simo_uart(simo_uart_instance* instance,int8_t* buffer, uint16_t buffer_len);



/**
 * @brief   Lee una cantidad buffer_len de bytes del puerto uart y los almacena en buffer
 * 
 * @param   simo_uart_instance*: instance
 * @param   int8_t* buffer: Array donde se guardan los bytes leidos
 * @param   uint16_t buffer_len: Tamaño del buffer
 * @return  None
 * 
 * **/

void read_simo_uart(simo_uart_instance* instance,int8_t* buffer,uint16_t buffer_len);



/**
 * @brief   Leer el puerto serie hasta detectar caracter  char_end
 * 
 * @param   simo_uart_instance* instance: Instancia de uart
 * @param   int8* buffer: array donde se almacenaran los bytes recibidos
 * @param   int16_t len_max: Numero maximo de bytes que se pueden recibir. Deben ser mayores o iguales al tamaño del buffer
 * @param   char end_char: Simbolo que indica el final de lectura de esta funcion
 * @return  uint8_t: Retorna el numero de bytes leidos
 * 
 * **/

uint read_simo_uart_until(simo_uart_instance* instance,int8_t* buffer,uint16_t len_max,char end_char);



/**
 * @brief   Habilito las interrupciones para manejar la uart
 * 
 * @param   simo_uart_instance* instance: Instancia de uart
 * @param   irq_rx_callback_t irq_function: callback de la irq
 * @return  None
 * 
 * **/

void set_rx_interrupcion_handler(simo_uart_instance* instance,irq_rx_callback_t irq_function);




#else
#endif

