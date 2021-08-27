#include "simo/uart/uart.h"
#include "hardware/gpio.h"

















/*
    Functions
*/


void init_simo_uart(simo_uart_instance* instance)
{
    uart_init(instance->uart,instance->baudrate);
    gpio_set_function(instance->rx_pin,GPIO_FUNC_UART);
    gpio_set_function(instance->tx_pin,GPIO_FUNC_UART);


    
}

void deinit_simo_uart(simo_uart_instance* instance)
{
    uart_deinit(instance->uart);

}



simo_err_t write_simo_uart(simo_uart_instance* instance,uint8_t* buffer, int8_t buffer_len)
{
    uart_write_blocking(instance->uart,buffer,buffer_len);
    return SYSTEM_OK;
}


simo_err_t read_simo_uart(simo_uart_instance* instance,uint8_t* buffer,int8_t buffer_len)
{
        uart_read_blocking(instance->uart,buffer,buffer_len);
        return SYSTEM_OK;
}





uint8_t read_simo_uart_until(simo_uart_instance* instance,int8_t* buffer,int16_t len_max,char end_char)
{
    int16_t counter=0;
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

