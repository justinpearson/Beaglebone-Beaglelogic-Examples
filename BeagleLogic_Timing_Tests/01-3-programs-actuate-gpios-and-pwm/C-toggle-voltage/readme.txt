Nov 28, 2016

Hi Scott, 

I've attached some C code that reads the ADC and EQEP sensors on the Beaglebone and sends a PWM and GPIO signal.

- build.sh compiles everything.
- jadcpwmeqep.h/c is the library.
- jpp_test_adc.c runs a quick test of the ADC. Same for EQEP and PWM.
- jpp_basic_loop.c runs the motor from 0 to 50%, changing speed and direction every 2 seconds.

You don't need all this code until we actually implement your algorithm on the BB; for now, see the interfaces below.

It's a little messy because, in a time of hasty desperation, I copied it from the guts of an Adafruit Python library and another random place on the web. It is not pretty code.

For now, here are the basic interfaces:

ADC:

int read_value(unsigned int ain, float *value);

- ain: ADC channel (0-6); set to 0 for now.
- value: pointer to your output value
- returns 1 if success, -1 if fail.


GPIO:

Used for motor direction. There are a pair of GPIOs that we set up as outputs in order to command the motor driver. Setting them to (1,0) goes clockwise whereas setting them to (0,1) goes counter-clockwise. (0,0) turns motor driver off.

int gpio_set_value(unsigned int gpio, unsigned int value);

gpio: set to 0 for now
value: 1 or 0. Use the macros
returns 0 on success, -1 on fail.

#define HIGH 1
#define LOW  0




EQEP:

int32_t eqep_get_position();

returns # of encoder ticks (4096 per revolution with this encoder)




PWM:

int pwm_set_duty_cycle(const char *key, float duty);

- key: set to some string like "asdf" for now
- duty: from 0 to 100 (duty cycle of the PWM). Note: no negative values. Motor direction is set with the GPIOs.
- returns: 0 if success, -1 if fail


Let me know if you have questions.

Best,
-Justin