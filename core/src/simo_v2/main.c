



#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "queue.h"
#include "pico/stdlib.h"
#include "simo/wdt/wdt.h"
#include <string.h>
#include <stdio.h>

// pruebas


#include "simo/uart.h"
#include "simo/spi.h"
#include "simo/memory/AT45DB041E.h"
 
#include "simo/memory/memory_store.h"
#include "simo/debug_interface.h"

#include "simo/SIM/sim_device.h"
#include "simo/request_command.h"
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


void sim_device_test(void* params)
{
    
    debug_init();

     sleep_ms(6000);

    debug_init();
   debug_printf("iniciamos programa \r\n");
   device_t * device = NULL;
   if (device == NULL)
   {
       debug_printf("error al crear device\n");

   }
   else 
   {
       debug_printf("device creado correctamente\n");
   }

    init_device(device);
    while(1)
    {
        debug_printf("debugg message \r\n");
        
        
        vTaskDelay(3500);
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

   //stdio_init_all();

    
  
   //init_device(device);

    
  //  simo_wdt_init();
     


   // BaseType_t ret =   xTaskCreate(_task3_spi,"spi test",6000,0,3,0);

   
 BaseType_t ret =   xTaskCreate(sim_device_test,"debug test",2000,0,3,0);
  
    vTaskStartScheduler();

    for (;;)
    {
        
        //should never get here
    }

    return 0;
}
