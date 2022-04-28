 /* ej4_display.c
 *
 * Created: 24/08/2021 03:12:20 p. m.
 * Author : GC-PC
 */
 #define F_CPU 1000000UL
 #include <avr/io.h>
 #include <util/delay.h>
 #define PUSHB0 PIND0
 #define PUSHB1 PIND1
 #define BUTTONS PIND
 #define SEGA PORTD1
 #define SEGB PORTD2
 #define SEGC PORTD3
 #define SEGD PORTD4
 #define SEGE PORTD5
 #define SEGF PORTD6
 #define SEGG PORTD7
 #define LED1 PORTC0
                    // 0   1    2    3    4    5     6   7    8     9
uint8_t DISPLAY[10] = {0x01,0x4f,0x12,0x06,0x4c,0x24,0x20,0x0f,0x00,0x04};
//0 a 255
void init_ports(void);
int main(void)
{
	init_ports();
	while (1)
	{
		if(!(bit_is_clear(BUTTONS, PUSHB0) && bit_is_clear(BUTTONS,PUSHB1)))
 		{
			for(uint8_t i = 0;i < 10;i++){
				PORTB = DISPLAY[i];
				/*if(bit_is_clear(SWITCHES,PUSHB0)) i--; */ // con un break tambien se puede
				_delay_ms(500);
				if (bit_is_clear(BUTTONS, PUSHB0)){
					PONER BREAK
					}
				}
				if (bit_is_clear(BUTTONS,PUSHB1))
				{
					for(uint8_t i = 0;i < 10;i++){
						PORTB = DISPLAY[i];
						/*if(bit_is_clear(SWITCHES,PUSHB0)) i--; */ // con un break tambien se puede
						_delay_ms(1000);
					}
				}
			}
		}
			
			//tambien se puede con un while
			//si quieres cambiar de display por un anodo comun, niegas lo que tenga el array de DISPLAY
// 		}else{
// 			PORTC ^= _BV(LED1); //TOGGLE CON XOR
// 			_delay_ms(500);
// 		}
	}
 }
 void init_ports(void)
 {
	//salidas
	DDRB  |= (1<<SEGA)|(1<<SEGB)|(1<<SEGC)|(1<<SEGD)|(1<<SEGE)|(1<<SEGF)|(1<<SEGG);
	//DDRC |= _BV(LED1);
	//entradas
	DDRD &= ~((1<<PUSHB0) | (1<<PUSHB1));
	//pullup
	PORTD |= _BV(PUSHB0) | _BV(PUSHB1);
	
	//Declaro como entrada los pines
// 	PORTB |=  (1<<SW0)|(1<<SW1)|(1<<SW2);// Activo Pull - UP
// 	PORTB &= ~(1<<SW3)|(1<<SW4)|(1<<SW5);// Activo pull -down
// 	//Outputs
// 	DDRD  |=  (1<<LED0)|(1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<LED4)|(1<<LED5); //Declaro Salidas
// 	PORTD &= ~(1<<LED0)|(1<<LED1)|(1<<LED2);//Apagadas Source
// 	PORTD |=  (1<<LED3)|(1<<LED4)|(1<<LED5);//Apagadas Sink
}