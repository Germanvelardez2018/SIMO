
#include "simo/uart.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include <string.h>
#define UART_DEFAULT    uart0





/**
 * @brief   devuelve el elemento uart correspondiente
 * 
 * @param   uart_t uart: hardware seleccionado
 *              UART_1
 *              UART_2
 * @return   uart_inst_t*: 
 *              uart_0
 *              uart_1
 * 
 * **/

#define N_UART 2         

/*!  UART0 GPIOS: TX: 1, RX: 2      opcionalmente    TX: 12, RX:13*/

#define UART0                   uart0
#define UART0_TX                0
#define UART0_TX_OPTIONAL       12
#define UART0_RX                1
#define UART0_RX_OPTIONAL       13



/*!  *    UART0 GPIOS: TX: 4, RX: 5      opcionalmente    TX: 8, RX: 9 */
#define UART1 uart1
#define UART1_TX                4
#define UART1_TX_OPTIONAL       8
#define UART1_RX                5
#define UART1_RX_OPTIONAL       9

#define N_BAUDRATES  5
 static  uint32_t  _baudrates[N_BAUDRATES]=
 {
        9600,
        19200,
        38400 ,
        57600,
        115200
 };
   





/**
 * @brief   Asigno los pines correspondiente al uart
 * 

 * @param   uart: uart a asignar pines
 * @return  NONE : NONE
 * 
 * **/


static void  _set_pins(uart_t uart)
{

    uint8_t pin_rx;
    uint8_t pin_tx;
     switch (uart)
    {
    case S_UART0:
        pin_tx = UART0_TX;
        pin_rx = UART0_RX;
        
        break;
    case S_UART1:
        pin_tx = UART1_TX;
        pin_rx = UART1_RX;
        break;   
    default:
        pin_tx = UART0_TX;
        pin_rx = UART0_RX;
        break;
    }

    gpio_set_function(pin_rx,GPIO_FUNC_UART);
    gpio_set_function(pin_tx,GPIO_FUNC_UART);  
}




/**
 * @brief   devuelve el baudrate valido mas cerca al numero
 * 

 * @param   baudrate: baudrate ingresado por parametro
 * @return  baudrate_t : baudrate valido
 * 
 * **/


static uint32_t _get_baudrate(uint32_t baudrate)
{
    int8_t c= 0;
    while( (baudrate > _baudrates[c]) && (c < N_BAUDRATES))
    {
        c++;
    }
    return _baudrates[c];
}


/**
 * @brief   devuelve un uart valido
 * 

 * @param   uart: baudrate ingresado por parametro
 * @return  uart_inst_t* : instancia valida de uart 
 * 
 * **/


static uart_inst_t*  _get_uart(uart_t uart)
{
   
    switch (uart)
    {
    case S_UART0:
        return  uart0;
        break;
    case S_UART1:
        return  uart1;    
    default:
        return  UART_DEFAULT;
        break;
    }
}





void s_uart_init(uart_t uart,uint32_t baudrate)
{
    uart_inst_t* u = _get_uart(uart);
    uint32_t b = _get_baudrate(baudrate);
    uart_init(u,b);
    _set_pins(uart);
    char buffer[30];
    
   
}


void s_uart_deinit(uart_t uart)
{
    uart_inst_t* u = _get_uart(uart);
    uart_deinit(u);
}



void s_uart_write(uart_t uart, int8_t* buf, uint32_t len_buf )
{
    uart_inst_t* u = _get_uart(uart) ;
    uart_write_blocking(u,buf,len_buf);
}


void s_uart_read(uart_t uart,int8_t* buf,uint32_t len_buf,uint32_t timeout_us)
{
    uart_inst_t* u = _get_uart(uart) ;   
    uint32_t counter= 0;
    while(uart_is_readable_within_us(u,timeout_us) && counter <= len_buf)
    {
        buf[counter] = uart_getc(u);
        counter ++;
    }
    
}

void s_set_interrupcion_handler(uart_t uart,bool rx_irq, bool tx_irq,uart_callback_t irq_function)
{
    uart_inst_t* u = _get_uart(uart);
  //deshabilitamos el FIFO's
  uart_set_fifo_enabled(u,false);


  int UART_IRQ = u == uart0 ? UART0_IRQ : UART1_IRQ;
  
  irq_set_exclusive_handler(UART_IRQ,irq_function); 

  irq_set_enabled(UART_IRQ, true);
  

  //Configuro la FIFO para rx
  uart_set_irq_enables(u,rx_irq,tx_irq);        

  //habilitamos nuevamente el fifo
  uart_set_fifo_enabled(u,true);

}


bool s_uart_is_readable(uart_t uart, uint32_t timeout_us)
{   
    uart_inst_t* u = _get_uart(uart);
    bool res = uart_is_readable_within_us(u, timeout_us);
    return res;
}

char s_uart_getc(uart_t uart)
{
    uart_inst_t* u = _get_uart(uart);
    return uart_getc(u);
}