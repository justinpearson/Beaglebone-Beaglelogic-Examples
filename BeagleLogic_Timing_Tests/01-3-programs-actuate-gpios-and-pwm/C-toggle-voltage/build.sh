#!/bin/bash

set -x
set -e

# g++ -g -Wall  -c common.c
# g++ -g -Wall  -c c_adc.c
# g++ -g -Wall  -std=c++11 -c eqep.cpp 
# g++ -g -Wall  -c event_gpio.c
# g++ -g -Wall  -c c_pwm.c
# g++ -g -Wall  -c jpp_test_adc.c
# g++ -g -Wall  common.o c_adc.o jpp_test_adc.o -o jpp_test_adc
# g++ -g -Wall  -c jpp_test_pwm.c
# g++ -g -Wall  -pthread c_pwm.o event_gpio.o common.o jpp_test_pwm.o -o jpp_test_pwm
# g++ -g -Wall  -std=c++11 -c jpp_basic_loop.cpp

# g++ -g -Wall -std=c++11 -c jpp_test_eqep.c
# g++ -g -Wall eqep.o jpp_test_eqep.o -o jpp_test_eqep





# 2016-07-21: When eqep was a cpp library:

#g++ -g -Wall -pthread -std=c++11  -c jadcpwmeqep.cpp
#g++ -g -Wall -pthread -std=c++11   jadcpwmeqep.o jpp_test_adc.c -o jpp_test_adc
#g++ -g -Wall -pthread -std=c++11   jadcpwmeqep.o jpp_test_pwm.c -o jpp_test_pwm
#g++ -g -Wall -pthread -std=c++11   jadcpwmeqep.o jpp_test_eqep.c -o jpp_test_eqep
#g++ -g -Wall -pthread -std=c++11   jadcpwmeqep.o jpp_basic_loop.cpp -o jpp_basic_loop


# 2016-07-22: I converted eqep to c lib:

gcc -g -Wall -Werror -pthread -lstdc++ -std=gnu99  -c jadcpwmeqep.c
# gcc -g -Wall -Werror -pthread -lstdc++ -std=gnu99 jadcpwmeqep.o jpp_test_adc.c -o jpp_test_adc      
# gcc -g -Wall -Werror -pthread -lstdc++ -std=gnu99 jadcpwmeqep.o jpp_test_pwm.c -o jpp_test_pwm   
# gcc -g -Wall -Werror -pthread -lstdc++ -std=gnu99 jadcpwmeqep.o jpp_test_eqep.c -o jpp_test_eqep    
# gcc -g -Wall -Werror -pthread -lstdc++ -std=gnu99 jadcpwmeqep.o jpp_basic_loop.c -o jpp_basic_loop

yourfile="c_toggle_voltage"

# gcc -g -Wall -Werror -pthread -lstdc++ -std=gnu99 jadcpwmeqep.o $yourfile".c" -o $yourfile

date; gcc -Wall -Werror -Wno-unused-variable -Wno-unused-result  -lstdc++ -std=gnu99 -O0 -DNDEBUG -lrt -lm  -o ./$yourfile jadcpwmeqep.o ./$yourfile".c"; date

