/*
 * recieve.c
 *    "TeraBot Atmega88 brain fuctions"
 *    Copyleft -- Manuel Soldini <manuel.soldini@gmail.com>
 * 
 * See GPL v3 licence for more info.
 *
 */

#include <avr/io.h>
#include <util/delay.h>

/* Higher level defines*/
#define OR ||
#define AND &&
#define NOT !

/* Define I/O */
#define RELAY  (1 << PD7)
#define LED   (1 << PD0)
#define PULSE_INPUT (1 << PB1)
#define LIGHT_INPUT (1 << PB5)

/* Logic defines */
#define PARPORT !(PINB & PULSE_INPUT)
#define HAND    (PINB & LIGHT_INPUT)

/* LED Operations */
#define OFF    PORTD |=  LED
#define ON     PORTD &= ~LED

/* RELAY Operations */
#define OPEN  PORTD |=  RELAY
#define CLOSE PORTD &= ~RELAY

void startup (){
    /* Configure RELAY and LED pins as output */
    DDRD = RELAY | LED; /* (1 << PD1) | (1 << PD0); */
    DDRB  = 0x00; /* Configure port B as input */

    PORTB = 0xFF; /* Turn on pull-ups */
    PORTD = 0x00;  /* Turn on led and off relay on port D */
}

void blink(uint8_t times, int time){
    uint8_t count = 0;
    while(count++ < times){
        OFF;
        _delay_ms(time);
        ON;
        _delay_ms(time);
    }
}

void open(){
    OPEN;
    blink(2, 600);
    CLOSE;
    blink(2, 600);
}

int main(){
    startup();
    blink(3, 1000);
    while(1){
    	if(PARPORT OR HAND){
    		open();
    	}else{
            _delay_ms(5);
    	}
    }
    return 0;
}

