/**
 * @file _AT45DB041E
 * @brief Driver para manejo de memoria externa AT45DB041E
 * @author German Velardez
 * @date 25/09/2021
 * 
 * 
 * */



#include "simo/spi.h"














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

} _AT45DB041E_t;




/**
 * 
 * @note Los pines CSn no funcionan bien por eso se utiliza un CS_PIN en este driver
 * 
 *  pines utilizados por defecto en SPI0
 *    SPI0_CLK                    2
 *    SPI0_MISO                   3 //master input  TX
 *    SPI0_MOSI                   4 //master output RX
 *    SPI0_CSn                    5
 
 * 
 
 
 pines  utilizados por defecto en SPI1
 * 
 *   SPI1_CLK                    10
 *   SPI1_MOSI                   11  //master input  TX
 *   SPI1_MISO                   12  //master output RX
 *   SPI1_CSn                    13  
 *   
 * 
 * **/



/**
 * @brief   Crea  una memoria AT45DB041E asignando memoria dinamica. 
 * @note    Necesario borrar con  s_AT45DB041Edelete() al finalizar uso
 * @note    En caso de falla retorna NULL

 * @param   spi: interfaz SPI elegida
 * @param   cs_pin: pin utilizado como CHIPSELECT (CS_PIN)
 * @return  mem :instancia de memoria o NUll 
 * 
 * **/


_AT45DB041E_t*  s__AT45DB041E_create(  spi_t spi, uint8_t cs_pin);



/**
 * @brief   Borrar memoria AT45DB041E enviado comandos de secuencia de 4 bytes 

 * @param   mem : instancia a un objeto 
 * @return  None: 
 * 
 * **/

void  s__AT45DB041E_full_erase(_AT45DB041E_t* mem);




/**
 * @brief   Iniciar memoria AT45DB041E enviado comandos de secuencia de 4 bytes 

 * @param   mem : instancia a un objeto 
 * @return  None: 
 * 
 * **/

int8_t  s__AT45DB041E_start(_AT45DB041E_t* mem);




void s__AT45DB041E_save_data(_AT45DB041E_t* mem, uint8_t* buff, uint8_t buff_len,uint16_t page, uint8_t position_page );


void s__AT45DB041E_read_data(_AT45DB041E_t* mem, uint8_t* buff, uint8_t buff_len,uint16_t page, uint8_t position_page );


