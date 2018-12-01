#ifndef __MAIN_H__
#define __MAIN_H_

#define PREDELAY_DEFAULT 2000
#define PREDELAY_MIN 0
#define PREDELAY_MAX 1<<30

#define INTERVAL_DEFAULT 1000
#define INTERVAL_MIN 0
#define INTERVAL_MAX 1<<30

#define RANDOM_FACTOR_DEFAULT 250
#define RANDOM_FACTOR_MIN 0
#define RANDOM_FACTOR_MAX 10240

#define NUM_CLICKS_DEFAULT 32
#define NUM_CLICKS_MIN -1 /* -1 = infinite */
#define NUM_CLICKS_MAX INT_MAX

typedef enum button_e {
    BUTTON_TAP = 0,
    BUTTON_STOP,
    BUTTON_START
} button_t;

typedef enum spin_e {
    SPIN_PREDELAY = 0,
    SPIN_INTERVAL,
    SPIN_RANDOM,
    SPIN_NUMBER
} spin_t;

/* Common functions. GUI's should call back to these */

void common_tap_button(void);
void common_stop_button(void);
void common_start_button(void);

void common_alarm_callback(void);

/* Stuff that has to be implemented for each GUI */

int init_gui(int argc, char **argv);
void close_gui(void);
void main_loop(void);
void set_button_sensitive(button_t button, int state);
void set_spin_value(spin_t spin, int value);
int get_spin_value(spin_t spin);
void set_alarm(int ms);
void click_mouse_button(void);

#endif
