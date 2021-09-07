
#include "simo/comm/comm.h"
#include "simo/uart/uart.h"
#include "simo/timer/timer.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <string.h>














 //Funcion del modulo

#define   _TIMER_PERIODE_              5000
#define   _BUFFER_IRQ_RX_LEN_          50
#define   _N_QUEUE_                    4
#define   _TYPE_ELEMENT_QUEUE_         sizeof(char*)




static QueueHandle_t _QUEUE_IN_;


static  simo_uart_instance interface ;
static uint16_t _counter =0;

static char buffer_rx[_BUFFER_IRQ_RX_LEN_];









/**
 * @brief   Rutina de interrupcion 
 * 
 * @param   None  
 * @return  None
 * 
 * **/
static void _IRQ_RX_COMM_(void)
{

    _counter=0;
    while(uart_is_readable_within_us(interface.uart,1000) && (_counter <= _BUFFER_IRQ_RX_LEN_))
    {
        buffer_rx[_counter]= uart_getc(interface.uart);
        _counter++;
    }
    buffer_rx[_counter]=0;
    char* b = &(buffer_rx[0]);
    xQueueSend(_QUEUE_IN_,&(b),10);

}













/**
 * @brief   Callback del timer asociado al modulo
 * 
 * @param   None  
 * @return  None
 * 
 * **/

 static void _CALLBACK_COMM_(void* params)
 {

 
    write_simo_uart(&interface,"Sensors check  \r\n",strlen("Sensors check  \r\n"));


 }













void   comm_init(comm_config_t* config)
{
    
    interface.uart = uart0;
    interface.rx_pin = 1;
    interface.tx_pin = 0;
    interface.baudrate = 115200;
    interface.irq_rx = false;
    interface.irq_tx = false;
    init_simo_uart(&interface);
    soft_timer_t t ; 
    create_timer_function(&t,_CALLBACK_COMM_,_TIMER_PERIODE_,1);
    start_timer(&t);

    set_rx_interrupcion_handler(&interface,_IRQ_RX_COMM_);


    //creo la tarea que procesa

    xTaskCreate(comm_task,"comm process",5*1024,NULL,tskIDLE_PRIORITY+2,NULL);
    
}



void   comm_deinit(comm_config_t* config)
{
    
}




void comm_task(void* params)
{

    _QUEUE_IN_ = xQueueCreate(_N_QUEUE_ ,  sizeof(char*));    //Inicializo la queue que recibira los buffer proveniente de rx irq
   
   
    char  *buffer_in;
    
    while(1)
    {
        if(  xQueueReceive(_QUEUE_IN_,&buffer_in,portMAX_DELAY) == pdPASS)
        {
             write_simo_uart(&interface,(buffer_in),strlen(buffer_in));
             write_simo_uart(&interface,"\n",1);
            _counter = 0;
        }
        else
        {
            write_simo_uart(&interface,"nada\n",strlen("nada\n"));
        }

    }

}