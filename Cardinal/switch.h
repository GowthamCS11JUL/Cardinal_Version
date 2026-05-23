#ifndef switch_H_
#define switch_H_

typedef enum
{
    switch_0= 0,
    switch_1,
    switch_2
} switch_id;

typedef enum
{
    relay_0= 0,
    relay_1,
    relay_2
} relay_id;

void switch_relay_init(void);
void switch_0_on(void);
void switch_1_on(void);
void switch_2_on(void);
void relay_0_on(void);
void relay_1_on(void);
void relay_2_on(void);
void switch_0_off(void);
void switch_1_off(void);
void switch_2_off(void);
void relay_0_off(void);
void relay_1_off(void);
void relay_2_off(void);
void relay_all_off(void);
void switch_all_off(void);
void switch_on_select(switch_id id);
void relay_on_select(relay_id id);
void switch_off_select(switch_id id);
void relay_off_select(relay_id id);

#endif