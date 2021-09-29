/**
 * @file memory.h
 * @brief Driver para manejo de memoria externa AT45DB041E
 * @author German Velardez
 * @date 25/09/2021
 * 
 * 
 * */



#include "simo/spi.h"






/**
 * de memoria principal a buffer
 * 53h buffer 1
 * 55h buffer 2
 * 
 * 
 * lectura
 *  D4h(fast) y D1h(low) para usar buffer  1  
 *  D6h (fast) y D3h(low) para usar buffer 2 
 *  escritura:
 *   84h buffer 1
 *   87h buffer 2
 *  mover de buffer a pagina principal (borrado de pagina previo incluido).Se copia todo el buffer
 *   83h buffer 1
 *   86 buffer 2
 * 
 * en caso de error de programacion o borrado, cambiara bit EPE del registro de estado
 * 
 * escribir buffer --> borra pagina---> pasar buffer a pagina. Se copia todo el buffer
 * 
 * 82h buffer1
 * 85h buffer2
 * 
 * Parecido  a el anterior pero sin borrado de pagina automatico. 
 * 88h buffer 1
 * 89h buffer 2
 * 
 * 
 * de buffer a memoria principal con borrado incluido. Pero solo bytes utiles del buffer, no todo el buffer
 * 82h buffer1
 * 85h buffer2
 * 
 * lo mismo que el anterior pero sin borrado intermedio
 * 02h buffer1
 * 
 * 
 * leer-modificar-escribir
 * 58h buffer 1
 * 59h buffer 2
 * 
 * borrado de pagina
 * 81h
 * borrado block
 * 50h
 * borrado sector (memoria principal tiene 9 sectores)
 * 7ch
 * 
 * borrado de todo el chip
 * secuencia de 4 bytes
 * C7h, 94h, 80h y 9Ah 
 * 
 * protector por software (sector)
 *   habilitar: 3Dh,2Ah, 7Fh y A9h 
 *   deshabilitar:  3Dh, 2Ah, 7Fh y 9Ah 
 * 
 * 
 * --registro de proteccion de sectores (un byte de 00h a FFh)
 * 
 * borrar registro de procteccion: (borrado full resultado FFh)
 * secuencia : 3Dh, 2Ah, 7Fh y CFh
 * 
 * 
 * programar el registro de proteccion
 * secuencia 3Dh, 2Ah, 7Fh y FCh + byte con los registro seteados
 * (utiliza buffer 1 para gestionar esto)
 * 
 * para leer el registro de proteccion: 
 * comandos 32h seguido de leectura de 3 bytes
 * @note 10k de ciclos de programacion/borrado del registro de proteccion
 * 
 * bloque de sector:
 * secuencia 3Dh, 2Ah, 7Fh 30h + 3 bytes de dirreccion
 * 
 * 
 * leer registro de estado
 * comandos D7h  devuelve 2 bytes (realmente devuelve 4. 2 de registro y repeticion del mismo)

--- apagado profundo (mantiene contenido buffers)

comandos:
deep sleep B9h   ((en modo deep sleep ignora todos los comandos menos el de reanudar))
reanudar   ABh 


 ---ultra apagado profundo

ultra deep sleep 79h
reanudar con un Csn en bajo durante un tiempo r


configuracion de pamaño de buffer y memoria. Por defecto 264

configurar en 256 secuencia:
    3Dh, 2Ah, 80h A6h

configurar en 264 secuencia:
    3Dh, 2Ah, 80h A7h

    para configurar esto usa un registro no volatil con 10k de ciclos borrado
 
 -------codigo de manofactura

  comandos 9FH 
  repuesta 4 bytes, 
  1 bytes manofacture id
  2 byte ID device
  3  byte 01h ---para verificar q termina secuencia
  y 1 bytes mas de shapa  00h (edidata)


  ----------reiniciio por software
  secuencia : F0h, 00h, 00h y 00h 
 
 * **/









