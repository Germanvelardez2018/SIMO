
#include "simo/memory/_AT45DB041E.h"  // nueva version
#include "simo/memory/memory_store.h"
#include <stdlib.h>
#include "pico/time.h"


#define COUNTER_DATA_ADDRESS            (10)
#define MEMORY_APP_SPI                S_SPI1

#define MEMORY_APP_BAUDRATE_FAST       (50*100000) //50 MHz
#define MEMORY_APP_BAUDRATE_LOW        (10*100000) //10 MHz
#define CS_MEMORY                       9


/**
 * Variables privadas
 * **/

static _AT45DB041E_t* _memory_app ;

 uint16_t get_counter_data()
{



    
    uint8_t counter[2] = {0};
    s__AT45DB041E_read_data(_memory_app,counter,2,COUNTER_DATA_ADDRESS,0);


   uint16_t c = (uint16_t)(counter[1]<<8) + (uint16_t)(counter[0]) ;  // primero en llegar es la parte alta
   // uint16_t counter_data = (uint16_t)((uint16_t)(counter[1] << 8)+ (uint16_t)counter[0]);
    return c;
}

 void set_memory_counter_data(uint16_t counter)
{

     s__AT45DB041E_save_data(_memory_app,(uint8_t*)&counter,2,COUNTER_DATA_ADDRESS,0);
  

    
}


void s_memory_store_full_clear(void)
{
     s__AT45DB041E_full_erase(_memory_app); // BORRAMOS MEMORIA 
   
}


void s_memory_store_init(void)
{
    _memory_app = s__AT45DB041E_create(MEMORY_APP_SPI,CS_MEMORY);
    //inicio la memoria flash
    s__AT45DB041E_start(_memory_app);

  //s__AT45DB041E_full_erase(_memory_app); // BORRAMOS MEMORIA 
    sleep_us(1000);
  //  set_memory_counter_data(0); // por unica vez
}


void s_memory_store_deinit(void)
{

}





//funciona correctamente

uint16_t s_memory_store_add_page(char* data, uint8_t len_data, uint16_t page)
{
    uint16_t _page = page + DATA_OFFSET;

    // primero escribo la cantidad de bytes del buffer en el primer byte . SIrve para poder leerlo luego
    s__AT45DB041E_save_data(_memory_app,(uint8_t*)&len_data,1,_page,0);

    sleep_us(10);
    // luego escribo los datos
    s__AT45DB041E_save_data(_memory_app,(uint8_t*)data,len_data,_page,1);  // en la siguiente posicion
    //modifico el counter data
   
    return page;
}


//funciona mal
uint16_t s_memory_store_add_data(char* data, uint8_t len_data)
{
    //leer el contador de datos
    uint16_t counter_data = get_counter_data();

    sleep_us(10);

    uint16_t page = counter_data +  DATA_OFFSET;

    // primero escribo la cantidad de bytes del buffer en el primer byte . SIrve para poder leerlo luego
    s__AT45DB041E_save_data(_memory_app,(uint8_t*)&len_data,1,page,0);

    sleep_us(10);
    // luego escribo los datos
    s__AT45DB041E_save_data(_memory_app,(uint8_t*)data,len_data,page,1);  // en la siguiente posicion
    //modifico el counter data
    uint16_t _counter_data = counter_data + 1;
    sleep_us(10);
    set_memory_counter_data(_counter_data);

    return counter_data;
}



uint16_t s_memory_store_read_data(char* buffer,uint8_t len_buff,uint16_t page_num)
{
    uint8_t len[1];

    uint16_t pg = page_num + (uint) DATA_OFFSET;
    //leo el tamanio del buffer que necesito
    s__AT45DB041E_read_data(_memory_app, len,1 ,pg ,0 );  // leo el tamaño del buffer a utilizar

   
    sleep_us(100);
    s__AT45DB041E_read_data(_memory_app, buffer,(uint8_t)len[1] ,pg ,1 ); // empiezo a leer desde la posicion siguiente


   
    return len[1];

  
}



