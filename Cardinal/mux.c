#include"headers.h"
#include "ti/devices/msp/m0p/mspm0g110x.h"
#include "variables.h"


void led_timer_init()
{
Delay_Timer_Initialize(&delay,TIMG7,7,32000000);  
}




void led_blink(void)
{
    static uint32_t lastToggle = 0;
    static uint8_t ledState = 0;

    DL_GPIO_initDigitalOutput(IOMUX_PINCM1);
    DL_GPIO_enableOutput(GPIOA, DL_GPIO_PIN_0);
    //  DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_0);

    Delay_Timer_Start(&delay);

    lastToggle = Delay_Timer_Get(&delay);

    while (1)
    {
        uint32_t currentTime = Delay_Timer_Get(&delay);

        /* 500000 us = 500 ms */
        if ((currentTime - lastToggle) >= 5000000)
        {
            lastToggle = currentTime;

            if (ledState)
            {
                DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_0);
                ledState = 0;
            }
            else
            {
                DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_0);
                ledState = 1;
            }

            break;  // remove this if continuous blinking required
        }
    }

    executing_command->response[0] = 'P';
    executing_command->response[1] = 'A';
    executing_command->response[2] = 'S';
    executing_command->response[3] = 'S';
    executing_command->resp_len = 4;
}

void Led_off(void)
{
    DL_GPIO_initDigitalOutput(IOMUX_PINCM1);   

    /* Enable output driver for PA0 */
    DL_GPIO_enableOutput(GPIOA, DL_GPIO_PIN_0);

    /* Start with LED OFF */
    DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_0);

    executing_command->response[0] = 'P';
    executing_command->response[1] = 'A';
    executing_command->response[2] = 'S';
    executing_command->response[3] = 'S';
    executing_command->resp_len = 4;

}



void MUX1_init(void)
{
    /* Configure EN */
    DL_GPIO_initDigitalOutput(MUX1_ADC_MUX_EN_BAR_0_IOMUX);
    DL_GPIO_enableOutput(MUX1_ADC_MUX_EN_BAR_0_PORT,
                         MUX1_ADC_MUX_EN_BAR_0_PIN);

    /* Configure S lines */
    DL_GPIO_initDigitalOutput(MUX1_ADC_MUX1_S0_IOMUX);
    DL_GPIO_enableOutput(MUX1_ADC_MUX1_S0_PORT,
                         MUX1_ADC_MUX1_S0_PIN);

    DL_GPIO_initDigitalOutput(MUX1_ADC_MUX1_S1_IOMUX);
    DL_GPIO_enableOutput(MUX1_ADC_MUX1_S1_PORT,
                         MUX1_ADC_MUX1_S1_PIN);

    DL_GPIO_initDigitalOutput(MUX1_ADC_MUX1_S2_IOMUX);
    DL_GPIO_enableOutput(MUX1_ADC_MUX1_S2_PORT,
                         MUX1_ADC_MUX1_S2_PIN);

    DL_GPIO_initDigitalOutput(MUX1_ADC_MUX1_S3_IOMUX);
    DL_GPIO_enableOutput(MUX1_ADC_MUX1_S3_PORT,
                         MUX1_ADC_MUX1_S3_PIN);

    /* Disable mux */
    DL_GPIO_setPins(MUX1_ADC_MUX_EN_BAR_0_PORT,
                    MUX1_ADC_MUX_EN_BAR_0_PIN);
}

