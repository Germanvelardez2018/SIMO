
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
 

static QueueSetHandle_t _QUEUE_RESPONSES_MAIN_;

#define PIN_BLINK      9


#define BLINK      25





    //inicio el SP1
    #define CMD_LEN         4
    #define RES_LEN         4
    #define ERASE_SECUENCE_LEN       4
    #define DUMMY_BYTE      0                         
    uint8_t cmd[CMD_LEN]=
    {
        CMD_RDID,   //comando para leer ID del chip
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };
    uint8_t res[RES_LEN]=
    {
      DUMMY_BYTE,
      DUMMY_BYTE,
      DUMMY_BYTE,
      DUMMY_BYTE,
    };

    uint8_t erase_cmd[ERASE_SECUENCE_LEN]=
    {
        0xC7,
        0x94,
        0x80,
        0x9A
    };


static void _task_test_spi(void* params)
{
    

    vTaskDelay(10000); // espero 10 s
    
     
    s_uart_init(S_UART0,115200);
    
    s_uart_write(S_UART0,"borrar flash\n",strlen("borrar flash\n"));
    s_spi_init(S_SPI1,10*1000);

    // secuencia para borrar flash

    gpio_init(PIN_BLINK);
    gpio_set_dir(PIN_BLINK, 1);
    gpio_put(PIN_BLINK, 1);  //flanco ascendente
    vTaskDelay(500);
    gpio_put(PIN_BLINK, 0);  //flanco ascendente


    s_spi_write(S_SPI1,erase_cmd,ERASE_SECUENCE_LEN);

    gpio_put(PIN_BLINK, 1);  //flanco ascendente
    vTaskDelay(4000);
            s_uart_write(S_UART0,"se borro la memoria\n",strlen("se borro la memoria\n"));





  

    while(1)
    {
        vTaskDelay(1);
        s_uart_write(S_UART0,"paso check\n",strlen("paso check\n"));


//
        
        gpio_put(PIN_BLINK, 0);  //flanco descendente

        s_spi_write_read(S_SPI1,cmd,res,RES_LEN);
   
    
       
      
        gpio_put(PIN_BLINK, 1);  //flanco ascendente

        s_uart_write(S_UART0,"bit:\n",strlen("bit:\n"));
        s_uart_write(S_UART0,res,RES_LEN);
        s_uart_write(S_UART0,"\n",strlen("\n"));
        vTaskDelay(2000);
      
        vTaskDelay(1000);
           
    }
   
    

}




void task_led(void* params)
{
   
   // uart_init(S_UART0,115200);
   // s_uart_write(S_UART0,"iniciando pruebas de SPI\n",strlen("iniciando pruebas de SPI\n"));

    while(1)
    {
     //   s_uart_write(S_UART0,"blink\n",strlen("blink\n"));
      gpio_put(PIN_BLINK, 1);    // flanco descendente
      vTaskDelay(1000);
      gpio_put(PIN_BLINK, 0);    // flanco descendente

        vTaskDelay(1000);

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


 

   
    //simo_wdt_init();
     


    BaseType_t ret =   xTaskCreate(_task_test_spi,"spi test",3000,0,3,0);

    if( ret == pdPASS)
    {
     //   s_uart_write(S_UART0,"paso check\n",strlen("paso check\n"));
        gpio_put(BLINK, 1);   // creacion de tarea fallo
    }
    
    //xTaskCreate(_task_test_spi,"spi test",2000,0,3,0);
    vTaskStartScheduler();

    for (;;)
    {
        
        //should never get here
    }

    return 0;
}
