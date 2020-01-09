#include <Arduino.h>
#line 1 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
/*
 * Software UART-transmit for ATtiny13A - (for Debuging)
 * 
 * Delay micro second per bit at 9,6 - 12 Mhz CPU Speed :
 * (Set/tune value of US_L for the best received data)
 * Baud : 9600 , US_L : 96 - 106
 * Baud : 19200 , US_L : 46 - 49 
 * Baud : 38400 , US_L : 23 - 24
 * Baud : 57600 , US_L : 14 - 15
 * Baud : 115200 , US_L : 6
 * 
 * Use external clock source for the best result

*/
#include <avr\io.h>
#include <util\delay.h>

#define TX_PIN 2
#define RX_PIN 1

#define LOW 0
#define HIGH 1

#define US_L 105 // <------ For Baud rate 9600bps
#define US_S 103
#define US_RX 105

volatile char unsigned incomingData[10];
volatile int dataCount = 0 ;

#line 31 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
unsigned char serRead();
#line 39 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
void sendChar(char _data);
#line 52 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
void sendStr(char _data[] , bool _addline);
#line 86 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
int main(void);
#line 31 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
unsigned char serRead()
{
    unsigned char _buffer = incomingData[dataCount];
    incomingData[dataCount] = 0 ;
    dataCount--;
    return _buffer ;
}

void sendChar(char _data)
{
    PORTB &= ~_BV(TX_PIN); // Start bit
    _delay_us(US_L);
    for (int i = 0 ; i < 8 ; i++)
    {
        ((_data >> i) & 0x01) ? PORTB |= _BV(TX_PIN) : PORTB &= ~_BV(TX_PIN); // Data bit 8
        _delay_us(US_L);
    }
    PORTB |= _BV(TX_PIN); // Stop bit 0
    _delay_us(100);
}

void sendStr(char _data[] , bool _addline)
{
    int _size = strlen(_data);
    for (int i = 0 ; i < _size ; i++)
    {
        sendChar(_data[i]);
    }
    if (_addline)
    {
       sendChar(13); 
       sendChar(10);
    }
}

void sendStr(char _data[] , bool _addline = 0);

ISR(INT0_vect)
{
    unsigned char buffer = 0 ;
    _delay_us(US_L); //wait for LOW level start bit
    for (int i = 0 ; i < 8 ; i++)
    {
        if (PINB & _BV(RX_PIN)) buffer |= _BV(i);
        else buffer &= ~_BV(i);
        _delay_us(US_RX);
    }
    if ((PINB & _BV(RX_PIN)) && buffer != 0 && buffer != 0x7F) //Store char/byte
    {
        incomingData[dataCount] = buffer ;
        dataCount++;
        if (dataCount>10) dataCount = 0 ; // Overflow ;
    } 
}

int main(void)
{
    //Setup I/O
    DDRB = _BV(TX_PIN); // Set TX pin output
    DDRB &= ~_BV(RX_PIN) ; // Set RX pin as input
    PORTB |= _BV(TX_PIN); // Bus idle
    
    //Interupt setting
	GIMSK |= _BV(INT0); // enable INT0 interrupt handler
	MCUCR |= _BV(ISC01); // trigger INTO interrupt on falling edge
    sei(); // enable global interrupts

    char word1[15] = "I Receive : " ;

    while (1)
    {
        if (dataCount > 0)
        {
            sendStr(word1);
            for (int i = 0 ; i < dataCount ; i++)
            {
                sendChar(serRead());
            }
            sendChar(13);
            sendChar(10);
        }
        _delay_ms(100);

    }
    
}

