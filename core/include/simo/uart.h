/**
  @file uart.h  (simplificado)
  @brief Estructuras y funciones asociadas al manejo del harware uart.
  @author German Velardez
  @date 12/2021
*/




#ifndef   _SIMO_UART_H
#define   _SIMO_UART_H


  #include "hardware/uart.h"



  typedef enum {
      S_UART0,
      S_UART1
  } uart_t;





  typedef void (*uart_callback_t)(void);


  /**
   * @brief   Inicia el uart seleccionado
   * 
   * @param   uart: hardware seleccionado
   *              UART_1
   *              UART_2
   * @param   baudrate: baudrate a lo que funciona el sistema
   * @return  None
   * 
   * **/

  void s_uart_init(uart_t uart,uint32_t baudrate);


  /**
   * @brief   Rutina de interrupcion para la recepcion de mensaje (simo_comm_irq())
   * 
   * @param   None  
   * @return  None
   * 
   * **/

  void s_uart_deinit(uart_t uart);

  /**
   * @brief   Rutina de interrupcion para la recepcion de mensaje (simo_comm_irq())
   * 
   * @param   None  
   * @return  None
   * 
   * **/

  void s_uart_write(uart_t uart, int8_t* buf, uint32_t len_buf );



  /**
   * @brief   Consulta si existen elemento por leer en el buffer uart
   * 
   * @param   uart: uart fifo por leer
   * @return  timeout_us: tiempo de espera en microsegundos
   * 
   * **/

  bool s_uart_is_readable(uart_t uart, uint32_t timeout_us);

  /**
   * @brief   Rutina de interrupcion para la recepcion de mensaje (simo_comm_irq())
   * 
   * @param   None  
   * @return  None
   * 
   * **/

  void s_uart_read(uart_t uart,int8_t* buf,uint32_t len_buf,uint32_t timeout_us);



  /**
   * @brief   Rutina de interrupcion para la recepcion de mensaje (simo_comm_irq())
   * 
   * @param    uart: uart a configurar
   * @param    rx_irq: interrupcion para recepcion por uart
   * @param    tx_irq: interrupcion para transmicion por uart
   * @param    irq_function: la funcion que maneja la interrupcion
   * @return  None
   * 
   * **/

  void s_set_interrupcion_handler(uart_t uart,bool rx_irq, bool tx_irq,uart_callback_t irq_function);



  char s_uart_getc(uart_t uart);


#endif