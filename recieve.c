/*
*/

#define F_CPU 100000L
#include <avr/io.h>
#include <util/delay.h>
/* #include <avr/interrupt.h> */

#define N_TIMES 10

/* Defino los I/O */
#define RELE  (1 << PD0)
#define LED   (1 << PD7)
#define INPUT (1 << PB1)

/* Sensar pulsador */
#define PULL  PINB & INPUT

/* Operaciones del LED */
#define ON    PORTD |=  LED
#define OFF   PORTD &= ~LED

/* Operaciones del RELE */
#define OPEN  PORTD |=  RELE
#define CLOSE PORTD &= ~RELE

void startup (){
	/*Configura como salida RELE y LED INDICADOR*/
	DDRD = RELE | LED;/* (1 << PD1) | (1 << PD0); */
	DDRB  = 0x00; /* Configura como entrada PB0: ~(1 << PB0) */

	PORTB = 0xFF;
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
	_delay_ms(time);
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
	blink(3, 10);
	while(1){
//		_delay_ms(15);
		if(PULL){
			blink(4, 500);
//			open();
			ON;
		}else{
			OFF;	
		}
	}
	return 0;
}

