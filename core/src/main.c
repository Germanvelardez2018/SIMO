#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "simo/uart/uart.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#include "simo/timer/timer.h"
#include "simo/comm/comm.h"
#include <string.h>

#define LED_PIN PICO_DEFAULT_LED_PIN

#define GPIO_ON 1
#define GPIO_OFF 0



static  simo_uart_instance interface ;



/**
 * @brief   Funcion asociada a timer
 * 
 * @param   void* params: No se usa, es parte de la estructura de puntero a funcion que se asocia al timer 
 * @return  None
 * 
 * **/

static void blink_funcion(void *param)
{

    gpio_put(LED_PIN, GPIO_ON);
    vTaskDelay(100);
    gpio_put(LED_PIN, GPIO_OFF);
    vTaskDelay(200);
   

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

  
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);





    



    static soft_timer_t timer_led;

    status_t res = create_timer_function(&timer_led, blink_funcion, 1000, 1);

    start_timer(&timer_led);

    static comm_config_t comm_cfg;

    comm_init(&(comm_cfg));
    vTaskStartScheduler();

    for (;;)
    {
        //should never get here
    }

    return 0;
}