// Codigos de operacion

 // to read out the status reg

#define M_STAT_BUSY_BIT      (1<<7) // bit that indicates device is busy or ready
#define M_STAT_READY_VALUE  (1<<7) /* value of busy bit to indicate device is ready */
#define M_STAT_BUSY_VALUE   (0<<7) /* value of busy bit to indicate device is busy */


// Register/Setting Commands
#define CMD_WPSEL                   (0x68) // to enter and enable individual block protect mode
#define CMD_DP                      (0x79) // enter ultra-deep power down mode
#define CMD_RDP                     (0xAB) // release from deep power down mode
#define CMD_SBL                     (0xC0) // to set burst length

// Read/Write Array Commands
#define CMD_READ                    (0x01) // low power continous read, max speed 15 MHz .Also use 0x03

#define CMD_FAST_READ               (0x0B) // max speed 85 MHz. Also its posible to use 0x1B

#define CMD_PP                      (0x02) /* to program the selected page, without built-in erase */
#define CMD_SSE                     (0x81) /* subsector erase: "256byte subsector" is called "page" on AT45 */
#define CMD_SE                      (0x7C) /* sector erase: "64K sector" is called "sector" on AT45 */
#define CMD_BE                      (0xC7) /* bulk erase: "bulk erase" is called "chip erase" on AT45 */
#define CMD_BE_ADDR                 (0x94809A) /* chip erase needs these three additional opcode bytes, we send it as "addr" */

// Read device ID
#define CMD_RDID                    (0x9F) /* read device ID */

// Disable lockdown sequence
#define CMDS_LOCKDOWN_DISABLE		0x34, 0x55, 0xAA, 0x40
#define LEN_LOCKDOWN_DISABLE		(4)

// Chip IDs
#define FLASH_SPI_MANUFACTORY_ID    (0x1F)
#define FLASH_SPI_MEMORY_TYPE_ID    (0x24)
#define FLASH_SPI_MEMORY_DENSITY_ID (0x00)

/* delay time for different operations. DELAY_MSEC * DELAY_LOOP_COUNT == total delay time */
#define PP_DELAY_MSEC               (1)
#define PP_DELAY_LOOP_COUNT         (5)  /* PageProgram 256B, Typ. 1.5ms, Max. 3ms */
#define BE_DELAY_MSEC               (500)
#define BE_DELAY_LOOP_COUNT         (40) /* ChipErase Typ. 6s, Max. 17s */
#define SE_DELAY_MSEC               (100)
#define SE_DELAY_LOOP_COUNT         (20) /* SectorErase64K Typ. 700ms, Max. 1100ms */
#define SSE_DELAY_MSEC              (10)
#define SSE_DELAY_LOOP_COUNT        (5)  /* SubSectorErase2K Typ. 30ms, Max. 35ms */

/* These values are based on the data sheet but a product
 * might want to use longer values based on how the chip
 * has been connected (e.g. if no active discharge, longer
 * power down delay might be necessary).
 */
#define FLASH_SPI_POWER_UP_MAX_DELAY_MSEC     (4)
#define FLASH_SPI_POWER_DOWN_MAX_DELAY_USEC   (1000)

// for the non-multiple power of two page size, configure nlflash_spi
// driver to use page+offset addressing
#define FLASH_SPI_USE_PAGE_OFFSET_ADDRESSING 1
#define FLASH_SPI_NUM_OFFSET_BITS 9 // 264 bytes needs 9 bits of offset














#define AT45DB041E_BUFFER    256  // tambien es posible 264




typedef struct 
{
     spi_t      spi;
     uint8_t    cs_pin;
     uint8_t*    buffer;
     uint8_t    counter_buff;

} AT45DB041E_t;



AT45DB041E_t*  s_AT45DB041E_create(  spi_t spi, uint8_t cs_pin);



void  s_AT45DB041E_full_erase(AT45DB041E_t* mem);