void MUX2_init(void)
{
    /* Enable GPIO power once globally in system init ideally */
    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);

    /* -------- EN̅ -------- */
    DL_GPIO_initDigitalOutput(MUX2_ADC_MUX_EN_BAR_1_IOMUX);
    DL_GPIO_enableOutput(MUX2_ADC_MUX_EN_BAR_1_PORT,
                         MUX2_ADC_MUX_EN_BAR_1_PIN);

    /* -------- S4 -------- */
    DL_GPIO_initDigitalOutput(MUX2_ADC_MUX1_S4_IOMUX);
    DL_GPIO_enableOutput(MUX2_ADC_MUX1_S4_PORT,
                         MUX2_ADC_MUX1_S4_PIN);

    /* -------- S5 -------- */
    DL_GPIO_initDigitalOutput(MUX2_ADC_MUX1_S5_IOMUX);
    DL_GPIO_enableOutput(MUX2_ADC_MUX1_S5_PORT,
                         MUX2_ADC_MUX1_S5_PIN);

    /* -------- S6 -------- */
    DL_GPIO_initDigitalOutput(MUX2_ADC_MUX1_S6_IOMUX);
    DL_GPIO_enableOutput(MUX2_ADC_MUX1_S6_PORT,
                         MUX2_ADC_MUX1_S6_PIN);

    /* -------- S7 -------- */
    DL_GPIO_initDigitalOutput(MUX2_ADC_MUX1_S7_IOMUX);
    DL_GPIO_enableOutput(MUX2_ADC_MUX1_S7_PORT,
                         MUX2_ADC_MUX1_S7_PIN);

    /* Disable MUX initially (EN̅ HIGH) */
    DL_GPIO_setPins(MUX2_ADC_MUX_EN_BAR_1_PORT,
                    MUX2_ADC_MUX_EN_BAR_1_PIN);
}


void MUX3_init(void)
{
    DL_GPIO_enablePower(GPIOA);

    /* EN */
    DL_GPIO_initDigitalOutput(MUX3_ADC_MUX_EN_BAR_2_IOMUX);
    DL_GPIO_enableOutput(MUX3_PORT,
                         MUX3_ADC_MUX_EN_BAR_2_PIN);

    /* S0 */
    DL_GPIO_initDigitalOutput(MUX3_ADC_MUX2_S0_IOMUX);
    DL_GPIO_enableOutput(MUX3_PORT,
                         MUX3_ADC_MUX2_S0_PIN);

    /* S1 */
    DL_GPIO_initDigitalOutput(MUX3_ADC_MUX2_S1_IOMUX);
    DL_GPIO_enableOutput(MUX3_PORT,
                         MUX3_ADC_MUX2_S1_PIN);

    /* S2 */
    DL_GPIO_initDigitalOutput(MUX3_ADC_MUX2_S2_IOMUX);
    DL_GPIO_enableOutput(MUX3_PORT,
                         MUX3_ADC_MUX2_S2_PIN);

    /* S3 */
    DL_GPIO_initDigitalOutput(MUX3_ADC_MUX2_S3_IOMUX);
    DL_GPIO_enableOutput(MUX3_PORT,
                         MUX3_ADC_MUX2_S3_PIN);

    /* Disable MUX initially (EN̅ HIGH) */
    DL_GPIO_setPins(MUX3_PORT,
                    MUX3_ADC_MUX_EN_BAR_2_PIN);
}

void MUX4_init(void)
{
    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);

    /* EN */
    DL_GPIO_initDigitalOutput(MUX4_ADC_MUX_EN_BAR_3_IOMUX);
    DL_GPIO_enableOutput(MUX4_ADC_MUX_EN_BAR_3_PORT,
                         MUX4_ADC_MUX_EN_BAR_3_PIN);

    /* S4 */
    DL_GPIO_initDigitalOutput(MUX4_ADC_MUX2_S4_IOMUX);
    DL_GPIO_enableOutput(MUX4_ADC_MUX2_S4_PORT,
                         MUX4_ADC_MUX2_S4_PIN);

    /* S5 */
    DL_GPIO_initDigitalOutput(MUX4_ADC_MUX2_S5_IOMUX);
    DL_GPIO_enableOutput(MUX4_ADC_MUX2_S5_PORT,
                         MUX4_ADC_MUX2_S5_PIN);

    /* S6 */
    DL_GPIO_initDigitalOutput(MUX4_ADC_MUX2_S6_IOMUX);
    DL_GPIO_enableOutput(MUX4_ADC_MUX2_S6_PORT,
                         MUX4_ADC_MUX2_S6_PIN);

    /* S7 */
    DL_GPIO_initDigitalOutput(MUX4_ADC_MUX2_S7_IOMUX);
    DL_GPIO_enableOutput(MUX4_ADC_MUX2_S7_PORT,
                         MUX4_ADC_MUX2_S7_PIN);

    /* Disable MUX initially (EN̅ HIGH) */
    DL_GPIO_setPins(MUX4_ADC_MUX_EN_BAR_3_PORT,
                    MUX4_ADC_MUX_EN_BAR_3_PIN);
}

