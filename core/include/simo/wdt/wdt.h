
/**
*  @file wdt.h
*  @brief Manejo del WDT del sistema, el tiempo de configuracion se modifica desde simo/config.h.
*  @author German Velardez
*  @date 9/2021


**/



/**
  * @brief Inicia el wdt y la tarea encargada de recargar el contador. El valor de desborse se configura en simo/config.h
  * @param  None
  * @retval None:
  */
void simo_wdt_init(void);


/**
  * @brief Desactiva el wdt y elimina la tarea que recarga el contador asociado
  * @param  None
  * @retval None:
  */
void simo_wdt_deinit(void);



