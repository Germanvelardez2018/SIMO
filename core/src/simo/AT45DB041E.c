#include "simo/memory/AT45DB041E.h"
#include "simo/spi.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

#include  <stdlib.h>

//bits de estado



#define AT45DB_STATUS_PGSIZE  (1 << 0) /* PAGE SIZE */
#define AT45DB_STATUS_PROTECT (1 << 1) /* PROTECT */
#define AT45DB_STATUS_COMP    (1 << 6) /* COMP */
#define AT45DB_STATUS_READY   (1 << 7) /* RDY/BUSY */
 

//comandos y secuencias

#define ERASE_SECUENCE		        0xC7, 0x94, 0x80, 0x9A     //secuencia de borrado del chip completo
#define ERASE_SECUENCE_LEN          4                           
#define RESUME_CMD                  0xAB                      //salgo del deep sleep_us
#define GETSTATUS_CMD               0xD7                      //Leo los registros de estado de la memoria

#define WRITE_WITH_BUFF1            0x82                     // usar buffer 1 para escribir en memoria

#define AT45DB_PG_SIZE_256_SECUENCE    0x3D, 0x2A, 0x80, 0xA6    //Programa tamaño de pagina en 256
#define AT45DB_PG_SIZE_256_LEN          4

#define AT45DB_PG_SIZE_264_SECUENCE     0x3D, 0x2A, 0x80 ,0xA7    //Programa tamaño de pagina en 264
#define AT45DB_PG_SIZE_264_LEN          4









// Secuencia de ID product

#define GET_ID_CMD                0x9F
#define MANUFACTURER_ID           0x1F    //id byte  1
#define DEVICE_ID_1               0x24    //id byte  2
#define DEVICE_ID_2               0x00    //id byte  3
#define EDI                       0x01    // id byte 4








// escribir en memoria

#define WRITE_CMD                    0x82    //write  mem principal mediante buffer 1
#define CMD_FAST_READ               (0x0B) // max speed 85 MHz. Also its posible to use 0x1B


/* Programacion del tamaño de pagina */

static  uint8_t at45db_pgsize_256_cmd[] = {  AT45DB_PG_SIZE_256_SECUENCE    };
static  uint8_t at45db_pgsize_264_cmd[] = {  AT45DB_PG_SIZE_264_SECUENCE    };


/* Secuencia de borrado de todo el chip*/
static  uint8_t erase_cmd[ERASE_SECUENCE_LEN] = {ERASE_SECUENCE};














/*****************************************************************************/
/*Status Register Format:                                   */
/* ------------------------------------------------------------------------- */
/* | bit7   | bit6   | bit5   | bit4   | bit3   | bit2   | bit1   | bit0   | */
/* |--------|--------|--------|--------|--------|--------|--------|--------| */
/* |RDY/BUSY| COMP   |         device density            |   X    |   X    | */
/* ------------------------------------------------------------------------- */
/* 0:busy   |        |        AT45DB041:0111             | protect|page size */
/* 1:ready  |        |        AT45DB161:1011             |                   */
/* --------------------------------------------------------------------------*/
/*****************************************************************************/




/**
 *  Memoria utilizada: at45db041E
 * PAGINAS: 2048
 * BLOQUES: 256
 * SECTORES: 8
 * 
 * 
 * 
 * Se pueden usar paginas de 264bytes o de 256bytes. 
 * 
 * 
 * 
 * **/





// estructura usada 

static flash_storage_t __flash;




/**
 * @brief   Crea  una memoria AT45DB041E asignando memoria dinamica. 
 * @note    Necesario borrar con  s_AT45DB041Edelete() al finalizar uso
 * @note    En caso de falla retorna NULL

 * @param   spi: interfaz SPI elegida
 * @param   cs_pin: pin utilizado como CHIPSELECT (CS_PIN)
 * @return  mem :instancia de memoria o NUll 
 * 
 * **/


