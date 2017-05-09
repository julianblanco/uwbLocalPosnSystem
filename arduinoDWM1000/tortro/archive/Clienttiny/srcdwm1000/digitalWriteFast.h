/*
  Optimized digital functions for AVR microcontrollers
  by Watterott electronic (www.watterott.com)
  based on http://code.google.com/p/digitalwritefast
 */

#ifndef __digitalWriteFast_h_
#define __digitalWriteFast_h_ 1

// general macros/defines
#ifndef BIT_READ
# define BIT_READ(value, bit)            ((value) &   (1UL << (bit)))
#endif
#ifndef BIT_SET
# define BIT_SET(value, bit)             ((value) |=  (1UL << (bit)))
#endif
#ifndef BIT_CLEAR
# define BIT_CLEAR(value, bit)           ((value) &= ~(1UL << (bit)))
#endif
#ifndef BIT_WRITE
# define BIT_WRITE(value, bit, bitvalue) (bitvalue ? BIT_SET(value, bit) : BIT_CLEAR(value, bit))
#endif

#ifndef SWAP
#define SWAP(x,y) do{ (x)=(x)^(y); (y)=(x)^(y); (x)=(x)^(y); }while(0)
#endif

#ifndef DEC
# define DEC (10)
#endif
#ifndef HEX
# define HEX (16)
#endif
#ifndef OCT
# define OCT (8)
#endif
#ifndef BIN
# define BIN (2)
#endif


// --- Arduino Uno ---
#if (defined(ARDUINO_AVR_UNO) || \
       defined(ARDUINO_AVR_DUEMILANOVE) || \
       defined(ARDUINO_ARCH_AVR) || \
       defined(__AVR_ATmega328__) || \
       defined(__AVR_ATmega328P__) || \
       defined(__AVR_ATmega328PB__) || \
       defined(__AVR__))

#define UART_RX_PIN     (0) //PD0
#define UART_TX_PIN     (1) //PD1

#define I2C_SDA_PIN     (18) //A4
#define I2C_SCL_PIN     (19) //A5

#define SPI_HW_SS_PIN   (10) //PB0
#define SPI_HW_MOSI_PIN (11) //PB2
#define SPI_HW_MISO_PIN (12) //PB3
#define SPI_HW_SCK_PIN  (13) //PB1

#if defined(__AVR_ATmega328PB__)
#define __digitalPinToPortReg(P) \
(((P) >= 0 && (P) <= 7) ? &PORTD : (((P) >= 8 && (P) <= 13) ? &PORTB : (((P) >= 14 && (P) <= 19) ? &PORTC : &PORTE)))
#define __digitalPinToDDRReg(P) \
(((P) >= 0 && (P) <= 7) ? &DDRD : (((P) >= 8 && (P) <= 13) ? &DDRB : (((P) >= 14 && (P) <= 19) ? &DDRC : &DDRE)))
#define __digitalPinToPINReg(P) \
(((P) >= 0 && (P) <= 7) ? &PIND : (((P) >= 8 && (P) <= 13) ? &PINB : (((P) >= 14 && (P) <= 19) ? &PINC : &PINE)))
#define __digitalPinToBit(P) \
(((P) >= 0 && (P) <= 7) ? (P) : (((P) >= 8 && (P) <= 13) ? (P) - 8 : (((P) >= 14 && (P) <= 19) ? (P) - 14 : (((P) >= 20 && (P) <= 21) ? (P) - 18 : (P) - 22))))
#else
#define __digitalPinToPortReg(P) \
(((P) >= 0 && (P) <= 7) ? &PORTD : (((P) >= 8 && (P) <= 13) ? &PORTB : &PORTC))
#define __digitalPinToDDRReg(P) \
(((P) >= 0 && (P) <= 7) ? &DDRD : (((P) >= 8 && (P) <= 13) ? &DDRB : &DDRC))
#define __digitalPinToPINReg(P) \
(((P) >= 0 && (P) <= 7) ? &PIND : (((P) >= 8 && (P) <= 13) ? &PINB : &PINC))
#define __digitalPinToBit(P) \
(((P) >= 0 && (P) <= 7) ? (P) : (((P) >= 8 && (P) <= 13) ? (P) - 8 : (P) - 14))
#endif


// --- Other ---
#else

#define I2C_SDA_PIN     SDA
#define I2C_SCL_PIN     SCL

#define SPI_HW_SS_PIN   SS
#define SPI_HW_MOSI_PIN MOSI
#define SPI_HW_MISO_PIN MISO
#define SPI_HW_SCK_PIN  SCK


#endif
//#endif  //#ifndef digitalPinToPortReg


#ifndef digitalWriteFast
#if (defined(__AVR__) || defined(ARDUINO_ARCH_AVR))
#define digitalWriteFast(P, V) \
if (__builtin_constant_p(P) && __builtin_constant_p(V)) { \
  BIT_WRITE(*__digitalPinToPortReg(P), __digitalPinToBit(P), (V)); \
} else { \
  digitalWrite((P), (V)); \
}
#else
#define digitalWriteFast digitalWrite
#endif
#endif


#ifndef pinModeFast
#if (defined(__AVR__) || defined(ARDUINO_ARCH_AVR))
#define pinModeFast(P, V) \
if (__builtin_constant_p(P) && __builtin_constant_p(V)) { \
  BIT_WRITE(*__digitalPinToDDRReg(P), __digitalPinToBit(P), (V)); \
} else { \
  pinMode((P), (V)); \
}
#else
#define pinModeFast pinMode
#endif
#endif


#ifndef digitalReadFast
#if (defined(__AVR__) || defined(ARDUINO_ARCH_AVR))
#define digitalReadFast(P) ( (int) __digitalReadFast((P)) )
#define __digitalReadFast(P ) \
  (__builtin_constant_p(P) ) ? ( \
  ( BIT_READ(*__digitalPinToPINReg(P), __digitalPinToBit(P))) ) : \
  digitalRead((P))
#else
#define digitalReadFast digitalRead
#endif
#endif

#endif //__digitalWriteFast_h_