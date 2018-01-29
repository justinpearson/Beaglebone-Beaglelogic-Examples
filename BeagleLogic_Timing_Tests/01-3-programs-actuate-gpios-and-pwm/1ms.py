import pdb
import traceback
import time

import Adafruit_BBIO.PWM as PWM
MY_PWM_PIN = 'P8_34'

import Adafruit_BBIO.GPIO as GPIO
MY_PWM_DIR_PIN_1 = 'P8_45'
MY_PWM_DIR_PIN_2 = 'P8_46'
MY_PWM_STBY = 'P8_44'

MAX_VOLTAGE = 5.0 # volts

def start():

    GPIO.setup( MY_PWM_DIR_PIN_1, GPIO.OUT)
    GPIO.output(MY_PWM_DIR_PIN_1, GPIO.LOW)                         

    GPIO.setup( MY_PWM_DIR_PIN_2, GPIO.OUT)
    GPIO.output(MY_PWM_DIR_PIN_2, GPIO.LOW)                         

    GPIO.setup( MY_PWM_STBY, GPIO.OUT)
    GPIO.output(MY_PWM_STBY, GPIO.LOW) # stby low = off

    # start PWM
    PWM.start(MY_PWM_PIN,0,50000) # duty cycle 0%, freq 1000HZ.
    GPIO.output(MY_PWM_STBY, GPIO.HIGH)


def shutdown():
    print("Shutting down PWM...")
    PWM.stop( MY_PWM_PIN )

    
    print('stopping motor...')
    GPIO.output(MY_PWM_STBY, GPIO.LOW)
    GPIO.output(MY_PWM_DIR_PIN_1, GPIO.LOW)         
    GPIO.output(MY_PWM_DIR_PIN_2, GPIO.LOW)

    print('cleaning up GPIOs...')
    GPIO.cleanup()
    
    print('cleaning up PWM...')
    PWM.cleanup()


def write_voltage(v):

    # direction
    if v>0: # should turn motor cw from rest
        pin1 = GPIO.LOW
        pin2 = GPIO.HIGH
    else:
        pin1 = GPIO.HIGH
        pin2 = GPIO.LOW

    # duty cycle: percentage of full-scale
    # note: pwm can be set w/ non-ints.
    duty = abs(1.0*v/MAX_VOLTAGE)*100.0

    # limits
    if duty > 100: duty = 100;
    if duty < 0: duty = 0;

    GPIO.output(MY_PWM_DIR_PIN_1, pin1)         
    GPIO.output(MY_PWM_DIR_PIN_2, pin2)                        
    PWM.set_duty_cycle(MY_PWM_PIN,duty)


def main():
    start()
    v = 0
    step = 1

    print('3...')
    time.sleep(1)
    print('2...')
    time.sleep(1)
    print('1...')
    time.sleep(1)
    print('go!')
    for i in range(1000):
#        print("i={}".format(i))
        v = v + step
        if v > MAX_VOLTAGE or v < -MAX_VOLTAGE: step = -step
        write_voltage(v)
        time.sleep(.001)

if __name__ == '__main__':
#        pdb.set_trace()
    try:
    	raw_input('ENTER to start!')
        main()          

    except Exception as e:
        print("Exception:")
        print(e)
    	traceback.print_exc()

    finally:
        shutdown()
