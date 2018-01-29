

CC=gcc
CFLAGS=-g -Wall -Werror -lstdc++ -std=gnu99 -lm
TENSCALC=$(shell echo tmpC_TS_*.c)
TENSCALCO=$(TENSCALC:.c=.o)

# pthread ?
# -Werror : I'd rather see all the warnings and 

.PHONY: all clean

all: main

main : main.o $(TENSCALCO) jpp-pru-lib.o util-jpp.o jpp-pru-lib.bin
	@echo "=========================="
	@echo "Making main executable ..."
	$(CC) $(CFLAGS) -lprussdrv -lrt main.o $(TENSCALCO) jpp-pru-lib.o util-jpp.o -o $@

main.o : main.c 
	$(CC) $(CFLAGS) -Wno-implicit-function-declaration -Wno-unused-variable -c $<

$(TENSCALCO) : $(TENSCALC)
	@echo "=========================="
	@echo "Compiling tenscalc lib ..."
	date
	$(CC) $(CFLAGS) -Wno-unused-variable -Wno-unused-result -O1 -DNDEBUG -lrt -c $<
	date

jpp-pru-lib.bin : jpp-pru-lib.p jpp-pru-lib.hp 
	@echo "=========================="
	@echo "Using pasm to assemble .p file into .bin file ..."
	pasm -b $<

jpp-pru-lib.o : jpp-pru-lib.c jpp-pru-lib.h jpp-pru-lib.hp 
	@echo "=========================="
	@echo "building PRU C library..."
	$(CC) $(CFLAGS) -lprussdrv -c $<

util-jpp.o : util-jpp.c
	@echo "=========================="
	@echo "building util-jpp library..."
	$(CC) $(CFLAGS) -lrt -c $<



clean:
	rm *.o *.bin main