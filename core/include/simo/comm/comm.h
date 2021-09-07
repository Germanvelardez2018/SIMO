/**
 * @file comm.h
 * @brief Funciones para manejar modulos de comunicacion externos.
 * @author German Velardez
 * @date 9/2021
 * 
 * 
 * */

 #include "simo/core.h"



    /*! Tipos de interfaces de hardware utilizadas en la comunicacion */

    typedef enum
    {

    COMM_UART, /*!<  Comunicacion mediante UART */
    
    COMM_I2C, /*!<  Comunicacion mediante I2C */


    COMM_SPI /*!<   Comunicacion mediante SPI */

    } comm_interface_t;





 /*! Estructura para configurar el modulo de comunicacion*/

typedef struct
{
   comm_interface_t hard_interface;  /*!<  Interfaz de hardware  */
   char* buffer;                    /*!<  Buffer de comunicacion */
   void* data;                      /*!<  Estructura de datos a enviar o almacenar */
} comm_config_t;






/**
 * @brief   inicia comunicacion
 * 
 * @param   comm_config_t* config:  
 * @return  None
 * 
 * **/

void   comm_init(comm_config_t* config);




/**
 * @brief   deshabilita la  comunicacion
 * 
 * @param   comm_config_t* config:  
 * @return  None
 * 
 * **/

void   comm_deinit(comm_config_t* config);


/**
 * @brief   Tarea que procesa los elementos
 * 
 * @param   void* params: NO SE USA  
 * @return  None
 * 
 * **/

void comm_task(void* params);
