/**
* @file timer.h
* @brief Funciones para lanzar rutinas periodicas o one shot. Nota: Timers por software no recomendables cuando se necesita una alta precisión.
* @author German Velardez
* @date 9/2021
 * **/
#include "FreeRTOSConfig.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"


#include "simo/config.h"
#include "simo/core.h"






typedef void (*callback_function)(void*);
/**< Puntero a funcion callback para asociar a timer por software */

typedef  TimerHandle_t  soft_timer_t; 
/**< Timer por software, basado en api Freertos */










/**
  * @brief Tarea que se encarga de reinicia el contador de wdt. Se llama en simo_wdt_init
  * @param  None
  * @retval None:
  */
void simo_watch_task(void* params);

 /**
  * @brief Asocia una funcion de callback con un sotf_timer_t
  * @param   timer: punter a la instancia del timer
  * @param   callback: funcion a ejecutar 
  * @param   periodic:  funcion (x==1)periodica  o (x!=1) one shot
  * @retval simo_err_t: Estado del sistema
  */

status_t simo_timer_create( soft_timer_t* timer,callback_function callback, TickType_t time,uint8_t periodic);



/**
  * @brief Elimina la configuracion de un timer
  * @param   timer: Puntero a la instancia del timer
  *
  * @retval None
  */

void simo_timer_delete(soft_timer_t* timer);

/**
  * @brief Inicia el timer
  * @param   timer: Puntero a la instancia del timer
  *
  * @retval None
  */

void simo_timer_start(soft_timer_t* timer);

/**
  * @brief Frena un timer que ya fue configurado e iniciado.
  * @param   timer: Puntero a la instancia del timer
  *
  * @retval None
  */

void simo_timer_stop(soft_timer_t* timer);



/**
  * @brief Resetea el contador del timer.
  * @param   timer: Puntero a la instancia del timer
  *
  * @retval None
  */

void simo_timer_reset(soft_timer_t* timer);