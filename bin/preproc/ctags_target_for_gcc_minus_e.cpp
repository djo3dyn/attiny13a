# 1 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
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
# 15 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
# 16 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 2
# 17 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 2
# 28 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"

# 28 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
volatile char unsigned incomingData[10];
volatile int dataCount = 0 ;

unsigned char serRead()
{
    unsigned char _buffer = incomingData[dataCount];
    incomingData[dataCount] = 0 ;
    dataCount--;
    return _buffer ;
}

void sendChar(char _data)
{
    
# 41 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
   (*(volatile uint8_t *)((0x18) + 0x20)) 
# 41 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
         &= ~
# 41 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
             (1 << (
# 41 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
             2
# 41 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
             ))
# 41 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                        ; // Start bit
    _delay_us(105 /* <------ For Baud rate 9600bps*/);
    for (int i = 0 ; i < 8 ; i++)
    {
        ((_data >> i) & 0x01) ? 
# 45 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
                               (*(volatile uint8_t *)((0x18) + 0x20)) 
# 45 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                                     |= 
# 45 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
                                        (1 << (
# 45 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                                        2
# 45 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
                                        )) 
# 45 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                                                    : 
# 45 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
                                                      (*(volatile uint8_t *)((0x18) + 0x20)) 
# 45 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                                                            &= ~
# 45 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
                                                                (1 << (
# 45 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                                                                2
# 45 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
                                                                ))
# 45 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                                                                           ; // Data bit 8
        _delay_us(105 /* <------ For Baud rate 9600bps*/);
    }
    
# 48 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
   (*(volatile uint8_t *)((0x18) + 0x20)) 
# 48 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
         |= 
# 48 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
            (1 << (
# 48 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
            2
# 48 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
            ))
# 48 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                       ; // Stop bit 0
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


# 68 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
extern "C" void __vector_1 /* External Interrupt 0 */ (void) __attribute__ ((signal,used, externally_visible)) ; void __vector_1 /* External Interrupt 0 */ (void)

# 69 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
{
    unsigned char buffer = 0 ;
    _delay_us(105 /* <------ For Baud rate 9600bps*/); //wait for LOW level start bit
    for (int i = 0 ; i < 8 ; i++)
    {
        if (
# 74 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
           (*(volatile uint8_t *)((0x16) + 0x20)) 
# 74 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                & 
# 74 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
                  (1 << (
# 74 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                  1
# 74 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
                  ))
# 74 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                             ) buffer |= 
# 74 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
                                         (1 << (
# 74 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                                         i
# 74 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
                                         ))
# 74 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                                               ;
        else buffer &= ~
# 75 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
                       (1 << (
# 75 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                       i
# 75 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
                       ))
# 75 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                             ;
        _delay_us(105);
    }
    if ((
# 78 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
        (*(volatile uint8_t *)((0x16) + 0x20)) 
# 78 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
             & 
# 78 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
               (1 << (
# 78 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
               1
# 78 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
               ))
# 78 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                          ) && buffer != 0 && buffer != 0x7F) //Store char/byte
    {
        incomingData[dataCount] = buffer ;
        dataCount++;
        if (dataCount>10) dataCount = 0 ; // Overflow ;
    }
}

int main(void)
{
    //Setup I/O
    
# 89 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
   (*(volatile uint8_t *)((0x17) + 0x20)) 
# 89 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
        = 
# 89 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
          (1 << (
# 89 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
          2
# 89 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
          ))
# 89 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                     ; // Set TX pin output
    
# 90 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
   (*(volatile uint8_t *)((0x17) + 0x20)) 
# 90 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
        &= ~
# 90 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
            (1 << (
# 90 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
            1
# 90 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
            )) 
# 90 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                        ; // Set RX pin as input
    
# 91 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
   (*(volatile uint8_t *)((0x18) + 0x20)) 
# 91 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
         |= 
# 91 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
            (1 << (
# 91 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
            2
# 91 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
            ))
# 91 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                       ; // Bus idle

    //Interupt setting
 
# 94 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
(*(volatile uint8_t *)((0x3B) + 0x20)) 
# 94 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
      |= 
# 94 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
         (1 << (6))
# 94 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                  ; // enable INT0 interrupt handler
 
# 95 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
(*(volatile uint8_t *)((0x35) + 0x20)) 
# 95 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
      |= 
# 95 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
         (1 << (1))
# 95 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
                   ; // trigger INTO interrupt on falling edge
    
# 96 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino" 3
   __asm__ __volatile__ ("sei" ::: "memory")
# 96 "d:\\Microcontroller\\Attiny13A\\Arduino\\Software_UART\\Software_UART.ino"
        ; // enable global interrupts

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
