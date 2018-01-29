// root@arm:~/adafruit-beaglebone-io-python/source# gcc -g -pthread common.c  c_adc.c jpp_test_adc.c 
// root@arm:~/adafruit-beaglebone-io-python/source# ./a.out
// ADC2 value: 3939.000000root@arm:~/adafruit-beaglebone-io-python/source# 
// root@arm:~/adafruit-beaglebone-io-python/source# 
// root@arm:~/adafruit-beaglebone-io-python/source# gcc -g -pthread common.c  c_adc.c jpp_test_adc.c 
// root@arm:~/adafruit-beaglebone-io-python/source# ./a.out
// ADC2 value: 3981.000000
// root@arm:~/adafruit-beaglebone-io-python/source# # Plug ADC2 (P9_37) to AGND
// root@arm:~/adafruit-beaglebone-io-python/source# # Hope the value is like 0
// root@arm:~/adafruit-beaglebone-io-python/source# ./a.out
// ADC2 value: 0.000000
// root@arm:~/adafruit-beaglebone-io-python/source# # Plug ADC2 to VDD_ADC (1.8Volts) (P9_32)
// root@arm:~/adafruit-beaglebone-io-python/source# ./a.out
// ADC2 value: 4093.000000
// root@arm:~/adafruit-beaglebone-io-python/source# # Very close to 4096 (full scale) (good)
// root@arm:~/adafruit-beaglebone-io-python/source# # Great success!

#include "jadcpwmeqep.h"
#include <stdio.h>

// jpp 2016-07-19
// read the ADC from C. 

int main() {

  if (!adc_setup()) {
		printf("Unable to setup ADC system. Possible causes are: \n"
			"  - Module 'ti_am335x_adc' is not loaded \n");
	}

	int ain;
	float value;
	int success;
	const char *channel = "AIN2";

	if (!get_adc_ain(channel, &ain)) {
		printf("Invalid AIN key or name.");
	}

	success = read_value(ain, &value);

	if (success == -1) {
		printf( "Error while reading AIN port. Invalid or locked AIN file.");
	}

printf("ADC2 value: %f\n",value);

 printf("Unloading device tree...");
 adc_cleanup();
 
 return 0;
 
}
