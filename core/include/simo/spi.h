/**
  @file spi.h  (simplificado)
  @brief Estructuras y funciones asociadas al manejo del harware spi.
  @author German Velardez
  @date 25/09/2021
*/

#include <stdint.h>
#include <stdbool.h>


typedef enum 
{
    S_SPI0,
    S_SPI1
} spi_t;




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

void s_spi_init(spi_t uart,uint32_t baudrate);


/**
 * @brief   Rutina de interrupcion para la recepcion de mensaje (simo_comm_irq())
 * 
 * @param   None  
 * @return  None
 * 
 * **/

void s_spi_deinit(spi_t  spi);

/**
 * @brief   Rutina de interrupcion para la recepcion de mensaje (simo_comm_irq())
 * 
 * @param   None  
 * @return  None
 * 
 * **/

void s_spi_write(spi_t  spi, int8_t* buf, uint32_t len_buf );



/**
 * @brief   Consulta si existen elemento por leer en el buffer uart
 * 
 * @param   uart: uart fifo por leer
 * @return  timeout_us: tiempo de espera en microsegundos
 * 
 * **/

bool s_spi_is_readable(spi_t  spi);

/**
 * @brief   Rutina de interrupcion para la recepcion de mensaje (simo_comm_irq())
 * 
 * @param   None  
 * @return  None
 * 
 * **/

void s_spi_read(spi_t  spi,int8_t* buf,uint8_t tx_data,uint8_t len_buf);

