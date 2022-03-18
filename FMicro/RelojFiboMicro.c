/*
 * RelojFiboMicro.c
 *
 * Created: 05/10/2021 09:48:20 p. m.
 * Author: Daniel Dorantes, Alexis García, Joshua Martínez
 */

#asm
 .equ __ds1302_port=0x08
 .equ __ds1302_io=4
 .equ __ds1302_sclk=3
 .equ __ds1302_rst=2
#endasm

#include <ds1302.h>
#include <delay.h>
#include <stdio.h>
#include <mega328p.h>

unsigned char h,m,s,temp;

void main(void)
{
    
    // USART initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART Receiver: Off
    // USART Transmitter: On
    // USART0 Mode: Asynchronous
    // USART Baud Rate: 9600
    UCSR0A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
    UCSR0B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (0<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
    UCSR0C=(0<<UMSEL01) | (0<<UMSEL00) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
    UBRR0H=0x00;
    UBRR0L=0x33; 
    
    // initialize the DS1302
    rtc_init(0,0,0);
              
    while(1)
    { 
      /* read time from the DS1302 RTC */
      rtc_get_time(&h,&m,&s);
      temp=s;
      delay_ms(1100);
      rtc_get_time(&h,&m,&s);
      if (temp==s)
        rtc_set_time(0,0,0); 
      
      putchar(h);
      putchar(m);
    }
}
