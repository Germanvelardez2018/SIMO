

#include "simo/SIM/communication.h"
#include "simo/SIM/sim_device.h"
#include "simo/uart/uart.h"
#include <string.h>

//interfaz por uart
#define _BUFF_COMMANDS 100
#define _BUFF_RESPONSE 20
#define _DEVICE_NAME_ "SIM7000G"
#define _QUEUE_SIZE    sizeof(char*)
#define _QUEUE_N_ELEMENTS 4
#define _TIME_OUT_RESPONSE 100
#define _TASK_DELAY 500

static QueueHandle_t _queue_response;
static sim_device_t *_device;

static simo_uart_instance _interface =
    {.uart = uart0,
     .rx_pin = 1,
     .tx_pin = 0,
     .baudrate = 115200,
     .irq_rx = false,
     .irq_tx = false};

/**
 * @brief   Rutina de interrupcion 
 * 
 * @param   None  
 * @return  None
 * 
 * **/

static void _IRQ_RX_COMMUNICATION(void)
{
   
    if(_device != NULL)
    {
        _device->b_r_counter = 0;
        while (uart_is_readable_within_us(_interface.uart, _TIME_OUT_RESPONSE) && ((_device->b_r_counter) <= (_device->b_size_responses)))
        {
            _device->p_B_RESPONSES[_device->b_r_counter] = uart_getc(_interface.uart);
            _device->b_r_counter++;
        }
        _device->p_B_RESPONSES[_device->b_r_counter] = 0;

      
        _device->b_r_counter = 0;
        char* b = &(_device->p_B_RESPONSES[0]);
        xQueueSend(_queue_response, &(_device->p_B_RESPONSES), 0);
    }

 
}

static void task_comunication(void *params)
{
    simo_uart_write(&_interface, "INICIO TASK COMM \r\n", strlen("INICIO TASK COMM \r\n"));
    _queue_response = xQueueCreate(_QUEUE_N_ELEMENTS, _QUEUE_SIZE); //Inicializo la queue que recibira los buffer proveniente de rx irq

    char* buffer_in;

    while (1)
    {
        if (xQueueReceive(_queue_response, &buffer_in, portMAX_DELAY) == pdPASS)
        {
            simo_uart_write(&_interface, "Commm:", strlen("Commm:"));
            simo_uart_write(&_interface, (buffer_in), strlen(buffer_in));
            simo_uart_write(&_interface, "\n", 1);
        }
        
    }
}

void simo_communication_init()
{

     _device = init_sim_device(_BUFF_COMMANDS,_BUFF_RESPONSE,_DEVICE_NAME_);

    _queue_response = xQueueCreate(_QUEUE_N_ELEMENTS, sizeof(char*));

    simo_uart_init(&_interface);
    simo_uart_write(&_interface,get_name_device(_device),strlen(get_name_device(_device)));

    xTaskCreate(task_comunication, "task comm", 5 * 1024, NULL, tskIDLE_PRIORITY + 2, NULL);
    simo_set_rx_interrupcion_handler(&(_interface),_IRQ_RX_COMMUNICATION);
}
