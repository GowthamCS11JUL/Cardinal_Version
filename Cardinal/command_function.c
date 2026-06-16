
#include "command_function.h"
#include "headers.h"
#include "i2c_common.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "variables.h"

#define MAX_VOLTAGE_MV 5000
#define PREFIX "SET_VOLTAGE_"
#define SET_VOLTAGE_PREFIX_LEN 12
static uint32_t return_data = 0;

// Led Indicator

void led_init(void) {
  DL_GPIO_initDigitalOutput(LED_LED_PIN_IOMUX);
  DL_GPIO_enableOutput(LED_PORT, LED_LED_PIN_PIN);
}
void led_turn_on(void) { DL_GPIO_setPins(LED_PORT, LED_LED_PIN_PIN); }
void led_turn_off(void) { DL_GPIO_clearPins(LED_PORT, LED_LED_PIN_PIN); }

/* =======================
   HELPER FUNCTIONS
======================= */

//  Manual HEX conversion
static void send_u32_hex(uint32_t value) {
  const char hex[] = "0123456789ABCDEF";
  char buffer[8];

  for (int i = 0; i < 8; i++) {
    buffer[7 - i] = hex[value & 0xF];
    value >>= 4;
  }

  memcpy(executing_command->response, buffer, 8);
  executing_command->resp_len = 8;
}

//  FAIL response
static void send_fail(void) {
  memcpy(executing_command->response, "FAIL", 4);
  executing_command->resp_len = 4;
}

/* =======================
   DATA TRANSMIT
======================= */

static void data_transmit(uint32_t status) { send_u32_hex(status); }

/* =======================
   RESET FUNCTIONS
======================= */

void reset_i2c(void) {
  reset_current_measurement();
  reset_io_expander();
  data_transmit(0X00);
}

void reset_io_expander(void) {
  uint8_t write_cmd[3] = {0x08, 0x00, 0x00};
  uint8_t read_cmd[1] = {0x08};

  return_data = i2c_common(SLAVE_U6_0, write_cmd, 3, read_cmd, 2);

  data_transmit(return_data);
}

void reset_current_measurement(void) {
  voltage_current_measurement_reset_site_0();
  // voltage_current_measurement_reset_site_1();
  // voltage_current_measurement_reset_site_2();
}

void reset_dac(void) {
  uint8_t write_cmd[3] = {0x08, 0x00, 0x10};
  uint8_t read_cmd[1] = {0x08};
  i2c_common(SLAVE_U6_0, write_cmd, 3, read_cmd, 2);
  i2c_common(SLAVE_U6_1, write_cmd, 3, read_cmd, 2);
  i2c_common(SLAVE_U6_2, write_cmd, 3, read_cmd, 2);
}

/* =======================
   MUX + ADC
======================= */

static void read_mux_adc(uint8_t mux1, uint8_t mux2, uint8_t mux3, uint8_t mux4,
                         uint8_t mux_on) {
  uint32_t out = 0;

  if (mux_on & 0x01) {
    mux_select(MUX_ID_1, mux1);
    mux_select(MUX_ID_2, mux2);

    delay_cycles(64);

    ADC122S625_Read(&spi_adc, 0); // dummy
    delay_cycles(64);

    out = ADC122S625_Read(&spi_adc, 0);

    send_u32_hex(out);
    return;
  }

  if (mux_on & 0x02) {
    mux_select(MUX_ID_3, mux3);
    mux_select(MUX_ID_4, mux4);

    delay_cycles(32000);
    ADC122S625_Read(&spi_adc, 1); // dummy
    delay_cycles(32000);

    out = ADC122S625_Read(&spi_adc, 1);

    send_u32_hex(out);
    return;
  }

  send_fail();
}

/* =======================
   IO EXPANDER
======================= */

void io_expander_config(uint8_t slave_address) {
  uint8_t write_cmd[2] = {0x03, 0x00};
  uint8_t read_cmd[1] = {0x00};

  i2c_common(slave_address, write_cmd, 2, read_cmd, 1);
}

/* =======================
   OPAMP
======================= */

void opamp_en(uint8_t slave_address, uint8_t opamp_no) {
  if (opamp_no >= 3)
    return;

  uint8_t opamp_select = 0x10 << opamp_no;

  io_expander_config(slave_address);

  uint8_t write_cmd[2] = {0x01, 0x10};
  uint8_t read_cmd[1] = {0x00};

  i2c_common(slave_address, write_cmd, 2, read_cmd, 1);
}

/* =======================
   POWER CONTROL
======================= */

void ldo_power_off_site_0(void) {
  uint8_t write_cmd[2] = {0x01, 0x00};
  uint8_t read_cmd[1] = {0x01};

  io_expander_config(SLAVE_U16);
  i2c_common(SLAVE_U16, write_cmd, 2, read_cmd, 1);
}

