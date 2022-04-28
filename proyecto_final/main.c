#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#define SEG1A PORTD6 // defino las salidas pero realmente no se usan
#define SEG1B PORTD5
#define SEG1C PORTD4
#define SEG1D PORTD3
#define SEG1E PORTD2
#define SEG1F PORTD1
#define SEG1G PORTD0
#define SEG2A PORTB6
#define SEG2B PORTB5
#define SEG2C PORTB4
#define SEG2D PORTB3
#define SEG2E PORTB2
#define SEG2F PORTB1
#define SEG2G PORTB0

#define MODO PINB7 // boton del modo de la maquina
#define CAMBIO PIND7 //subir o bajar

// variables
enum states {s0,s1,s2,s3};
volatile enum states state;
volatile uint8_t disp = 0;
volatile uint8_t num1;
volatile uint8_t digito1;
volatile uint8_t digito2;
volatile unsigned char x;
// funciones
void init_ports(void);
void init_interrupt(void);
void init_timer0(void);
void timer0_on(void);
void timer0_off(void);
void ADC_init(void);
void ADC_on(void);
int map(long x, long in_min, long in_max, long out_min, long out_max); // mapear rangos
int seleccionarNumero(uint8_t num);

int main(void) {
	cli();
	init_ports();
	init_timer0();
	timer0_on();
	init_interrupt();
	ADC_init();
	sei();
	state = s0;
	uint8_t counter = 0;
	while (1) {
		switch (state) {
			case s0:
			if (disp > 99) {
				disp = 0;
			}
			uint8_t numero1 = disp;
			uint8_t digito1 = numero1 % 10;
			numero1 = numero1 / 10;
			uint8_t digito2 = numero1 % 10;
			int mostrar1 = seleccionarNumero(digito1);
			int mostrar2 = seleccionarNumero(digito2);
			PORTB = mostrar1;
			PORTD = mostrar2;
			if (TCNT0 == 97) //0.1s
			{
				counter++;
				TCNT0 = 0;
				if (counter == 10) {
					disp++;
					counter = 0;
				}
			}
			break;
			case s1:
			numero1 = disp;
			digito1 = numero1 % 10;
			numero1 = numero1 / 10;
			digito2 = numero1 % 10;
			mostrar1 = seleccionarNumero(digito1);
			mostrar2 = seleccionarNumero(digito2);
			PORTB = mostrar1;
			PORTD = mostrar2;
			break;
			case s2:
			numero1 = disp;
			digito1 = numero1 % 10;
			numero1 = numero1 / 10;
			digito2 = numero1 % 10;
			mostrar1 = seleccionarNumero(digito1);
			mostrar2 = seleccionarNumero(digito2);
			PORTB = mostrar1;
			PORTD = mostrar2;
			break;
			case s3:
			ADC_on();
			uint8_t valor = map(x, 0, 255, 0, 99);
			uint8_t numr1 = valor;
			uint8_t digit1 = numr1 % 10;
			numr1 = numr1 / 10;
			uint8_t digit2 = numr1 % 10;
			uint8_t most1 = seleccionarNumero(digit1);
			uint8_t most2 = seleccionarNumero(digit2);
			PORTB = most1;
			PORTD = most2;
			break;
			default:;
		}
	}
}

void init_ports(void) {
	// inputs
	DDRB &= ~(1 << MODO);
	PORTB |= (1 << MODO);
	DDRD &= ~(1 << CAMBIO);
	PORTD |= (1 << CAMBIO);
	// outputs
	DDRD |= 0b1111111;
	PORTD &= 0b0000000;
	DDRB |= 0b1111111;
	PORTB &= 0b0000000;
	DDRC |= _BV(PORTC0);
	PORTC &= ~_BV(PORTC0);
}

void init_timer0(void) {
	TCCR0A &= ~_BV(WGM01) | _BV(WGM00);
	TCCR0B &= ~_BV(WGM02);
}

void timer0_on(void) {
	TCNT0 = 0;
	TCCR0B |= _BV(CS02) | _BV(CS00);
	TCCR0B &= ~_BV(CS01);
}

void timer0_off(void) {
	TCCR0B &= ~_BV(CS02) | _BV(CS01) | _BV(CS00); //detenido
}

int seleccionarNumero(uint8_t num) {
	uint8_t DISPLAYSEG[10] = {0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B};
	if (num < 0 || num > 9) {
		return DISPLAYSEG[0];
		} else {
		return DISPLAYSEG[num];
	}
}

void init_interrupt(void) {
	PCICR |= _BV(PCIE0);
	PCMSK0 |= _BV(PCINT7); //pb7
	PCICR |= _BV(PCIE2);
	PCMSK2 |= _BV(PCINT23); // pd7
}

ISR(PCINT0_vect) {
	if (bit_is_clear(PINB, MODO)) {
		_delay_ms(150);
		if (bit_is_clear(PINB, MODO)) {
			switch (state) {
				case s0:
				state = s1;
				break;
				case s1:
				state = s2;
				break;
				case s2:
				state = s3;
				break;
				case s3:
				state = s0;
				break;
				default:;
			}
		}
	}
}

ISR(PCINT2_vect) {
	if (bit_is_clear(PIND, CAMBIO)) {
		_delay_ms(150);
		if (bit_is_clear(PIND, CAMBIO)) {
			if (state == s1) {
				if (disp < 99) {
					disp++;
					} else if (disp == 99) {
					disp = 99;
				}
				} else if (state == s2) {
				if (disp > 0) {
					disp--;
					} else if (disp == 0) {
					disp = 0;
				}
			}
		}
	}
}

void ADC_init(void) {
	ADMUX &= ~(1 << REFS1);
	ADMUX |= (1 << REFS0);
	ADMUX |= (1 << ADLAR);
	ADMUX &= ~(1 << MUX3);
	ADMUX |= (1 << MUX2);
	ADMUX &= ~(1 << MUX1);
	ADMUX |= (1 << MUX0); // c5
	ADCSRA |= (1 << ADATE);
	ADCSRA |= (1 << ADIE);
	ADCSRA &= ~(1 << ADPS0);
	ADCSRA |= (1 << ADPS1);
	ADCSRA |= (1 << ADPS2);
}

void ADC_on(void) {
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADSC);
}

ISR(ADC_vect) {
	x = ADCH;
}

int map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}