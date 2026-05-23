
#include "command_function.h"
#include "headers.h"
#include "i2c_common.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "variables.h"

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

static uint32_t return_data = 0;


//Led Indicator

void led_init(void)
{
 DL_GPIO_initDigitalOutput(LED_LED_PIN_IOMUX);
 DL_GPIO_enableOutput(LED_PORT, LED_LED_PIN_PIN);
}
void led_turn_on(void)
{
DL_GPIO_setPins(LED_PORT, LED_LED_PIN_PIN);
}
void led_turn_off(void)
{
DL_GPIO_clearPins(LED_PORT, LED_LED_PIN_PIN);
}

/* =======================
   HELPER FUNCTIONS
======================= */

//  Manual HEX conversion 
static void send_u32_hex(uint32_t value)
{
    const char hex[] = "0123456789ABCDEF";
    char buffer[8];

    for (int i = 0; i < 8; i++)
    {
        buffer[7 - i] = hex[value & 0xF];
        value >>= 4;
    }

    memcpy(executing_command->response, buffer, 8);
    executing_command->resp_len = 8;
}

// 🔴 FAIL response
static void send_fail(void)
{
    memcpy(executing_command->response, "FAIL", 4);
    executing_command->resp_len = 4;
}

/* =======================
   DATA TRANSMIT
======================= */

static void data_transmit(uint32_t status)
{
    send_u32_hex(status);
}

/* =======================
   RESET FUNCTIONS
======================= */

void reset_i2c(void)
{
    reset_current_measurement();
    reset_io_expander();
    data_transmit(0X00);
}

void reset_io_expander(void)
{
    uint8_t write_cmd[2] = {0x01, 0x00};
    uint8_t read_cmd[1]  = {0x01};

    io_expander_config(SLAVE_U16);
    i2c_common(SLAVE_U16, write_cmd, 2, read_cmd, 1);

    // io_expander_config(SLAVE_U17);
    // i2c_common(SLAVE_U17, write_cmd, 2, read_cmd, 1);
}

void reset_current_measurement(void)
{
    voltage_current_measurement_reset_site_0();
    // voltage_current_measurement_reset_site_1();
    // voltage_current_measurement_reset_site_2();
}

void reset_dac(void)
{
    uint8_t write_cmd[3] = {0x08, 0x00, 0x10};
    uint8_t read_cmd[1]  = {0x08};
    i2c_common(SLAVE_U6_0, write_cmd, 3, read_cmd, 2);
    // i2c_common(SLAVE_U6_1, write_cmd, 3, read_cmd, 2);
    // i2c_common(SLAVE_U6_2, write_cmd, 3, read_cmd, 2);
}

/* =======================
   MUX + ADC
======================= */

static void read_mux_adc(uint8_t mux1, uint8_t mux2, uint8_t mux3, uint8_t mux4,
                         uint8_t mux_on) {
  uint32_t raw = 0;
  uint32_t corrected_adc = 0;
  if (mux_on & 0x01) {
    mux_select(MUX_ID_1, mux1);
    mux_select(MUX_ID_2, mux2);

    delay_cycles(64);

    ADC122S625_Read(&spi_adc, 0); // dummy
    delay_cycles(64);

    raw = ADC122S625_Read(&spi_adc, 0);

    // float batt_v = (raw * 5.0f) / 2048.0f;

    // float dmm_v = (batt_v + 0.014425f) / 1.003024f;

    // corrected_adc = (uint32_t)((dmm_v * 2048.0f) / 5.0f);

    // send_u32_hex(corrected_adc);
    send_u32_hex(raw);
    return;
  }

  if (mux_on & 0x02) {
    mux_select(MUX_ID_3, mux3);
    mux_select(MUX_ID_4, mux4);

    delay_cycles(64);

    ADC122S625_Read(&spi_adc, 1); // dummy
    delay_cycles(64);

    raw = ADC122S625_Read(&spi_adc, 1);
    // float batt_v = (raw * 5.0f) / 2048.0f;

    // float dmm_v = (batt_v + 0.014425f) / 1.003024f;

    // corrected_adc = (uint32_t)((dmm_v * 2048.0f) / 5.0f);

    // send_u32_hex(corrected_adc);
    send_u32_hex(raw);
    return;
  }

  send_fail();
}

