#ifndef DEVICE_CORE_H
#define DEVICE_CORE_H


#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/* --- types ---------------------------------------------------------------- */

#define IO volatile        // read/write registers
#define O  volatile        // read-only registers
#define I  const volatile  // write-only registers

typedef uint32_t word;

/* --- debug macros --------------------------------------------------------- */

#ifdef DEBUG
// TODO
//#define ASSERT(x)
#else
#endif


#endif
