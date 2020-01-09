#include <avr\io.h>
#include <util\delay.h>

//Define Seven Segment
#define NONE    0b00000000
#define ZERO    0b00111111
#define ONE     0b00000110
#define TWO     0b01011011 
#define THREE   0b01001111
#define FOUR    0b01100110
#define FIVE    0b01101101
#define SIX     0b01111101
#define SEVEN   0b00000111
#define EIGHT   0b01111111
#define NINE    0b01101111
#define CHR_A   0b01110111
#define CHR_B   0b01111100
#define CHR_C   0b00111001
#define CHR_D   0b01011110
#define CHR_E   0b01111001
#define CHR_F   0b01110001

#define COM_CATHODE  0
#define COM_ANODE   1

#define LATCH 2 //Pin connected to ST_CP of 74HC595
#define DATA 1 //Pin connected to SH_CP of 74HC595
#define CLOCK 4 //Pin connected to DS of 74HC595

#define LATCH_H PORTB |= _BV(LATCH)
#define LATCH_L PORTB &= ~_BV(LATCH)
#define DATA_H PORTB |= _BV(DATA)
#define DATA_L PORTB &= ~_BV(DATA)
#define CLOCK_H PORTB |= _BV(CLOCK)
#define CLOCK_L PORTB &= ~_BV(CLOCK)

int number = 0 ;
int segment[4];

byte seg_decode(byte input)
{
  switch (input)
  {
    case 0 : return ZERO ;
    break ;
    case 1 : return ONE ;
    break ;
    case 2 : return TWO ;
    break ;
    case 3 : return THREE ;
    break ;
    case 4 : return FOUR ;
    break ;
    case 5 : return FIVE ;
    break ;
    case 6 : return SIX ;
    break ;
    case 7 : return SEVEN ;
    break ;
    case 8 : return EIGHT ;
    break ;
    case 9 : return NINE ;
    break ;
    case 10 : return CHR_A ;
    break ;
    case 11 : return CHR_B ;
    break ;
    case 12 : return CHR_C ;
    break ;
    case 13 : return CHR_D ;
    break ;
    case 14 : return CHR_E ;
    break ;
    case 15 : return CHR_F ;
    break ;
    default : return NONE ;
    break ;
  }
}

unsigned int dec2bcd(unsigned int number)
{
  
    unsigned char i=0;
    unsigned int k = 0;
    while(number)
    {
        k = ( k ) | ((number%10) << i*4);
        number = number / 10;
        i++;
    }
    return(k);
 
}

void decto7seg(unsigned int input , int _seg[4] , bool compin)
{
  int digit[4];
  for (int i = 0 ; i < 4 ; i++)
  {
     digit[i] = (dec2bcd(input) >> (i * 4) ) & 0x0F ;
     if (compin) _seg[i] = ~ seg_decode(digit[i]);
     else _seg[i] = seg_decode(digit[i]);
  }
}

void hexto7seg(unsigned int input , int _seg[4] , bool compin )
{
  int digit[4];
  for (int i = 0 ; i < 4 ; i++)
  {
     digit[i] = (input >> (i * 4) ) & 0x0F ;
    if (compin) _seg[i] = ~ seg_decode(digit[i]);
     else _seg[i] = seg_decode(digit[i]);
  }
}


void shiftOut(byte myDataOut) {

  for (int i = 7 ; i >= 0 ; i-- )  
  {
    CLOCK_L ;
    if ( myDataOut & (1 << i ) ) DATA_H ; //Data out 0000 0000 , Q7-Q6-Q5-Q4 Q3-Q2-Q1-Q0 
    else DATA_L ;
    CLOCK_H;
  }
  CLOCK_L;
}

int main(void)
{
  DDRB = 0b00011111;
  PORTB = 0x00;
  while(1)
  {
   
    number++ ;
    decto7seg(number , segment , COM_ANODE);
   
    LATCH_L ;
    for (int i = 0 ; i < 4 ; i++)
    {
      shiftOut(segment[0]); 
      shiftOut(segment[1]);
      shiftOut(segment[2]);
      shiftOut(segment[3]);
    } 
    LATCH_H ;
    _delay_ms(1000);
  }
}
