CC=msp430-gcc

#CFLAGS=-Os -Wall -g -I/opt/msp430-gcc-4.4.5/msp430/include -mmcu=msp430x20x2
CFLAGS=-Os -Wall -g -I/opt/msp430-gcc-4.4.5/msp430/include

OBJS=main.o


all: $(OBJS)
	$(CC) $(CFLAGS) $(EXTRA) -o main.elf $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -fr main.elf $(OBJS)
