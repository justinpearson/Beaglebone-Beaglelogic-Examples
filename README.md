This is a dump of some files and notes when I was using the BeagleLogic high-speed data sampler in my Beaglebone Black PRU work. It's just a data dump, not a nice writeup -- sorry!



Nov 29: Install BeagleLogic (100MHz logic analyzer) to Yankee BB to measure preemption times on Zulu BB
-----------------------------------------------------------------------------------------------------------

Nov 29, 2016

Following instructions from

https://github.com/abhishek-kakkar/BeagleLogic/wiki/BeagleLogic-%22no-setup-required%22-setup:-Introducing-System-Image!

Downloaded 900MB SD image from

https://docs.google.com/uc?id=0B3KfnknFj8FjOVk3RVdDYXE3dEk&export=download

    beaglelogic-2016-04-15.img.tar.xz

Now to write SD card.

Following my instructions from "Installing the QoT stack (UCLA trip with Sean Kim) (Aug 12, 2016)" from

    file:///home/roseline/Dropbox/DC_motor/Notes/notes.html

Right-click the img.tar.xz, 'extract here', creates

    bone-debian-8.4-lxqt-4gb-armhf-2016-04-10-4gb.img

Right-click the .img, Open with Disk Manager or something.

Restore to /dev/sdc (7.2 GB)


You may need to unmount the sd card first:

start gparted (the graphical version) (search from "windows" menu) 

select sd card from drop-down menu

    /dev/sdc (7.21GB)

right-click each of the 3 partitions, unmounted 




Booting up

ftdi cable

plug in ethernet

minicom

apply power

log in: debian, temppwd

set up dhcp like this:


    sudo su

    nano /etc/network/interfaces

uncomment for eth0 so it's like this:

    # The primary network interface
    auto eth0
    iface eth0 inet dhcp
    # Example to keep MAC address between reboots
    # hwaddress ether 6c:ec:eb:af:10:ad





Note: note: to hard-code eth, do this:

    # jpp
    # IPv4 address
    #iface eth0 inet static
    #       address 10.42.0.125
    #       netmask 255.255.255.0
    #       network 10.42.0.0
    #       broadcast 10.42.0.255
    #       gateway 10.42.0.1


ifconfig to ensure you've got an IP

ssh in

log out of minicom

close minicom



    cd /opt/BeagleLogic

sudo git pull

ctrl-c out of commit msg

sudo git pull again, seems to have worked

reboot

https://github.com/abhishek-kakkar/BeagleLogic/wiki/BeagleLogic-%22no-setup-required%22-setup:-Introducing-System-Image!

After SSHing into the BeagleBone. you can directly use the dd and the sigrok commands as described in Using BeagleLogic: Post Processing right away. No configuration, no loading of modules required as everything is managed on system boot.

You can alternatively open up the web interface of BeagleLogic by logging onto port 4000 of your BeagleBone. The URL is usually http://192.168.7.2:4000/ if the BeagleBone is directly connected to your PC via USB.

browser to 

    http://10.42.0.125:4000

I see the web interface like he shows in the website.

'capture'

P8_43,4,5,6 show flat lines, plausible.

Next, shold hook up BB victor to it w/ a python program w/ pwm or something.



Ok, how about we use the PWM pin from Victor, and run one of victor's programs to run teh DC motor? Or 

How to see what the BeagleLogic's board's pins are configured as? Don't want to plug two GPIO outputs together...


The pins in question are P8_43, 44, 45, 46.

Derek's book, pg 211: Fig 6-6: BBB P8 header pins: 

P8_43,4,5,6 are $PINS 42,43,40,41

    # echo $PINS
    /sys/kernel/debug/pinctrl/44e10800.pinmux/pins
    # echo $SLOTS
    /sys/devices/bone_capemgr.9/slots


    root@beaglebone:/sys/kernel/debug/pinctrl/44e10800.pinmux# cat pins
    registered pins: 142
    pin 0 (44e10800) 00000031 pinctrl-single 
    pin 1 (44e10804) 00000031 pinctrl-single 
    pin 2 (44e10808) 00000031 pinctrl-single 
    ...
    pin 40 (44e108a0) 0000002e pinctrl-single 
    pin 41 (44e108a4) 0000002e pinctrl-single 
    pin 42 (44e108a8) 0000002e pinctrl-single 
    pin 43 (44e108ac) 0000002e pinctrl-single 
    ...

0x2e = 0010 1110