/* =======================
   IO EXPANDER
======================= */

void io_expander_config(uint8_t slave_address)
{
    uint8_t write_cmd[2] = {0x03, 0x00};
    uint8_t read_cmd[1]  = {0x00};

    i2c_common(slave_address, write_cmd, 2, read_cmd, 1);
}

/* =======================
   OPAMP
======================= */

void opamp_en(uint8_t slave_address, uint8_t opamp_no)
{
    if (opamp_no >= 3)
        return;

    uint8_t opamp_select = 0x10 << opamp_no;

    io_expander_config(slave_address);

    uint8_t write_cmd[2] = {0x01, 0x10};
    uint8_t read_cmd[1]  = {0x00};

    i2c_common(slave_address, write_cmd, 2, read_cmd, 1);
}

/* =======================
   POWER CONTROL
======================= */

void ldo_power_off_site_0(void)
{
    uint8_t write_cmd[2] = {0x01, 0x00};
    uint8_t read_cmd[1]  = {0x01};

    io_expander_config(SLAVE_U16);
    i2c_common(SLAVE_U16, write_cmd, 2, read_cmd, 1);
}

void ldo_power_on_site_0(uint8_t value)
{
    value |= 0x04;

    uint8_t write_cmd[2] = {0x01, value};
    uint8_t read_cmd[1]  = {0x01};

    io_expander_config(SLAVE_U16);

    return_data = i2c_common(SLAVE_U16, write_cmd, 2, read_cmd, 1);
    data_transmit(return_data);
}

void power_supply_3v3_1_site_0(void)
{
    led_turn_on();
    ldo_power_off_site_0();

    uint8_t write_cmd[3] = {0x08, 0xA8, 0xF5};
    uint8_t read_cmd[1]  = {0x08};

    return_data = i2c_common(SLAVE_U6_0, write_cmd, 3, read_cmd, 2);

    opamp_en(SLAVE_U16, 0);

    data_transmit(return_data);
    led_turn_off();
}


void power_supply_3v3_2_site_0(void)
{
    led_turn_on();
    ldo_power_off_site_0();

    uint8_t write_cmd[2] = {0x01, 0x08};
    uint8_t read_cmd[1]  = {0x01};

    io_expander_config(SLAVE_U16);
    i2c_common(SLAVE_U16, write_cmd, 2, read_cmd, 1);

    ldo_power_on_site_0(write_cmd[1]);
    led_turn_off();
}

void power_supply_2v7_1_site_0(void)
{
    led_turn_on();
    // ldo_power_off_site_0();

    uint8_t write_cmd[3] = {0x08, 0x8A, 0x3D};
    uint8_t read_cmd[1]  = {0x08};

    return_data = i2c_common(SLAVE_U6_0, write_cmd, 3, read_cmd, 2);

    opamp_en(SLAVE_U16, 0);

    data_transmit(return_data);
    led_turn_off();
}

void power_supply_2v7_2_site_0(void)
{
    // ldo_power_off_site_0();
    led_turn_on();
    uint8_t write_cmd[2] = {0x01, 0x0D};
    uint8_t read_cmd[1]  = {0x01};

    io_expander_config(SLAVE_U16);
    return_data =i2c_common(SLAVE_U16, write_cmd, 2, read_cmd, 1);
    data_transmit(return_data);

    // ldo_power_on_site_0(write_cmd[1]);
    led_turn_off();
}

/* =======================
   MEASUREMENTS
======================= */

void battery_voltage_check_site_0(void)
{
    led_turn_on();
    read_mux_adc(0x00, 0x00, 0x00, 0x00, 0x01);
    led_turn_off();
}

void switch_voltage_default_site_0(void)
{
    led_turn_on();
    read_mux_adc(0x01, 0x00, 0x00, 0x00, 0x01);
    led_turn_off();
}

void led_status_voltage_0_0_site_0(void)
{
    led_turn_on();
    read_mux_adc(0x02, 0x00, 0x00, 0x00, 0x01);
    led_turn_off();
}

void led_status_voltage_0_1_site_0(void)
{
    led_turn_on();
    read_mux_adc(0x03, 0x00, 0x00, 0x00, 0x01);
    led_turn_off();
}