void mux_disable_all(void)
{
    /* EN̅ HIGH = Disabled */

    DL_GPIO_setPins(MUX1_ADC_MUX_EN_BAR_0_PORT,
                    MUX1_ADC_MUX_EN_BAR_0_PIN);

    DL_GPIO_setPins(MUX2_ADC_MUX_EN_BAR_1_PORT,
                    MUX2_ADC_MUX_EN_BAR_1_PIN);

    DL_GPIO_setPins(MUX3_PORT,
                    MUX3_ADC_MUX_EN_BAR_2_PIN);

    DL_GPIO_setPins(MUX4_ADC_MUX_EN_BAR_3_PORT,
                    MUX4_ADC_MUX_EN_BAR_3_PIN);
}

void mux_disable(mux_id_t id)
{
    switch (id)
    {
        case MUX_ID_1:
            DL_GPIO_setPins(MUX1_ADC_MUX_EN_BAR_0_PORT,
                            MUX1_ADC_MUX_EN_BAR_0_PIN);
            break;

        case MUX_ID_2:
            DL_GPIO_setPins(MUX2_ADC_MUX_EN_BAR_1_PORT,
                            MUX2_ADC_MUX_EN_BAR_1_PIN);
            break;

        case MUX_ID_3:
            DL_GPIO_setPins(MUX3_PORT,
                            MUX3_ADC_MUX_EN_BAR_2_PIN);
            break;

        case MUX_ID_4:
            DL_GPIO_setPins(MUX4_ADC_MUX_EN_BAR_3_PORT,
                            MUX4_ADC_MUX_EN_BAR_3_PIN);
            break;

        default:
            break;
    }
}

/* -------- MUX1 Select -------- */
static inline void mux1_set_select(uint8_t ch)
{
    ch &= 0x0F;

    DL_GPIO_writePinsVal(MUX1_ADC_MUX1_S0_PORT,
                         MUX1_ADC_MUX1_S0_PIN,
                         (ch & 0x01) ? MUX1_ADC_MUX1_S0_PIN : 0);

    DL_GPIO_writePinsVal(MUX1_ADC_MUX1_S1_PORT,
                         MUX1_ADC_MUX1_S1_PIN,
                         (ch & 0x02) ? MUX1_ADC_MUX1_S1_PIN : 0);

    DL_GPIO_writePinsVal(MUX1_ADC_MUX1_S2_PORT,
                         MUX1_ADC_MUX1_S2_PIN,
                         (ch & 0x04) ? MUX1_ADC_MUX1_S2_PIN : 0);

    DL_GPIO_writePinsVal(MUX1_ADC_MUX1_S3_PORT,
                         MUX1_ADC_MUX1_S3_PIN,
                         (ch & 0x08) ? MUX1_ADC_MUX1_S3_PIN : 0);
    
   
}

/* -------- MUX2 Select -------- */
static inline void mux2_set_select(uint8_t ch)
{
    ch &= 0x0F;

    DL_GPIO_writePinsVal(MUX2_ADC_MUX1_S4_PORT,
                         MUX2_ADC_MUX1_S4_PIN,
                         (ch & 0x01) ? MUX2_ADC_MUX1_S4_PIN : 0);

    DL_GPIO_writePinsVal(MUX2_ADC_MUX1_S5_PORT,
                         MUX2_ADC_MUX1_S5_PIN,
                         (ch & 0x02) ? MUX2_ADC_MUX1_S5_PIN : 0);

    DL_GPIO_writePinsVal(MUX2_ADC_MUX1_S6_PORT,
                         MUX2_ADC_MUX1_S6_PIN,
                         (ch & 0x04) ? MUX2_ADC_MUX1_S6_PIN : 0);

    DL_GPIO_writePinsVal(MUX2_ADC_MUX1_S7_PORT,
                         MUX2_ADC_MUX1_S7_PIN,
                         (ch & 0x08) ? MUX2_ADC_MUX1_S7_PIN : 0);
    
    
}

