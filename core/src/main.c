
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

    vTaskDelay(100);




    //mem = s_AT45DB041E_create(S_SPI1,PIN_CS);
    s_uart_write(S_UART0,"test 3: se creo memoria\n",strlen("test 3: se creo memoria\n"));
    //uint8_t res = s_AT45DB041E_start(mem);
    s_uart_write(S_UART0,"test 3: memoria start \n",strlen("test 3: memoria start \n"));

   



    char msg1[]= "river plate 2";
    char msg2[]= "boca jr 1";
    char msg3[]= "river puntero del campeonato 2021";
    char msg4[]= "Bataglia trabaja en rappi";
    char msg5[]= "Bataglia dedicate a la play";
    char msg6[]= "tevez volve a china";
    char msg7[]= "dos golazos";


   

    uint16_t w1,w2,w3,w4,w5,w6,w7;



    char counter[40];






    //guardo primer mensaje
    w1 = s_memory_store_add_data(msg1,strlen(msg1)+1);
 
   
   sprintf(counter,"contador de datos: %u \n",w1);
    s_uart_write(S_UART0,counter,strlen(counter));


   //guardo segundo mensaje
    w2 = s_memory_store_add_data(msg2,strlen(msg2)+1);
  
     sprintf(counter,"contador de datos: %u \n",w2);
    s_uart_write(S_UART0,counter,strlen(counter));

  //guardo tercer mensaje
    w3 = s_memory_store_add_data(msg3,strlen(msg3)+1);
  
    sprintf(counter,"contador de datos: %u \n",w3);
    s_uart_write(S_UART0,counter,strlen(counter));
    
 
  //guardo cuarto mensaje
    w4 = s_memory_store_add_data(msg4,strlen(msg4)+1);
  
    sprintf(counter,"contador de datos: %u \n",w4);
    s_uart_write(S_UART0,counter,strlen(counter));



 //guardo quinto mensaje
    w5 = s_memory_store_add_data(msg5,strlen(msg5)+1);
  
    sprintf(counter,"contador de datos: %u \n",w5);
    s_uart_write(S_UART0,counter,strlen(counter));



    

     //guardo septimo mensaje
    w6 = s_memory_store_add_data(msg6,strlen(msg6)+1);
  
    sprintf(counter,"contador de datos: %u \n",w6);
    s_uart_write(S_UART0,counter,strlen(counter));



w6 = s_memory_store_add_data(msg7,strlen(msg7)+1);
  
    sprintf(counter,"contador de datos: %u \n",w7);
    s_uart_write(S_UART0,counter,strlen(counter));

  
   vTaskDelay(10);
    uint8_t elements_read1[100];
    uint8_t elements_read2[100];
    uint8_t elements_read3[100];
    uint8_t elements_read4[100];
    uint8_t elements_read5[100];
    uint8_t elements_read6[100];
    uint8_t elements_read7[100];










    uint16_t r1,r2,r3,r4,r5,r6;

   r1 =  s_memory_store_read_data( elements_read1,0,0); //pagina 1 
   r2 =  s_memory_store_read_data( elements_read2,0,1); //pagina 2
   r3 =  s_memory_store_read_data( elements_read3,0,2); //pagina 2

   r4 =  s_memory_store_read_data( elements_read4,0,3); //pagina 2

   r5=  s_memory_store_read_data( elements_read5,0,4); //pagina 2
   r6 =  s_memory_store_read_data( elements_read6,0,5); //pagina 2
   r3 =  s_memory_store_read_data( elements_read7,0,6); //pagina 2

   

  
   
    vTaskDelay(10);
    

   char buffer[100];

  
     sprintf(buffer,"mensaje leido: %s \n",elements_read1);
         s_uart_write(S_UART0,buffer,strlen(buffer));


     sprintf(buffer,"mensaje leido: %s \n",elements_read2);
         s_uart_write(S_UART0,buffer,strlen(buffer));


     sprintf(buffer,"mensaje leido: %s \n",elements_read3);
         s_uart_write(S_UART0,buffer,strlen(buffer));


      sprintf(buffer,"mensaje leido: %s \n",elements_read4);
      s_uart_write(S_UART0,buffer,strlen(buffer));



      sprintf(buffer,"mensaje leido: %s \n",elements_read5);
      s_uart_write(S_UART0,buffer,strlen(buffer));

      sprintf(buffer,"mensaje leido: %s \n",elements_read6);
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
     


    BaseType_t ret =   xTaskCreate(_task3_spi,"spi test",6000,0,3,0);

   
    
  
    vTaskStartScheduler();

    for (;;)
    {
        
        //should never get here
    }

    return 0;
}
