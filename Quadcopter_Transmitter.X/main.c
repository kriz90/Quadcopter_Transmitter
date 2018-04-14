/*
 * File:   main.c
 * Author: krish
 *
 * Created on 5 April, 2018, 12:18 PM
 */


#include <xc.h>
#include "/home/krish/MPLABXProjects/Quadcopter_Transmitter.X/lcd.h"
#define _XTAL_FREQ 16000000

int page_no=0;
unsigned int P,I,D;
void pic_init(void);
void disp_PID(void);
void pic_init()
{
    TRISD = 0x00;
    PORTD = 0x00;
    TRISB &= 0xFC;
    OPTION_REG |= 0x40;
    INTCON |= 0x90;
}

void interrupt ext_int()
{
    if(INTE & INTF)
    {
        INTCON &= 0xEF;
        INTF = 0;
        page_no++;
        int j=0;
        while(j<3)
        {
            __delay_ms(500);
            ++j;
        }
        INTCON |= 0x10;
        disp_PID();
    }
}

void disp_PID()
{
    switch(page_no)
    {
        case 1:
        {
            lcd_cmd(0x01);
            lcd_string("P=");
            lcd_cmd(0xC0);
            lcd_int(P);
            break;
        }
        case 2:
        {
            lcd_cmd(0x01);
            lcd_string("I=");
            lcd_cmd(0xC0);
            lcd_int(I);
            break;
        }
        case 3:
        {
            lcd_cmd(0x01);
            lcd_string("D=");
            lcd_cmd(0xC0);
            lcd_int(D);
            break;
        }
        case 4:
        {
            lcd_cmd(0x01);
            break;
        }
    }
}

void main(void) {
    pic_init();
    lcd_init();
    lcd_string("kriz Quad Tx");
    __delay_ms(500);
    lcd_cmd(0x01);
    while(1)
    {
        __delay_ms(10);
    }
    return;
}
