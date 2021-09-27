#include "simo/spi.h"


#include "hardware/spi.h"
#include "hardware/gpio.h"


#define SPI_DEFAULT  spi1    // por defecto spi1
 


#define SPI0_CLK                    2
#define SPI0_MISO                   3 //master input  TX
#define SPI0_MOSI                   4 //master output RX
#define SPI0_CSn                    5

#define SPI1_CLK                    10
#define SPI1_MISO                   11 //master input  TX
#define SPI1_MOSI                   12 //master output RX
#define SPI1_CSn                    13






/**
 * @brief   Asigno la instancia SPI correspondiente
 * 

 * @param   spi: spi a asignar
 * @return  NONE : NONE
 * 
 * **/



static spi_inst_t* _get_spi(spi_t spi)
{
    spi_inst_t* _spi;
    switch (spi)
    {
    case S_SPI0:
        _spi= spi0;
        break;
    
    case S_SPI1:
        _spi = spi1;
    default:
        _spi = spi1; // por default usar SPI1,
        break;
    }
    return _spi;
  
}



/**
 * @brief   Configuro los pines correspondiente al SPI seleccionado
 * 

 * @param   spi: spi a configurar pines
 * @return  NONE : NONE
 * 
 * **/



static void _set_pins(spi_t spi)
{

    uint8_t clk_pin;
    uint8_t miso_pin;
    uint8_t mosi_pin;
    uint8_t cs_pin;

    switch (spi)
    {
    case S_SPI0:
         clk_pin = SPI0_CLK  ; 
         miso_pin = SPI0_MISO ;  
         mosi_pin = SPI0_MOSI  ; 
         cs_pin = SPI0_CSn   ;
        break; 
    
    case S_SPI1:
         clk_pin = SPI1_CLK  ; 
         miso_pin = SPI1_MISO  ; 
         mosi_pin = SPI1_MOSI   ;
         cs_pin = SPI1_CSn   ;
         break;
    default:
         clk_pin = SPI1_CLK  ; 
         miso_pin = SPI1_MISO  ; 
         mosi_pin = SPI1_MOSI   ;
         cs_pin = SPI1_CSn ;
        break;
    }
    // configuro pins
    gpio_set_function(clk_pin,GPIO_FUNC_SPI);
    gpio_set_function(miso_pin,GPIO_FUNC_SPI);  
    gpio_set_function(mosi_pin,GPIO_FUNC_SPI);
    gpio_set_function(cs_pin,GPIO_FUNC_SPI);  

  
}


void s_spi_init(spi_t spi,uint32_t baudrate)
{
    // obtengo la instancia spi
    spi_inst_t* _spi = _get_spi(spi);
    // configuro pines asociados
    _set_pins(spi);
    // configuro la interfaz
    spi_init(_spi,baudrate);
}



void s_spi_deinit(spi_t  spi){
     // obtengo la instancia spi
    spi_inst_t* _spi = _get_spi(spi);
    spi_deinit(_spi);
    

}



void s_spi_write(spi_t  spi, int8_t* buf,uint32_t len_buf){
     // obtengo la instancia spi
    spi_inst_t* _spi = _get_spi(spi);
    spi_write_blocking(_spi,buf,len_buf);

}




bool s_spi_is_readable(spi_t  spi){
     // obtengo la instancia spi
    spi_inst_t* _spi = _get_spi(spi);
    bool res = spi_is_readable(_spi);
    return res;
}



void s_spi_read(spi_t  spi,int8_t* buf,uint8_t tx_data,uint8_t len_buf){
     // obtengo la instancia spi
    spi_inst_t* _spi = _get_spi(spi);
    spi_read_blocking(_spi,tx_data,buf,len_buf);

}