static inline bool __at45db_check_id(AT45DB041E_t* mem){
  
 //envio comando para obtener product ID

    uint8_t cmd[5]=
    {
        GET_ID_CMD,
        0,
        0,
        0,
        0
    };

// buffer para datos
    uint8_t  data[5]={
        0, //dummy
        0,
        0,
        0,
        0
    };

  
  
     //en alto el CS Pin
    gpio_put(mem->cs_pin,0 );  //flanco ascendente
    s_spi_write_read(mem->spi,cmd,data,5);    //leo el primer byte del registro estado
    //en alto el CS Pin
    gpio_put(mem->cs_pin, 1);  //flanco ascendente

   // sleep_us(1);

    //checkeo respuesta correcta
    if( data[1] != MANUFACTURER_ID    
        || data[2] != DEVICE_ID_1        
        || data[3] != DEVICE_ID_2        
        || data[4] != EDI) 
    {
        return false;  //fallo checkeo de ID
    }
        return true;
}



static inline uint8_t __at45db_get_status(AT45DB041E_t* mem)
{
    
    uint8_t cmd[2]={GETSTATUS_CMD,0};
    uint8_t status[2]={0,0};

            //flanco ascendente 
     //en alto el CS Pin
    gpio_put(mem->cs_pin,0 );           //flanco ascendente
    s_spi_write_read(mem->spi,cmd,status,2);    //leo el primer byte del registro estado

     //en alto el CS Pin
    gpio_put(mem->cs_pin, 1);  //flanco ascendente
    return  status[1];
}






/**
 * @brief   Espero hasta que la memoria deje de estar ocupada. Devuelvo el primer byte de status

    @note La funcion espera en un while tramos de 10 us, deberia tener un timeout. NO lo tiene (aun).
 * @param   spi: interfaz SPI elegida
 * @return   status :devuelvo el primer byte de estado 
 * 
 * **/

static inline uint8_t __at45_is_bussy(AT45DB041E_t* mem)
{
    uint8_t sr;

    while(!((sr =__at45db_get_status(mem)) & AT45DB_STATUS_READY))  //mientras este ocupado, espere
    {
        sleep_us(1);
    }
    return sr;  //es el primer byte del registro de estados
}




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

    //en alto el CS Pin
    s_spi_init(S_SPI1,20*1000);
    gpio_init(_mem->cs_pin);
    gpio_set_dir(_mem->cs_pin, 1);

    gpio_put(_mem->cs_pin, 1);  //flanco ascendente

    // retorno el puntero creado
    return _mem;
}




int8_t  s_AT45DB041E_start(AT45DB041E_t* mem)
{
    // CS DE ALTO A BAJO  (INICIO DE COMANDO)

    gpio_put(mem->cs_pin, 1);  //flanco ascendente
    gpio_put(mem->cs_pin, 0);  //flanco descendente

    //Despierto el micro en caso de deep sleep_us
    s_spi_write(mem->spi,(uint8_t*)RESUME_CMD,1);

    gpio_put(mem->cs_pin, 1);  //flanco ascendente

    
    

    //obtengo el id del producto
    if(!__at45db_check_id(mem)) return 0;
    
    //configuro tamaño de pagina y buffer: 256

    if(!(__at45_is_bussy(mem) & AT45DB_STATUS_PGSIZE)) //pregunto si page_size es 264. Si es true, configuro en 256
    {
    
    gpio_put(mem->cs_pin, 0);  //flanco descendente

    s_spi_write(mem->spi,(uint8_t*)at45db_pgsize_256_cmd,AT45DB_PG_SIZE_264_LEN);

    gpio_put(mem->cs_pin, 1);  //flanco ascendente

    }

   

    //CD DE BAJO A ALTO (FIN DE COMANDO)
    return 1;
}




void  s_AT45DB041E_full_erase(AT45DB041E_t* mem)
{
    // CS DE ALTO A BAJO  (INICIO DE COMANDO)
     gpio_put(mem->cs_pin, 0);  //flanco descendente
    
    s_spi_write(mem->spi,erase_cmd,ERASE_SECUENCE_LEN);
    
    //CD DE BAJO A ALTO (FIN DE COMANDO)
    gpio_put(mem->cs_pin, 1);  //flanco ascendente
}



