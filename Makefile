MICRO = 88 


all: recieve send
	@echo "Done"

recieve: recieve.c
	avr-gcc -O -mmcu=atmega$(MICRO) -Wall -pedantic -o recieve.bin recieve.c
	avr-objcopy -j .text -O ihex recieve.bin recieve.hex
	@rm -f recieve.bin

program: recieve.hex
	sudo avrdude -c usbtiny -p m$(MICRO) -F -U f:w:recieve.hex
	@rm -f recieve.hex

fuses:
	sudo avrdude -c usbtiny -p m$(MICRO) -F -U lfuse:w:0x62:m -U hfuse:w:0xdf:m #-U efuse:w:0xf9:m

read:
	@sudo avrdude -c usbtiny -p m$(MICRO) -F -U lfuse:r:lfuse:m -U hfuse:r:hfuse:m
	@echo "lfuse"
	@cat lfuse
	@echo "hfuse"
	@cat hfuse
	@rm -f *fuse

send:
	gcc send.c -O2 -o send
	@chmod 777 send
	@chmod +s send

clean:
	@rm -f recieve.hex recieve.bin send

run:
	python bot.py 
