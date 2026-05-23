/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G110X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G110X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define CPUCLK_FREQ                                                     32000000



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMA0)
#define TIMER_0_INST_IRQHandler                                 TIMA0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMA0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                             (0U)
/* Defines for TIMER_2 */
#define TIMER_2_INST                                                     (TIMG7)
#define TIMER_2_INST_IRQHandler                                 TIMG7_IRQHandler
#define TIMER_2_INST_INT_IRQN                                   (TIMG7_INT_IRQn)
#define TIMER_2_INST_LOAD_VALUE                                         (65534U)




/* Defines for I2C_0 */
#define I2C_0_INST                                                          I2C1
#define I2C_0_INST_IRQHandler                                    I2C1_IRQHandler
#define I2C_0_INST_INT_IRQN                                        I2C1_INT_IRQn
#define I2C_0_BUS_SPEED_HZ                                                100000
#define GPIO_I2C_0_SDA_PORT                                                GPIOB
#define GPIO_I2C_0_SDA_PIN                                         DL_GPIO_PIN_3
#define GPIO_I2C_0_IOMUX_SDA                                     (IOMUX_PINCM16)
#define GPIO_I2C_0_IOMUX_SDA_FUNC                      IOMUX_PINCM16_PF_I2C1_SDA
#define GPIO_I2C_0_SCL_PORT                                                GPIOB
#define GPIO_I2C_0_SCL_PIN                                         DL_GPIO_PIN_2
#define GPIO_I2C_0_IOMUX_SCL                                     (IOMUX_PINCM15)
#define GPIO_I2C_0_IOMUX_SCL_FUNC                      IOMUX_PINCM15_PF_I2C1_SCL


/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_32_MHZ_115200_BAUD                                      (17)
#define UART_0_FBRD_32_MHZ_115200_BAUD                                      (23)




/* Defines for SPI_0 */
#define SPI_0_INST                                                         SPI0
#define SPI_0_INST_IRQHandler                                   SPI0_IRQHandler
#define SPI_0_INST_INT_IRQN                                       SPI0_INT_IRQn
#define GPIO_SPI_0_PICO_PORT                                              GPIOB
#define GPIO_SPI_0_PICO_PIN                                      DL_GPIO_PIN_17
#define GPIO_SPI_0_IOMUX_PICO                                   (IOMUX_PINCM43)
#define GPIO_SPI_0_IOMUX_PICO_FUNC                   IOMUX_PINCM43_PF_SPI0_PICO
#define GPIO_SPI_0_POCI_PORT                                              GPIOB
#define GPIO_SPI_0_POCI_PIN                                      DL_GPIO_PIN_19
#define GPIO_SPI_0_IOMUX_POCI                                   (IOMUX_PINCM45)
#define GPIO_SPI_0_IOMUX_POCI_FUNC                   IOMUX_PINCM45_PF_SPI0_POCI
/* GPIO configuration for SPI_0 */
#define GPIO_SPI_0_SCLK_PORT                                              GPIOB
#define GPIO_SPI_0_SCLK_PIN                                      DL_GPIO_PIN_18
#define GPIO_SPI_0_IOMUX_SCLK                                   (IOMUX_PINCM44)
#define GPIO_SPI_0_IOMUX_SCLK_FUNC                   IOMUX_PINCM44_PF_SPI0_SCLK
#define GPIO_SPI_0_CS2_PORT                                               GPIOB
#define GPIO_SPI_0_CS2_PIN                                        DL_GPIO_PIN_7
#define GPIO_SPI_0_IOMUX_CS2                                    (IOMUX_PINCM24)
#define GPIO_SPI_0_IOMUX_CS2_FUNC               IOMUX_PINCM24_PF_SPI0_CS2_POCI2



/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOB)

/* Defines for LED_PIN: GPIOB.13 with pinCMx 30 on package pin 1 */
#define LED_LED_PIN_PIN                                         (DL_GPIO_PIN_13)
#define LED_LED_PIN_IOMUX                                        (IOMUX_PINCM30)
/* Port definition for Pin Group Chipselect_bar */
#define Chipselect_bar_PORT                                              (GPIOB)