// not_counter_len  is always false
void s_AT45DB041E_write_counter_pages(AT45DB041E_t* mem ,uint8_t* count)
{

    // cmd escribir | 3bytes de direccion(  11 bits pagina (0 a 2048| 8 bytes posicion de la pagina | 5 dummy bits)
    uint32_t bytes_addres =0;   
    uint8_t cmd[4] ;    
      
    cmd[0] = WRITE_CMD;
    cmd[1] = (bytes_addres >> 24) & 0xff;
    cmd[2] = (bytes_addres >> 16)  & 0xff;
    cmd[3] = (bytes_addres >> 8)& 0xff;

    
 // CS DE ALTO A BAJO  (INICIO DE COMANDO)
     gpio_put(mem->cs_pin, 0);  //flanco descendente


    // comandos
    s_spi_write(mem->spi,cmd,4);     // escribo comando para escribir 
  
    s_spi_write(mem->spi,count,2); // primer byte de la pagina, numero de bytes a escribir
    
    

  //CD DE BAJO A ALTO (FIN DE COMANDO)
    gpio_put(mem->cs_pin, 1);  //flanco ascendente

    // esperamos
    __at45_is_bussy(mem);


}




// not_counter_len  is always false
void s_AT45DB041E_write_page(AT45DB041E_t* mem ,uint8_t* buffer,uint8_t len_buffer, uint16_t pg_num,uint8_t pos_page)
{

    // cmd escribir | 3bytes de direccion(  11 bits pagina (0 a 2048| 8 bytes posicion de la pagina | 5 dummy bits)
    uint32_t bytes_addres = ( (uint32_t)(pg_num)) << 21  | ((uint32_t) (pos_page)) << 13 ;     
    uint8_t cmd[4] ;    
      
    cmd[0] = WRITE_CMD;
    cmd[1] = (bytes_addres >> 24)  & 0xff;
    cmd[2] = (bytes_addres >> 16)  & 0xff;
    cmd[3] = (bytes_addres >> 8)& 0xff;

    
 // CS DE ALTO A BAJO  (INICIO DE COMANDO)
     gpio_put(mem->cs_pin, 0);  //flanco descendente


    // comandos
    s_spi_write(mem->spi,cmd,4);     // escribo comando para escribir 
    
    uint8_t len[1] = {len_buffer};
    s_spi_write(mem->spi,len,1); // primer byte de la pagina, numero de bytes a escribir
    gpio_put(mem->cs_pin, 1);  //flanco ascendente

     sleep_us(100);
   
 
  
    cmd[3]= cmd[3] | (0x01 << 5); // quiero leer despues del primer bytes (contador)    
    // comandos
    gpio_put(mem->cs_pin, 0);  //flanco descendente

    s_spi_write(mem->spi,cmd,4);     // escribo comando para escribir 

   s_spi_write(mem->spi,buffer,len_buffer);    //buffer a escribir
  //CD DE BAJO A ALTO (FIN DE COMANDO)
    gpio_put(mem->cs_pin, 1);  //flanco ascendente

    // esperamos
    __at45_is_bussy(mem);


}









void s_AT45DB041E_read_counter(AT45DB041E_t* mem ,uint8_t* buffer)
{
// cmd escribir | 3bytes de direccion(  11 bits pagina (0 a 2048| 8 bytes posicion de la pagina | 5 dummy bits)
    
    uint32_t bytes_addres = 0;      
  

    uint8_t cmd[5];
    cmd[0] = CMD_FAST_READ;
    cmd[1] = (bytes_addres >> 24) & 0xff;
    cmd[2] = (bytes_addres >> 16) & 0xff;
    cmd[3] = (bytes_addres >> 8)  & 0xff;
    cmd[4] = 0;
    

    // CS DE ALTO A BAJO  (INICIO DE COMANDO)
     gpio_put(mem->cs_pin, 0);  //flanco descendente
    // comandos
    s_spi_write(mem->spi,cmd,5);
    // comandos

   
    s_spi_read(mem->spi,buffer,0,2);    //leo la primera posicion de la dirrecicon pedida

    gpio_put(mem->cs_pin, 1);  //flanco ascendente

    // esperamos
    __at45_is_bussy(mem);


}




