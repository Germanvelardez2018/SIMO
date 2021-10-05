#include "simo/memory/AT45DB041E.h"
#include "simo/memory/_AT45DB041E.h"  // nueva version
#include "simo/memory/memory_store.h"
#include <stdlib.h>
#include "pico/time.h"



#define MEMORY_APP_SPI                S_SPI1

#define MEMORY_APP_BAUDRATE_FAST       (50*100000) //50 MHz
#define MEMORY_APP_BAUDRATE_LOW        (10*100000) //10 MHz
#define CS_MEMORY                       9


/**
 * Variables privadas
 * **/

static _AT45DB041E_t* _memory_app ;

static uint16_t _get_counter_data()
{



     //preguntar por el contador de datos
    uint8_t counter[2] = {0};
    s__AT45DB041E_read_data(_memory_app,counter,2,0,0);
//    s_AT45DB041E_read_data(_memory_app,counter,2, 0 );

   uint16_t c = (uint16_t)(counter[1]<<8) + (uint16_t)(counter[0]) ;  // primero en llegar es la parte alta
   // uint16_t counter_data = (uint16_t)((uint16_t)(counter[1] << 8)+ (uint16_t)counter[0]);
    return c;
}

static void _set_memory_counter_data(uint16_t counter)
{
 //   uint8_t _counter[2];
  
 //   _counter[0]= (counter >> 8)& 0xff;
  //  _counter[1]= (counter >> 16)  & 0xff;
     s__AT45DB041E_save_data(_memory_app,(uint8_t*)&counter,2,0,0);
    // s_AT45DB041E_write_data(_memory_app ,(uint8_t* )_counter,2, 0 );

    
}


void s_memory_store_init(void)
{
    _memory_app = s__AT45DB041E_create(MEMORY_APP_SPI,CS_MEMORY);
    //inicio la memoria flash
    s__AT45DB041E_start(_memory_app);

  //  s__AT45DB041E_full_erase(_memory_app); // BORRAMOS MEMORIA 
    sleep_us(100);
    _set_memory_counter_data(0); // por unica vez
}


void s_memory_store_deinit(void)
{

}


uint16_t s_memory_store_add_data(char* data, uint8_t len_data)
{
    //leer el contador de datos
    uint16_t counter_data = _get_counter_data();



    uint16_t page = counter_data + 256;

    // primero escribo la cantidad de bytes del buffer en el primer byte . SIrve para poder leerlo luego
    s__AT45DB041E_save_data(_memory_app,(uint8_t*)&len_data,1,page,0);


    // luego escribo los datos
    s__AT45DB041E_save_data(_memory_app,(uint8_t*)data,len_data,page,1);  // en la siguiente posicion

    


   


    //modifico el counter data
    uint16_t _counter_data = counter_data + 1;
    _set_memory_counter_data(_counter_data);

    return _counter_data;
}

uint16_t s_memory_store_read_data(char* buffer,uint8_t len_buff,uint16_t page_num)
{
    uint8_t len[1];
    //leo el tamanio del buffer que necesito
    s__AT45DB041E_read_data(_memory_app, len,1 ,255+page_num ,0 );  // leo el tamaño del buffer a utilizar

   
    sleep_us(100);
    s__AT45DB041E_read_data(_memory_app, buffer,(uint8_t)len[1] ,255+page_num ,1 ); // empiezo a leer desde la posicion siguiente


   
    return len[1];

  
}