#ifndef COMMAND_FUNCTION_H
#define COMMAND_FUNCTION_H

#include <stdint.h>

/* =======================
   Slave Addresses
======================= */
#define SLAVE_U6_0 0x4A
#define SLAVE_U6_1 0x49
#define SLAVE_U6_2 0x4B
#define SLAVE_U7_0 0x40
#define SLAVE_U7_1 0x41
#define SLAVE_U7_2 0x44
#define SLAVE_U16  0x3B
#define SLAVE_U17  0x3C

/* =======================
   IO Expander
======================= */
void io_expander_config(uint8_t slave_address);

/* =======================
   Opamp Control
======================= */
void opamp_en(uint8_t slave_address, uint8_t opamp_no);

/* =======================
   reset I2C
======================= */

 void reset_i2c(void);

/* =======================
   reset IO_Expander
======================= */
void reset_io_expander(void);

/* =======================
   Reset CURRENT MEASUREMNET 
======================= */

void reset_current_measurement(void);

/* =======================
   reset DAC
======================= */

void reset_dac(void);


/* =======================
   Power Control
======================= */
void ldo_power_off_site_0(void);
void ldo_power_on_site_0(uint8_t value);

void power_supply_3v3_1_site_0(void);
void power_supply_3v3_2_site_0(void);

void power_supply_2v7_1_site_0(void);
void power_supply_2v7_2_site_0(void);

/* =======================
   Measurement Functions
======================= */
void battery_voltage_check_site_0(void);
void switch_voltage_default_site_0(void);

void led_status_voltage_0_0_site_0(void);
void led_status_voltage_0_1_site_0(void);
void led_status_voltage_1_0_site_0(void);
void led_status_voltage_2_0_site_0(void);

void led_status_voltage_1_site_0(void);
void led_status_voltage_2_site_0(void);
void led_status_voltage_3_site_0(void);

void switch_voltage_press_site_0(void);

/* =======================
   Voltage / Current IC
======================= */
void voltage_current_measurement_reset_site_0(void);
// void voltage_current_measurement_site_0(void);
void voltage_current_measurement_site_off(void);
void voltage_current_measurement_site_on(void);
void voltage_current_measurement_reset_site_1(void);
void voltage_current_measurement_reset_site_2(void);
void voltage_current_measurement_site_on_1(void);
void turn_off_all(void);
void power_supply_3v3_2_site_1(void);
void ldo_power_on_site_1(uint8_t value);
void ldo_power_off_site_1(void);
void ramp_supply_2v7_1_site_0(void);

//LED
void led_init(void);

void led_turn_on(void);

void led_turn_off(void);

void reset_mcu(void);

#endif /* COMMAND_FUNCTION_H */