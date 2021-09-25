#include "simo/i2c.h"

#include "hardware/i2c.h"
#include "hardware/gpio.h"


#define N_I2C 2

/*!  I2C0 */

#define I2C0_SDA 4 // posible conflicto con UART1_TX 4
#define I2C0_SDA_OPTIONAL 20
#define I2C0_SCL 5 // posible conflicto con UART1_RX 5
#define I2C0_SCL_OPTIONAL 21

/*!  I2C1 */

#define I2C1_SDA 2 // conflicto con UART1_TX
#define I2C1_SDA_OPTIONAL 10
#define I2C1_SCL 3 // conflicto con UART1_RX
#define I2C1_SCL_OPTIONAL 11

/**
 * @brief   Configuro los pines correspondiente al i2c
 * 

 * @param   i2c : i2c a asignar pines
 * @return  NONE : NONE
 * 
 * **/

static void _get_pins(i2c_t i2c)
{
  uint8_t pin_sda;
  uint8_t pin_scl;

  switch (i2c)
  {
  case S_I2C0:
    pin_sda = I2C0_SDA;
    pin_scl = I2C0_SCL;
    break;
  case S_I2C1:
    pin_sda = I2C1_SDA;
    pin_scl = I2C1_SCL;
  default:
    pin_sda = I2C0_SDA;
    pin_scl = I2C0_SCL;
    break;
    gpio_set_function(pin_sda, GPIO_FUNC_I2C);
    gpio_set_function(pin_scl, GPIO_FUNC_I2C);
    gpio_pull_up(pin_sda);
    gpio_pull_up(pin_scl);
  }
}

/**
 *  @brief inicia el puerto i2c
 *  @param i2c: interfaz i2c a utilizar
 *  @param baudrate: Baudrate en Hz (e.g 100kHz is 100000)
 * @return None:
 * 
 * **/

static i2c_inst_t *_get_i2c(i2c_t i2c)
{

  i2c_inst_t* _i2c;

  switch (i2c)
  {
  case S_I2C0:
    _i2c = i2c0;
    
    break;

  case S_I2C1:
    _i2c = i2c1;
    break;

  default:
    // Por default i2c0
    _i2c = i2c0;
    break;
  }

  return _i2c;
}



void s_i2c_init(i2c_t i2c, uint32_t baudrate)
{

  i2c_inst_t *_i2c = _get_i2c(i2c);
  // inicio el modulo i2c
  i2c_init(_i2c, baudrate);
  // configuro los pines correspondientes (uso i2c_t como parametro)
  _get_pins(i2c);
}



void s_i2c_deinit(i2c_t i2c)
{
  i2c_inst_t *_i2c = _get_i2c(i2c);
  i2c_deinit(_i2c);
  // se deben reiniciar los pines
}



void s_i2c_set_baudrate(i2c_t i2c, uint32_t baudrate)
{
  i2c_inst_t *_i2c = _get_i2c(i2c);
  i2c_set_baudrate(_i2c, baudrate);
}



void s_i2c_set_mode(i2c_t i2c, bool slave_mode, uint8_t slave_address)
{

  i2c_inst_t *_i2c = _get_i2c(i2c);
  i2c_set_slave_mode(_i2c, slave_mode, slave_address);
}


void s_i2c_write(i2c_t i2c, uint8_t slave_address,  uint8_t *data, uint32_t data_len, bool nostop)
{
  i2c_inst_t *_i2c = _get_i2c(i2c);

  i2c_write_blocking(_i2c, slave_address, data, data_len, nostop);
}

void s_i2c_read(i2c_t i2c, uint8_t slave_address,  uint8_t *data, uint32_t data_len, bool nostop)
{

  i2c_inst_t *_i2c = _get_i2c(i2c);

  i2c_read_blocking(_i2c, slave_address, data, data_len, nostop);
}