#include "headers.h"


static uint32_t return_data = 0;

//offset
static uint32_t offset_value=0;
// Led Indicator


/* ------------------------------------------------ */
/* STATIC  COMMAND                                 */
/* ------------------------------------------------ */


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

  return_data = i2c_common(DAC_IC, write_cmd, 3, read_cmd, 2);

  data_transmit(return_data);
}

void reset_current_measurement(void) {
  voltage_current_measurement_reset_site_0();

}

void reset_dac(void) {
  uint8_t write_cmd[3] = {0x08, 0x00, 0x10};
  uint8_t read_cmd[1] = {0x08};
  i2c_common(DAC_IC, write_cmd, 3, read_cmd, 2);
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


/* =======================
   LDO POWET SUPPLY
======================= */

void ldo_power_off_site_0(void) {
  uint8_t write_cmd[2] = {0x01, 0x00};
  uint8_t read_cmd[1] = {0x01};

  io_expander_config(IO_EXPANDER_IC);
  i2c_common(IO_EXPANDER_IC, write_cmd, 2, read_cmd, 1);
}

void ldo_power_on_site_0(uint8_t value) {
  value |= 0x04;

  uint8_t write_cmd[2] = {0x01, value};
  uint8_t read_cmd[1] = {0x01};

  io_expander_config(IO_EXPANDER_IC);

  return_data = i2c_common(IO_EXPANDER_IC, write_cmd, 2, read_cmd, 1);
  data_transmit(return_data);
}

/* =======================
   LDO  POWER SUPPLY 3V3
======================= */

void power_supply_3v3_2_site_0(void) {
  led_turn_on();
  ldo_power_off_site_0();

  uint8_t write_cmd[2] = {0x01, 0x08};
  uint8_t read_cmd[1] = {0x01};

  io_expander_config(IO_EXPANDER_IC);
  i2c_common(IO_EXPANDER_IC, write_cmd, 2, read_cmd, 1);

  ldo_power_on_site_0(write_cmd[1]);
  led_turn_off();
}

/* =======================
   LDO  POWER SUPPLY 2V7
======================= */

void power_supply_2v7_2_site_0(void) {

  led_turn_on();
  uint8_t write_cmd[2] = {0x01, 0x0D};
  uint8_t read_cmd[1] = {0x01};

  io_expander_config(IO_EXPANDER_IC);
  return_data = i2c_common(IO_EXPANDER_IC, write_cmd, 2, read_cmd, 1);
  data_transmit(return_data);

  led_turn_off();
}


/* =======================
   DAC  POWER SUPPLY
======================= */


/* =======================
   DAC  POWER SUPPLY 3V3
======================= */

void power_supply_3v3_1_site_0(void) {
  led_turn_on();
  // ldo_power_off_site_0();

  uint8_t write_cmd[3] = {0x08, 0xA8, 0xF5};
  uint8_t read_cmd[1] = {0x08};

  return_data = i2c_common(DAC_IC, write_cmd, 3, read_cmd, 2);

  opamp_en(IO_EXPANDER_IC, 0);

  data_transmit(return_data);
  led_turn_off();
}

/* =======================
   DAC  POWER SUPPLY 2V7
======================= */

void power_supply_2v7_1_site_0(void) {
  led_turn_on();
  // ldo_power_off_site_0();

  uint8_t write_cmd[3] = {0x08, 0x8A, 0x3D};
  uint8_t read_cmd[1] = {0x08};

  return_data = i2c_common(DAC_IC, write_cmd, 3, read_cmd, 2);

  opamp_en(IO_EXPANDER_IC, 0);

  data_transmit(return_data);
  led_turn_off();
}


/* =======================
   MEASUREMENTS
======================= */

//TP1 AND TP2

void battery_voltage_check_site_0(void) {
  led_turn_on();
  read_mux_adc(0x00, 0x00, 0x00, 0x00, 0x01);
  led_turn_off();
}


//TP6 AND TP2

void switch_voltage_default_site_0(void) {
  led_turn_on();
  read_mux_adc(0x01, 0x00, 0x00, 0x00, 0x01);
  led_turn_off();
}


//TP9 AND TP2
void led_status_voltage_0_0_site_0(void) {
  led_turn_on();
  read_mux_adc(0x02, 0x00, 0x00, 0x00, 0x01);
  led_turn_off();
}

//TP8 AND TP2
void led_status_voltage_0_1_site_0(void) {
  led_turn_on();
  read_mux_adc(0x03, 0x00, 0x00, 0x00, 0x01);
  led_turn_off();
}

//TP7 AND TP2
void led_status_voltage_1_0_site_0(void) {
  led_turn_on();
  read_mux_adc(0x04, 0x00, 0x00, 0x00, 0x01);
  led_turn_off();
}

//TP11 AND TP2
void led_status_voltage_2_0_site_0(void) {
  led_turn_on();

  mux_select(MUX_ID_1, 0x03);
  mux_select(MUX_ID_2, 0x01);
  delay_cycles(64);

  read_mux_adc(0x05, 0x00, 0x00, 0x00, 0x01);
  led_turn_off();
}

//TP11 and TP3

void led_status_voltage_1_site_0(void) {
  led_turn_on();
  read_mux_adc(0x06, 0x06, 0x00, 0x00, 0x01);
  led_turn_off();
}

// TP11 and TP4

void led_status_voltage_2_site_0(void) {
  led_turn_on();
  read_mux_adc(0x07, 0x07, 0x00, 0x00, 0x01);
  led_turn_off();
}

// TP11 and TP5
void led_status_voltage_3_site_0(void) {
  led_turn_on();
  read_mux_adc(0x08, 0x08, 0x00, 0x00, 0x01);
  led_turn_off();
}

// Pressed voltage,,Across TP6 and TP2 .
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


//CURRENT MEASUREMENT

void voltage_current_measurement_reset_site_0(void) {
  uint8_t write_cmd[3] = {0x00, 0x80, 0X00};
  uint8_t read_cmd[1] = {0x00};

  i2c_common(CURRENT_MEASUREMENT_IC, write_cmd, 3, read_cmd, 0);
}


void voltage_current_measurement_site_on(void) {

  led_turn_on();

  uint8_t read_cmd[3] = {0x04, 0x00, 0x00}; // CURRENT register

  uint32_t value = 0;

  /* Read current */
  value = i2c_common(CURRENT_MEASUREMENT_IC, NULL, 0, read_cmd, 3);
  value = value >> 4;

  if (value > 0x7FFFF) {
    value = 0XFFFFF - value;
  }

  /* Send raw or converted */
  data_transmit(value);
  led_turn_off();
}


void vbus_measurement(void)
{
  led_turn_on();

  uint8_t read_cmd[3] = {0x05, 0x00, 0x00}; // CURRENT register

  uint32_t value = 0;

  /* Read current */
  value = i2c_common(CURRENT_MEASUREMENT_IC, NULL, 0, read_cmd, 3);
  value = value >> 4;

  if (value > 0x7FFFF) {
    value = 0XFFFFF - value;
  }

  /* Send raw or converted */
  data_transmit(value);
  led_turn_off();


}
/* ------------------------------------------------ */
/* DYNAMIC COMMAND                                 */
/* ------------------------------------------------ */




/* STRING TO UINT                                   */
/* ------------------------------------------------ */

uint32_t string_to_uint(char *str) {
  uint32_t value = 0;

  uint8_t i = 0;

  while (str[i] != '\0') {
    /* ---------------------------------------- */
    /* INVALID CHARACTER CHECK                  */
    /* ---------------------------------------- */

    if ((str[i] < '0') ||

        (str[i] > '9')) {
      return 0;
    }

    /* ---------------------------------------- */
    /* ASCII -> INTEGER                         */
    /* ---------------------------------------- */

    value =

        (value * 10)

        + (str[i] - '0');

    i++;
  }

  return value;
}

/* ------------------------------------------------ */
/* DAC CONVERSION                                   */
/* ------------------------------------------------ */

/*
 * 16-bit DAC
 *
 * 0mV    -> 0
 * 5000mV -> 65535
 */

static uint32_t voltage_to_dac(uint32_t millivolt) 
{
  uint64_t temp;

  // 1. Multiply the target millivolts by 2^16 (65,536 total steps)
  // Using ULL ensures the entire math operation is calculated in 64-bit space to prevent overflow
  temp = ((uint64_t)millivolt *65535ULL );

  // 2. Divide by the actual VREF in millivolts (5.000V = 5000mV)
  // [CORRECTED: Changed 5000ULL to 4096ULL]
  temp /= 5000ULL;

  return (uint32_t)temp;
}




/* ------------------------------------------------ */
/* POWER COMMAND                                    */
/* ------------------------------------------------ */

/*
 * COMMAND:
 *
 * POWER_SET_3300
 *
 * tokens[0] = POWER
 * tokens[1] = SET
 * tokens[2] = 3300
 * 
 */

void power_command_handler(UART_DATA *usb_data,Parsed_Command_t *cmd) 
{
  uint32_t voltage_mv;


  uint32_t dac_code;

  uint8_t write_cmd[3]={0x08,0x00,0x00};
  uint8_t read_cmd[2];

  /* -------------------------------------------- */
  /* TOKEN COUNT CHECK                            */
  /* -------------------------------------------- */

  if (cmd->token_count < 3) 
  {
    UART_Target_Transmit(usb_data->uartTargetIndex,(uint8_t *)"INVALID_POWER_FORMAT\r\n",22);

    return;
  }

  /* -------------------------------------------- */
  /* SUBCOMMAND CHECK                             */
  /* -------------------------------------------- */

  if (strcmp(cmd->tokens[1],"SET") != 0) 
  {
    UART_Target_Transmit(usb_data->uartTargetIndex,(uint8_t *)"INVALID_POWER_CMD\r\n",19);

    return;
  }

  /* -------------------------------------------- */
  /* STRING -> INTEGER                            */
  /* -------------------------------------------- */

  voltage_mv =string_to_uint(cmd->tokens[2]);


  /* -------------------------------------------- */
  /* VOLTAGE RANGE CHECK                          */
  /* -------------------------------------------- */

  if ((voltage_mv == 0) ||(voltage_mv > 5000)) 
  {
    UART_Target_Transmit(usb_data->uartTargetIndex,(uint8_t *)"INVALID_VOLTAGE\r\n",17);

    return;
  }

  /* -------------------------------------------- */
  /* DAC CONVERSION                               */
  /* -------------------------------------------- */

dac_code = voltage_to_dac(voltage_mv);

write_cmd[1] = (uint8_t)((dac_code >> 8) & 0xFF); // Upper byte (MSB)
write_cmd[2] = (uint8_t)(dac_code & 0xFF);        // Lower byte (LSB)

  /* -------------------------------------------- */
  /* DAC WRITE                                    */
  /* -------------------------------------------- */

  i2c_common(DAC_IC, write_cmd, 3, read_cmd, 2);
  opamp_en(IO_EXPANDER_IC, 0);
 

  /* -------------------------------------------- */
  /* UART RESPONSE                                */
  /* -------------------------------------------- */

  sprintf((char *)usb_data->tx_buffer,"POWER_%u_OK\r\n",voltage_mv);

  UART_Target_Transmit( usb_data->uartTargetIndex,usb_data->tx_buffer,strlen((char *)usb_data->tx_buffer));
}

/* ------------------------------------------------ */
/* RESISTOR COMMAND                                 */
/* ------------------------------------------------ */

/*
 * COMMAND:
 *
 * Calibration_set_1200
 *
 * tokens[0] = Calibration
 * tokens[1] = set
 * tokens[2] = 1200
 */

void calibration_command_handler(UART_DATA *usb_data,Parsed_Command_t *cmd) 
    {
  /* -------------------------------------------- */
  /* TOKEN COUNT CHECK                            */
  /* -------------------------------------------- */

  if (cmd->token_count < 3) {
    UART_Target_Transmit(usb_data->uartTargetIndex,(uint8_t *)"INVALID_RESISTOR_FORMAT\r\n",25);

    return;
  }

  /* -------------------------------------------- */
  /* SUBCOMMAND CHECK                             */
  /* -------------------------------------------- */

  if (strcmp(cmd->tokens[1], "SET" ) != 0) {
    UART_Target_Transmit(usb_data->uartTargetIndex,(uint8_t *)"INVALID_RESISTOR_CMD\r\n",22);

    return;
  }
  /* -------------------------------------------- */
  /* STRING -> INTEGER                            */
  /* -------------------------------------------- */

   offset_value=string_to_uint(cmd->tokens[2]);
 

 
  /* -------------------------------------------- */
  /* INVALID RESISTOR                             */
  /* -------------------------------------------- */

  UART_Target_Transmit(usb_data->uartTargetIndex,(uint8_t *)"Calibration_done\r\n",19);
}


