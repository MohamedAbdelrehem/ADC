#define  LCD16X2_H_
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#define LCD_DATA_PORT PORTB
#define LCD_CONTROL_PORT PORTA
#define LCD_RS PA7
#define LCD_EN PA6

void lcd_command_write(char command)
{

	LCD_CONTROL_PORT |=( 1 << LCD_EN);
	LCD_DATA_PORT =command;
	_delay_ms(1);
	LCD_CONTROL_PORT=0x00;
	_delay_ms(1);
}


void lcd_init()
{

	lcd_command_write(0x38);
	lcd_command_write(0x01);
	lcd_command_write(0x06);
	lcd_command_write(0x0e);

}

void lcd_data_write(char data)
{

	LCD_CONTROL_PORT=_BV(LCD_EN) | _BV(LCD_RS);
	LCD_DATA_PORT=data ;
	_delay_ms(10);
	LCD_CONTROL_PORT=_BV(LCD_RS);
}

void lcd_string_write(char *dat)
{

	for(int i=0;i< (strlen(dat))  ;i++)
	{
		lcd_data_write(dat[i]);
	}
}

unsigned int read_adc(unsigned char channel){
	
	
	channel&= 0b00000111;
	ADMUX |= channel;
	ADCSRA |=(1<<ADSC);
	
	while((ADCSRA &(1<<ADIF))==0);

	return ADC;
}
void adc_init(){
	
	
	ADMUX |=(1<<REFS0);
	ADMUX |=(0<<REFS1);


	ADCSRA |=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);


}

int main(void)
{
	char st[15],str[15];
	double volt;
	unsigned int adc_value=0;
	DDRA=0xFE;
	DDRB=0xFF;
	adc_init();
	while(1)
	{
		lcd_init();
		lcd_command_write(0x01);
		adc_value =read_adc(0);
		volt = (adc_value * 5.0 / 1024) * 100;
		dtostrf(volt,3,0,st);
		sprintf(str,"Temp =%s.0",st);
		lcd_string_write(str);
		_delay_ms(1000);
	}
}