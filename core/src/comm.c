
#include "simo/comm/comm.h"
#include "simo/uart/uart.h"
#include "simo/timer/timer.h"
#include <string.h>














 //Funcion del modulo

#define    _TIMER_PERIODE_      4000




static  simo_uart_instance interface ;





 static void _CALLBACK_COMM_(void* params)
 {

 
    write_simo_uart(&interface,"_CALLBACK_COMM \r\n",strlen("_CALLBACK_COMM \r\n"));





 }














void   comm_init(comm_config_t* config)
{

   
    
        interface.uart = uart0;
        interface.rx_pin = 1;
        interface.tx_pin = 0;
        interface.baudrate = 115200;
        interface.irq_en = false;
    
    init_simo_uart(&interface);
    soft_timer_t t ; 
    create_timer_function(&t,_CALLBACK_COMM_,_TIMER_PERIODE_,1);
    start_timer(&t);
    
}



void   comm_deinit(comm_config_t* config)
{
    
}