
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"
#include "pico/stdlib.h"
#include "simo/wdt/wdt.h"
#include <string.h>
#include <stdio.h>

// pruebas

#include "simo/sim_device.h"
#include "simo/uart.h"
#include "simo/spi.h"
#include "simo/memory/AT45DB041E.h"
 
#include "simo/memory/memory_store.h"


#define PIN_CS      9

#define BLINK       8




static void _task3_spi(void *param)
{
    vTaskDelay(10000);
    s_uart_init(S_UART0,115200);
    
    s_uart_write(S_UART0,"test 3: driver memoria spi\n",strlen("test 3: driver memoria spi\n"));



    // instancio una memoria
    //static AT45DB041E_t* mem;

    s_uart_write(S_UART0,"test 3: se creara memoria\n",strlen("test 3: se creara memoria\n"));
    
    
    s_memory_store_init();




    //mem = s_AT45DB041E_create(S_SPI1,PIN_CS);
    s_uart_write(S_UART0,"test 3: se creo memoria\n",strlen("test 3: se creo memoria\n"));
    //uint8_t res = s_AT45DB041E_start(mem);
    s_uart_write(S_UART0,"test 3: memoria start \n",strlen("test 3: memoria start \n"));

   



    char msg1[]= "mensaje de prueba 1 aleatorio";
    char msg2[]= "mensaje de prueba 2 perspectiva";
    char msg3[]= "mensaje de prueba 3 logico";
    char msg4[]= "mensaje de prueba 4 nada";
    char msg5[]= "mensaje de prueba 5 logico2";


   

    uint16_t w1,w2,w3, w4 ,w5 ;




   //guardo segundo mensaje
    w2 = s_memory_store_add_data(msg2,strlen(msg2)+1);
    s_uart_write(S_UART0,"counter inicial: ",strlen("counter2: "));
    s_uart_write(S_UART0,(uint8_t*)&w2,2);
    s_uart_write(S_UART0,"\n",strlen("\n"));


    //guardo primer mensaje
    w1 = s_memory_store_add_data(msg1,strlen(msg1)+1);
    s_uart_write(S_UART0,"counter1: ",strlen("counter1: "));
   
    s_uart_write(S_UART0,(uint8_t*)&w1,2);
    s_uart_write(S_UART0,"\n",strlen("\n"));

 


    w3 = s_memory_store_add_data(msg3,strlen(msg3)+1);
    s_uart_write(S_UART0,"counter3: ",strlen("counter3: "));
    s_uart_write(S_UART0,(uint8_t*)&w3,2);
    s_uart_write(S_UART0,"\n",strlen("\n"));

    w4 = s_memory_store_add_data(msg4,strlen(msg4)+1);
    s_uart_write(S_UART0,"counter4: ",strlen("counter4: "));
    s_uart_write(S_UART0,(uint8_t*)&w4,2);
    s_uart_write(S_UART0,"\n",strlen("\n"));


     w5 = s_memory_store_add_data(msg5,strlen(msg5)+1);
    s_uart_write(S_UART0,"counter5: ",strlen("counter5: "));
    s_uart_write(S_UART0,(uint8_t*)&w5,2);
    s_uart_write(S_UART0,"\n",strlen("\n"));


    //s_AT45DB041E_write_page(mem,msg,strlen(msg)+1,10,0,false);
    s_uart_write(S_UART0,"test 3:Se escribio 1: en memoria:  ",strlen("test 3:Se escribio 1: en memoria:  "));
    s_uart_write(S_UART0,msg1,strlen(msg1));
    s_uart_write(S_UART0,"\n",1);

      s_uart_write(S_UART0,"test 3:Se escribio 2: en memoria:  ",strlen("test 3:Se escribio 2: en memoria:  "));
    s_uart_write(S_UART0,msg2,strlen(msg2));
    s_uart_write(S_UART0,"\n",1);

     //s_AT45DB041E_write_page(mem,msg,strlen(msg)+1,10,0,false);
    s_uart_write(S_UART0,"test 3:Se escribio 3: en memoria:  ",strlen("test 3:Se escribio 1: en memoria:  "));
    s_uart_write(S_UART0,msg3,strlen(msg3));
    s_uart_write(S_UART0,"\n",1);

      s_uart_write(S_UART0,"test 3:Se escribio 4: en memoria:  ",strlen("test 3:Se escribio 2: en memoria:  "));
    s_uart_write(S_UART0,msg4,strlen(msg4));
    s_uart_write(S_UART0,"\n",1);

     s_uart_write(S_UART0,"test 3:Se escribio 5: en memoria:  ",strlen("test 3:Se escribio 2: en memoria:  "));
    s_uart_write(S_UART0,msg5,strlen(msg5));
    s_uart_write(S_UART0,"\n",1);

    vTaskDelay(100);

   vTaskDelay(10);
    uint8_t elements_read1[100];
    uint8_t elements_read2[100];
     uint8_t elements_read3[100];
    uint8_t elements_read4[100];
     uint8_t elements_read5[100];











    uint16_t r1,r2,r3,r4,r5;
   r1 =  s_memory_store_read_data( elements_read1,0,0); //pagina 1 
   r2 =  s_memory_store_read_data( elements_read2,0,1); //pagina 2
   r3 =  s_memory_store_read_data( elements_read3,0,2); //pagina 1 
   r4 =  s_memory_store_read_data( elements_read4,0,3); //pagina 2
     r5 =  s_memory_store_read_data( elements_read5,0,4); //pagina 2


  
   
    vTaskDelay(10);
    s_uart_write(S_UART0,"mensaje 1:Se leyo ",strlen("mensaje 1:Se leyo "));

    char buf1[30];
    sprintf(buf1,"bytes leidos %u \n",r1);
    s_uart_write(S_UART0,buf1,strlen(buf1));
   

    s_uart_write(S_UART0,(elements_read1),strlen(elements_read1));
    s_uart_write(S_UART0,"\n",1);

    
    sprintf(buf1,"bytes leidos %u \n",r2);
    s_uart_write(S_UART0,buf1,strlen(buf1));

    s_uart_write(S_UART0,(elements_read2),strlen(elements_read2));
    s_uart_write(S_UART0,"\n",1);

     sprintf(buf1,"bytes leidos %u \n",r3);
    s_uart_write(S_UART0,buf1,strlen(buf1));

    s_uart_write(S_UART0,(elements_read3),strlen(elements_read3));
    s_uart_write(S_UART0,"\n",1);


    sprintf(buf1,"bytes leidos %u \n",r4);
    s_uart_write(S_UART0,buf1,strlen(buf1));

    s_uart_write(S_UART0,(elements_read4),strlen(elements_read4));
    s_uart_write(S_UART0,"\n",1);
  

     sprintf(buf1,"bytes leidos %u \n",r5);
    s_uart_write(S_UART0,buf1,strlen(buf1));

    s_uart_write(S_UART0,(elements_read5),strlen(elements_read5));
    s_uart_write(S_UART0,"\n",1);
    while(1)
    {
        vTaskDelay(500);
    }

}







/**
 * @brief   Inicio el programa principal del sistema
 * @param   None
 * @return  int 0: 
 * 
 * **/

int main()
{

    stdio_init_all();


 
   
    
    simo_wdt_init();
     


    BaseType_t ret =   xTaskCreate(_task3_spi,"spi test",3000,0,3,0);

   
    
  
    vTaskStartScheduler();

    for (;;)
    {
        
        //should never get here
    }

    return 0;
}
