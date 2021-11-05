#include <stdint.h>

#define CONFIG_OFFSET      (0)         //Empezamos en sector 0
#define API_NAME_ADDRESS                    (CONFIG_OFFSET+ 1)    //Nombre de la aplicacion
#define URL_SERVER                          (CONFIG_OFFSET+ 2)   //IP del servidor MQTT 

#define DATA_OFFSET        (256)   //Empezamos en Sector 1




/**
 * CREDENCIALES
 * 
 * **/




/**
 * Formato de los datos
 * 
 *  Los datos se escriben en paginas individuales ( 256bytes)
 *  1 byte => tamano del dato almacenado (255 bytes maximo)
 *  2...256bytes => data en formato JSON
 * 
 * **/



void s_memory_store_init(void);


void s_memory_store_full_clear(void);

void s_memory_store_deinit(void);


uint16_t s_memory_store_add_data(char* data, uint8_t len_data);

uint16_t s_memory_store_read_data(char* buffer,uint8_t len_buff,uint16_t page_num);


uint16_t s_memory_store_add_page(char* data, uint8_t len_data, uint16_t page);




uint16_t get_counter_data();

void set_memory_counter_data(uint16_t counter);
