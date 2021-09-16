#include "sim_device.h"

 sim_device_t* device;


int main(void)
{
    printf("iniciamos el programa\r\n");
     
   
    device = init_sim_device(100,20,"SIM7000");
    printf("el device tiene buffer size:%d\r\n",get_buffer_size_commands(device));
    printf(" el device se llama %s\r\n",get_name_device(device));
  
    if(device == NULL)
    {
        printf(" devices es null\r\n");
    }
   else
   {
        printf("el dispositivo %s se inicio correstamente\r\n",get_name_device(device));
        set_command(device, "comandos de salida");
        send_command(device);
   }


    return 0;
}