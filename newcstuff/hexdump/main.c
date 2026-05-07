#include <stdio.h>
#include <stdint.h>

#include "hexdump.h"

/*---------------------------------------------------------------------------*/
// PROTOTYPES
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
// MAIN
/*---------------------------------------------------------------------------*/
int main(void)
{
    uint8_t buffer[300];
    
    // Fill with data
    for (size_t idx = 0; idx < sizeof(buffer); idx++)
    {
        buffer[idx] = (uint8_t)((idx + 65u) & 0xffu);
    }
    
    printf("\nTest 1: 3 full lines\n");
    hexdump(buffer, 0x1000, 48);

    printf("\nTest 2: one byte at start of line\n");
    hexdump(buffer, 0x1000, 1);

    printf("\nTest 3: one byte at end of line\n");
    hexdump(buffer, 0x100f, 1);

    printf("\nTest 4: half line going to half line\n");
    hexdump(buffer, 0x1008, 16);
    
    return 0;
}


// End of main.c
