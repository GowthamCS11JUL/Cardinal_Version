#include "headers.h"
#include "i2c.h"


void i2c_init()
{
   I2C_Controller_Initialize(&I2C_MCU, I2C1, 1);

}