/* Defines for Chipselect_bar_0: GPIOB.20 with pinCMx 48 on package pin 19 */
#define Chipselect_bar_Chipselect_bar_0_PIN                     (DL_GPIO_PIN_20)
#define Chipselect_bar_Chipselect_bar_0_IOMUX                    (IOMUX_PINCM48)
/* Defines for ADC_MUX_EN_BAR_0: GPIOA.2 with pinCMx 7 on package pin 42 */
#define MUX1_ADC_MUX_EN_BAR_0_PORT                                       (GPIOA)
#define MUX1_ADC_MUX_EN_BAR_0_PIN                                (DL_GPIO_PIN_2)
#define MUX1_ADC_MUX_EN_BAR_0_IOMUX                               (IOMUX_PINCM7)
/* Defines for ADC_MUX1_S0: GPIOA.9 with pinCMx 20 on package pin 55 */
#define MUX1_ADC_MUX1_S0_PORT                                            (GPIOA)
#define MUX1_ADC_MUX1_S0_PIN                                     (DL_GPIO_PIN_9)
#define MUX1_ADC_MUX1_S0_IOMUX                                   (IOMUX_PINCM20)
/* Defines for ADC_MUX1_S1: GPIOB.6 with pinCMx 23 on package pin 58 */
#define MUX1_ADC_MUX1_S1_PORT                                            (GPIOB)
#define MUX1_ADC_MUX1_S1_PIN                                     (DL_GPIO_PIN_6)
#define MUX1_ADC_MUX1_S1_IOMUX                                   (IOMUX_PINCM23)
/* Defines for ADC_MUX1_S2: GPIOB.8 with pinCMx 25 on package pin 60 */
#define MUX1_ADC_MUX1_S2_PORT                                            (GPIOB)
#define MUX1_ADC_MUX1_S2_PIN                                     (DL_GPIO_PIN_8)
#define MUX1_ADC_MUX1_S2_IOMUX                                   (IOMUX_PINCM25)
/* Defines for ADC_MUX1_S3: GPIOB.9 with pinCMx 26 on package pin 61 */
#define MUX1_ADC_MUX1_S3_PORT                                            (GPIOB)
#define MUX1_ADC_MUX1_S3_PIN                                     (DL_GPIO_PIN_9)
#define MUX1_ADC_MUX1_S3_IOMUX                                   (IOMUX_PINCM26)
/* Defines for ADC_MUX_EN_BAR_1: GPIOA.3 with pinCMx 8 on package pin 43 */
#define MUX2_ADC_MUX_EN_BAR_1_PORT                                       (GPIOA)
#define MUX2_ADC_MUX_EN_BAR_1_PIN                                (DL_GPIO_PIN_3)
#define MUX2_ADC_MUX_EN_BAR_1_IOMUX                               (IOMUX_PINCM8)
/* Defines for ADC_MUX1_S4: GPIOB.14 with pinCMx 31 on package pin 2 */
#define MUX2_ADC_MUX1_S4_PORT                                            (GPIOB)
#define MUX2_ADC_MUX1_S4_PIN                                    (DL_GPIO_PIN_14)
#define MUX2_ADC_MUX1_S4_IOMUX                                   (IOMUX_PINCM31)
/* Defines for ADC_MUX1_S5: GPIOB.15 with pinCMx 32 on package pin 3 */
#define MUX2_ADC_MUX1_S5_PORT                                            (GPIOB)
#define MUX2_ADC_MUX1_S5_PIN                                    (DL_GPIO_PIN_15)
#define MUX2_ADC_MUX1_S5_IOMUX                                   (IOMUX_PINCM32)
/* Defines for ADC_MUX1_S6: GPIOB.16 with pinCMx 33 on package pin 4 */
#define MUX2_ADC_MUX1_S6_PORT                                            (GPIOB)
#define MUX2_ADC_MUX1_S6_PIN                                    (DL_GPIO_PIN_16)
#define MUX2_ADC_MUX1_S6_IOMUX                                   (IOMUX_PINCM33)
/* Defines for ADC_MUX1_S7: GPIOA.12 with pinCMx 34 on package pin 5 */
#define MUX2_ADC_MUX1_S7_PORT                                            (GPIOA)
#define MUX2_ADC_MUX1_S7_PIN                                    (DL_GPIO_PIN_12)
#define MUX2_ADC_MUX1_S7_IOMUX                                   (IOMUX_PINCM34)
/* Port definition for Pin Group MUX3 */
#define MUX3_PORT                                                        (GPIOA)

