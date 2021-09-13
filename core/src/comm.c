
#include "simo/comm/comm.h"
#include "simo/uart/uart.h"
#include "simo/timer/timer.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <string.h>














 //Funcion del modulo

#define   _TIMER_PERIODE_              500
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

 
    simo_uart_write(&interface,"Sensors check  \r\n",strlen("Sensors check  \r\n"));
    vTaskDelay(500);

 }









char start_msg[] =" inicio el programam \r\n";


void   simo_comm_init(comm_config_t* config)
{
    
    interface.uart = uart0;
    interface.rx_pin = 1;
    interface.tx_pin = 0;
    interface.baudrate = 115200;
    interface.irq_rx = false;
    interface.irq_tx = false;
    simo_uart_init(&interface);


  

    soft_timer_t t ; 

    simo_timer_create(&t,_CALLBACK_COMM_,_TIMER_PERIODE_,1);
    simo_timer_start(&t);

    simo_set_rx_interrupcion_handler(&interface,_IRQ_RX_COMM_);


    //creo la tarea que procesa
      simo_uart_write(&interface,start_msg,strlen(start_msg));

    xTaskCreate(simo_comm_task,"comm task",5*1024,NULL,tskIDLE_PRIORITY+2,NULL);
    
}



void   simo_comm_deinit(comm_config_t* config)
{
    
}




void simo_comm_task(void* params)
{

    _QUEUE_IN_ = xQueueCreate(_N_QUEUE_ ,  sizeof(char*));    //Inicializo la queue que recibira los buffer proveniente de rx irq
   
   
    char  *buffer_in;
    
    while(1)
    {
        if(  xQueueReceive(_QUEUE_IN_,&buffer_in,portMAX_DELAY) == pdPASS)
        {
             simo_uart_write(&interface,"Commm:",strlen("Commm:"));
             simo_uart_write(&interface,(buffer_in),strlen(buffer_in));
             simo_uart_write(&interface,"\n",1);
            _counter = 0;
        }
      

    }

}