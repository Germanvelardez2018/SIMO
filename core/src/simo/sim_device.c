
#include "simo/sim_device.h"

#include "simo/uart.h"



// Definiciones estaticas del dispositivo sim
 

#define SIM_UART                     S_UART0      //puerto UART a utilizar
#define SIM_BAUDRATE                 115200
#define BUFFER_LEN_COMM              100
#define BUFFER_LEN_RESP              100
#define TIMEOUT_RX                   100



//funciones a utilizar



static device_t* _dev = NULL;

static QueueSetHandle_t* p_QUEUE_SIM_RESPONSES = NULL;



static void _IRQ_callback(void)
{
 
    //contador a o
    _dev->bresp_c = 0;
    while(s_uart_is_readable(SIM_UART,TIMEOUT_RX) && (_dev->bresp_c <= _dev->bresp_len))
    {
       
        _dev->b_resp[_dev->bresp_c] = s_uart_getc(SIM_UART);
        _dev->bresp_c ++;
    }
    _dev->b_resp[_dev->bresp_c] = 0; //caracter de finalizacion
    _dev->bresp_c = 0;
    //envio por queue
    xQueueSend((*p_QUEUE_SIM_RESPONSES),&(_dev->b_resp),0);
}


/**
 * @brief   Inicio el puerto a utilizar por el SIM device
 * 
 * @param void:  None
 * @return void: none
 * 
 * **/

static void _init_sim_device(void)
{
    // Inicio el puerto uart
    
    s_uart_init(SIM_UART,SIM_BAUDRATE);
    s_set_interrupcion_handler(SIM_UART,true,false,_IRQ_callback);

}






/**
 * @brief   envio los datos del buffer por salida uart
 * 
 * @param char* b: No se utilizar
 * @return  none
 * 
 * **/

static void _write_sim_device(char* b, uint32_t len)
{
    s_uart_write(SIM_UART,b,len);   
}

/**
 * @brief   envio los datos del buffer por salida uart
 * 
 * @param char* b: array de elementos a enviar
 * @param uint32_t len: Tamaño del array de datos
 * @return  none
 * 
 * **/

static void _read_sim_device(char* b, uint32_t len)
{
    // leo el puerto y almaceno en buffer
    s_uart_read(SIM_UART,b,(uint32_t)len,TIMEOUT_RX);
    
    
}





device_t* create_sim_device(QueueHandle_t* QUEUE_SIM_RESPONSES)
{  
    p_QUEUE_SIM_RESPONSES = QUEUE_SIM_RESPONSES;  

    _dev = create_device(BUFFER_LEN_COMM,BUFFER_LEN_RESP,_init_sim_device,_write_sim_device,_read_sim_device);
    
    return _dev;
}
