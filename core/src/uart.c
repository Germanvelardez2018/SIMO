





#include "simo/uart/uart.h"
#include "hardware/gpio.h"





#define IRQ_RX_UART             true    //Solo utilizaremos irq para recibir datos por uart
#define IRQ_TX_UART             false












void init_simo_uart(simo_uart_instance* instance)
{
    uart_init(instance->uart,instance->baudrate);
    gpio_set_function(instance->rx_pin,GPIO_FUNC_UART);
    gpio_set_function(instance->tx_pin,GPIO_FUNC_UART);    
}

void deinit_simo_uart(simo_uart_instance* instance)
{
    return  uart_deinit(instance->uart);
}




void write_simo_uart(simo_uart_instance* instance,int8_t* buffer, uint16_t buffer_len)
{
    return   uart_write_blocking(instance->uart,buffer,buffer_len);
   
}


void read_simo_uart(simo_uart_instance* instance,int8_t* buffer,uint16_t buffer_len)
{
    return uart_read_blocking(instance->uart,buffer,buffer_len);

}





uint read_simo_uart_until(simo_uart_instance* instance,int8_t* buffer,uint16_t len_max,char end_char)
{
    uint counter=0;
    uint8_t c; 

    while (c != end_char && (counter <len_max-1))
    {
       uart_read_blocking(instance->uart,&c,1);
        if(c != end_char)
          {
            buffer[counter] = c;
            counter++;
          }
    }
     
     buffer[counter]=0;  
    return counter;
}




void set_rx_interrupcion_handler(simo_uart_instance* instance,irq_rx_callback_t irq_function)
{
  //deshabilitamos el FIFO's
  uart_set_fifo_enabled(instance->uart,false);


  int UART_IRQ = instance->uart == uart0 ? UART0_IRQ : UART1_IRQ;
  
  irq_set_exclusive_handler(UART_IRQ,irq_function); 

  irq_set_enabled(UART_IRQ, true);
  

  //Configuro la FIFO para rx
  uart_set_irq_enables(instance->uart,IRQ_RX_UART,IRQ_TX_UART);        

  //habilitamos nuevamente el fifo
  uart_set_fifo_enabled(instance->uart,true);

}


