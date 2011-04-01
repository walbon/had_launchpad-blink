#PREFIX=/usr/local/msp430-gcc-4.4.3
PREFIX=/opt/msp430-gcc-4.4.5
CC=$(PREFIX)/bin/msp430-gcc

#CFLAGS= -Wall -g -mmcu=msp430x2012
CFLAGS=-Os -Wall -g -mmcu=msp430x2012
#CFLAGS=-Os -Wall -g -I/opt/msp430-gcc-4.4.5/msp430/include

LOBJS=reg.o morse.o
POBJS=main.o
TOBJS=test.o
#OBJS=main.o


all: $(LOBJS) $(POBJS)
	$(CC) $(CFLAGS) $(EXTRA) -o main.elf $(LOBJS) $(POBJS)

console: CC=gcc
console: CFLAGS=""
console : $(LOBJS) $(TOBJS)
	gcc  -o test $(LOBJS) $(TOBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -fr main.elf test $(LOBJS) $(POBJS) $(TOBJS)
