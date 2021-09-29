#include "simo/memory/AT45DB041E.h"
#include "simo/spi.h"
#include "hardware/gpio.h"
#include  <stdlib.h>







#define ERASE_SECUENCE		        0xC7, 0x94, 0x80, 0x9A
#define ERASE_SECUENCE_LEN           4


//< Puerto SPI utilizado por defecto>

#define MEMORY_SPI      S_SPI1

/**
 * 
 * @note
 * pines  utilizados por defecto en SPI1
 * 
 *   SPI1_CLK                    10
 *   SPI1_MOSI                   11  //master input  TX
 *   SPI1_MISO                   12  //master output RX
 *   SPI1_CSn                    13  
 *   
 * 
 * **/




/**
 * @brief   Crea  una memoria AT45DB041E asignando memoria dinamica. 
 * @note    Necesario borrar con  s_AT45DB041Edelete() al finalizar uso
 * @note    En caso de falla retorna NULL

 * @param   spi: interfaz SPI elegida
 * @param   cs_pin: pin utilizado como CHIPSELECT (CS_PIN)
 * @return  mem :instancia de memoria o NUll 
 * 
 * **/


AT45DB041E_t*  s_AT45DB041E_create( spi_t spi, uint8_t cs_pin)
{

     
    AT45DB041E_t* _mem = (AT45DB041E_t*) malloc(sizeof(AT45DB041E_t));
    if( _mem == NULL) return NULL;                          //fallo asignacion de memoria

    _mem->buffer  = (uint8_t*) malloc(AT45DB041E_BUFFER * sizeof(uint8_t));
    if( _mem->buffer == NULL ) return NULL;   // fallo asignacion de memoria

    // asigno pinCS e interfaz SPI
    _mem->spi = spi;
    _mem-> cs_pin = cs_pin;
    _mem->counter_buff = 0;

    // retorno el puntero creado
    return _mem;
}



/**
 * @brief   Borrar memoria AT45DB041E enviado comandos de secuencia de 4 bytes 

 * @param   mem : instancia a un objeto 
 * @return  None: 
 * 
 * **/


void  s_AT45DB041E_full_erase(AT45DB041E_t* mem)
{
    // CS DE ALTO A BAJO  (INICIO DE COMANDO)
    uint8_t erase_cmd[ERASE_SECUENCE_LEN]={ERASE_SECUENCE};
    s_spi_write(mem->spi,erase_cmd,ERASE_SECUENCE_LEN);
    //CD DE BAJO A ALTO (FIN DE COMANDO)
}

