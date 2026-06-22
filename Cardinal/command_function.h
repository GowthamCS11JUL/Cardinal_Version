
#ifndef COMMAND_FUNCTION_H
#define COMMAND_FUNCTION_H

#include "headers.h"
#include <stdint.h>

/* =======================
   Slave Addresses
======================= */
#define DAC_IC 0x4A                  /**< I2C Address for the DAC IC */
#define CURRENT_MEASUREMENT_IC 0x40  /**< I2C Address for the Current Measurement IC */
#define IO_EXPANDER_IC  0x3B         /**< I2C Address for the IO Expander IC */


/**
 * @brief Configures the IO expander direction and registers.
 * @param slave_address The I2C address of the target IO expander.
 */
void io_expander_config(uint8_t slave_address);

/**
 * @brief Enables a specific operational amplifier via the IO expander.
 * @param slave_address The I2C address of the IO expander.
 * @param opamp_no The channel index of the opamp to enable (0 to 2).
 */
void opamp_en(uint8_t slave_address, uint8_t opamp_no);

/**
 * @brief Resets all I2C blocks including current measurement and IO expanders.
 */
void reset_i2c(void);

/**
 * @brief Resets the IO expander registers to default state.
 */
void reset_io_expander(void);

/**
 * @brief Resets the current measurement IC hardware/registers.
 */
void reset_current_measurement(void);

/**
 * @brief Resets the DAC IC to default configuration.
 */
void reset_dac(void);

/**
 * @brief Turns off all power rails, resets I2C, and indicates status via LED.
 */
void turn_off_all(void);

/**
 * @brief Disables the power supply rail on Site 0 via IO Expander.
 */
void ldo_power_off_site_0(void);

/**
 * @brief Enables the power supply rail on Site 0 with a given value mask.
 * @param value The configuration configuration bitmask to apply.
 */
void ldo_power_on_site_0(uint8_t value);

/**
 * @brief Activates the 3.3V power supply rail (Option 1) on Site 0 using the DAC.
 */
void power_supply_3v3_1_site_0(void);

/**
 * @brief Activates the 3.3V power supply rail (Option 2) on Site 0 using the LDO,Across TP1 and TP2 .
 */
void power_supply_3v3_2_site_0(void);

/**
 * @brief Activates the 2.7V power supply rail (Option 1) on Site 0 using the DAC,Across TP1 and TP2 .
 */
void power_supply_2v7_1_site_0(void);

/**
 * @brief Activates the 2.7V power supply rail (Option 2) on Site 0 using the LDO,Across TP1 and TP2 .
 */
void power_supply_2v7_2_site_0(void);

/**
 * @brief Checks and reads the battery voltage level on Site 0,Across TP1 and TP2 .
 */
void battery_voltage_check_site_0(void);

/**
 * @brief Reads the default floating voltage state of the switch on Site 0,Across TP1 and TP2 .
 */
void switch_voltage_default_site_0(void);

/**
 * @brief Measures the voltage for LED status 0_0 on Site 0,Across TP9 and TP2 .
 */
void led_status_voltage_0_0_site_0(void);

/**
 * @brief Measures the voltage for LED status 0_1 on Site 0,,Across TP8 and TP2.
 */
void led_status_voltage_0_1_site_0(void);

/**
 * @brief Measures the voltage for LED status 1_0 on Site 0,Across TP7 and TP2.
 */
void led_status_voltage_1_0_site_0(void);

/**
 * @brief Measures the voltage for LED status 2_0 on Site 0,Across TP11 and TP2.
 */
void led_status_voltage_2_0_site_0(void);

/**
 * @brief Measures the voltage for LED channel 1 on Site 0,Across TP11 and TP3.
 */
void led_status_voltage_1_site_0(void);

/**
 * @brief Measures the voltage for LED channel 2 on Site 0,Across TP11 and TP4.
 */
void led_status_voltage_2_site_0(void);

/**
 * @brief Measures the voltage for LED channel 3 on Site 0 Across TP11 and TP5.
 */
void led_status_voltage_3_site_0(void);

/**
 * @brief Activates the switch, waits for stabilization, and captures the pressed voltage,,Across TP6 and TP2 .
 */
void switch_voltage_press_site_0(void);

/**
 * @brief Resets the voltage and current measurement IC settings for Site 0.
 */
void voltage_current_measurement_reset_site_0(void);

/**
 * @brief Triggers and reads the active current consumption value from the monitor IC.
 */
void voltage_current_measurement_site_on(void);

void vbus_measurement(void);

/**
 * @brief Initializes the status indicator LED GPIO pin.
 */
void led_init(void);

/**
 * @brief Turns on the on-board status indicator LED.
 */
void led_turn_on(void);

/**
 * @brief Turns off the on-board status indicator LED.
 */
void led_turn_off(void);

/**
 * @brief Forces a system Power-On Reset (POR) on the MCU.
 */
void reset_mcu(void);

/**
 * @brief Decodes a series of standard text characters into an unsigned 32-bit mathematical value.
 * @param str Reference pointer handling input character sequences.
 * @return Decoded decimal values. Returns `0` if an invalid char range is detected.
 */
uint32_t string_to_uint(char *str);

/* ==========================================================================
   Dynamic Command Processing Handlers
   ========================================================================== */

/**
 * @brief Parses incoming text strings to change reference outputs on the flying DAC power link.
 * @note Processes input variants using token patterns: `POWER_SET_<millivolts>`.
 * @param usb_data Data structure hosting structural UART configurations and tracking frames.
 * @param cmd Decoded framework containing isolated command tokens.
 */
void power_command_handler(UART_DATA *usb_data,Parsed_Command_t *cmd) ;

/**
 * @brief Sets correction parameters and alters internal calibration offset variables.
 * @note Processes input variants using token patterns: `ADC_<offset>`.
 * @param usb_data Data structure hosting structural UART configurations and tracking frames.
 * @param cmd Decoded framework containing isolated command tokens.
 */
void calibration_command_handler(UART_DATA *usb_data, Parsed_Command_t *cmd);


#endif /* COMMAND_FUNCTION_H */