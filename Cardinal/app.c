#include "headers.h"
#include "variables.h"



void app_init()
{
usb_init();
cmd_data_setup();
i2c_init();
spi_init();
led_timer_init();
mux_init_all();
// switch_all_off();
led_init();
reset_i2c();
opamp_en(IO_EXPANDER_IC, 0);
}

void cmd_data_setup()
{
   usb_cmd_data_setup(&USB_DATA,0,"Power_supply_3.3V_On","OK",power_supply_3v3_1_site_0);
   usb_cmd_data_setup(&USB_DATA,1,"Power_supply_3.3V_On_2","OK",power_supply_3v3_2_site_0);
   usb_cmd_data_setup(&USB_DATA,2,"Power_supply_2.7V_On","OK",power_supply_2v7_1_site_0);
   usb_cmd_data_setup(&USB_DATA,3,"Power_supply_2.7V_On_2","OK",power_supply_2v7_2_site_0);
   usb_cmd_data_setup(&USB_DATA,4,"Battery_Voltage_Check","OK",battery_voltage_check_site_0);
    usb_cmd_data_setup(&USB_DATA,5,"Ibat_Power_Off","OK", voltage_current_measurement_site_on);
   usb_cmd_data_setup(&USB_DATA,6,"Switch_Voltage_Default","OK",switch_voltage_default_site_0);
   usb_cmd_data_setup(&USB_DATA,7,"Delay_of_250ms_turn_on_1","OK",switch_voltage_press_site_0);
   usb_cmd_data_setup(&USB_DATA,8,"Delay_of_250ms_turn_off","OK",switch_voltage_press_site_0);
   usb_cmd_data_setup(&USB_DATA,9,"Delay_of_250ms_turn_on_2","OK",switch_voltage_press_site_0);
   usb_cmd_data_setup(&USB_DATA,10,"Ibat_Power_On","OK",voltage_current_measurement_site_on);
   usb_cmd_data_setup(&USB_DATA,11,"LED_On_Out_Voltage_0_0","OK",led_status_voltage_0_0_site_0);
   usb_cmd_data_setup(&USB_DATA,12,"LED_On_Out_Voltage_0_1","OK",led_status_voltage_0_1_site_0);
   usb_cmd_data_setup(&USB_DATA,13,"LED_On_Out_Voltage_1_0","OK",led_status_voltage_1_0_site_0);
   usb_cmd_data_setup(&USB_DATA,14,"LED_Off_Out_Voltage_0_0","OK",led_status_voltage_0_0_site_0);
   usb_cmd_data_setup(&USB_DATA,15,"LED_Off_Out_Voltage_0_1","OK",led_status_voltage_0_1_site_0);
   usb_cmd_data_setup(&USB_DATA,16,"LED_Off_Out_Voltage_1_0","OK",led_status_voltage_1_0_site_0);
   usb_cmd_data_setup(&USB_DATA,17,"LED_Off_Out_Voltage_2_0","OK",led_status_voltage_2_0_site_0);
   usb_cmd_data_setup(&USB_DATA,18,"LED_On_Out_Voltage_2_0","OK",led_status_voltage_2_0_site_0);
   usb_cmd_data_setup(&USB_DATA,19,"LED1_On_Voltage","OK",led_status_voltage_1_site_0);
   usb_cmd_data_setup(&USB_DATA,20,"LED2_On_Voltage","OK",led_status_voltage_2_site_0);
   usb_cmd_data_setup(&USB_DATA,21,"LED3_On_Voltage","OK",led_status_voltage_3_site_0);
   usb_cmd_data_setup(&USB_DATA,22,"VBUS_MEASURE","OK",vbus_measurement);
   usb_cmd_data_setup(&USB_DATA,23,"Power_supply_2.7V_Off","OK",turn_off_all);
   usb_cmd_data_setup(&USB_DATA,24,"Reset","OK",reset_mcu);

}


void command_dispatcher(UART_DATA *usb_data, Parsed_Command_t *cmd) {
  /* -------------------------------------------- */ /* POWER */ /* --------------------------------------------
                                                                  */
  if (strcmp(cmd->tokens[0], "POWER") == 0) {
    power_command_handler(usb_data, cmd);
    return;
  } /* -------------------------------------------- */ /* Calibration_value */ /* --------------------------------------------
                                                                       */
  if (strcmp(cmd->tokens[0], "Calibration_") == 0) {
    calibration_command_handler(usb_data, cmd);
    return;
  } /* -------------------------------------------- */ /* UNKNOWN */ /* --------------------------------------------
                                                                      */
  UART_Target_Transmit(usb_data->uartTargetIndex,
                       (uint8_t *)"UNKNOWN_COMMAND\r\n", 17);
}



 void UART0_IRQHandler(void)
{
    UART_Interface_IRQ(&USB_UART);
}

void TIMG0_IRQHandler(void)
{
    Timer_Timeout_IRQ(&USB_Timeout);
}
void I2C1_IRQHandler(void)
{
    I2C_Controller_IRQ(&I2C_MCU);
}


void TIMG7_IRQHandler(void)
{
    Delay_Timer_IRQ(&delay);
}

void SPI0_IRQHandler(void)
{
    SPI_IRQ(&spi_adc);
}

