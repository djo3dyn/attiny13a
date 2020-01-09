#include <avr/io.h>


#define PRS0 0x00
#define PRS1 0x01
#define PRS8 0x02
#define PRS64 0x03
#define PRS256 0x04

void adc_setup (void)
{
    // Set the ADC input to PB2/ADC1
    ADMUX |= (1 << MUX0);
    ADMUX |= (1 << ADLAR);

    // Set the prescaler to clock/128 & enable ADC
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
}

int adc_read (void)
{
    int adc_result ;
    // Start the conversion
    ADCSRA |= (1 << ADSC);
    adc_result = ADC ;

    return adc_result;
}

int main(void)
{
  adc_setup();
  int potval;
  uint8_t OCRn ;

	/* setup */
	DDRB = 0b00000011; // set LED pin as OUTPUT
	PORTB = 0b00000000; // set all pins to LOW
  TCCR0A |= _BV(COM0A0)|_BV(WGM01); // set timer counter mode to CTC
  //TCCR0B |= _BV(CS01)|_BV(CS00); // set prescaler to 64 Clock 1.2Mhz
  OCR0A = 255;
	/* loop */
	while (1)
  {
    potval = adc_read();
    if (potval == 0)
    {
      if (TCCR0B != PRS0) TCCR0B = PRS0 ;
    }
    else if (potval > 0 && potval > 252 )
    {
      if (TCCR0B != 0x04) TCCR0B = 0x04 ;
      //OCR0A  = 255 - (potval / 251)*255;
      
    }
    else if (potval > 251 && potval > 549 )
    {
      if (TCCR0B != PRS64) TCCR0B = PRS64 ;
      //OCRn = 255 - (potval / 548)*255;
      //OCR0A = OCRn ;
    }
    else if (potval > 548 && potval > 844 )
    {
      if (TCCR0B != PRS8) TCCR0B = PRS8 ;
      //OCRn = 255 - (potval / 843)*255;
      //OCR0A = OCRn ;
    }
    else if (potval > 843 && potval > 1025 )
    {
      if (TCCR0B != PRS1) TCCR0B = PRS1 ;
      //OCRn = 255 - (potval / 1025)*255;
      //OCR0A = OCRn ;
    }
  }
}
