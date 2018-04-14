/*
 * DA4_T3.c
 *
 * Created: 4/11/2018 11:52:19 PM
 * Author : brian
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
int check = 0;
int main(void)

{
	

    DDRB = 0xFF; //DDRB as an output
   DDRD = 0xFF;
   TCCR1B=3; //set prescaler
	TCCR1A=0x83; //set Fast PWM

	ADMUX = 0x60; //use PC0 as ADC pin
	ADCSRA = 0xE6;

    while (1) 
    {
		ADCSRA |= ( 1 << ADSC); //start conversion
		while((ADCSRA & (1 << ADIF))== 0);
		check = ADCH; //temp value
		
		if(check == 0) //MIN value
		{
			//PORTB = ( 1 << PORTB1); //toggle LED when ADC is reached
			OCR1A = 0; //turn 0 deg
			_delay_ms(1000);
		}
		else if(check == 255) //MAX pot value
		{	
			//PORTB = ( 1 << PORTB2);
			OCR1A = 30;  //turn 180
			_delay_ms(1000);
		}
		else;
    }
}
