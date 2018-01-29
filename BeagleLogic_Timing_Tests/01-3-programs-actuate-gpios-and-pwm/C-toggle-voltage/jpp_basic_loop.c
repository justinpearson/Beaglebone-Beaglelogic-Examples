
#include "jadcpwmeqep.h"
#include <stdio.h>
#include <unistd.h>


#define MY_PWM_PIN "P8_34"
#define MY_PWM_DIR_PIN_1 "P8_45"
#define MY_PWM_DIR_PIN_2 "P8_46"
#define MY_PWM_STBY "P8_44"



int main() {

  ////////////////////////////
  // ADC setup

  if (!adc_setup()) {
    printf("Unable to setup ADC system. Possible causes are: \n"
	   "  - Module 'ti_am335x_adc' is not loaded \n");
  }

  int ain;
  float value;
  int success;
  const char *channel_adc = "AIN2";

  if (!get_adc_ain(channel_adc, &ain)) {
    printf("Invalid AIN key or name.");
  }

  success = read_value(ain, &value);

  if (success == -1) {
    printf( "Error while reading AIN port. Invalid or locked AIN file.");
  }

  printf("ADC2 value: %f\n",value);

  // //////////////////////////////
  // // PWM setup


  printf("Initializing GPIOs and setting low...\n");


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


  sleep(1);

  printf("Initializing PWM to 0 and GPIO to LOW...\n");

  char key[8];
  const char *channel_pwm = MY_PWM_PIN;
  float frequency = 50000.0;
  float duty_cycle = 0.0;
  int polarity = 0;

  printf("get key returns: %d\n", get_pwm_key(channel_pwm, key));
	
  printf("pwm start returns: %d\n", pwm_start(key, duty_cycle, frequency, polarity));

  gpio_set_value(pin1, LOW);
  gpio_set_value(pin2, LOW);
  gpio_set_value(stby, HIGH);

  bool clockwiseQ = true;

  // ///////////////////////////////
  // // EQEP setup


    printf("Note: I'm using the qQEP sysfs entry:");
  printf("%s",EQEP_SYSFS);
  printf(", so make sure that exists!!\n");

  printf("Calling constructor...\n");
  eqep_init();

  printf("Setting period...\n");
  // Set the unit time period to 100,000,000 ns, or 0.1 seconds
  eqep_set_period(100000000L);









  ///////////////////////////////
  // Loop
  printf("Starting loop...\n");
  for( int i=0; i<10; i++) {
    printf("iter %d\n",i);

    // read eqep encoder of motor shaft

    printf("Shaft: %d\n", eqep_get_position());

    // read ADC
    float raw_adc;
    read_value(ain, &raw_adc);
    printf("Raw ADC: %f\n",raw_adc);

    // Write pwm duty & direction

    float duty = 10.0*i/2.0;


    clockwiseQ = !clockwiseQ;

    printf("Duty: %f, cw: %d\n",duty,clockwiseQ);
    
    if( clockwiseQ ) {
      gpio_set_value(pin1, LOW);
      gpio_set_value(pin2, HIGH);
    }
    else {
      gpio_set_value(pin1, HIGH);
      gpio_set_value(pin2, LOW);
    }


    
    duty = (duty>0.0) ?   duty : -duty;
    duty = (duty>100) ? 100 :  duty;
    duty = (duty<0)   ?   0 :  duty;


    pwm_set_duty_cycle(key, duty);

    sleep(2);



  }








  ///////////////////////
  // Cleanup



  adc_cleanup();
  
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
