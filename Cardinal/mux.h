#ifndef MUX_H_
#define MUX_H_

void led_blink(void);
void Led_off(void);

typedef enum
{
    MUX_ID_1 = 0,
    MUX_ID_2,
    MUX_ID_3,
    MUX_ID_4
} mux_id_t;

/* Init all mux GPIOs */
void mux_init_all(void);

/* Select channel (0–15) from given mux */
void mux_disable(mux_id_t id);
static void mux1_set_select(uint8_t ch);
static void mux2_set_select(uint8_t ch);
static void mux3_set_select(uint8_t ch);
static void mux4_set_select(uint8_t ch);
void mux_init_all(void);
void mux_select(mux_id_t id, uint8_t channel);
 
 void led_timer_init(void);


#endif