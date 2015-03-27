// ------------------------------------------------------------------
// kvr / KUT AVR Library
// Base Library / "kvr/base.h" / v1.0
// Author: MIZUNE Pine
// ------------------------------------------------------------------
//
// - v1.0
//   èâî≈ÅB
//
// - v1.1 (2012-10-06)
//   ATtiny 2313 ånóÒÇ…ëŒâûÅB
// 
// ------------------------------------------------------------------

#ifndef __KVR_BASE__
#define __KVR_BASE__

#define KVR_BASE_VERSION 10100UL // version 1.00.00

#ifndef F_CPU
#error "F_CPU is not defined."
#endif

// ATmega XX4
#if defined(__AVR_ATmega164P__)  || \
    defined(__AVR_ATmega164A__)  || \
    defined(__AVR_ATmega324P__)  || \
    defined(__AVR_ATmega324A__)  || \
    defined(__AVR_ATmega324PA__) || \
    defined(__AVR_ATmega644__)   || \
    defined(__AVR_ATmega644P__)  || \
    defined(__AVR_ATmega644A__)  || \
    defined(__AVR_ATmega644PA__) || \
    defined(__AVR_ATmega1284P__)
#define KVR_BASE_XX4

// ATmega XX8
#elif defined(__AVR_ATmega48__)   || \
      defined(__AVR_ATmega48A__)  || \
      defined(__AVR_ATmega48P__)  || \
      defined(__AVR_ATmega88__)   || \
      defined(__AVR_ATmega88A__)  || \
      defined(__AVR_ATmega88P__)  || \
      defined(__AVR_ATmega88PA__) || \
      defined(__AVR_ATmega168__)  || \
      defined(__AVR_ATmega168A__) || \
      defined(__AVR_ATmega168P__) || \
      defined(__AVR_ATmega328__)  || \
      defined(__AVR_ATmega328P__)
#define KVR_BASE_XX8

// ATtiny 2313
#elif defined (__AVR_ATtiny2313__) || \
      defined (__AVR_ATtiny2313A__)
#define KVR_BASE_2313
#endif

#endif
