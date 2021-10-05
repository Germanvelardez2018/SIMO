
#include <stdint.h>










void s_memory_init();


void s_memory_deinit();




uint16_t s_memory_get_data_counter();

void s_memory_set_data_counter();


// devuelve la posicion donde se almaceno el dato
uint16_t  s_memory_save_data(uint8_t* buff,uint8_t len_buff);




uint16_t s_memory_read_data(uint8_t buff,uint8_t len_max,uint16_t page);



