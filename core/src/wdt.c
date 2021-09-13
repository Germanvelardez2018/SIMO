
#include "FreeRTOS.h"
#include "task.h"

#include "simo/wdt/wdt.h"
#include "simo/config.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "hardware/watchdog.h"

#define SIMO_WDT_PRIORITY     (configMAX_PRIORITIES - 1)
#define TIMER_DIVIDER         2      /*Este numero debe ser mayor que 1 a medida que el micro se cobrecarga de tareas*/       
#define PIN_BLINKING          PICO_DEFAULT_LED_PIN    /*Pin que parpadea al refrescar watch*/
#define BLINK_TIME            50            /*Tiempo entre destellos*/


#define LED_PIN PICO_DEFAULT_LED_PIN

#define GPIO_ON 1
#define GPIO_OFF 0

static TaskHandle_t _WDT_TASK_HANDLER;  /**< Referencia a la tarea encargada de recargar el dwt */







/**
  * @brief Tarea que se encarga de reinicia el contador de wdt. Se llama en simo_wdt_init
  * @param  None
  * @retval None:
  */

static void task_watching_simo(void *params)
{
  
    watchdog_enable(TIME_WDT, 1);


    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

  

    while (1)

    {
        watchdog_update();
        gpio_put(LED_PIN, GPIO_ON);
        vTaskDelay(TIME_BLINK);
        gpio_put(LED_PIN, GPIO_OFF);

        vTaskDelay(TIME_WDT / TIMER_DIVIDER);
    }
}


/**
  * @brief Inicia el wdt y la tarea encargada de recargar el contador. El valor de desborse se configura en simo/config.h
  * @param  None
  * @retval None:
  */
void simo_wdt_init(void)
{
  xTaskCreate(task_watching_simo, "simo watching", 4 * 1024,(void*)( TIME_WDT +2*(TIME_BLINK)), SIMO_WDT_PRIORITY, &_WDT_TASK_HANDLER);
}

/**
  * @brief Desactiva el wdt y elimina la tarea que recarga el contador asociado
  * @param  None
  * @retval None:
  */
void simo_wdt_deinit(void)
{

   // Al parecer el wdt no puede desactivarse, revisar
 // vTaskDelete(_WDT_TASK_HANDLER);  
  gpio_put(LED_PIN, GPIO_OFF);
}





