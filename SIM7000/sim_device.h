/**
 *  Archivo para dispositivos SIM
 * 
 * **/

#include <stdint.h>
#include <stdio.h>
#define BUFFER_RESPONSE    100
#define NAME_LEN           20
#define MAX_BUFFER_SIZE    200

typedef enum {
    DEVICE_NOT_STARTED,
    DEVICE_STARTED
}device_status_t;


typedef struct {
    char* p_BUFFER_RESPONSES;
    char* p_BUFFER_COMMANDS;
    char  device_name[NAME_LEN];
    uint8_t buffer_size_command;
    uint8_t buffer_size_response;
    int8_t status;

}sim_device_t;









sim_device_t *init_sim_device(uint8_t buffer_size_command, uint8_t buffer_size_response, const char *device_name);

char* get_buffer_response(sim_device_t* device);

uint8_t get_buffer_size_commands(sim_device_t* device);

uint8_t get_buffer_size_response(sim_device_t *device);

char* get_name_device(sim_device_t* device);



int8_t set_command(sim_device_t* device, const char* command);

int8_t send_command(sim_device_t* device);


