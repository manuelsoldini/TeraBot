/*
*/

#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
/* #include <avr/interrupt.h> */

#define N_TIMES 10

/* Defino los I/O */
#define RELE  (1 << PD0)
#define LED   (1 << PD1)
#define INPUT (1 << PB0)

/* Sensar pulsador */
#define PULL  ~(0xFF) & INPUT

/* Operaciones del LED */
#define ON    PORTD |=  LED
#define OFF   PORTD &= ~LED

/* Operaciones del RELE */
#define OPEN  PORTD |=  RELE
#define CLOSE PORTD &= ~RELE

void startup (){
	/*Configura como salida RELE y LED INDICADOR*/
	DDRD = RELE | LED;/* (1 << PD1) | (1 << PD0); */
	DDRB  = ~INPUT; /* Configura como entrada PB0: ~(1 << PB0) */

	PORTB = INPUT;
	PORTD = 0x00;  /* apago todo en el puerto D */
}

uint8_t bounce(){
	uint16_t count = 0;
    uint8_t pos = 0, neg = 0;
	while(count < N_TIMES){
		if(PULL){
			pos += 1;
		}else{
            neg += 1;
        }
        _delay_ms(10);
		count++;
	}
	return (pos > neg) ? 1 : 0;
}

void blink(uint8_t times, uint16_t time){
    uint8_t count = 0;
    while(count < times){
        ON;
        _delay_ms(time);
        OFF;
        count++;
    }
}

void open(){
    OPEN;
    blink(1, 300);
    CLOSE;
    blink(4, 300);
}

int main(){
    startup();
    blink(3, 600);
	while(1){
		_delay_ms(15);
        if(PULL){
            if(bounce()){
                open();
            }
        }
	}
	return 0;
}

