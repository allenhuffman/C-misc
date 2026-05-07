#ifndef HEXDUMP_H
#define HEXDUMP_H

#include <stddef.h>   // size_t
#include <stdint.h>   // uintptr_t

/*---------------------------------------------------------------------------*/
// PROTOTYPES
/*---------------------------------------------------------------------------*/
void hexdump(const void *dataptr, uintptr_t address, size_t size);

#endif // HEXDUMP_H

// End of hexdump.h
    