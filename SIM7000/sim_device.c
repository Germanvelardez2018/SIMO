#include "sim_device.h"

#include <string.h>
#include <stdlib.h>

#define _NO_NAME_DEVICE_ "SIN NOMBRE"

/**
 * @brief   Iniciamos un dispositivo sim_device
 * 
 * @param   char* buffer_size
 * @param   const char* device_name: Nombre del dispositivo
 * @return  int8_t _device_status:
 *              -1 fallo el inicio del dispositivo
 *               1 inicio exitoso
 * 
 * **/

sim_device_t *init_sim_device(uint8_t buffer_size_command, uint8_t buffer_size_response, const char *device_name)
{
    //asignamos memoria al sim_device
    sim_device_t *device = (sim_device_t *)malloc(sizeof(sim_device_t));
    if (device == NULL)
        return NULL;

    //empezamos las asignaciones
    device->buffer_size_command = buffer_size_command;
    device->buffer_size_response = buffer_size_response;
    device->p_BUFFER_COMMANDS = (char *)malloc(sizeof(char) * buffer_size_command);
    device->p_BUFFER_RESPONSES = (char *)malloc(sizeof(char) * buffer_size_response);

    if ((device->p_BUFFER_COMMANDS == NULL) || (device->p_BUFFER_RESPONSES == NULL))
    {
        device->status = -1;
        return NULL;
    }

    if (strlen(device_name) < NAME_LEN)
    {
        strcpy(device->device_name, device_name);
    }
    else
    {
        strcpy(device->device_name, _NO_NAME_DEVICE_);
    }
    printf("EL NOMBRE DEL DISPOSITIVO ES : %s\r\n", device->device_name);
    device->status = 1;
    return device; //retorno exitoso
}

char *get_buffer_response(sim_device_t *device)
{
    if (device != NULL)
        return device->p_BUFFER_RESPONSES; //retorno puntero a buffer del dispositivo
    return NULL;
}

uint8_t get_buffer_size_commands(sim_device_t *device)
{

    if (device != NULL)
        return device->buffer_size_command; //retorno el tamaño del dispositivo
    return 0;
}

uint8_t get_buffer_size_response(sim_device_t *device)
{

    if (device != NULL)
        return device->buffer_size_response; //retorno el tamaño del dispositivo
    return 0;
}

char *get_name_device(sim_device_t *device)
{
    if (device != NULL)
        return device->device_name;
    return "DEVICE NO STARTED";
}

int8_t set_command(sim_device_t *device, const char *command)
{
    
    if (device == NULL)
        return -1;
    if (strlen(command) >= (device->buffer_size_command))
        return -1;
 

    sprintf(device->p_BUFFER_COMMANDS, "<CR><LF>%s<CR><LF>", command);
}

int8_t send_command(sim_device_t *device)
{
    //llamaria a la funcion que envie el buffer
    printf("[send_command()]%s\r\n", device->p_BUFFER_COMMANDS);
}