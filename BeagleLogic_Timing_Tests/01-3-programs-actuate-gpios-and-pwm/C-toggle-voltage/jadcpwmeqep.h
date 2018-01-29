#ifndef JADCPWMEQEP_HPP
#define JADCPWMEQEP_HPP

// adc
int get_adc_ain(const char *key, int *ain);
int adc_setup(void);
int read_value(unsigned int ain, float *value);
void adc_cleanup(void);

// pwm
int get_gpio_number(const char *key, unsigned int *gpio);
int get_pwm_key(const char *input, char *key);
int pwm_start(const char *key, float duty, float freq, int polarity);
int pwm_disable(const char *key);
int pwm_set_frequency(const char *key, float freq);
int pwm_set_duty_cycle(const char *key, float duty);
void pwm_cleanup(void);


// gpio


#define NO_EDGE      0
#define RISING_EDGE  1
#define FALLING_EDGE 2
#define BOTH_EDGE    3

#define INPUT  0
#define OUTPUT 1
#define ALT0   4

#define HIGH 1
#define LOW  0

#define PUD_OFF  0
#define PUD_DOWN 1
#define PUD_UP   2


int gpio_export(unsigned int gpio);
int gpio_unexport(unsigned int gpio);
void exports_cleanup(void);
int gpio_set_direction(unsigned int gpio, unsigned int in_flag);
int gpio_get_direction(unsigned int gpio, unsigned int *value);
int gpio_set_value(unsigned int gpio, unsigned int value);
int gpio_get_value(unsigned int gpio, unsigned int *value);

int add_edge_detect(unsigned int gpio, unsigned int edge);
void remove_edge_detect(unsigned int gpio);
int add_edge_callback(unsigned int gpio, void (*func)(unsigned int gpio));
int event_detected(unsigned int gpio);
int gpio_event_add(unsigned int gpio);
int gpio_event_remove(unsigned int gpio);
int gpio_is_evented(unsigned int gpio);
int event_initialise(void);
void event_cleanup(void);
int blocking_wait_for_edge(unsigned int gpio, unsigned int edge);

// eqep
#include <stdint.h> // for int64_t etc
#include <stdbool.h> // for bool data type

//#define eQEP0 "/sys/devices/ocp.2/48300000.epwmss/48300180.eqep"
//#define eQEP1 "/sys/devices/ocp.2/48302000.epwmss/48302180.eqep"
//#define eQEP2 "/sys/devices/ocp.2/48304000.epwmss/48304180.eqep"

#define EQEP_SYSFS "/sys/devices/ocp.3/48302000.epwmss/48302180.eqep"
// arg, the "platform" dir isn't on stock BB
// old: eqep0: "/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep"



// jpp: july 22, 2016: converted from c++ to c

// Class which defines an interface to my eQEP driver

// Modes of operation for the eQEP hardware
    typedef enum 
    {
        // Absolute positioning mode
        eQEP_Mode_Absolute = 0,

        // Relative positioning mode
        eQEP_Mode_Relative = 1,
        
        // Error flag
        eQEP_Mode_Error = 2,
    } eQEP_Mode;




void eqep_init(); // jpp note: hard-coded for "absolute"

    // Reset the value of the encoder
    void eqep_set_position(int32_t position);

    // Get the position of the encoder, pass poll as true to poll the
    // pin, whereas passing false reads the immediate value
    int32_t eqep_get_position();

    // Set the polling period
    void eqep_set_period(uint64_t period);

    // Get the polling period of the encoder
    uint64_t eqep_get_period();

    // Set the mode of the eQEP hardware
    void eqep_set_mode(eQEP_Mode mode);

    // Get the mode of the eQEP hardware
    eQEP_Mode eqep_get_mode();




#endif 
