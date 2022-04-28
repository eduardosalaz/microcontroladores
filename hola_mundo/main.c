/*
 * holamundo.c
 *
 * Created: 12-Aug-21 11:16:12
 * Author : Salazar
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL // 1 MHz

int main(void)
{          //76543210   
    DDRD = 0b11100000; // con esto dice que el bit 7 una salida
	// o DDRD = 0x80, lo mismo en hexadecimal.
	//para que sea salida tienes que especificar el 1 en el primer bit
    while (1) 
    {
		PORTD = 0b10000000; // con esto enciendes el bit 7 ESTE ES UN PUERTO
    }
}

