#define F_CPU 16000000
#define BAUD  9600
#define BRC   ((F_CPU/16/BAUD)-1)

#include <avr/io.h>
#include <util/delay.h>

void USART_Init(void);
void serialChar(uint8_t c);
void serialString(char *str);
unsigned char ReceiveByte(void);
void print_byte(uint8_t byte);
void USART_Init()
{
	UBRR0L = BRC;
	UBRR0H = (BRC >> 8);
	
	UCSR0B = (1 << TXEN0)|(1 << RXEN0);
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

void serialChar(uint8_t c)
{
	while(!(UCSR0A & (1 << UDRE0 )));
	UDR0 = c ;
	
}
void serialString(char *str)
{
	while(*str)
	{
		serialChar(*str++);
	}
	_delay_ms(1000);
}
unsigned char ReceiveByte(void){
	while(!(UCSR0A & (1 << RXC0 )));
	return UDR0;
}
void print_byte(uint8_t byte){
	serialChar('0'+ (byte/100)); /* Hundreds */
	serialChar('0'+ ((byte/10) % 10)); /* Tens */
	serialChar('0'+ (byte % 10)); /* Ones */
}
