
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
#include "simo/debug_interface.h"

#define PIN_CS      9

#define BLINK       8




static void _task3_spi(void *param)
{
    vTaskDelay(10000);
    s_uart_init(S_UART0,115200);
    
    s_uart_write(S_UART0,"test 3: driver memoria spi\n",strlen("test 3: driver memoria spi\n"));


    s_uart_write(S_UART0,"test 3: se creara memoria\n",strlen("test 3: se creara memoria\n"));
    
    
    vTaskDelay(100);
    s_memory_store_init(); // se configura pagina 256bytes



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


/*
    set_memory_counter_data(0);  // configuramos a cero el contador de paginas


    //guardo primer mensaje
    w1 = s_memory_store_add_data(msg1,strlen(msg1)+1);
 
   
   sprintf(counter,"contador de datos: %u \n",w1);
    s_uart_write(S_UART0,counter,strlen(counter));

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


w7 = s_memory_store_add_data(msg7,strlen(msg7)+1);
  
    sprintf(counter,"contador de datos: %u \n",w7);
    s_uart_write(S_UART0,counter,strlen(counter));


w7 = s_memory_store_add_data(msg7,strlen(msg7)+1);
  
    sprintf(counter,"contador de datos: %u \n",w7);
    s_uart_write(S_UART0,counter,strlen(counter));


w7 = s_memory_store_add_data(msg7,strlen(msg7)+1);
  
    sprintf(counter,"contador de datos: %u \n",w7);
    s_uart_write(S_UART0,counter,strlen(counter));




  */
   vTaskDelay(10);

    uint16_t  r;
    uint8_t elements_read[100];
    char buff[100];
    sleep_ms(2);
    uint16_t c = get_counter_data(); // obtengo el contador de paginas de la memoria
    sleep_ms(2);

    sprintf(buff,"Numero de pagina a leer: %d \n",c); // numero de pagina
    s_uart_write(S_UART0,buff,strlen(buff));


     vTaskDelay(10);

    for(uint16_t index=0; index < c ; index ++)
    {

  
        r =  s_memory_store_read_data( elements_read,0,index); //pagina 1 
       

        sprintf(buff,"[%d] %s \n",index,elements_read);
        s_uart_write(S_UART0,buff,strlen(buff));
        vTaskDelay(10);
        

    }
        s_uart_write(S_UART0,"Finalizo lectura de memoria",strlen("Finalizo lectura de memoria"));

    
    while(1)
    {
        vTaskDelay(500);
    }

}


void debug_test(void* params)
{
    while(1)
    {
        debug_printf("debugg message \r\n");
        vTaskDelay(1500);
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

  //  stdio_init_all();

    debug_init();

 
   
    
    simo_wdt_init();
     


   // BaseType_t ret =   xTaskCreate(_task3_spi,"spi test",6000,0,3,0);

   
    BaseType_t ret =   xTaskCreate(debug_test,"debug test",2000,0,3,0);
  
    vTaskStartScheduler();

    for (;;)
    {
        
        //should never get here
    }

    return 0;
}
