TARGET = recieve
MMCU = atmega88
F_CPU = 1000000UL
SUDOER = sudo
#If rules.d is well configure SUDOER should be 
#SUDOER = 


CC = avr-gcc
CFLAGS = -Os -g
SRC = $(shell find .  -name '*.[c]')
INC = $(shell find .  -name '*.[h]')

ifeq ($(MMCU), atmega8)
	TARGET_P = m8
	HFUSE = 0xd9
	LFUSE = 0xe4
	MMCU_N = 0
else
ifeq ($(MMCU), atmega88)
	TARGET_P = m88
	HFUSE = 0xdf
	LFUSE = 0xe2
	MMCU_N = 1
else
	$(error Target no soportado)
endif
endif

CDEFINES = -DMMCU=$(MMCU_N) -DF_CPU=$(F_CPU)


all: hex

bin: $(SRC) $(INC)
	$(CC) $(CDEFINES) -mmcu=$(MMCU) $(CFLAGS) -o $(TARGET).bin $(SRC)
	avr-size -d $(TARGET).bin

hex: bin
	avr-objcopy -j .text -O ihex $(TARGET).bin $(TARGET).hex

program: hex
	$(SUDOER) avrdude -c usbtiny -p $(TARGET_P) -F -U f:w:$(TARGET).hex

program_dw: bin
	avarice -w -j usb --erase --program --file $(TARGET).bin

fuse:
	$(SUDOER) avrdude -c usbtiny -p $(TARGET_P) -F -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m

asm: $(SRC) $(INC)
	$(CC) $(CDEFINES) -mmcu=$(MMCU) $(CFLAGS) -S -o $(TARGET).s $<

clean:
	rm -rf $(TARGET).hex $(TARGET).bin $(TARGET).s

