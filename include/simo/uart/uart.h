/*
    SIMO/UART.H

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







typedef void (*simo_function)(void*);

typedef struct
{
    uart_inst_t*   uart;
    uint8_t       rx_pin;
    uint8_t       tx_pin;
    uint          baudrate;
    bool          irq_en;
   
} simo_uart_instance;



/*
    Functions
*/


void init_simo_uart(simo_uart_instance* instance);

void deinit_simo_uart(simo_uart_instance*);



simo_err_t write_simo_uart(simo_uart_instance* instance,uint8_t* buffer, int8_t buffer_len);


simo_err_t read_simo_uart(simo_uart_instance* instance,uint8_t* buffer,int8_t buffer_len);


uint8_t read_simo_uart_until(simo_uart_instance* instance,int8_t* buffer,int16_t len_max,char end_char);
