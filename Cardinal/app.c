#include "command_function.h"
#include "headers.h"
#include "usb.h"
#include "variables.h"



void app_init()
{
led_timer_init();
usb_init();
cmd_data_setup();
i2c_init();
spi_init();
mux_init_all();
// switch_all_off();
led_init();
reset_i2c();
led_turn_on();

}

void cmd_data_setup()
{
   usb_cmd_data_setup(&USB_DATA,0,"Power_supply_3.3V_On","OK",power_supply_3v3_1_site_0);
   usb_cmd_data_setup(&USB_DATA,1,"Power_supply_3.3V_On_2","OK",power_supply_3v3_2_site_0);
//    usb_cmd_data_setup(&USB_DATA,2,"Led_blink","OK",led_blink);
//    usb_cmd_data_setup(&USB_DATA,3,"Led_off","OK",Led_off);
   usb_cmd_data_setup(&USB_DATA,2,"Power_supply_2.7V_On","OK",power_supply_2v7_1_site_0);
   usb_cmd_data_setup(&USB_DATA,3,"Power_supply_2.7V_On_2","OK",power_supply_2v7_2_site_0);
   usb_cmd_data_setup(&USB_DATA,4,"Battery_Voltage_Check","OK",battery_voltage_check_site_0);
    usb_cmd_data_setup(&USB_DATA,5,"Ibat_Power_Off","OK", voltage_current_measurement_site_on);
   usb_cmd_data_setup(&USB_DATA,6,"Switch_Voltage_Default","OK",switch_voltage_default_site_0);
   usb_cmd_data_setup(&USB_DATA,7,"Switch_Voltage_Press","OK",switch_voltage_press_site_0);
   usb_cmd_data_setup(&USB_DATA,8,"Ibat_Power_On","OK",voltage_current_measurement_site_on);
   usb_cmd_data_setup(&USB_DATA,9,"LED_On_Out_Voltage_0_0","OK",led_status_voltage_0_0_site_0);
   usb_cmd_data_setup(&USB_DATA,10,"LED_On_Out_Voltage_0_1","OK",led_status_voltage_0_1_site_0);
   usb_cmd_data_setup(&USB_DATA,11,"LED_On_Out_Voltage_1_0","OK",led_status_voltage_1_0_site_0);
   usb_cmd_data_setup(&USB_DATA,12,"LED_Off_Out_Voltage_0_0","OK",led_status_voltage_0_0_site_0);
   usb_cmd_data_setup(&USB_DATA,13,"LED_Off_Out_Voltage_0_1","OK",led_status_voltage_0_1_site_0);
   usb_cmd_data_setup(&USB_DATA,14,"LED_Off_Out_Voltage_1_0","OK",led_status_voltage_1_0_site_0);
   usb_cmd_data_setup(&USB_DATA,15,"LED_Off_Out_Voltage_2_0","OK",led_status_voltage_2_0_site_0);
   usb_cmd_data_setup(&USB_DATA,16,"LED_On_Out_Voltage_2_0","OK",led_status_voltage_2_0_site_0);
   usb_cmd_data_setup(&USB_DATA,17,"LED_On_Voltage_1","OK",led_status_voltage_1_site_0);
   usb_cmd_data_setup(&USB_DATA,18,"LED_On_Voltage_2","OK",led_status_voltage_2_site_0);
   usb_cmd_data_setup(&USB_DATA,19,"LED_On_Voltage_3","OK",led_status_voltage_3_site_0);
   usb_cmd_data_setup(&USB_DATA,20,"Power_supply_2.7V_Off","OK",turn_off_all);
   usb_cmd_data_setup(&USB_DATA,21,"Reset","OK",reset_mcu);
   usb_cmd_data_setup(&USB_DATA,22,"Ibat_Power_Off_1","OK", voltage_current_measurement_site_on_1);
   usb_cmd_data_setup(&USB_DATA,23,"Power_supply_3.3V_On_1_1","OK", power_supply_3v3_2_site_1);

   
}





 void UART0_IRQHandler(void)
{
    UART_Interface_IRQ(&USB_UART);
}

void TIMA0_IRQHandler(void)
{
    Timer_Timeout_IRQ(&USB_Timeout);
}
void I2C1_IRQHandler(void)
{
    I2C_Controller_IRQ(&I2C_MCU);
}

// void TIMG6_IRQHandler(void)
// {
  
//    Timer_Profiler_IRQ(&i2c_timeout);
// }

void TIMG7_IRQHandler(void)
{
    // Timer_Profiler_IRQ(&led_timer);
    Delay_Timer_IRQ(&delay);
}

void SPI0_IRQHandler(void)
{
    SPI_IRQ(&spi_adc);
}