/* Defines for ADC_MUX_EN_BAR_2: GPIOA.7 with pinCMx 14 on package pin 49 */
#define MUX3_ADC_MUX_EN_BAR_2_PIN                                (DL_GPIO_PIN_7)
#define MUX3_ADC_MUX_EN_BAR_2_IOMUX                              (IOMUX_PINCM14)
/* Defines for ADC_MUX2_S0: GPIOA.13 with pinCMx 35 on package pin 6 */
#define MUX3_ADC_MUX2_S0_PIN                                    (DL_GPIO_PIN_13)
#define MUX3_ADC_MUX2_S0_IOMUX                                   (IOMUX_PINCM35)
/* Defines for ADC_MUX2_S1: GPIOA.1 with pinCMx 2 on package pin 34 */
#define MUX3_ADC_MUX2_S1_PIN                                     (DL_GPIO_PIN_1)
#define MUX3_ADC_MUX2_S1_IOMUX                                    (IOMUX_PINCM2)
/* Defines for ADC_MUX2_S2: GPIOA.15 with pinCMx 37 on package pin 8 */
#define MUX3_ADC_MUX2_S2_PIN                                    (DL_GPIO_PIN_15)
#define MUX3_ADC_MUX2_S2_IOMUX                                   (IOMUX_PINCM37)
/* Defines for ADC_MUX2_S3: GPIOA.16 with pinCMx 38 on package pin 9 */
#define MUX3_ADC_MUX2_S3_PIN                                    (DL_GPIO_PIN_16)
#define MUX3_ADC_MUX2_S3_IOMUX                                   (IOMUX_PINCM38)
/* Defines for ADC_MUX_EN_BAR_3: GPIOA.8 with pinCMx 19 on package pin 54 */
#define MUX4_ADC_MUX_EN_BAR_3_PORT                                       (GPIOA)
#define MUX4_ADC_MUX_EN_BAR_3_PIN                                (DL_GPIO_PIN_8)
#define MUX4_ADC_MUX_EN_BAR_3_IOMUX                              (IOMUX_PINCM19)
/* Defines for ADC_MUX2_S4: GPIOA.21 with pinCMx 46 on package pin 17 */
#define MUX4_ADC_MUX2_S4_PORT                                            (GPIOA)
#define MUX4_ADC_MUX2_S4_PIN                                    (DL_GPIO_PIN_21)
#define MUX4_ADC_MUX2_S4_IOMUX                                   (IOMUX_PINCM46)
/* Defines for ADC_MUX2_S5: GPIOA.22 with pinCMx 47 on package pin 18 */
#define MUX4_ADC_MUX2_S5_PORT                                            (GPIOA)
#define MUX4_ADC_MUX2_S5_PIN                                    (DL_GPIO_PIN_22)
#define MUX4_ADC_MUX2_S5_IOMUX                                   (IOMUX_PINCM47)
/* Defines for ADC_MUX2_S6: GPIOB.24 with pinCMx 52 on package pin 23 */
#define MUX4_ADC_MUX2_S6_PORT                                            (GPIOB)
#define MUX4_ADC_MUX2_S6_PIN                                    (DL_GPIO_PIN_24)
#define MUX4_ADC_MUX2_S6_IOMUX                                   (IOMUX_PINCM52)
/* Defines for ADC_MUX2_S7: GPIOA.23 with pinCMx 53 on package pin 24 */
#define MUX4_ADC_MUX2_S7_PORT                                            (GPIOA)
#define MUX4_ADC_MUX2_S7_PIN                                    (DL_GPIO_PIN_23)
#define MUX4_ADC_MUX2_S7_IOMUX                                   (IOMUX_PINCM53)
/* Port definition for Pin Group Switch_EN */
#define Switch_EN_PORT                                                   (GPIOA)

/* Defines for SWITCH_EN_0: GPIOA.4 with pinCMx 9 on package pin 44 */
#define Switch_EN_SWITCH_EN_0_PIN                                (DL_GPIO_PIN_4)
#define Switch_EN_SWITCH_EN_0_IOMUX                               (IOMUX_PINCM9)
/* Defines for SWITCH_EN_1: GPIOA.5 with pinCMx 10 on package pin 45 */
#define Switch_EN_SWITCH_EN_1_PIN                                (DL_GPIO_PIN_5)
#define Switch_EN_SWITCH_EN_1_IOMUX                              (IOMUX_PINCM10)
/* Defines for SWITCH_EN_2: GPIOA.6 with pinCMx 11 on package pin 46 */
#define Switch_EN_SWITCH_EN_2_PIN                                (DL_GPIO_PIN_6)
#define Switch_EN_SWITCH_EN_2_IOMUX                              (IOMUX_PINCM11)
/* Port definition for Pin Group Relay_EN */
#define Relay_EN_PORT                                                    (GPIOA)

/* Defines for RELAY_EN_1: GPIOA.27 with pinCMx 60 on package pin 31 */
#define Relay_EN_RELAY_EN_1_PIN                                 (DL_GPIO_PIN_27)
#define Relay_EN_RELAY_EN_1_IOMUX                                (IOMUX_PINCM60)
/* Defines for RELAY_EN_0: GPIOA.28 with pinCMx 3 on package pin 35 */
#define Relay_EN_RELAY_EN_0_PIN                                 (DL_GPIO_PIN_28)
#define Relay_EN_RELAY_EN_0_IOMUX                                 (IOMUX_PINCM3)
/* Defines for RELAY_EN_2: GPIOA.24 with pinCMx 54 on package pin 25 */
#define Relay_EN_RELAY_EN_2_PIN                                 (DL_GPIO_PIN_24)
#define Relay_EN_RELAY_EN_2_IOMUX                                (IOMUX_PINCM54)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_TIMER_2_init(void);
void SYSCFG_DL_I2C_0_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_SPI_0_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
