#ifndef I2C_COMMON_H_
#define I2C_COMMON_H_

// Timer_Profiler i2c_timeout;

static bool I2C_Wait_With_Timeout(void);
// void com_timeout_init(void);
uint32_t i2c_common(uint8_t slave_address,uint8_t *write_command,uint8_t write_cmd_len,uint8_t *read_command,uint8_t read_cmd_len);

#endif