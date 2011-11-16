all: recieve send
	@echo "Done"

recieve: recieve.c
	avr-gcc -O -mmcu=atmega8 -Wall -pedantic -o recieve.bin recieve.c
	avr-objcopy -j .text -O ihex recieve.bin recieve.hex
	@rm -f recieve.bin

program: recieve.hex
	sudo avrdude -c usbtiny -p m8 -U f:w:recieve.hex
	@rm -f recieve.hex

send:
	gcc send.c -O -o send
	@chmod 777 send
	@chmod +s send

clean:
	@rm -f recieve.hex recieve.bin send

run:
	python bot.py 
