#include "comp.h"

int run_computer(struct comp * c){
    bool running = 1;
    while (running){
        // fetch instruction
        uint16_t instr = c->mem[c->adr[0]];
        // pass to decode function
        n1(c,instr);
    }
    return 0;
}