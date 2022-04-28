/****************************************************
 * LLENAR ESTE ESPACIO CON LOS SIGUIENTES DATOS:    *
 * Nombre: Eduardo Salazar Treviño                  *
 * Hora clase: M4                                   *
 * Día: Jueves                                      *
 * N° de lista: 28                                  *
 * N° de Equipo: 15                                 *
 * Dispositivo: ATMEGA328                           *
 * Rev: 1.0                                         *
 * Propósito de la actividad: Salidas               *
 *                                                  *
 *                                    Fecha: 19/8/21*
 ***************************************************/
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
 1     !RESET/PCINT14        PC6     15      PCINT1/OC1A           PB1
 2     RxD/PCINT16           PD0     16      PCINT2/OC1B/SS        PB2
 3     TxD/PCINT17           PD1     17      PCINT3/OC2A/MOSI      PB3
 4     INT0/PCINT18          PD2     18      PCINT4/MISO           PB4
 5     INT1/PCINT19/OC2B     PD3     19      PCINT5/SCK            PB5
 6     PCINT20               PD4     20      ANALOG VCC            AVCC
 7     +5v                   VCC     21      ANALOG REFERENCE      AREF
 8     GND                   GND     22      GND                   GND
 9     XTAL1/PCINT6          PB6     23      PCINT8/ADC0           PC0
 10    XTAL2/PCINT7          PB7     24      PCINT9/ADC1           PC1
 11    PCINT21/OC0B          PD5     25      PCINT10/ADC2          PC2
 12    PCINT22/OC0A/AIN0     PD6     26      PCINT11/ADC3          PC3
 13    PCINT23/AIN1          PD7     27      PCINT12/ADC4/SDA      PC4
 14    PCINT0/AIN1           PB0     28      PCINT13/ADC5/SCL      PC5
 */
/*******************Bibliotecas****************************/
#include <avr/io.h>//se incluyen las Bibliotecas de E/S del AVR atmega328P
#include <util/delay.h> // biblioteca de retardo
/*****************Macros y constantes**********************/
#define F_CPU 1000000UL //1 Mhz
#define LED_0 PORTD0 //LED_0 equivale al bit 0 del PORTD
#define LED_1 PORTD1
#define LED_2 PORTD2
#define LED_3 PORTD3
#define LED_4 PORTD4
#define TIME 500

void initialize_ports(void);

/*******************Programa principal*********************/
int main(void)
{
//--Inicialización
	initialize_ports();
//--Ejecución
    while (1) //loop infinito
    {
		//enciendo los puertos porque 0x1f?
		PORTD = 0b00000001;
		_delay_ms(TIME);
		PORTD = 0x00; // apago
		_delay_ms(TIME);
		PORTD = 0b00000010;
		_delay_ms(TIME);
		PORTD = 0x00; // apago
		_delay_ms(TIME);
		PORTD = 0b00000100;
		_delay_ms(TIME);
		PORTD = 0x00; // apago
		_delay_ms(TIME);
		PORTD = 0b00001000;
		_delay_ms(TIME);
		PORTD = 0x00; // apago
		_delay_ms(TIME);
		PORTD = 0b00010000;
		_delay_ms(TIME);
		PORTD = 0x00; // apago
		_delay_ms(TIME);
		PORTD = 0b00001000;
		_delay_ms(TIME);
		PORTD = 0x00; // apago
		_delay_ms(TIME);
		PORTD = 0b00000100;
		_delay_ms(TIME);
		PORTD = 0x00; // apago
		_delay_ms(TIME);
		PORTD = 0b00000010;
		_delay_ms(TIME);
		PORTD = 0x00; // apago
		_delay_ms(TIME);
		PORTD = 0b00000001;
		_delay_ms(TIME);
		PORTD = 0x00; // apago
    }
}
void initialize_ports(void)
{
    //--Entradas
	DDRD = (1<<LED_0) | (1<<LED_1) | (1<<LED_2) | (1<<LED_3) | (1<<LED_4);
//DDRD = 0x0F, 0b00001111
    
}