/*************************************************************************
 * LLENAR ESTE ESPACIO CON LOS SIGUIENTES DATOS:                         *
 *                                                                       *
 * Nombre, Hora, Día, Clase, #de lista, #de Equipo                       *
 * Dispositivo:                                                           *
 * Rev:                                                                  *
 * Propósito de la actividad:                                            *
 *                                                                       *
 *                                                         Fecha:        *
 ************************************************************************/
/*atmega328P PIN - OUT*/
/*       PIN - OUT
         atmega328P
          -------                                
    PC6  |1     28| PC5                         
    PD0  |2     27| PC4                          
    PD1  |3     26| PC3                          
    PD2  |4     25| PC2                          
    PD3  |5     24| PC1
    PD4  |6     23| PC0                          
    VCC  |7     22| GND                         
    GND  |8     21| AREF                          
    PB6  |9     20| AVCC                          
    PB7  |10    19| PB5                          
    PD5  |11    18| PB4                          
    PD6  |12    17| PB3
    PD7  |13    16| PB2
    PB0  |14    15| PB1
          --------
*/
/*atmega328P PIN FUNCTIONS*/
 /*
 atmega328P PIN FUNCTIONS
 pin   function              name    pin     function              name
 1     !RESET/PCINT14        PC6     15      PCINT1/PWM            PB1
 2     RxD/PCINT16           PD0     16      PCINT2/PWM/SS         PB2
 3     TxD/PCINT17           PD1     17      PCINT3/PWM/MOSI       PB3
 4     INT0/PCINT18          PD2     18      PCINT4/PWM/MISO       PB4
 5     INT1/PCINT19/PWM      PD3     19      PCINT5/SCK            PB5
 6     PCINT20               PD4     20      ANALOG VCC            AVCC
 7     +5v                   VCC     21      ANALOG REFERENCE      AREF
 8     GND                   GND     22      GND                   GND
 9     XTAL1/PCINT6          PB6     23      PCINT8/ADC0           PC0
 10    XTAL2/PCINT7          PB7     24      PCINT9/ADC1           PC1
 11    PCINT21/PWM           PD5     25      PCINT10/ADC2          PC2
 12    PCINT22/PWM/AIN0      PD6     26      PCINT11/ADC3          PC3
 13    PCINT23/AIN1          PD7     27      PCINT12/ADC4/SDA      PC4
 14    PCINT0/AIN1           PB0     28      PCINT13/ADC5/SCL      PC5
 */
 //Librerías************************************************************
#include <avr/io.h>//se incluyen las librerías de E/S del AVR atmega328P
#include <avr/interrupt.h>
//Macros (constantes)***************************************************
#define F_CPU 1000000UL //1 Mhz
#define SEGMA PORTD6  //definiciones
#define SEGMB PORTD5
#define SEGMC PORTD4
#define SEGMD PORTD3
#define SEGME PORTD2
#define SEGMF PORTD1
#define SEGMG PORTD0
#define LED1 PORTB0

#define LED1_ON   PORTB |=  _BV(LED1)  //macros
#define LED1_OFF  PORTB &=~ _BV(LED1)
#define LED1_TGLE PORTB ^=  _BV(LED1)
//Variables globales del programa **************************************
int primeravez = 1;
//Funciones*************************************************************
//Declaracion de Funciones**********************************************
void init_ports(void); // Función para inicializar por puertos
void ADC_init(void);
void ADC_on(void);
void init_timer0(void); //timer
void timer0_on(void);
void timer0_off(void);
//Programa principal****************************************************
int main(void)
{
    //Inicialización
    cli(); // clear
    init_ports(); // va hacía la inicialización
	init_timer0();
	timer0_on();
    ADC_init();
    sei(); //setea
    ADC_on(); //lo prende
    //Ejecución
    while (1)
    {
		uint8_t counter = 0;
		while (1)
		{
			if (TCNT0 == 97)//0.1s
			{
				counter++;
				TCNT0 = 0;
				if (counter == 10)
				{
					if (primeravez ==1)
					{
						LED1_ON;
						primeravez = 0;
					}else{
						LED1_OFF;
						primeravez = 1;
					}
					counter = 0;
				}
			}
		}    
    } // END loop infinito
} // END MAIN
//**********************************************************************
//Definición de funciónes
//**********************************************************************
//**********************************************************************
//initialize_ports : inicializa los puertos de entrada o salida
//***********************************************************************
void init_ports(void)
{
	DDRB  |=  _BV(LED1);
	DDRD  |= _BV(SEGMA) | _BV(SEGMB) | _BV(SEGMC) | _BV(SEGMD) | _BV(SEGME) | _BV(SEGMF) | _BV(SEGMG);    //salidas
	PORTD &= ~(_BV(SEGMA) | _BV(SEGMB) | _BV(SEGMC) | _BV(SEGMD) | _BV(SEGME) | _BV(SEGMF) | _BV(SEGMG));
	PORTB &= ~_BV(LED1);
}
void ADC_init(void)
{
    
    //Avcc como pin de referencia
    ADMUX &=~ (1<<REFS1); //0 en refs1  x and false = false, 0 
    ADMUX |=  (1<<REFS0); // 1 en refs0 x or true = true, 1
    
    //Ajustar a 8 bits
    ADMUX |= (1<<ADLAR); // son 8 bits
    
    // Escoger el PIN a leer ADC5 0101
    ADMUX &=~ (1<<MUX3); //  0
    ADMUX |=  (1<<MUX2); //  1
    ADMUX &=~ (1<<MUX1); //  0
    ADMUX |=  (1<<MUX0); // 1
    
    //Freerunning
    ADCSRA |= (1<<ADATE);
    
    //Enable interrupt
    ADCSRA |= (1<<ADIE);
    //velocidad de muestreo
    // 1 MHz clock / 8 = 125 kHz ADC clock debe de estar entre 50 - 200Khz
    ADCSRA &=~ (1<<ADPS0);
    ADCSRA |= (1<<ADPS1);
    ADCSRA |= (1<<ADPS2); 
}
void ADC_on(void)
{
    //Encendemos el ADC
    ADCSRA |= (1<<ADEN);
    // Iniciar la conversión
    ADCSRA |= (1 << ADSC);  
}
ISR(ADC_vect)
{
	unsigned char x;
	x = ADCH;
	if (x >= 0 && x <=50)
	{
		PORTD = 0x0e; // una L
	}else if (x > 50 && x <= 100)
	{
		PORTD = 0x57; // una K AFGEC
		//ACEFG
		//1010111
	}else if (x > 100 && x <=255)
	{
		PORTD = 0x37; // una H
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