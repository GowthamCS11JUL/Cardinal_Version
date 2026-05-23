#include "headers.h"

void switch_relay_init(void)
{
    DL_GPIO_initDigitalOutput(Switch_EN_SWITCH_EN_0_IOMUX);
    DL_GPIO_enableOutput(Switch_EN_PORT,Switch_EN_SWITCH_EN_0_PIN);

    DL_GPIO_initDigitalOutput(Switch_EN_SWITCH_EN_1_IOMUX);
    DL_GPIO_enableOutput(Switch_EN_PORT,Switch_EN_SWITCH_EN_1_PIN);

    DL_GPIO_initDigitalOutput(Switch_EN_SWITCH_EN_2_IOMUX);
    DL_GPIO_enableOutput(Switch_EN_PORT,Switch_EN_SWITCH_EN_2_PIN);

    DL_GPIO_initDigitalOutput(Relay_EN_RELAY_EN_0_IOMUX);
    DL_GPIO_enableOutput(Relay_EN_PORT,Relay_EN_RELAY_EN_0_PIN);

    DL_GPIO_initDigitalOutput(Relay_EN_RELAY_EN_1_IOMUX);
    DL_GPIO_enableOutput(Relay_EN_PORT,Relay_EN_RELAY_EN_1_PIN);

    DL_GPIO_initDigitalOutput(Relay_EN_RELAY_EN_2_IOMUX);
    DL_GPIO_enableOutput(Relay_EN_PORT,Relay_EN_RELAY_EN_2_PIN);

    switch_all_off();
    relay_all_off();


}

void switch_0_on(void)
{

 switch_1_off();
 switch_2_off();

 DL_GPIO_setPins(Switch_EN_PORT,Switch_EN_SWITCH_EN_0_PIN);

}

void switch_1_on(void)
{

switch_0_off();
switch_2_off();

 DL_GPIO_setPins(Switch_EN_PORT,Switch_EN_SWITCH_EN_1_PIN);

}

void switch_2_on(void)
{

switch_0_off();
switch_1_off();

DL_GPIO_setPins(Switch_EN_PORT,Switch_EN_SWITCH_EN_2_PIN);

}

void relay_0_off(void)
{
 DL_GPIO_setPins(Relay_EN_PORT,Relay_EN_RELAY_EN_0_PIN);

}

void relay_1_off(void)
{
 DL_GPIO_setPins(Relay_EN_PORT,Relay_EN_RELAY_EN_1_PIN);

}

void relay_2_off(void)
{
DL_GPIO_setPins(Relay_EN_PORT,Relay_EN_RELAY_EN_2_PIN);

}

void switch_0_off(void)
{
 DL_GPIO_clearPins(Switch_EN_PORT,Switch_EN_SWITCH_EN_0_PIN);

}
void switch_1_off(void)
{
 DL_GPIO_clearPins(Switch_EN_PORT,Switch_EN_SWITCH_EN_1_PIN);
}

void switch_2_off(void)
{
DL_GPIO_clearPins(Switch_EN_PORT,Switch_EN_SWITCH_EN_2_PIN);
}

void relay_0_on(void)
{

relay_1_off();
relay_2_off();

DL_GPIO_clearPins(Relay_EN_PORT,Relay_EN_RELAY_EN_0_PIN);

}

void relay_1_on(void)
{

relay_0_off();
relay_2_off();

DL_GPIO_clearPins(Relay_EN_PORT,Relay_EN_RELAY_EN_1_PIN);

}

void relay_2_on(void)
{

relay_0_off();
relay_1_off();
    
DL_GPIO_clearPins(Relay_EN_PORT,Relay_EN_RELAY_EN_2_PIN);

}

void relay_all_off(void)
{
 relay_0_off();
 relay_1_off();
 relay_2_off();
}

void switch_all_off(void)
{
    switch_0_off();
    switch_1_off();
    switch_2_off();
}

void switch_off_select(switch_id id)
{
    switch(id)
    {
        case switch_0: switch_0_off(); break;
        case switch_1: switch_1_off(); break;
        case switch_2: switch_2_off(); break;
        default: break;
    }
}

void relay_off_select(relay_id id)
{
    switch(id)
    {
        case relay_0: relay_0_off(); break;
        case relay_1: relay_1_off(); break;
        case relay_2: relay_2_off(); break;
        default: break;
    }
}

void switch_on_select(switch_id id)
{
switch(id)
{
case switch_0:switch_0_on();break;
case switch_1:switch_1_on();break;
case switch_2:switch_2_on();break;
default:break;
}
}

void relay_on_select(relay_id id)
{
    switch(id)
    {
        case relay_0: relay_0_on(); break;
        case relay_1: relay_1_on(); break;
        case relay_2: relay_2_on(); break;
        default: break;
    }
}
