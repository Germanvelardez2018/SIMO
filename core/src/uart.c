





#include "simo/uart/uart.h"
#include "hardware/gpio.h"












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

