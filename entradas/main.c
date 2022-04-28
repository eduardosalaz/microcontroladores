 /* EJ2_Puerto_paralelo.c
 *
 * Created: 24/08/2021 03:12:20 p. m.
 * Author : GC-PC
 */
 #include <avr/io.h>
 #define F_CPU 1000000UL
 #define SW0 PINB0
 #define SW1 PINB1
 #define SW2 PINB2
 #define SW3 PINB3
 #define SW4 PINB4
 #define SW5 PINB5
 
 #define LED0 PORTD0
 #define LED1 PORTD1
 #define LED2 PORTD2
 #define LED3 PORTD3
 #define LED4 PORTD4
 #define LED5 PORTD5

void init_ports(void);
int main(void)
{
	init_ports();
	while (1)
	{
		//SW0
		 if ((PINB & 0b00000001) == 0)//Leer pull-up
		{
			PORTD |= (1<<LED0);
		}
		else
		{
			PORTD &=~ (1<<LED0);
		}
		
		//SW1
		if (bit_is_clear(PINB,SW1))//Leer pull-up
		{
			PORTD |= _BV(LED1); //Marco bit value HIGH
		}
		else
		{
			PORTD &=~ _BV(LED1); //Marco bit value LOW
		}
 
		 //SW2
		if (bit_is_clear(PINB, SW2)) //leer pull - up
		{
			PORTD |= (1<<LED2);
		}
		else
		{
			PORTD &=~ (1<<LED2);
		}
 
		//SW3
		if (bit_is_set(PINB,SW3))//Leer pull-down
		{
			 PORTD &=~ (1<<LED3); //Marco bit value
		}
		else
		{
			PORTD |= (1<<LED3); //Marco bit value
		}
		//SW4
		if (bit_is_set(PINB,SW4))//Leer pull-down
		{
			PORTD &=~ (1<<LED4); //Marco bit value
		}
		else
		{
			PORTD |= (1<<LED4); //Marco bit value
		}
		//SW5
		if (bit_is_set(PINB,SW5))//Leer pull-down
		{
			PORTD &=~ (1<<LED5); //Marco bit value
		}
		else
		{
			PORTD |= (1<<LED5); //Marco bit value
		}
	}
 }
 void init_ports(void)
 {
	//Inputs
	DDRB  &= ~(1<<SW0)|(1<<SW1)|(1<<SW2)|(1<<SW3)|(1<<SW4)|(1<<SW5);
	//Declaro como entrada los pines
	PORTB |=  (1<<SW0)|(1<<SW1)|(1<<SW2);// Activo Pull - UP
	PORTB &= ~(1<<SW3)|(1<<SW4)|(1<<SW5);// Activo pull -down
	//Outputs
	DDRD  |=  (1<<LED0)|(1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<LED4)|(1<<LED5); //Declaro Salidas
	PORTD &= ~(1<<LED0)|(1<<LED1)|(1<<LED2);//Apagadas Source
	PORTD |=  (1<<LED3)|(1<<LED4)|(1<<LED5);//Apagadas Sink
}