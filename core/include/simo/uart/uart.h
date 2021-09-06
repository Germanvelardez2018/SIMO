/**
  @file uart.h
  @brief Estructuras y funciones asociadas al manejo del harware uart.
  @author German Velardez
  @date 9/2021


*/

#include "simo/core.h"
#include "hardware/uart.h"

#if RASPBERRY_PICO == 1
#define N_UART 2 //microcontroler is RASPBERRY PI PICO
#define RX_UART0 1
#define TX_UART0 0
#define UART0 uart0
#define UART1 uart1
#define BUFFER  256
#else
#define N_UART 3 // microcontroler is STM32F103C8T6
#endif









//!< Estructura asociada a configuracion de hardware UART


typedef struct
{
    uart_inst_t*   uart;     /*!<  Uart fisica a configurar */
    uint8_t       rx_pin;    /*!<  Pin RX del UART */
    uint8_t       tx_pin;    /*!<  Pin TX del UART */
    uint          baudrate; /*!<   Baurate del puerto*/
    bool          irq_en;   /*!<   Habilitar interrpciones */
   
} simo_uart_instance;



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
 * @brief   Inicia el hardware uart del sistema
 * 
 * @param   simo_uart_instance*: instance
 * @return  None
 * 
 * **/

void write_simo_uart(simo_uart_instance* instance,uint8_t* buffer, int8_t buffer_len);


/**
 * @brief   Inicia el hardware uart del sistema
 * 
 * @param   simo_uart_instance*: instance
 * @return  None
 * 
 * **/

void read_simo_uart(simo_uart_instance* instance,uint8_t* buffer,int8_t buffer_len);



/**
 * @brief   Inicia el hardware uart del sistema
 * 
 * @param   simo_uart_instance*: instance
 * @return  None
 * 
 * **/

uint read_simo_uart_until(simo_uart_instance* instance,int8_t* buffer,int16_t len_max,char end_char);
