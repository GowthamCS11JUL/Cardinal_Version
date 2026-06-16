/*
 * Copyright (c) 2023, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G110X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_TIMER_0_init();
    SYSCFG_DL_TIMER_2_init();
    SYSCFG_DL_I2C_0_init();
    SYSCFG_DL_UART_0_init();
    SYSCFG_DL_SPI_0_init();
    SYSCFG_DL_WWDT0_init();
}



SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerG_reset(TIMER_0_INST);
    DL_TimerG_reset(TIMER_2_INST);
    DL_I2C_reset(I2C_0_INST);
    DL_UART_Main_reset(UART_0_INST);
    DL_SPI_reset(SPI_0_INST);
    DL_WWDT_reset(WWDT0_INST);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerG_enablePower(TIMER_0_INST);
    DL_TimerG_enablePower(TIMER_2_INST);
    DL_I2C_enablePower(I2C_0_INST);
    DL_UART_Main_enablePower(UART_0_INST);
    DL_SPI_enablePower(SPI_0_INST);
    DL_WWDT_enablePower(WWDT0_INST);
    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_0_IOMUX_SDA,
        GPIO_I2C_0_IOMUX_SDA_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_0_IOMUX_SCL,
        GPIO_I2C_0_IOMUX_SCL_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_enableHiZ(GPIO_I2C_0_IOMUX_SDA);
    DL_GPIO_enableHiZ(GPIO_I2C_0_IOMUX_SCL);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_0_IOMUX_TX, GPIO_UART_0_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_0_IOMUX_RX, GPIO_UART_0_IOMUX_RX_FUNC);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI_0_IOMUX_SCLK, GPIO_SPI_0_IOMUX_SCLK_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI_0_IOMUX_PICO, GPIO_SPI_0_IOMUX_PICO_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_SPI_0_IOMUX_POCI, GPIO_SPI_0_IOMUX_POCI_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI_0_IOMUX_CS2, GPIO_SPI_0_IOMUX_CS2_FUNC);

    DL_GPIO_initDigitalOutput(LED_LED_PIN_IOMUX);

    DL_GPIO_initDigitalOutput(Chipselect_bar_Chipselect_bar_0_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_GRP_0_PIN_0_IOMUX);

    DL_GPIO_initDigitalOutput(MUX1_ADC_MUX_EN_BAR_0_IOMUX);

    DL_GPIO_initDigitalOutput(MUX1_ADC_MUX1_S0_IOMUX);

    DL_GPIO_initDigitalOutput(MUX1_ADC_MUX1_S1_IOMUX);

    DL_GPIO_initDigitalOutput(MUX1_ADC_MUX1_S2_IOMUX);

    DL_GPIO_initDigitalOutput(MUX1_ADC_MUX1_S3_IOMUX);

    DL_GPIO_initDigitalOutput(MUX2_ADC_MUX_EN_BAR_1_IOMUX);

    DL_GPIO_initDigitalOutput(MUX2_ADC_MUX1_S4_IOMUX);

    DL_GPIO_initDigitalOutput(MUX2_ADC_MUX1_S5_IOMUX);

    DL_GPIO_initDigitalOutput(MUX2_ADC_MUX1_S6_IOMUX);

    DL_GPIO_initDigitalOutput(MUX2_ADC_MUX1_S7_IOMUX);

    DL_GPIO_initDigitalOutput(MUX3_ADC_MUX_EN_BAR_2_IOMUX);

    DL_GPIO_initDigitalOutput(MUX3_ADC_MUX2_S0_IOMUX);

    DL_GPIO_initDigitalOutput(MUX3_ADC_MUX2_S1_IOMUX);

    DL_GPIO_initDigitalOutput(MUX3_ADC_MUX2_S2_IOMUX);

    DL_GPIO_initDigitalOutput(MUX3_ADC_MUX2_S3_IOMUX);

    DL_GPIO_initDigitalOutput(MUX4_ADC_MUX_EN_BAR_3_IOMUX);

    DL_GPIO_initDigitalOutput(MUX4_ADC_MUX2_S4_IOMUX);

    DL_GPIO_initDigitalOutput(MUX4_ADC_MUX2_S5_IOMUX);

    DL_GPIO_initDigitalOutput(MUX4_ADC_MUX2_S6_IOMUX);

    DL_GPIO_initDigitalOutput(MUX4_ADC_MUX2_S7_IOMUX);

    DL_GPIO_initDigitalOutput(Switch_EN_SWITCH_EN_0_IOMUX);

    DL_GPIO_initDigitalOutput(Switch_EN_SWITCH_EN_1_IOMUX);

    DL_GPIO_initDigitalOutput(Switch_EN_SWITCH_EN_2_IOMUX);

    DL_GPIO_initDigitalOutput(Relay_EN_RELAY_EN_1_IOMUX);

    DL_GPIO_initDigitalOutput(Relay_EN_RELAY_EN_0_IOMUX);

    DL_GPIO_initDigitalOutput(Relay_EN_RELAY_EN_2_IOMUX);

    DL_GPIO_clearPins(GPIOA, LED_LED_PIN_PIN |
		MUX1_ADC_MUX1_S0_PIN |
		MUX2_ADC_MUX1_S7_PIN |
		MUX3_ADC_MUX2_S0_PIN |
		MUX3_ADC_MUX2_S1_PIN |
		MUX3_ADC_MUX2_S2_PIN |
		MUX3_ADC_MUX2_S3_PIN |
		MUX4_ADC_MUX2_S4_PIN |
		MUX4_ADC_MUX2_S5_PIN |
		MUX4_ADC_MUX2_S7_PIN |
		Switch_EN_SWITCH_EN_0_PIN |
		Switch_EN_SWITCH_EN_1_PIN |
		Switch_EN_SWITCH_EN_2_PIN |
		Relay_EN_RELAY_EN_1_PIN |
		Relay_EN_RELAY_EN_2_PIN);
    DL_GPIO_setPins(GPIOA, MUX1_ADC_MUX_EN_BAR_0_PIN |
		MUX2_ADC_MUX_EN_BAR_1_PIN |
		MUX3_ADC_MUX_EN_BAR_2_PIN |
		MUX4_ADC_MUX_EN_BAR_3_PIN |
		Relay_EN_RELAY_EN_0_PIN);
    DL_GPIO_enableOutput(GPIOA, LED_LED_PIN_PIN |
		MUX1_ADC_MUX_EN_BAR_0_PIN |
		MUX1_ADC_MUX1_S0_PIN |
		MUX2_ADC_MUX_EN_BAR_1_PIN |
		MUX2_ADC_MUX1_S7_PIN |
		MUX3_ADC_MUX_EN_BAR_2_PIN |
		MUX3_ADC_MUX2_S0_PIN |
		MUX3_ADC_MUX2_S1_PIN |
		MUX3_ADC_MUX2_S2_PIN |
		MUX3_ADC_MUX2_S3_PIN |
		MUX4_ADC_MUX_EN_BAR_3_PIN |
		MUX4_ADC_MUX2_S4_PIN |
		MUX4_ADC_MUX2_S5_PIN |
		MUX4_ADC_MUX2_S7_PIN |
		Switch_EN_SWITCH_EN_0_PIN |
		Switch_EN_SWITCH_EN_1_PIN |
		Switch_EN_SWITCH_EN_2_PIN |
		Relay_EN_RELAY_EN_1_PIN |
		Relay_EN_RELAY_EN_0_PIN |
		Relay_EN_RELAY_EN_2_PIN);
    DL_GPIO_setLowerPinsPolarity(GPIOA, DL_GPIO_PIN_0_EDGE_RISE);
    DL_GPIO_clearInterruptStatus(GPIOA, GPIO_GRP_0_PIN_0_PIN);
    DL_GPIO_enableInterrupt(GPIOA, GPIO_GRP_0_PIN_0_PIN);
    DL_GPIO_clearPins(GPIOB, MUX1_ADC_MUX1_S1_PIN |
		MUX1_ADC_MUX1_S2_PIN |
		MUX1_ADC_MUX1_S3_PIN |
		MUX2_ADC_MUX1_S4_PIN |
		MUX2_ADC_MUX1_S5_PIN |
		MUX2_ADC_MUX1_S6_PIN |
		MUX4_ADC_MUX2_S6_PIN);
    DL_GPIO_setPins(GPIOB, Chipselect_bar_Chipselect_bar_0_PIN);
    DL_GPIO_enableOutput(GPIOB, Chipselect_bar_Chipselect_bar_0_PIN |
		MUX1_ADC_MUX1_S1_PIN |
		MUX1_ADC_MUX1_S2_PIN |
		MUX1_ADC_MUX1_S3_PIN |
		MUX2_ADC_MUX1_S4_PIN |
		MUX2_ADC_MUX1_S5_PIN |
		MUX2_ADC_MUX1_S6_PIN |
		MUX4_ADC_MUX2_S6_PIN);

}


SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);

    DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
    /* Set default configuration */
    DL_SYSCTL_disableHFXT();
    DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_1);
    DL_SYSCTL_setMCLKDivider(DL_SYSCTL_MCLK_DIVIDER_DISABLE);

}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   32000000 Hz = 32000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_0ClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 0U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_0_INST_LOAD_VALUE = (0 ms * 32000000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_0TimerConfig = {
    .period     = TIMER_0_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_ONE_SHOT_UP,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_0_init(void) {

    DL_TimerG_setClockConfig(TIMER_0_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_0ClockConfig);

    DL_TimerG_initTimerMode(TIMER_0_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_0TimerConfig);
    DL_TimerG_enableInterrupt(TIMER_0_INST , DL_TIMERG_INTERRUPT_LOAD_EVENT);
    DL_TimerG_enableClock(TIMER_0_INST);




}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   1000000 Hz = 32000000 Hz / (1 * (31 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_2ClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 31U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_2_INST_LOAD_VALUE = (65.535 ms * 1000000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_2TimerConfig = {
    .period     = TIMER_2_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC_UP,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_2_init(void) {

    DL_TimerG_setClockConfig(TIMER_2_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_2ClockConfig);

    DL_TimerG_initTimerMode(TIMER_2_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_2TimerConfig);
    DL_TimerG_enableInterrupt(TIMER_2_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
    DL_TimerG_enableClock(TIMER_2_INST);




}


static const DL_I2C_ClockConfig gI2C_0ClockConfig = {
    .clockSel = DL_I2C_CLOCK_BUSCLK,
    .divideRatio = DL_I2C_CLOCK_DIVIDE_1,
};

SYSCONFIG_WEAK void SYSCFG_DL_I2C_0_init(void) {

    DL_I2C_setClockConfig(I2C_0_INST,
        (DL_I2C_ClockConfig *) &gI2C_0ClockConfig);
    DL_I2C_setAnalogGlitchFilterPulseWidth(I2C_0_INST,
        DL_I2C_ANALOG_GLITCH_FILTER_WIDTH_50NS);
    DL_I2C_enableAnalogGlitchFilter(I2C_0_INST);

    /* Configure Controller Mode */
    DL_I2C_resetControllerTransfer(I2C_0_INST);
    /* Set frequency to 100000 Hz*/
    DL_I2C_setTimerPeriod(I2C_0_INST, 31);
    DL_I2C_setControllerTXFIFOThreshold(I2C_0_INST, DL_I2C_TX_FIFO_LEVEL_BYTES_1);
    DL_I2C_setControllerRXFIFOThreshold(I2C_0_INST, DL_I2C_RX_FIFO_LEVEL_BYTES_1);
    DL_I2C_enableControllerClockStretching(I2C_0_INST);

    /* Configure Interrupts */
    DL_I2C_enableInterrupt(I2C_0_INST,
                           DL_I2C_INTERRUPT_CONTROLLER_ARBITRATION_LOST |
                           DL_I2C_INTERRUPT_CONTROLLER_EVENT1_DMA_DONE |
                           DL_I2C_INTERRUPT_CONTROLLER_EVENT2_DMA_DONE |
                           DL_I2C_INTERRUPT_CONTROLLER_NACK |
                           DL_I2C_INTERRUPT_CONTROLLER_RXFIFO_FULL |
                           DL_I2C_INTERRUPT_CONTROLLER_RXFIFO_TRIGGER |
                           DL_I2C_INTERRUPT_CONTROLLER_RX_DONE |
                           DL_I2C_INTERRUPT_CONTROLLER_START |
                           DL_I2C_INTERRUPT_CONTROLLER_STOP |
                           DL_I2C_INTERRUPT_CONTROLLER_TXFIFO_EMPTY |
                           DL_I2C_INTERRUPT_CONTROLLER_TXFIFO_TRIGGER |
                           DL_I2C_INTERRUPT_CONTROLLER_TX_DONE);


    /* Enable module */
    DL_I2C_enableController(I2C_0_INST);


}


static const DL_UART_Main_ClockConfig gUART_0ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_0Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_0_init(void)
{
    DL_UART_Main_setClockConfig(UART_0_INST, (DL_UART_Main_ClockConfig *) &gUART_0ClockConfig);

    DL_UART_Main_init(UART_0_INST, (DL_UART_Main_Config *) &gUART_0Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115211.52
     */
    DL_UART_Main_setOversampling(UART_0_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_0_INST, UART_0_IBRD_32_MHZ_115200_BAUD, UART_0_FBRD_32_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_0_INST,
                                 DL_UART_MAIN_INTERRUPT_EOT_DONE |
                                 DL_UART_MAIN_INTERRUPT_RX |
                                 DL_UART_MAIN_INTERRUPT_RXD_NEG_EDGE |
                                 DL_UART_MAIN_INTERRUPT_RXD_POS_EDGE |
                                 DL_UART_MAIN_INTERRUPT_RX_TIMEOUT_ERROR |
                                 DL_UART_MAIN_INTERRUPT_TX);

    /* Configure FIFOs */
    DL_UART_Main_enableFIFOs(UART_0_INST);
    DL_UART_Main_setRXFIFOThreshold(UART_0_INST, DL_UART_RX_FIFO_LEVEL_1_4_FULL);
    DL_UART_Main_setTXFIFOThreshold(UART_0_INST, DL_UART_TX_FIFO_LEVEL_ONE_ENTRY);

    DL_UART_Main_enable(UART_0_INST);
}

static const DL_SPI_Config gSPI_0_config = {
    .mode        = DL_SPI_MODE_CONTROLLER,
    .frameFormat = DL_SPI_FRAME_FORMAT_MOTO4_POL0_PHA0,
    .parity      = DL_SPI_PARITY_NONE,
    .dataSize    = DL_SPI_DATA_SIZE_16,
    .bitOrder    = DL_SPI_BIT_ORDER_MSB_FIRST,
    .chipSelectPin = DL_SPI_CHIP_SELECT_2,
};

static const DL_SPI_ClockConfig gSPI_0_clockConfig = {
    .clockSel    = DL_SPI_CLOCK_BUSCLK,
    .divideRatio = DL_SPI_CLOCK_DIVIDE_RATIO_1
};

SYSCONFIG_WEAK void SYSCFG_DL_SPI_0_init(void) {
    DL_SPI_setClockConfig(SPI_0_INST, (DL_SPI_ClockConfig *) &gSPI_0_clockConfig);

    DL_SPI_init(SPI_0_INST, (DL_SPI_Config *) &gSPI_0_config);

    /* Configure Controller mode */
    /*
     * Set the bit rate clock divider to generate the serial output clock
     *     outputBitRate = (spiInputClock) / ((1 + SCR) * 2)
     *     1000000 = (32000000)/((1 + 15) * 2)
     */
    DL_SPI_setBitRateSerialClockDivider(SPI_0_INST, 15);
    /* Set RX and TX FIFO threshold levels */
    DL_SPI_setFIFOThreshold(SPI_0_INST, DL_SPI_RX_FIFO_LEVEL_1_2_FULL, DL_SPI_TX_FIFO_LEVEL_1_2_EMPTY);
    DL_SPI_enableInterrupt(SPI_0_INST, (DL_SPI_INTERRUPT_IDLE |
		DL_SPI_INTERRUPT_RX |
		DL_SPI_INTERRUPT_TX));

    /* Enable module */
    DL_SPI_enable(SPI_0_INST);
}

SYSCONFIG_WEAK void SYSCFG_DL_WWDT0_init(void)
{
    /*
     * Initialize WWDT0 in Watchdog mode with following settings
     *   Watchdog Source Clock = (LFCLK Freq) / (WWDT Clock Divider)
     *                         = 32768Hz / 2 = 16.38 kHz
     *   Watchdog Period       = (WWDT Clock Divider) ∗ (WWDT Period Count) / 32768Hz
     *                         = 2 * 2^15 / 32768Hz = 2.00 s
     *   Window0 Closed Period = (WWDT Period) * (Window0 Closed Percent)
     *                         = 2.00 s * 0% = 0.00 s
     *   Window1 Closed Period = (WWDT Period) * (Window1 Closed Percent)
     *                         = 2.00 s * 0% = 0.00 s
     */
    DL_WWDT_initWatchdogMode(WWDT0_INST, DL_WWDT_CLOCK_DIVIDE_2,
        DL_WWDT_TIMER_PERIOD_15_BITS, DL_WWDT_STOP_IN_SLEEP,
        DL_WWDT_WINDOW_PERIOD_0, DL_WWDT_WINDOW_PERIOD_0);

    /* Set Window0 as active window */
    DL_WWDT_setActiveWindow(WWDT0_INST, DL_WWDT_WINDOW0);

}