void led_status_voltage_1_0_site_0(void)
{
    led_turn_on();
    read_mux_adc(0x04, 0x00, 0x00, 0x00, 0x01);
    led_turn_off();
}

void led_status_voltage_2_0_site_0(void)
{
    led_turn_on();
    read_mux_adc(0x05, 0x00, 0x00, 0x00, 0x01);
    led_turn_off();
}

void led_status_voltage_1_site_0(void)
{
    led_turn_on();
    read_mux_adc(0x06, 0x06, 0x00, 0x00, 0x01);
    led_turn_off();
}

void led_status_voltage_2_site_0(void)
{
    led_turn_on();
    read_mux_adc(0x07, 0x07, 0x00, 0x00, 0x01);
    led_turn_off();
}

void led_status_voltage_3_site_0(void)
{
    led_turn_on();
    read_mux_adc(0x08, 0x08, 0x00, 0x00, 0x01);
    led_turn_off();
}

void switch_voltage_press_site_0(void)
{
    led_turn_on();
    switch_on_select(switch_0);
    // read_mux_adc(0x01, 0x00, 0x00, 0x00, 0x01);
    Delay_Timer_Start(&delay);
    uint32_t start = Delay_Timer_Get(&delay);
    while ((Delay_Timer_Get(&delay) - start) < 210000);
    read_mux_adc(0x01, 0x00, 0x00, 0x00, 0x01);
    switch_off_select(switch_0);
   led_turn_off();
   
}

/* =======================
   CURRENT MEASUREMENT
======================= */

// void voltage_current_measurement_site_on(void)
// {
//     uint8_t write_cmd_1[3]={0x00,0x00,0x10};
//     uint8_t read_cmd_1[3]={0x00,0x00,0x00};
//     uint8_t write_cmd_2[3]={0x02,0x11,0x90};
//     uint8_t read_cmd_2[3]={0x02,0x00,0x00};

//     uint8_t read_cmd[3] = {0x07, 0x00, 0x00};
//     uint32_t value = 0;
// //  0x1190
//     // while (1)
//     // {
//     //     value = i2c_common(SLAVE_U7_0, NULL, 0, read_cmd, 3);
//     //     lastbit=value&0X0000F;
//     //     value >>= 4;

//     //     // Repeat if value is in invalid range
//     //     if (lastbit!=0)
//     //     {
//     //         continue;
//     //     }

//     //     // Exit loop when valid value is found
//     //     data_transmit(value);
//     //     break;
//     // }

//     i2c_common(SLAVE_U7_0, write_cmd_1,3, read_cmd_1, 3);
//     i2c_common(SLAVE_U7_0, write_cmd_2,3, read_cmd_2, 3);
    
//    value = i2c_common(SLAVE_U7_0, NULL, 0, read_cmd, 3);
//     // if(value<=0x000F0)
//     // {
//     //     value=0;
//     // }
//     // else {
//     // value=(value>>4)&0XFFFF;
//     // }
//      value=(value>>4)&0XFFFF;
//      data_transmit(value);

//     // Now 'value' contains valid data
// }

void voltage_current_measurement_site_on(void)
{
    
    led_turn_on();
    // uint8_t write_cmd_1[3] = {0x00, 0x00, 0x10};  // CONFIG (ADCRANGE=0)
    // uint8_t write_cmd_2[3] = {0x02, 0x11, 0x90};  // SHUNT_CAL (correct!)

    uint8_t read_cmd[3] = {0x04, 0x00, 0x00};     // CURRENT register

    uint32_t value = 0;

    /* Configure INA228 */
    // i2c_common(SLAVE_U7_0, write_cmd_1, 3, NULL, 0);
    // i2c_common(SLAVE_U7_0, write_cmd_2, 3, NULL, 0);

    /* Read current */
    value = i2c_common(SLAVE_U7_0, NULL, 0, read_cmd, 3);
    value=value>>4;
    /* Sign extend 20-bit */
   if(value>0x7FFFF)
   {
   value=0XFFFFF-value;
   }


    /* Send raw or converted */
    data_transmit(value);
    led_turn_off();
}