void s_AT45DB041E_read_page(AT45DB041E_t* mem ,uint8_t* buffer,uint8_t len_buffer, uint16_t pg_num, uint8_t pos_page)
{
// cmd escribir | 3bytes de direccion(  11 bits pagina (0 a 2048| 8 bytes posicion de la pagina | 5 dummy bits)
    
    uint32_t bytes_addres = ( (uint32_t)(pg_num)) << 21  | ((uint32_t) (pos_page)) << 13 ;      
  

    uint8_t cmd[5];
    cmd[0] = CMD_FAST_READ;
    cmd[1] = (bytes_addres >> 24) & 0xff;
    cmd[2] = (bytes_addres >> 16) & 0xff;
    cmd[3] = (bytes_addres >> 8)  & 0xff;
    cmd[4] = 0;
    

    // CS DE ALTO A BAJO  (INICIO DE COMANDO)
     gpio_put(mem->cs_pin, 0);  //flanco descendente
    // comandos
    s_spi_write(mem->spi,cmd,5);
    // comandos

   //leo la primera posicion de la direccion pedida para saber cual es el tamanio del
            //leo buffer_len page
        
        s_spi_read(mem->spi,buffer,0,1);    //buffer a escribir

        gpio_put(mem->cs_pin, 1);  //flanco ascendente

        sleep_us(100);
        //leo la cantidad de bytes utilizadas en la pagina, o
    
        uint8_t true_len = (buffer[0]< len_buffer)?buffer[0]: len_buffer;

        cmd[3]= cmd[3] | (0x01 << 5); // quiero leer despues del primer bytes (contador)
        // CS DE ALTO A BAJO  (INICIO DE COMANDO)
        gpio_put(mem->cs_pin, 0);  //flanco descendente

        
        s_spi_write(mem->spi,cmd,5);
        
        
        s_spi_read(mem->spi,buffer,0,true_len);    //buffer a escribir
        //CD DE BAJO A ALTO (FIN DE COMANDO)

    
    
    gpio_put(mem->cs_pin, 1);  //flanco ascendente

    // esperamos
    __at45_is_bussy(mem);


}












/**
 Versiones simplificadas
**/

void s_AT45DB041E_write_data(AT45DB041E_t* mem ,uint8_t* data_buff,uint8_t len_buff, uint16_t pg_num )
{

    // cmd escribir | 3bytes de direccion(  11 bits pagina (0 a 2048| 8 bytes posicion de la pagina | 5 dummy bits)
   
     uint32_t bytes_addres = ( (uint32_t)(pg_num)) << 21  + ((uint32_t) (0)) << 13 ;     
    uint8_t cmd[4] ;    
      
    cmd[0] = WRITE_CMD;
    cmd[1] = (bytes_addres >> 24)  & 0xff;
    cmd[2] = (bytes_addres >> 16)  & 0xff;
    cmd[3] = (bytes_addres >> 8)   & 0xff;

    
 // CS DE ALTO A BAJO  (INICIO DE COMANDO)
     gpio_put(mem->cs_pin, 0);  //flanco descendente


    // comandos
    s_spi_write(mem->spi,cmd,4);     // escribo comando para escribir 
    

    // len_buff +

    
    s_spi_write(mem->spi,&len_buff,1); // primer byte de la pagina, numero de bytes a escribir
    s_spi_write(mem->spi,data_buff,len_buff);

    gpio_put(mem->cs_pin, 1);  //flanco ascendente

    sleep_us(10);
   
 
  
    gpio_put(mem->cs_pin, 1);  //flanco ascendente

    // esperamos
    __at45_is_bussy(mem);



}



void s_AT45DB041E_read_data(AT45DB041E_t* mem ,uint8_t* data_buff,uint8_t len_buff, uint16_t pg_num )
{

// cmd escribir | 3bytes de direccion(  11 bits pagina (0 a 2048| 8 bytes posicion de la pagina | 5 dummy bits)
    
    uint32_t bytes_addres = ( (uint32_t)(pg_num)) << 21  ;      
  
    uint8_t cmd[5];
    cmd[0] = CMD_FAST_READ;
    cmd[1] = (bytes_addres >> 24) & 0xff;
    cmd[2] = (bytes_addres >> 16) & 0xff;
    cmd[3] = (bytes_addres >> 8)  & 0xff;
    cmd[4] = 0;
    

    // CS DE ALTO A BAJO  (INICIO DE COMANDO)
     gpio_put(mem->cs_pin, 0);  //flanco descendente
    // comandos
    s_spi_write(mem->spi,cmd,5);
    // comandos

   //leo la primera posicion de la direccion pedida para saber cual es el tamanio del
            //leo buffer_len page
        
    s_spi_read(mem->spi,data_buff,0,len_buff);    //buffer a escribir

    gpio_put(mem->cs_pin, 1);  //flanco ascendente

    // esperamos
    __at45_is_bussy(mem);



}
