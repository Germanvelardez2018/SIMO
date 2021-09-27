#include "simo/AT45DB041E/memory.h"
#include "hardware/gpio.h"




/**
 * @note 
 * 1) Los datos, direcicon y comandos en i/o son siempre leidos y escritos en el flanco ascendente de clock 
 * 2) La memoria del dispositivo se divide en 3 niveles: sectores, bloques y paginas. Un sector contiene tamaño variables de bloques. 
 *    Un bloque tiene 8 paginas. Cada pagina 256/264 bytes
 * 3) El dispositivo se maneja mediante instrucciones
 * A)Secuencia de una instruccion
 * 
 *     A.1) cs de alto a bajo
 *     A.2) codigo de operacion de 8 bites
 *     A.3) La direccion de la memoria deseada o el buffer a utilizar
 *     La transferencia de datos se realizar con MSB primero
 * 
 *      |codigo operacion | direccion mem o buffer |
 * **/






// Para iniciar una operacion se requiere una transicion de ALTO a BAJO


static void _cspin_set_high()
{

}

// Para finalizar una operacion se requiere una transicion de BAJO a Alto

static void _cspin_set_low()
{

}







void s_init_memory()
{

    
}