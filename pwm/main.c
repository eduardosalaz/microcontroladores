#include <avr/io.h>
#include <avr/interrupt.h>
void pwm_init(void);
int main(void)
{
	cli();
	DDRB |= (1<<DDRB);
	pwm_init();
	sei();
	while (1)
	{
	}
}
void pwm_init()
{
	//Modo CTC
	TCCR1A &=~_BV(WGM10);
	TCCR1A &=~_BV(WGM11);
	TCCR1B |= _BV(WGM12);
	TCCR1B &=~_BV(WGM13);
	
	// puse prescaler de 1
	TCCR1B &=~_BV(CS12); // 0 
	TCCR1B &=~ _BV(CS11); // 0
	TCCR1B |= _BV(CS10); // 1
	//Enable inteerupts
	TIMSK1 |= (1<<OCIE1A) | (1<<OCIE1B); // Habilita las dos
	//Definir periodo y duty cyle
	//T = fmcu / N * 2 * prescaler (1) = OCR1A
	//T = 1,000,000 /( N * 2 * 1) = N = 1,000,000 / 500 = 2000
	OCR1A   = 1000;                       // define el el periodo
	OCR1B   = 1;                       // Define el duty cycle 50%
}
ISR (TIMER1_COMPA_vect)
{
	PORTB |= (1<<PORTB5); //pone en alto cada 10khz
}
ISR (TIMER1_COMPB_vect)
{
	PORTB &=~(1<<PORTB5); //pone en bajo cada el TON
}