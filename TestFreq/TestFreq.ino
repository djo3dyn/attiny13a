#include <avr/io.h>
#include <util/delay.h>

#define SCK 2

int main (void)
{
 /* set pin 5 of PORTB for output*/
 DDRB |= _BV(SCK);
 
 while(1) 
 {
  //PORTB |= _BV(SCK);
  //PORTB &= ~_BV(SCK);
  digitalWrite(2, HIGH);
  digitalWrite(2, LOW);
 }
}
