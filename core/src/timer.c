#include "simo/timer/timer.h"










/**
  * @brief Funcion que gestiona los handlers de los timers.
  * @retval None
  */


static void generic_handler(TimerHandle_t params)
{
  
    callback_function callback = (callback_function) pvTimerGetTimerID(params);
    (callback)(NULL); //ejecuto el callback

}




status_t simo_timer_create( soft_timer_t* timer,callback_function callback, TickType_t time,uint8_t periodic)
{

 

    BaseType_t _periodic;
    _periodic = (periodic == 1)? pdTRUE : pdFALSE;

    (*timer) = xTimerCreate("_SOFT_TIMER_",
                                  time,
                                 _periodic,
                                 (void*)callback,
                                 generic_handler);

    if((*timer) == NULL)
    {
        return SIMO_FAIL;
    }
    return   SIMO_OK;
}









void simo_timer_delete(soft_timer_t* timer)
{

}



void simo_timer_start(soft_timer_t* timer)
{
  xTimerStart((*timer),0);
}


void simo_timer_stop(soft_timer_t* timer)
{
  xTimerStop((*timer),0);
}

