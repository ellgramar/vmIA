/**/

#ifndef COMP_H
#define COMP_H
// includes
#include <stdint.h>
#include <stdbool.h>

// enum for comp struct
enum sr{
    ar = 0,
    tr = 1,
    fr = 2,
    srCount
};

enum adreg{
    pc = 0,
    sp = 1,
    fp = 3,
    lr = 4,
    adrCount
};

//  structures
/* typedef struct comp {
    uint16_t mem[0x8fffffff];    // 2^31 - 1 so mem is less than 4 GiB
    uint16_t reg[16];           // 16 GP registers
    uint16_t sreg[3];
} comp; */

typedef struct comp {
    uint16_t gpr[16];
    uint16_t spr[3];
    uint32_t adr[4];
    uint16_t mem[0x7fffffff];
    char screen[2000];
    // reserved input locations
    // uint16_t input[1];
    // uint16_t input[1];
}comp;


#endif