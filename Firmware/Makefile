CC = avr-gcc
MMCU = atmega8
CFLAGS = -I. -Os -mmcu=$(MMCU)a

SRC = main.c \
timer_conf.c \
spi_conf.c \
rh_rf95.c

all: main.hex

main.hex: main
	avr-objcopy -j .text -j .data -O ihex main main.hex

main: $(SRC)

clean:
	rm main main.hex *.o