void ldo_power_on_site_0(uint8_t value) {
  value |= 0x04;

  uint8_t write_cmd[2] = {0x01, value};
  uint8_t read_cmd[1] = {0x01};

  io_expander_config(SLAVE_U16);

  return_data = i2c_common(SLAVE_U16, write_cmd, 2, read_cmd, 1);
  data_transmit(return_data);
}

void power_supply_3v3_1_site_0(void) {
  led_turn_on();
  // ldo_power_off_site_0();

  uint8_t write_cmd[3] = {0x08, 0xA8, 0xF5};
  uint8_t read_cmd[1] = {0x08};

  return_data = i2c_common(SLAVE_U6_0, write_cmd, 3, read_cmd, 2);

  // opamp_en(SLAVE_U16, 0);

  data_transmit(return_data);
  led_turn_off();
}

void power_supply_3v3_2_site_0(void) {
  led_turn_on();
  ldo_power_off_site_0();

  uint8_t write_cmd[2] = {0x01, 0x08};
  uint8_t read_cmd[1] = {0x01};

  io_expander_config(SLAVE_U16);
  i2c_common(SLAVE_U16, write_cmd, 2, read_cmd, 1);

  ldo_power_on_site_0(write_cmd[1]);
  led_turn_off();
}

void power_supply_2v7_1_site_0(void) {
  led_turn_on();
  // ldo_power_off_site_0();

  uint8_t write_cmd[3] = {0x08, 0x8A, 0x3D};
  uint8_t read_cmd[1] = {0x08};

  return_data = i2c_common(SLAVE_U6_0, write_cmd, 3, read_cmd, 2);

  // opamp_en(SLAVE_U16, 0);

  data_transmit(return_data);
  led_turn_off();
}

void power_supply_2v7_2_site_0(void) {

  led_turn_on();
  uint8_t write_cmd[2] = {0x01, 0x0D};
  uint8_t read_cmd[1] = {0x01};

  io_expander_config(SLAVE_U16);
  return_data = i2c_common(SLAVE_U16, write_cmd, 2, read_cmd, 1);
  data_transmit(return_data);

  led_turn_off();
}

/* =======================
   MEASUREMENTS
======================= */

void battery_voltage_check_site_0(void) {
  led_turn_on();
  read_mux_adc(0x00, 0x00, 0x00, 0x00, 0x01);
  led_turn_off();
}

void switch_voltage_default_site_0(void) {
  led_turn_on();
  read_mux_adc(0x01, 0x00, 0x00, 0x00, 0x01);
  led_turn_off();
}

void led_status_voltage_0_0_site_0(void) {
  led_turn_on();
  read_mux_adc(0x02, 0x00, 0x00, 0x00, 0x01);
  led_turn_off();
}

void led_status_voltage_0_1_site_0(void) {
  led_turn_on();
  read_mux_adc(0x03, 0x00, 0x00, 0x00, 0x01);
  led_turn_off();
}

void led_status_voltage_1_0_site_0(void) {
  led_turn_on();
  read_mux_adc(0x04, 0x00, 0x00, 0x00, 0x01);
  led_turn_off();
}
//
void led_status_voltage_2_0_site_0(void) {
  led_turn_on();

  mux_select(MUX_ID_1, 0x03);
  mux_select(MUX_ID_2, 0x01);
  delay_cycles(64);

  read_mux_adc(0x05, 0x00, 0x00, 0x00, 0x01);
  led_turn_off();
}

void led_status_voltage_1_site_0(void) {
  led_turn_on();
  read_mux_adc(0x06, 0x06, 0x00, 0x00, 0x01);
  led_turn_off();
}

void led_status_voltage_2_site_0(void) {
  led_turn_on();
  read_mux_adc(0x07, 0x07, 0x00, 0x00, 0x01);
  led_turn_off();
}

void led_status_voltage_3_site_0(void) {
  led_turn_on();
  read_mux_adc(0x08, 0x08, 0x00, 0x00, 0x01);
  led_turn_off();
}

void switch_voltage_press_site_0(void) {
  uint32_t startTime;

  led_turn_on();

  switch_on_select(switch_0);

  startTime = Delay_Timer_Get(&delay);

  /* Wait for settling */

  while ((Delay_Timer_Get(&delay) - startTime) < 210000UL) {
    __NOP();
  }
// delay_cycles(800000);

  /* Read after stabilization */

  read_mux_adc(0x01, 0x00, 0x00, 0x00, 0x01);

  switch_off_select(switch_0);

  led_turn_off();
}

void voltage_current_measurement_site_on(void) {

  led_turn_on();

  uint8_t read_cmd[3] = {0x04, 0x00, 0x00}; // CURRENT register

  uint32_t value = 0;

  /* Read current */
  value = i2c_common(SLAVE_U7_0, NULL, 0, read_cmd, 3);
  value = value >> 4;

  if (value > 0x7FFFF) {
    value = 0XFFFFF - value;
  }

  /* Send raw or converted */
  data_transmit(value);
  led_turn_off();
}

