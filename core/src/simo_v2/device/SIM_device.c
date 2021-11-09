#include "device/SIM_device.h"
#include "simo/uart.h"
#include "comm/interface.h"
#include "comm/comm.h"
#include <string.h>
// private fucntions

#include "debug/debug_port.h"






static void _serial_write(char* buffer, uint16_t len)
{
    s_uart_write(SIM_UART,buffer,len);
}




static void _serial_read(char* buffer,uint16_t len, uint16_t timeout)
{
    s_uart_read(SIM_UART,buffer,len,timeout);
}






static void _serial_init(void* params)
{
    s_uart_init(SIM_UART,SIM_BAUDRATE);

}




comm_t* create_sim_device()
{
    interface_t * interface = interface_create(_serial_init,_serial_write,_serial_read);
    if (interface == NULL) return NULL ;


    comm_t* comm = comm_create(SIM_BUFFER_LEN,interface);

    if(comm == NULL)return NULL;

    return comm;



}

void init_sim_device(comm_t* comm)
{
    if(comm != NULL)
    {
        //init interface

        interface_init(comm->interface);

        // init debug
    }
}

void send_cmd(comm_t* comm,char* cmd)
{
    debug_printf(cmd);
    comm->interface->write(cmd, strlen(cmd));
}


void read_response(comm_t* comm,uint16_t timeout)
{
   
    comm->interface->read(comm->buffer,comm->buffer_len,1000);
     debug_printf("leimos puerto\n");
}

void send_and_check(comm_t* comm, char* cmd,uint16_t timeout)
{
    send_cmd(comm,cmd);
    debug_printf("leyendo respuesta\n");
    read_response(comm,timeout);
    

    
}