/* -------- MUX3 Select -------- */
static inline void mux3_set_select(uint8_t ch)
{
    ch &= 0x0F;

    DL_GPIO_writePinsVal(MUX3_PORT,
                         MUX3_ADC_MUX2_S0_PIN,
                         (ch & 0x01) ? MUX3_ADC_MUX2_S0_PIN : 0);

    DL_GPIO_writePinsVal(MUX3_PORT,
                         MUX3_ADC_MUX2_S1_PIN,
                         (ch & 0x02) ? MUX3_ADC_MUX2_S1_PIN : 0);

    DL_GPIO_writePinsVal(MUX3_PORT,
                         MUX3_ADC_MUX2_S2_PIN,
                         (ch & 0x04) ? MUX3_ADC_MUX2_S2_PIN : 0);

    DL_GPIO_writePinsVal(MUX3_PORT,
                         MUX3_ADC_MUX2_S3_PIN,
                         (ch & 0x08) ? MUX3_ADC_MUX2_S3_PIN : 0);
    
   
}

/* -------- MUX4 Select -------- */
static inline void mux4_set_select(uint8_t ch)
{
    ch &= 0x0F;

    DL_GPIO_writePinsVal(MUX4_ADC_MUX2_S4_PORT,
                         MUX4_ADC_MUX2_S4_PIN,
                         (ch & 0x01) ? MUX4_ADC_MUX2_S4_PIN : 0);

    DL_GPIO_writePinsVal(MUX4_ADC_MUX2_S5_PORT,
                         MUX4_ADC_MUX2_S5_PIN,
                         (ch & 0x02) ? MUX4_ADC_MUX2_S5_PIN : 0);

    DL_GPIO_writePinsVal(MUX4_ADC_MUX2_S6_PORT,
                         MUX4_ADC_MUX2_S6_PIN,
                         (ch & 0x04) ? MUX4_ADC_MUX2_S6_PIN : 0);

    DL_GPIO_writePinsVal(MUX4_ADC_MUX2_S7_PORT,
                         MUX4_ADC_MUX2_S7_PIN,
                         (ch & 0x08) ? MUX4_ADC_MUX2_S7_PIN : 0);
    
    
}

/* ============================= */
/* ===== Public Functions ===== */
/* ============================= */

void mux_init_all(void)
{
    /* Enable GPIO power once */
    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);

    /* Call your existing init functions */
    MUX1_init();
    MUX2_init();
    MUX3_init();
    MUX4_init();

    /* Ensure all muxes disabled */
    mux_disable_all();
}

void mux_select(mux_id_t id, uint8_t channel)
{
    channel &= 0x0F;
    
    /* 2️ Update select lines */
    switch (id)
    {
        case MUX_ID_1: mux1_set_select(channel); break;
        case MUX_ID_2: mux2_set_select(channel); break;
        case MUX_ID_3: mux3_set_select(channel); break;
        case MUX_ID_4: mux4_set_select(channel); break;
        default: return;
    }

    /* 3️ Small stabilization delay (~200ns @32MHz) */
    for (volatile int i = 0; i < 20; i++);

    /* 4️ Enable selected mux */
    switch (id)
    {
        case MUX_ID_1:
            DL_GPIO_clearPins(MUX1_ADC_MUX_EN_BAR_0_PORT,
                              MUX1_ADC_MUX_EN_BAR_0_PIN);
            break;

        case MUX_ID_2:
            DL_GPIO_clearPins(MUX2_ADC_MUX_EN_BAR_1_PORT,
                              MUX2_ADC_MUX_EN_BAR_1_PIN);
            break;

        case MUX_ID_3:
            DL_GPIO_clearPins(MUX3_PORT,
                              MUX3_ADC_MUX_EN_BAR_2_PIN);
            break;

        case MUX_ID_4:
            DL_GPIO_clearPins(MUX4_ADC_MUX_EN_BAR_3_PORT,
                              MUX4_ADC_MUX_EN_BAR_3_PIN);
            break;
    }
}

