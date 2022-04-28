|/*
 * af2.c
 *
 * Created: 14-Sep-21 13:07:09
 * Author : Salazar
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL //1 MHz
#include <util/delay.h>
#include <stdbool.h> // para booleanos
//entradas
#define BUT0 PIND0
#define BUT1 PIND1
#define BUTTONS PIND
//salidas
#define LED0 PORTB6
#define LED1 PORTB5
#define LED2 PORTB4
#define LED3 PORTB3
#define LED4 PORTB2
#define LED5 PORTB1
#define LED6 PORTB0

// auto fantastico
uint8_t AUTO[12] = {0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20};
uint8_t LIBRE[2] = {0x78, 0x07};
void init_ports(void);
bool presionado(char boton);

int main(void)
{
	init_ports();
	uint8_t i, j;
    while (1) 
    {
		if( !presionado(BUT0) && !presionado(BUT1) ) // 0 0 
		{
			for(i=0;i<12;i++)
			{
				if( !presionado(BUT0) && !presionado(BUT1) ) // 0 0
				{
					PORTB = AUTO[i];
					_delay_ms(500);	
				}else if( !presionado(BUT0) && presionado(BUT1)){ // 0 1
					i--;
				}else if( presionado(BUT0) && !presionado(BUT1)){ // 1 0
					for(j=0;j<2;j++){
						PORTB = LIBRE[j];
						_delay_ms(100);
					}
				}else if( presionado(BUT0) && presionado(BUT1)){ // 1 1
					PORTB = 0x7F; // 1111111
				}
			}
		}else if( presionado(BUT0) && !presionado(BUT1)) // 1 0
		{
			for(j=0;j<2;j++){
				PORTB = LIBRE[j];
				_delay_ms(100);
			}
		}else if( presionado(BUT0) && presionado(BUT1)) // 1 1
		{
			PORTB = 0x7F;
		}
	}
}

void init_ports(){
	// entradas
	DDRD &= ~((1<<BUT0) | (1<<BUT1));
	PORTD |= (1<<BUT0) | (1<<BUT1);
	// salidas
	DDRB |= _BV(LED0) | _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4) | _BV(LED5) | _BV(LED6);
    PORTB &= ~(_BV(LED0) | _BV(LED1) | _BV(LED2) | _BV(LED3) | _BV(LED4) | _BV(LED5) | _BV(LED6));
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
