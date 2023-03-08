/*
 * lcd_driver.h
 *
 * Created: 10/30/2022 10:14:45 AM
 *  Author: Mohamed
 */ 


#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#ifndef LCD_DATA
#define LCD_DATA PORTB
#endif  

#define LCD_CONT PORTA
#define en PA6
#define rs PA7

void LCD_cmd( char command)
{
	LCD_CONT = _BV(en);
	LCD_DATA = command;
	_delay_ms(1);
	LCD_CONT = 0x00;
	_delay_ms(1);
}

void init_LCD(void){
	
	
	
	LCD_cmd(0x38);				//Initialize 8bit mode
	_delay_ms(1);
	LCD_cmd(0x1);				//clear
	_delay_ms(1);
	LCD_cmd(0x6);
	_delay_ms(1);

	LCD_cmd(0x0E);				//First line start
	_delay_ms(1);
	
}

void LCD_write( char data){
	LCD_CONT = _BV(en) | _BV(rs);
	LCD_DATA = data;
	_delay_ms(1);
	LCD_CONT = _BV(rs);
	_delay_ms(1);
	
}

void LCD_String (char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)
	{
		LCD_write (str[i]);
	}
}

#endif /* LCD_DRIVER_H_ */