0,1,2: mode. 110 = 6 = pr1-pru1_pru_r31_0,1,2,3. Good, they're hooked up to be set by PRU registers.
3: puden: pull-up/down enable. 1=disable
4: putypesel pull-up/down type select: 0=pull-down
5: rxactive: 1=it's an GPIO input. (0 is a GPIO output)
6: slewctrl 0=fast.

So these things are set up to be fast inputs, accessible by the PRU. Good.


Just for funzies, check: 

    root@beaglebone:/sys/kernel/debug/pinctrl/44e10800.pinmux# cat pinmux-pins 
    ...
    pin 40 (44e108a0): 4a300000.prurproc (GPIO UNCLAIMED) function pinmux_pru_pru_pins group pinmux_pru_pru_pins
    pin 41 (44e108a4): 4a300000.prurproc (GPIO UNCLAIMED) function pinmux_pru_pru_pins group pinmux_pru_pru_pins
    pin 42 (44e108a8): 4a300000.prurproc (GPIO UNCLAIMED) function pinmux_pru_pru_pins group pinmux_pru_pru_pins
    pin 43 (44e108ac): 4a300000.prurproc (GPIO UNCLAIMED) function pinmux_pru_pru_pins group pinmux_pru_pru_pins
    ...

Not sure about that.


Ok, time to plug in BeagleLogic into our main MPC/MHE experiment. 

Yankee P8_43 <=> Victor PWM to motor driver
P8_44 <=> AIN1 on motor driver
P8_45 <=> AIN2 on motor driver
P8_46 <=> EQEP channel A

