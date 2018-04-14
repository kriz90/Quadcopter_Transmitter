/* 
 * File:   lcd.h
 * Author: Krishna Boopathy.J
 * Comments: This is a library file for interfacing 16x2 LCD with PIC 16F877A
 * Revision history: v1.1
 */
#include <xc.h>
#define _XTAL_FREQ 16000000

void lcd_init(void);
void lcd_data(int);
void lcd_cmd(int);
void lcd_string(char *);
void lcd_int(int);

void lcd_init()
{
    __delay_ms(50);
    lcd_cmd(0x33);
    lcd_cmd(0x32);
    lcd_cmd(0x28);
    lcd_cmd(0x06);
    lcd_cmd(0x0E);
    lcd_cmd(0x01);
}

void lcd_cmd(int c)
{
    PORTD = (c & 0xF0);
    PORTD |= 0x08;
    __delay_ms(20);
    PORTD &= 0xF7;
    PORTD = (c << 4) & (0xF0);
    PORTD |= 0x08;
    __delay_ms(20);
    PORTD &= 0xF7;    
}

void lcd_data(int d)
{
    PORTD = (d & 0xF0) | (0x04);
    PORTD |= 0x08;
    __delay_ms(20);
    PORTD &= 0xF7; 
    PORTD = (d << 4) | (0x04);
    PORTD |= 0x08;
    __delay_ms(20);
    PORTD &= 0xF7;     
}

void lcd_string(char *s)
{
    int i=0;
    while(s[i] != '\0')
    {
        lcd_data(s[i]);
        i++;
    }
}

void lcd_int(int i)
{
    int j=0;
    while(i!=0)
    {
        j=(j*10)+(i%10);
        i=i/10;        
    }
    i=j;
    while(i!=0)
    {
        lcd_data((i%10)+0x30);
        i=i/10;
    }
}