void voltage_current_measurement_reset_site_0(void) {
  uint8_t write_cmd[3] = {0x00, 0x80, 0X00};
  uint8_t read_cmd[1] = {0x00};

  i2c_common(SLAVE_U7_0, write_cmd, 3, read_cmd, 0);
}

void voltage_current_measurement_reset_site_1(void) {
  uint8_t write_cmd[3] = {0x00, 0x80, 0X00};
  uint8_t read_cmd[1] = {0x00};

  i2c_common(SLAVE_U7_1, write_cmd, 3, read_cmd, 0);
}
void voltage_current_measurement_reset_site_2(void) {
  uint8_t write_cmd[3] = {0x00, 0x80, 0X00};
  uint8_t read_cmd[1] = {0x00};

  i2c_common(SLAVE_U7_2, write_cmd, 3, read_cmd, 0);
}

void turn_off_all(void) {
  led_turn_on();
  reset_i2c();
  led_turn_off();
}
void reset_mcu(void) {
  reset_io_expander();
  DL_SYSCTL_resetDevice(DL_SYSCTL_RESET_POR);
}

void voltage_current_measurement_site_on_1(void) {
  uint8_t write_config[3] = {0x00, 0x45, 0x27}; // typical config
  uint8_t write_cal[3] = {0x05, 0x0E, 0x8F};    // CAL

  uint8_t read_cmd[3] = {0x04, 0x00, 0x00}; // CURRENT reg

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

void ldo_power_on_site_1(uint8_t value) {
  value |= 0x40;

  uint8_t write_cmd[2] = {0x01, value};
  uint8_t read_cmd[1] = {0x01};

  io_expander_config(SLAVE_U16);

  return_data = i2c_common(SLAVE_U16, write_cmd, 2, read_cmd, 1);
  data_transmit(return_data);
}
void ldo_power_off_site_1(void) {
  uint8_t write_cmd[2] = {0x01, 0x00};
  uint8_t read_cmd[1] = {0x01};

  io_expander_config(SLAVE_U16);
  i2c_common(SLAVE_U16, write_cmd, 2, read_cmd, 1);
}

void power_supply_3v3_2_site_1(void) {

  uint8_t write_cmd[2] = {0x01, 0x80};
  uint8_t read_cmd[1] = {0x01};

  io_expander_config(SLAVE_U16);
  i2c_common(SLAVE_U16, write_cmd, 2, read_cmd, 1);

  ldo_power_on_site_1(write_cmd[1]);
}

void set_voltage_handler(void) {
  /* Pointer after "SET_VOLTAGE_" */
  char *arg = (char *)(USB_DATA.cmd_buffer + SET_VOLTAGE_PREFIX_LEN);

  uint32_t voltage = 0;
  uint8_t digit = 0;

  /* ---------------------------------
     Check if value exists
     --------------------------------- */
  if (*arg == '\0') {
    set_usb_response("ERR_MISSING_VALUE");
    return;
  }

  /* ---------------------------------
     Parse HEX value
     --------------------------------- */
  while (*arg != '\0') {
    char c = *arg;

    if (c >= '0' && c <= '9') {
      digit = c - '0';
    } else if (c >= 'A' && c <= 'F') {
      digit = c - 'A' + 10;
    } else if (c >= 'a' && c <= 'f') {
      digit = c - 'a' + 10;
    } else {
      set_usb_response("ERR_INVALID_HEX");
      return;
    }

    /* ---------------------------------
       Prevent 16-bit overflow
       --------------------------------- */
    if (voltage > 0x0FFF) {
      set_usb_response("ERR_OUT_OF_RANGE");
      return;
    }

    /* HEX accumulate */
    voltage = (voltage << 4) | digit;

    arg++;
  }

  /* ---------------------------------
     Apply DAC value
     --------------------------------- */
  apply_voltage((uint16_t)voltage);

  /* ---------------------------------
     Success response
     --------------------------------- */
  set_usb_response("PASS");
}

/* =========================================================
   Apply 16-bit DAC value directly
   ========================================================= */
void apply_voltage(uint16_t dac_value) {
  ldo_power_off_site_0();

  /* Split 16-bit DAC value */
  uint8_t msb_byte = (dac_value >> 8) & 0xFF;
  uint8_t lsb_byte = dac_value & 0xFF;

  uint8_t write_cmd[3] = {0x08, msb_byte, lsb_byte};

  uint8_t read_cmd[1] = {0x08};

  return_data = i2c_common(SLAVE_U6_0, write_cmd, 3, read_cmd, 2);

  data_transmit(return_data);
}

/* =========================================================
   Safe USB response helper
   ========================================================= */
void set_usb_response(const char *msg) {
  if ((executing_command != NULL) && (msg != NULL)) {
    uint8_t len = strlen(msg);

    if (len > MAX_RESP_LEN) {
      len = MAX_RESP_LEN;
    }

    memcpy(executing_command->response, msg, len);

    executing_command->resp_len = len;
  }
}