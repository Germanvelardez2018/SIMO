/**
  @file spi.h  (simplificado)
  @brief Estructuras y funciones asociadas al manejo del harware spi.
  @author German Velardez
  @date 25/09/2021
*/






#ifndef   _SPI_H
  #define _SPI_H
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
 * @param   spi: hardware seleccionado
 *              S_SPI_0
 *              S_SPI_1
 * @param   baudrate: baudrate a lo que funciona el sistema
 * @return  None
 * 
 * **/

void s_spi_init(spi_t spi,uint32_t baudrate);


/**
 * @brief   Deshabilitar el periferico SPI
 * 
 * @param   spi: instancia de hardware a deshabilitar  
 * @return  None
 * 
 * **/

void s_spi_deinit(spi_t  spi);

/**
 * @brief   Escribir bytes mediante SPI
 * 
 * @param   spi: instancia de hardware a utilizar
 * @param   buf: buffer de datos a enviar
 * @param   len_buf: tamaño del buffer utilizado  
 * @return  None
 * 
 * **/

void s_spi_write(spi_t  spi, int8_t* buf, uint32_t len_buf );



/**
 * @brief   consultar si esta disponible para lectura
 * 
 * @param   spi: instancia de hardware a utilizar
 
 * @return  res: verdadero o falso
 * 
 * **/

bool s_spi_is_readable(spi_t  spi);

/**
 * @brief   
 * 
 * @param   None  
 * @return  None
 * 
 * **/


/**
 * @brief   Leer bytes mediante SPI
 * 
 * @param   spi: instancia de hardware a utilizar
 * @param   buf: buffer de datos donde se almacenara bytes leidos
 * @param   len_buf: tamaño del buffer utilizado  
 * @return  None
 * 
 * **/
void s_spi_read(spi_t  spi,int8_t* buf,uint8_t tx_data,uint32_t len_buf);




/**
 * @brief   Leer y escribir bytes meduante SPI
 * 
 * @param   spi: instancia de hardware a utilizar
 * @param   buf_w: buffer de datos a escribir
 * @param   buf: buffer de datos leidos
 * @param   len_buf: tamaño del buffer utilizado  
 * @return  None
 * 
 * **/

void s_spi_write_read(spi_t spi, uint8_t* buf_w, uint8_t* buff_r, uint32_t len_buff);


#endif

