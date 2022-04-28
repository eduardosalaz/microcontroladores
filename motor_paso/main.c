/*
* motorpap.c
*
* Created: 07/10/2021 11:06:33 a. m.
* Author : estef
*/
#include <avr/io.h>
#define F_CPU 1000000UL //1Mhz
#include <util/delay.h>
#include <stdbool.h> // para booleanos#define BOTON PIND0
#define BUTTONS PIND//Pines
#define BUTON PIND0
#define OUT_A PORTB0
#define OUT_B PORTB1
#define OUT_C PORTB2
#define OUT_D PORTB3//Macros
#define OUT_A_ON PORTB |= _BV(OUT_A)
#define OUT_A_OFF PORTB &= ~_BV(OUT_A)
#define OUT_B_ON PORTB |= _BV(OUT_B)
#define OUT_B_OFF PORTB &= ~_BV(OUT_B)
#define OUT_C_ON PORTB |= _BV(OUT_C)
#define OUT_C_OFF PORTB &= ~_BV(OUT_C)
#define OUT_D_ON PORTB |= _BV(OUT_D)
#define OUT_D_OFF PORTB &= ~_BV(OUT_D)
const int TIME = 2000;//Estados
// enum cadena {elementos} elemento_de_cadena
enum states {s0,s1,s2,s3} state;
void init_ports(void);
bool presionado(char boton);
int main(void)
{
	init_ports();
	state = s0;
	while (1)
	{
		if(!(presionado(BUTON)))	{
			switch(state){
				case s0:
				OUT_A_ON;
				OUT_B_OFF;
				OUT_C_OFF;
				OUT_D_ON;
				_delay_ms(TIME);
				state = s3;
				break;
				case s1:
				OUT_A_ON;
				OUT_B_ON;
				OUT_C_OFF;
				OUT_D_OFF;
				_delay_ms(TIME);
				state = s0;
				break;
				case s2:
				OUT_A_OFF;
				OUT_B_ON;
				OUT_C_ON;
				OUT_D_OFF;
				_delay_ms(TIME);
				state = s1;
				break;
				case s3:
				OUT_A_OFF;
				OUT_B_OFF;
				OUT_C_ON;
				OUT_D_ON;
				_delay_ms(TIME);
				state = s2;
				break;
			}
			}else{
			//s0 s1 s2 s3            state = s0;
			switch(state){
				case s0:
				OUT_A_ON;
				OUT_B_OFF;
				OUT_C_OFF;
				OUT_D_ON;
				_delay_ms(TIME);
				state = s1;
				break;
				case s1:
				OUT_A_ON;
				OUT_B_ON;
				OUT_C_OFF;
				OUT_D_OFF;
				_delay_ms(TIME);
				state = s2;
				break;
				case s2:
				OUT_A_OFF;
				OUT_B_ON;
				OUT_C_ON;
				OUT_D_OFF;
				_delay_ms(TIME);
				state = s3;
				break;
				case s3:
				OUT_A_OFF;
				OUT_B_OFF;
				OUT_C_ON;
				OUT_D_ON;
				_delay_ms(TIME);
				state = s0;
				break;
			}
		}
	}
}
void init_ports(void){
	//entrada
	DDRD &= ~((1<<BUTON) | (1<<BUTON));
	PORTD |= (1<<BUTON) | (1<<BUTON);
	//Salidas
	DDRB |= _BV(OUT_A) | _BV(OUT_B) | _BV(OUT_C) | _BV(OUT_D);
}
	
bool presionado(char boton){
	if (bit_is_clear(BUTTONS, boton))
	{
		_delay_ms(35);
		if (bit_is_clear(BUTTONS, boton))
		{
			return true;
		}
	}
	return false;
}

