/*
 * Joystick.c
 *
 * Created: 22-06-2020 15:26:47
 * Author : Sravani Malekar
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"// header file for serial communication

#define XPIN (1 << MUX0)//ADC1 channel
#define YPIN (1 << MUX1)//ADC2 channel

void ADC_Init0(void);//func for initialization of ADC0
uint8_t readADC(uint8_t channel);//func to enable use of multiple ADC

int main(void)
{
	USART_Init();//Initializing UART
    ADC_Init0();//Initializing ADC0
	DDRB &= ~(1 << 2) ;//setting PORTB as input
	PORTB |= (1 << 2);//enable pull-up resistor
	uint8_t Xval;
	uint8_t Yval;
	    
    while (1) 
    {
		Xval = readADC(XPIN);// reading Xvalue from Joystick
		Yval = readADC(YPIN);// reading Yvalue from Joystick
		
		
		serialString("X value is :");
		print_byte(Xval);
		serialString(" Y value is :");
		print_byte(Yval);
		
		if((PINB &(1 << 2))== 0){//reading Switch State from Joystick
			serialString(" Switch State:");
			serialChar('1');
		}
		else{
			serialString(" Switch State:");
			serialChar('0');
		}
		
		serialString("\r\n");
		_delay_ms(1000);
		
		
    }
	return 0;
}

void ADC_Init0(void){
	ADMUX |= (1 << REFS0)|(1 << ADLAR);// ref.voltage selection and left adjustment bits
	ADCSRA |= (1 << ADEN);// ADC enable bit
	ADCSRA |= (1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);// setting prescaler as 128

}
uint8_t readADC(uint8_t channel){
	
	ADMUX = (11110000 & ADMUX)|(channel);
	ADCSRA |= (1 << ADSC);// starting conversation
	while(ADCSRA & (1 << ADSC));
	return(ADCH);//returning most significant bits
}