Now ready to drive the motor on Victor and see if we see anything on the BeagleLogic.


    2016-11-30 11:11:37 [root@beaglebone /home/debian/BB_PRU_stuff/Integration-test/15-horizon-sweep/Ts5_T20_L10_S3] 
    # ./run 400
    Running  at realtime priority:
    Current local time and date: Wed Nov 30 11:13:43 2016
    Welcome to the Beaglebone PRU library for real-time controls!
    NOTE: if you get a seg fault, make sure the jppprugpio device tree overlay has been loaded!!
    Here's the cmd: root@beaglebone# echo jppprugpio > /sys/devices/bone_capemgr.9/slots
    Assumes you have jppprugpio-00A0.dto in /lib/firmware
    Also do this:
    echo bone_eqep1 > $SLOTS
    Resetting EQEP  to 0...
    Found EQEP sysid entry. Resetting eqep...
    prussdrv_init() (returned 0)
    prussdrv_open (returned 0)
    prussdrv_pruintc_init (returned 0


Then I run the web interface for BeagleLogic. I did 1MHz, 1000 samples. If I do too many, like 100,000 samples, it hangs my browser.

Plots look ok.

"Save Capture" and "Dump Raw Data" buttons don't seem to work.

Accordign to 

https://github.com/abhishek-kakkar/BeagleLogic/issues/3

that's expected. Could save the html, which appears to save the data in a weird sigrok format.

For now, since we're just gonna get it into matlab, let's see if we can capture it with dd or something.

Seems to work:

    dd if=/dev/beaglelogic bs=262144 count=1 of=capture.raw

-rw-r--r-- 1 root root 262144 Nov 30 11:24 capture.raw

You're supposed to set up the sample rate etc from the sysfs interface, eg

https://github.com/abhishek-kakkar/BeagleLogic/wiki/BeagleLogic-Primer-:-Getting-Started

At this point BeagleLogic cannot be run as it has no memory allocated to it. Allocate memory by writing the size in bytes to this sysfs attribute

echo 33554432 > /sys/devices/virtual/misc/beaglelogic/memalloc


But I didn't do that.


Can use sigrok-cli on BL to capture, then tx to NUC to view w/ pulseview:

On controller:

    2016-11-30 12:08:11 [root@beaglebone /home/debian/BB_PRU_stuff/Integration-test/15-horizon-sweep/Ts5_T20_L10_S3] 
    # ./run 400

This starts it running.

On BeagleLogic:

    root@beaglebone:~# sigrok-cli -d beaglelogic --samples 10M -c samplerate=10M --channels P8_43,P8_44,P8_45,P8_46  -o booger.sr
    root@beaglebone:~# ls -l
    total 332
    -rw-r--r-- 1 root root  72029 Nov 30 11:48 booger.sr


On NUC:

 1956  30/11/16 11:48:33 scp root@10.42.0.125:/root/booger.sr . && pulseview booger.sr 


PulseView is a pretty cool program.


Make it a CSV so you can import it into matlab:

    root@beaglebone:~# sigrok-cli -d beaglelogic --samples 1M -c samplerate=10M --channels P8_43,P8_44,P8_45,P8_46  -o booger.csv -O csv
    root@beaglebone:~# ls -lstr
    total 8148
       4 drwxr-xr-x 2 root root    4096 Apr 10  2016 tmp
     256 -rw-r--r-- 1 root root  262144 Nov 30 11:24 capture.raw
      72 -rw-r--r-- 1 root root   72029 Nov 30 11:48 booger.sr
    7816 -rw-r--r-- 1 root root 8000130 Nov 30 12:09 booger.csv

    $ head booger.csv
    ; CSV, generated by libsigrok 0.4.0 on Wed Nov 30 12:09:06 2016
    ; Channels (4/8): P8_45, P8_46, P8_43, P8_44
    ; Samplerate: 10 MHz
    0,1,0,1
    0,1,0,1
    0,1,0,1
    0,1,0,1
    0,1,0,1
    0,1,0,1
    0,1,0,1

Note it's a lot bigger. Would be better to convert from .sr to .csv, how?

Not sure. The .sr file is small. 

Which output format is the best? 

      107  sigrok-cli -d beaglelogic --samples 1M -c samplerate=10M --channels P8_43,P8_44,P8_45,P8_46  -o booger.bits -O bits
      108  sigrok-cli -d beaglelogic --samples 1M -c samplerate=10M --channels P8_43,P8_44,P8_45,P8_46  -o booger.hex -O hex
      109  sigrok-cli -d beaglelogic --samples 1M -c samplerate=10M --channels P8_43,P8_44,P8_45,P8_46  -o booger.ascii -O ascii
      110  sigrok-cli -d beaglelogic --samples 1M -c samplerate=10M --channels P8_43,P8_44,P8_45,P8_46  -o booger.binary -O binary
      111  sigrok-cli -d beaglelogic --samples 1M -c samplerate=10M --channels P8_43,P8_44,P8_45,P8_46  -o booger.vcd -O vcd
      112  sigrok-cli -d beaglelogic --samples 1M -c samplerate=10M --channels P8_43,P8_44,P8_45,P8_46  -o booger.ols -O ols
      113  sigrok-cli -d beaglelogic --samples 1M -c samplerate=10M --channels P8_43,P8_44,P8_45,P8_46  -o booger.gnuplot -O gnuplot
      114  sigrok-cli -d beaglelogic --samples 1M -c samplerate=10M --channels P8_43,P8_44,P8_45,P8_46  -o booger.chronovu-la8 -O chronovu-la8
      115  sigrok-cli -d beaglelogic --samples 1M -c samplerate=10M --channels P8_43,P8_44,P8_45,P8_46  -o booger.csv -O csv
      116  sigrok-cli -d beaglelogic --samples 1M -c samplerate=10M --channels P8_43,P8_44,P8_45,P8_46  -o booger.analog -O analog
      117  sigrok-cli -d beaglelogic --samples 1M -c samplerate=10M --channels P8_43,P8_44,P8_45,P8_46  -o booger.analog -O analog
      118  sigrok-cli -d beaglelogic --samples 1M -c samplerate=10M --channels P8_43,P8_44,P8_45,P8_46  -o booger.sr -O sr


Note that it only takes .1 sec to collect the data; the rest of the time is spend writing to disk. 

The csv file is easy to read in matlab, but is big.


      root@beaglebone:~# for f in `ls -S booger*`; do  wc $f; done
    1000005 1000010 9888980 booger.ols
    1000003 1000023 8000130 booger.csv
      62502  500009 4875056 booger.bits
      54058   54065 4378448 booger.ascii
      20838  500009 1645908 booger.hex
          0       1 1000005 booger.chronovu-la8
          0       1 1000000 booger.binary
      8584  42920 136861 booger.gnuplot
     6225 12486 80399 booger.vcd
      299  2113 72029 booger.sr
    0 0 0 booger.analog

Looks like .sr is the best, with .vcd and .gnuplot close. the last two record only the times when the discrete GPIO signal changed, seems sensible.


pulseview requires .sr to view.

matlab can't import .sr, .gnuplot, or .vcd. :(


With .csv, can "Import Data" into matlab. It's 1e6 samples long. Presumably each sample is 1/10e6 sec apart, since sample rate was 10 MHz.


Can record to .sr on the BL (fast), scp to NUC (fast, bc file is small), then convert to CSV via:

    $ sigrok-cli -i booger.sr -o booger.csv -O csv

Note: 10M samples of 4 channels is ~80MB. 


Test BeagleLogic w/ fun generator
-------------------------------------

Main idea: generate a square wave w/ a function generator and sample it with the BL. The BL should have collected a square wave -- if you look at the sample times when a rising or falling edge happens, they should always be the same number of samples apart.

Our fun generator goes up to 10MHz, but the signal looks crappy. I settled for 1 MHz. 

Collect data:

    root@beaglebone:~# sigrok-cli -d beaglelogic --samples 10M -c samplerate=100M --channels P8_43,P8_44,P8_45,P8_46  -o booger.csv -O csv
    root@beaglebone:~# ls -l *.csv
    -rw-r--r-- 1 root root 80000131 Nov 30 13:56 booger.csv
    root@beaglebone:~# ls -hl *.csv
    -rw-r--r-- 1 root root 77M Nov 30 13:56 booger.csv
    root@beaglebone:~# sigrok-cli -d beaglelogic --samples 10M -c samplerate=100M --channels P8_43  -o booger.csv -O csv
    root@beaglebone:~# ls -hl *.csv
    -rw-r--r-- 1 root root 20M Nov 30 13:57 booger.csv
    root@beaglebone:~# wc $_
    ^C
    root@beaglebone:~# wc booger.csv
    10000003 10000020 20000110 booger.csv
    root@beaglebone:~# head booger.csv
    ; CSV, generated by libsigrok 0.4.0 on Wed Nov 30 13:57:10 2016
    ; Channels (1/8): P8_43
    ; Samplerate: 100 MHz
    0
    0
    0
    0
    0
    0
    0


transfer to NUC:


$ scp root@10.42.0.125:/root/booger.csv .
Debian GNU/Linux 8

BeagleBoard.org Debian Image 2016-04-10

Support/FAQ: http://elinux.org/Beagleboard:BeagleBoneBlack_Debian

default username:password is [debian:temppwd]

    booger.csv                                                   100%   19MB   9.5MB/s   00:02    
    2016-11-30 13:58:59 [roseline@roseline-controller-2 ~] 
    $ 



Analyze in matlab:

"import data" > booger.csv > rename 1st column "onemhz" > import


    >> 
    d=diff(onemhz);
    f = find(d);

    >> length(f)

    ans =

          198194

    >> f(1:10)

    ans =

        32
        82
       133
       183
       234
       284
       335
       385
       436
       486

Those are the indices (10ns apart) where a edge was detected in the square wave.

They should all be 50 indices apart, because 100 MHz sampling a 1 MHz square wave: 

1 MHz = 1 cycle / 1 us = 2 edges / 1 us

(100 samples / 1 us) / (2 edges / 1 us ) = 50 samples per edge.

df = diff(f);

hist(df)  % looks good.


    >> u = unique(df);
    >> u

    u =

        49
        50
        51
        52


    >> for i=1:length(u); disp(length(find(df==u(i)))); end;
            6215

           95826

           95808

       344


That is, of the 10 million data points, 198194 detected an edge. Of those, about half occurred after 50 data points, and half after 51 data points.

These data points are 10ns apart, so an error of 1 data point (10ns) seems like really good time resolution.

    $ mv booger.csv 1Mhz_square_wave_sampled_by_100MHz_beaglelogic.csv
    2016-11-30 14:21:46 [roseline@roseline-controller-2 ~] 
    $ 




Timing analysis of MPC/MHE PRU code (nov 30, 2016)
---------------------------------------------------

BB Victor (.122):

    sleping for .1 sec...
    Write mpc-data.txt or whatever...
    Done writing data file. Closing...
    Shutting down ...
    Quitting 'run' shell script...
    2016-11-30 14:23:25 [root@beaglebone /home/debian/BB_PRU_stuff/Integration-test/15-horizon-sweep/Ts5_T20_L10_S3] 
    # ./run 400


BB Yankee (BeagleLogic, .125):

    root@beaglebone:~# sigrok-cli -d beaglelogic --samples 10M -c samplerate=100M --channels P8_43,P8_44,P8_45,P8_46 -o mpcmhe_Ts5_T20_L10_S3_10M_samps_100MHz_rate.csv -O csv

     77M -rw-r--r-- 1 root root  77M Nov 30 14:27 mpcmhe_Ts5_T20_L10_S3_10M_samps_100MHz_rate.csv



NUC:



    $ scp root@10.42.0.125:/root/mpcmhe_Ts5_T20_L10_S3_10M_samps_100MHz_rate.csv .
    Debian GNU/Linux 8

BeagleBoard.org Debian Image 2016-04-10

Support/FAQ: http://elinux.org/Beagleboard:BeagleBoneBlack_Debian

default username:password is [debian:temppwd]

    mpcmhe_Ts5_T20_L10_S3_10M_samps_100MHz_rate.csv              100%   76MB  10.9MB/s   00:07    
    2016-11-30 14:27:59 [roseline@roseline-controller-2 ~] 
    $ 


    2016-11-30 14:27:59 [roseline@roseline-controller-2 ~] 
    $ head mpcmhe_Ts5_T20_L10_S3_10M_samps_100MHz_rate.csv 
    ; CSV, generated by libsigrok 0.4.0 on Wed Nov 30 14:26:57 2016
    ; Channels (4/8): P8_45, P8_46, P8_43, P8_44
    ; Samplerate: 100 MHz
    0,1,1,1
    0,1,1,1
    0,1,1,1
    0,1,1,1
    0,1,1,1
    0,1,1,1
    0,1,1,1
    2016-11-30 14:29:41 [roseline@roseline-controller-2 ~] 
    $ 



Matlab analysis on NUC:


    mpcmhe_beaglelogic_timing_analysis.m

    mpcmhe_beaglelogic_import_SCRIPT.m

    mpcmhe_Ts5_T20_L10_S3_10M_samps_100MHz_rate.csv



Yankee 

    P8_43 <=> Victor PWM to motor driver
    P8_44 <=> AIN1 on motor driver
    P8_45 <=> AIN2 on motor driver
    P8_46 <=> EQEP channel A


I low-pass-filtered the PWM signal with a moving-average filter, averaging 10^4 samples of the pwm. This readily shows where the PWM duty-cycle changes.

From there, we can get very good bounds on precisely when the PWM changes duty cycle -- does it happen at true sample times, or is there much jitter?

Also, does it happen at the same times as the AIN1&2 change? That's very important.

Also, can verify that the AIN1&2 both change at precisely the same time. (Important for not thrashing the motor or braking inadvertantly.)



Timing in the PID C controller (Dec 1, 2016)
-----------------------------------------------

On BB with motor:

    Done writing data file. Closing...
    2016-12-01 16:27:58 [root@beaglebone /home/debian/BB_PRU_stuff/Integration-test/10-PID/20160928] 
    # echo 1 > /sys/devices/ocp.3/pwm_test_P8_34.12/run && ./main 1 .5 200


On BL:

    root@beaglebone:/home/debian# sigrok-cli -d beaglelogic --samples 10M -c samplerate=100M --channels P8_43,P8_44,P8_45,P8_46 -o pid-c.sr 
    root@beaglebone:/home/debian# 


On NUC: import and convert to CSV (faster  on NUC)


    2016-12-01 16:29:14 [roseline@roseline-controller-2 ~] 
    $ scp root@10.42.0.125:/home/debian/pid-c.sr .
    Debian GNU/Linux 8

    BeagleBoard.org Debian Image 2016-04-10

    Support/FAQ: http://elinux.org/Beagleboard:BeagleBoneBlack_Debian

    default username:password is [debian:temppwd]

    pid-c.sr                                                                                                                                                     100%   30KB  30.4KB/s   00:00    
    2016-12-01 16:29:31 [roseline@roseline-controller-2 ~] 



    2016-12-01 16:29:35 [roseline@roseline-controller-2 ~] 
    $ sigrok-cli -i pid-c.sr -o pid-c.csv -O csv


In Matlab

    4.0K -rw-rw-r--   1 roseline roseline 1020 Dec  1 14:06 mpcmhe_beaglelogic_timing_analysis.m




Note: this PID controller actually uses the send_single_voltage() -- so it uses the PRU. 



NOTE: if the PRU code is running, it MAY be writing a PWM value to the registers, if you left the PRU running! 

Arg, the python rot-inv-pend-v2.py actually uses a different set of GPIOs, since the PRU uses like P9_38 etc, whereas rot-inv-pend uses P8_44 etc.

Another complicating factor is that Python's Adafruit_BBIO PWM.start('P8_34') and stop('P8_34') load and unload the bone_pwm_P8_34 DTO, which screws up my PRU code.


When I run hw_init.sh, it turns on the pwm. If I turn it off, then the PRU code doesn't cmd any pwm. I think there's a conflict btwn who's commanding the PWM.

Perhaps best to just make a new set of tests that don't involve physical hardware, maybe we can have the PRU script drive one set of pwm & gpio and the python script drive a different set. Doing it simultaneously would let us watch as we crank up the "other" cpu loads.