void voltage_current_measurement_reset_site_0(void)
{
    uint8_t write_cmd[3] = {0x00, 0x80,0X00};
    uint8_t read_cmd[1]  = {0x00};

    i2c_common(SLAVE_U7_0, write_cmd, 3, read_cmd, 0);
}

void voltage_current_measurement_reset_site_1(void)
{
    uint8_t write_cmd[3] = {0x00, 0x80,0X00};
    uint8_t read_cmd[1]  = {0x00};

    i2c_common(SLAVE_U7_1, write_cmd, 3, read_cmd, 0);
}
void voltage_current_measurement_reset_site_2(void)
{
    uint8_t write_cmd[3] = {0x00, 0x80,0X00};
    uint8_t read_cmd[1]  = {0x00};

    i2c_common(SLAVE_U7_2, write_cmd, 3, read_cmd, 0);
}

void turn_off_all(void)
{
    led_turn_on();
    reset_i2c();
    led_turn_off();
   
}
void reset_mcu(void)
{
     DL_SYSCTL_resetDevice(DL_SYSCTL_RESET_POR);
}


void voltage_current_measurement_site_on_1(void)
{
    uint8_t write_config[3] = {0x00, 0x45, 0x27};  // typical config
    uint8_t write_cal[3]    = {0x05, 0x0E, 0x8F};  // CAL

    uint8_t read_cmd[3]     = {0x04, 0x00, 0x00};  // CURRENT reg

    uint32_t value = 0;
    int16_t raw = 0;

    /* Configure INA226 */
    i2c_common(SLAVE_U7_0, write_config, 3, NULL, 0);
    i2c_common(SLAVE_U7_0, write_cal, 3, NULL, 0);

    /* Read current */
    value = i2c_common(SLAVE_U7_0, NULL, 0, read_cmd, 2);

    /* Convert to signed 16-bit */

    data_transmit((uint32_t)value);
}

void ldo_power_on_site_1(uint8_t value)
{
    value |= 0x40;

    uint8_t write_cmd[2] = {0x01, value};
    uint8_t read_cmd[1]  = {0x01};

    io_expander_config(SLAVE_U16);

    return_data = i2c_common(SLAVE_U16, write_cmd, 2, read_cmd, 1);
    data_transmit(return_data);
}
void ldo_power_off_site_1(void)
{
    uint8_t write_cmd[2] = {0x01, 0x00};
    uint8_t read_cmd[1]  = {0x01};

    io_expander_config(SLAVE_U16);
    i2c_common(SLAVE_U16, write_cmd, 2, read_cmd, 1);
}

void power_supply_3v3_2_site_1(void)
{
   
    uint8_t write_cmd[2] = {0x01, 0x80};
    uint8_t read_cmd[1]  = {0x01};

    io_expander_config(SLAVE_U16);
    i2c_common(SLAVE_U16, write_cmd, 2, read_cmd, 1);

    ldo_power_on_site_1(write_cmd[1]);
}

void ramp_supply_2v7_1_site_0(void) {
  led_turn_on();

  uint8_t write_cmd[3] = {0x08, 0x80, 0x00};
  uint8_t read_cmd[1] = {0x08};

  uint16_t dac_code;

  /* =====================================================
     RAMP DAC
  ===================================================== */
  for (dac_code = 0x8000; dac_code <= 0x8A3D; dac_code++) {
    /* ---------------------------------------------
       SPLIT 16-BIT DAC VALUE
    --------------------------------------------- */

    write_cmd[1] = (dac_code >> 8) & 0xFF;
    write_cmd[2] = dac_code & 0xFF;

    /* ---------------------------------------------
       WRITE + VERIFY
    --------------------------------------------- */

    return_data = i2c_common(SLAVE_U6_0, write_cmd, 3, read_cmd, 2);
    opamp_en(SLAVE_U16, 0);
    /* ---------------------------------------------
       ERROR CHECK
    --------------------------------------------- */

    if (return_data == 0xEEEEEEEE) {
      break;
    } else if (return_data == 0xFFFFFFFF) {
      break;
    } else if (return_data == 0) {
      break;
    }

    /* Optional small ramp delay */
    delay_cycles(1000);
  }



  data_transmit(return_data);

  led_turn_off();
}