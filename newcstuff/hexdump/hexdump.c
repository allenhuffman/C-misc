#include <ctype.h>      // isprint()
#include <inttypes.h>   // PRIxPTR
#include <stdint.h>
#include <stdio.h>

/*
1000:                                           41 42                AB
1010: 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f 50 51 52  CDEFGHIJKLMNOPQR
1020: 53 54 55 56 57 58 59 5a 5b 5c 5d 5e 5f 60 61 62  STUVWXYZ[\]^_`ab
1030: 63 64 65 66 67 68 69 6a 6b 6c 6d 6e 6f 70 71 72  cdefghijklmnopqr
1040: 73 74 75 76 77 78 79 7a 7b 7c 7d 7e 7f 80 81 82  stuvwxyz{|}~....
1050: 83 84 85 86 87 88 89 8a 8b 8c 8d 8e 8f 90 91 92  ................
1060: 93 94 95 96 97 98 99 9a 9b 9c 9d 9e 9f a0 a1 a2  ................
1070: a3 a4 a5 a6 a7 a8 a9 aa ab ac ad ae af b0 b1 b2  ................
1080: b3 b4 b5 b6 b7 b8 b9 ba bb bc bd be bf c0        ..............
*/

/*---------------------------------------------------------------------------*/
// Print one ASCII column section: 'leading' blank columns, then characters.
/*---------------------------------------------------------------------------*/
static void print_ascii_col (const uint8_t *ptr, size_t start, size_t end,
                             unsigned int leading)
{
    putchar (' ');
    
    for (unsigned int s = 0; s < leading; s++)
    {
        putchar(' ');
    }
    
    for (size_t pos = start; pos <= end; pos++)
    {
        putchar (isprint ((unsigned char)ptr[pos]) ? ptr[pos] : '.');
    }
}

/*---------------------------------------------------------------------------*/
// Hex Dump
/*---------------------------------------------------------------------------*/
void hexdump (const void *dataptr, uintptr_t address, size_t size)
{
    const uint8_t *ptr = (const uint8_t*)dataptr;

    //printf ("hexdump (%p, 0x%04" PRIxPTR ", %zu)\n", dataptr, address, size);

    if ((NULL != ptr) && (0 != size))
    {
        // If not starting at an even 16-byte boundary...
        if ((address % 16) != 0)
        {
            // Print address.
            printf ("%04" PRIxPTR ": ", address - (address % 16u));
    
            // Space over for missing leading columns.
            for (unsigned int idx = 0; idx < (address % 16u); idx++)
            {
                fputs("   ", stdout);
            }
        }
    
        size_t lineAsciiStart = 0;

        for (size_t idx = 0; idx < size; idx++)
        {
            // If at the start of a 16-byte block...
            if (((address + idx) % 16u) == 0u)
            {
                // And we have already printed a line...
                if (idx > 0)
                {
                    unsigned int leading = (unsigned int)((address + lineAsciiStart) % 16u);
                    print_ascii_col(ptr, lineAsciiStart, idx - 1, leading);
                    putchar ('\n');
                }

                lineAsciiStart = idx;
    
                printf("%04" PRIxPTR ": ", address + idx);
            }
    
            printf ("%02x ", ptr[idx]);
            
            if (idx == size - 1)
            {
                size_t remaining = 15u - ((address + idx) % 16u);
                for (size_t i = 0; i < remaining; i++)
                {
                    fputs("   ", stdout);
                }
                unsigned int leading = (unsigned int)((address + lineAsciiStart) % 16u);
                print_ascii_col (ptr, lineAsciiStart, idx, leading);
                putchar ('\n');
            }        
        }
        
        putchar ('\n');
    }
}

// End of hexdump.c
