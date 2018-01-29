#include "jadcpwmeqep.h"
#include <stdio.h>
#include <unistd.h> // for: unsigned int sleep(unsigned int seconds);


// JPP, 2016-07-19
// Goal: Write a C++ program that runs a DC motor.

// All this commented shit comes from
// (Beaglebone's rootfs):/root/BB_Actuator/beaglebot/encoders/api/python/test_pwm_gpios_SIMPLE.py
// which just runs the PWM a little.
// Run the py file like this:
// # cd /root/BB_Actuator/beaglebot/encoders/api/python
// # python test_pwm_gpios_SIMPLE.py

// We're gonna paste in the C++ code from the adafruit library that is what runs when you run the python code.
// Hopefully that will make a C++ file that runs the pwm and gpios.

/* MY_PWM_PIN = 'P8_34' */
/* MY_PWM_DIR_PIN_1 = 'P8_45' */
/* MY_PWM_DIR_PIN_2 = 'P8_46' */
/* MY_PWM_STBY = 'P8_44' */
#define MY_PWM_PIN "P8_34"
#define MY_PWM_DIR_PIN_1 "P8_45"
#define MY_PWM_DIR_PIN_2 "P8_46"
#define MY_PWM_STBY "P8_44"



int main() {


	printf("Hello world!\n");

/* import time */

/* import pdb */

/* # pdb.set_trace() */

/* import Adafruit_BBIO.PWM as PWM */

// TODO: how initialize?





/* import Adafruit_BBIO.GPIO as GPIO */

// TODO: how initialize?


    // int i;

    // for (i=0; i<120; i++)
    //     gpio_direction[i] = -1;

    // module_setup = 1;




/*     # '''Motor actuated by a Sparkfun motor driver that expects: */
/*     #    - PWM signal */
/*     #    - 2 digital outputs for direction */
/*     #    - 1 dig out for 'standby' */
/*     # ''' */

/* #    def __init__(self): */
	printf("Initializing GPIOs and setting low...\n");


/* GPIO.setup(MY_PWM_DIR_PIN_1, GPIO.OUT) */
/* GPIO.setup(MY_PWM_DIR_PIN_2, GPIO.OUT) */
/* GPIO.setup(MY_PWM_STBY, GPIO.OUT) */
/* GPIO.output(MY_PWM_DIR_PIN_1, GPIO.LOW)			 */
/* GPIO.output(MY_PWM_DIR_PIN_2, GPIO.LOW)			 */
/* GPIO.output(MY_PWM_STBY, GPIO.LOW)			 */


	unsigned int pin1, pin2, stby;

	get_gpio_number(MY_PWM_DIR_PIN_1, &pin1);
	get_gpio_number(MY_PWM_DIR_PIN_2, &pin2);
	get_gpio_number(MY_PWM_STBY, 	 &stby);

	gpio_export(pin1);
	gpio_export(pin2);
	gpio_export(stby);

	gpio_set_direction(pin1, OUTPUT);
	gpio_set_direction(pin2, OUTPUT);
	gpio_set_direction(stby, OUTPUT);

	gpio_set_value(pin1, LOW);
	gpio_set_value(pin2, LOW);
	gpio_set_value(stby, LOW);


	sleep(2);


/* #    def start(self): */
	printf("Initializing PWM to 0 and GPIO to LOW...\n");

/* PWM.start(MY_PWM_PIN,0,50000) # duty cycle 0%, freq 50kHz. */


	char key[8];
	const char *channel = MY_PWM_PIN;
	float frequency = 50000.0;
	float duty_cycle = 0.0;
	int polarity = 0;

	printf("get key returns: %d\n", get_pwm_key(channel, key));
	
	printf("pwm start returns: %d\n", pwm_start(key, duty_cycle, frequency, polarity));



/* GPIO.output(MY_PWM_DIR_PIN_1, GPIO.LOW)			 */
/* GPIO.output(MY_PWM_DIR_PIN_2, GPIO.LOW)			 */
/* GPIO.output(MY_PWM_STBY, GPIO.HIGH)			 */

	gpio_set_value(pin1, LOW);
	gpio_set_value(pin2, LOW);
	gpio_set_value(stby, HIGH);



	sleep(2);

/*     # def set_duty(self,drive_cw,duty_cycle): */
/*     #     '''Command the pendulum arm to move at */
/*     #        speed 'duty cycle' in direction 'drive_cw'. */

/*     #        drive_cw: True/False */
/*     #        duty in percent (0-100). */
/*     #     ''' */


/* 	# Set direction. */
/* #	if drive_cw: */

/*             # Note: because of the gearing on the pendulum, when the */
             // # motor turns cw, the pend arm turns ccw. So we actually 
/*             # need to flip the direction from what you'd expect from */
/*             # the motor driver's datasheet: */
             // # https://www.sparkfun.com/datasheets/Robotics/TB6612FNG.pdf 

	printf("Setting cw motion...\n");

 // # motor counter-clockwise -> pend arm cw 
 // GPIO.output(MY_PWM_DIR_PIN_1, GPIO.LOW)	 
/* GPIO.output(MY_PWM_DIR_PIN_2, GPIO.HIGH)			 */

	gpio_set_value(pin1, LOW);
	gpio_set_value(pin2, HIGH);




	sleep(2);

	printf("Setting 20 duty...\n");
/* PWM.set_duty_cycle(MY_PWM_PIN,20)  */

	pwm_set_duty_cycle(key, 20.0);

	sleep(2);

	printf("Setting ccw motion...\n");
/* # motor clockwise -> pend arm ccw */
/* GPIO.output(MY_PWM_DIR_PIN_1, GPIO.HIGH)	 */
/* GPIO.output(MY_PWM_DIR_PIN_2, GPIO.LOW)			 */

	gpio_set_value(pin1, HIGH);
	gpio_set_value(pin2, LOW);

	sleep(2);

	printf("Setting 50 duty...\n");
/* PWM.set_duty_cycle(MY_PWM_PIN,50) */

	pwm_set_duty_cycle(key, 50.0);


	sleep(2);

	printf("Setting 0 duty...\n");
/* PWM.set_duty_cycle(MY_PWM_PIN,0)  */

	pwm_set_duty_cycle(key, 0.0);


	sleep(2);

	printf("Shutting down...\n");

/* PWM.stop(MY_PWM_PIN) */

	pwm_disable(key);

/* GPIO.output(MY_PWM_STBY, GPIO.LOW) */
/* GPIO.output(MY_PWM_DIR_PIN_1, GPIO.LOW)	 */
/* GPIO.output(MY_PWM_DIR_PIN_2, GPIO.LOW) */

	gpio_set_value(pin1, LOW);
	gpio_set_value(pin2, LOW);
	gpio_set_value(stby, LOW);

	sleep(2);

	printf("Cleaning up...\n");

/* GPIO.cleanup() */

	event_cleanup();

/* PWM.cleanup() */

	pwm_cleanup();


	return 0;
}
