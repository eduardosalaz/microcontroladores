/*
 * INT.c
 *
 * Created: 21/10/2021 10:11:23 a. m.
 * Author : GC-PC
 */ 
#include <avr/io.h>
#define F_CPU 10000000UL// 1Mhz
#include <avr/interrupt.h>
#include <util/delay.h>
//Etiquetas
//--Inputs
#define BUT0 PIND2
//--Outputs
#define LED0 PORTB0
#define LED1 PORTB1
#define LED2 PORTB2
#define LED3 PORTB3
#define LEDS PORTB

volatile uint8_t val;
uint8_t LIBRE[4] = {0b0000001, 0b0000010, 0b0000100, 0b0001000}; 
uint8_t LIBRE2[4] = {0b0001111, 0b0000111, 0b0000011, 0b0000001};


//Funciones
void init_ports(void);
void init_interrupt(void);
void init_timer0(void); //timer
void timer0_on(void);
void timer0_off(void);
int main(void)
{
    cli();
    init_ports();
    init_interrupt();
	init_timer0();
	timer0_on();
    sei();
	val = 0;
	uint8_t counter = 0;
    while (1) 
    {
		switch(val){
			case 0:
				for (uint8_t i = 0; i<4;i++)
				{
					if (TCNT0 == 97)//0.1s
					{
						counter++;
						TCNT0 = 0;
						if (counter == 10)
						{
							PORTB = LIBRE[i];
							counter = 0;
						}
					}
				}
				break;
			case 1:
				for (uint8_t i = 0; i<4;i++)
				{
					if (TCNT0 == 97)//0.1s
					{
						counter++;
						TCNT0 = 0;
						if (counter == 10)
						{
							PORTB = LIBRE2[i];
							counter = 0;
						}
					}
				}
				break;
			default:;
		}
	}
}
//Funciones
void init_ports(void)
{
//--Inputs
    DDRD &= ~_BV(BUT0);
    PORTD |=  _BV(BUT0);
//--Outputs
    DDRB |=  _BV(LED0) | _BV(LED1) | _BV(LED2) | _BV(LED3);
    LEDS &= ~_BV(LED0) | _BV(LED1) | _BV(LED2) | _BV(LED3);
}
void init_interrupt(void)
{
//--External Interrupt Control Register
//----INT0 LOW LEVEL
    EICRA &= ~_BV(ISC00);
    EICRA &= ~_BV(ISC01);
//--External Interrupt Mask Register
    //----INT0 ENABLE
    EIMSK |=  _BV(INT0);
}
ISR (INT0_vect)
{
	if (val == 1)
	{
		val = 0;
	}else{	
	    val = 1;
	}
}
void init_timer0(void)
{
	TCCR0A &= ~_BV(WGM01) | _BV(WGM00);
	TCCR0B &= ~_BV(WGM02);
}
void timer0_on(void)
{
	TCNT0 = 0; //variable contador
	TCCR0B |=  _BV(CS02) | _BV(CS00);
	TCCR0B &= ~_BV(CS01);
}
void timer0_off(void)
{
	TCCR0B &= ~_BV(CS02) | _BV(CS01) | _BV(CS00); //detenido
}