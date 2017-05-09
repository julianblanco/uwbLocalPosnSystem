#include "Arduino.h" 
#include "SPI.h"

#define BIT_READ(value, bit) (((value) >> (bit)) & 0x01)
#define BIT_SET(value, bit) ((value) |= (1UL << (bit)))
#define BIT_CLEAR(value, bit) ((value) &= ~(1UL << (bit)))
#define BIT_WRITE(value, bit, bitvalue) (bitvalue ? BIT_SET(value, bit) : BIT_CLEAR(value, bit))

#if !defined(digitalPinToPortReg)


// Standard Arduino Pins
#define digitalPinToPortReg(P) \
(((P) >= 0 && (P) <= 7) ? &PORTD : (((P) >= 8 && (P) <= 13) ? &PORTB : &PORTC))
#define digitalPinToDDRReg(P) \
(((P) >= 0 && (P) <= 7) ? &DDRD : (((P) >= 8 && (P) <= 13) ? &DDRB : &DDRC))
#define digitalPinToPINReg(P) \
(((P) >= 0 && (P) <= 7) ? &PIND : (((P) >= 8 && (P) <= 13) ? &PINB : &PINC))
#define __digitalPinToBit(P) \
(((P) >= 0 && (P) <= 7) ? (P) : (((P) >= 8 && (P) <= 13) ? (P) - 8 : (P) - 14))

#if defined(__AVR_ATmega8__)
// 3 PWM
#define __digitalPinToTimer(P) \
(((P) ==  9 || (P) == 10) ? &TCCR1A : (((P) == 11) ? &TCCR2 : 0))
#define __digitalPinToTimerBit(P) \
(((P) ==  9) ? COM1A1 : (((P) == 10) ? COM1B1 : COM21))
#else  //168,328

// 6 PWM
#define __digitalPinToTimer(P) \
(((P) ==  6 || (P) ==  5) ? &TCCR0A : \
(((P) ==  9 || (P) == 10) ? &TCCR1A : \
(((P) == 11 || (P) ==  3) ? &TCCR2A : 0)))
#define __digitalPinToTimerBit(P) \
(((P) ==  6) ? COM0A1 : (((P) ==  5) ? COM0B1 : \
(((P) ==  9) ? COM1A1 : (((P) == 10) ? COM1B1 : \
(((P) == 11) ? COM2A1 : COM2B1)))))
#endif  //defined(__AVR_ATmega8__)

#endif  //#if !defined(digitalPinToPortReg)




#define __atomicWrite__(A,P,V) \
if ( (int)(A) < 0x40) { bitWrite(*(A), __digitalPinToBit(P), (V) );}  \
else {                                                         \
uint8_t register saveSreg = SREG;                          \
cli();                                                     \
bitWrite(*(A), __digitalPinToBit(P), (V) );                   \
SREG=saveSreg;                                             \
} 


#ifndef digitalWriteFast
#define digitalWriteFast(P, V) \
do {                       \
if (__builtin_constant_p(P) && __builtin_constant_p(V))   __atomicWrite__((uint8_t*) digitalPinToPortReg(P),P,V) \
else  digitalWrite((P), (V));         \
}while (0)
#endif  //#ifndef digitalWriteFast2

#if !defined(pinModeFast)
#define pinModeFast(P, V) \
do {if (__builtin_constant_p(P) && __builtin_constant_p(V)) __atomicWrite__((uint8_t*) digitalPinToDDRReg(P),P,V) \
else pinMode((P), (V)); \
} while (0)
#endif


#ifndef noAnalogWrite
#define noAnalogWrite(P) \
	do {if (__builtin_constant_p(P) )  __atomicWrite((uint8_t*) __digitalPinToTimer(P),P,0) \
		else turnOffPWM((P));   \
} while (0)
#endif		


#ifndef digitalReadFast
	#define digitalReadFast(P) ( (int) _digitalReadFast_((P)) )
	#define _digitalReadFast_(P ) \
	(__builtin_constant_p(P) ) ? ( \
	( BIT_READ(*digitalPinToPINReg(P), __digitalPinToBit(P))) ) : \
	digitalRead((P))
#endif

