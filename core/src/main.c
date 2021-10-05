
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

   



    char msg1[]= "river plate 2";
    char msg2[]= "boca jr 1";
    char msg3[]= "gran partido de julian Alvarez";


   

    uint16_t w1,w2,w3;



    char counter[40];






    //guardo primer mensaje
    w1 = s_memory_store_add_data(msg1,strlen(msg1)+1);
 
   
   sprintf(counter,"contador de datos: %u \n",w1);
    s_uart_write(S_UART0,counter,strlen(counter));


   //guardo segundo mensaje
    //w2 = s_memory_store_add_data(msg2,strlen(msg2)+1);
  
    // sprintf(counter,"contador de datos: %u \n",w2);
    //s_uart_write(S_UART0,counter,strlen(counter));

  //guardo tercer mensaje
   // w3 = s_memory_store_add_data(msg3,strlen(msg3)+1);
  
   // sprintf(counter,"contador de datos: %u \n",w3);
   // s_uart_write(S_UART0,counter,strlen(counter));
    
 




 

    vTaskDelay(100);

   vTaskDelay(10);
    uint8_t elements_read1[100];
    uint8_t elements_read2[100];
    uint8_t elements_read3[100];










    uint16_t r1,r2,r3;
   r1 =  s_memory_store_read_data( elements_read1,0,0); //pagina 1 
   r2 =  s_memory_store_read_data( elements_read2,0,1); //pagina 2
   r3 =  s_memory_store_read_data( elements_read3,0,2); //pagina 2

   

  
   
    vTaskDelay(10);
    

   char buffer[50];

  
     sprintf(buffer,"mensaje leido: %s \n",elements_read1);
         s_uart_write(S_UART0,buffer,strlen(buffer));


     sprintf(buffer,"mensaje leido: %s \n",elements_read2);
         s_uart_write(S_UART0,buffer,strlen(buffer));


     sprintf(buffer,"mensaje leido: %s \n",elements_read3);
         s_uart_write(S_UART0,buffer,strlen(buffer));


 



    s_uart_write(S_UART0,"Fin de las pruebas\n",strlen("Fin de las pruebas\n"));


    
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
