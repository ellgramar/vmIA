#ifndef INSTR_H
#define INSTR_H

#include <stdint.h>


#include "comp.h"


// first nibble opcodes
void n1(struct comp * c, uint16_t instr);
// second nibble opcodes
void n2(struct comp * c, uint16_t instr, uint16_t nibble3, uint16_t nibble4);
// third nibble opcodes
void n3(struct comp * c, uint16_t instr, uint16_t nibble4);
// fourth nibble opcodes
void n4(struct comp * c, uint16_t instr);
// flag setter
void flag_setter(struct comp * c,uint16_t instr1, uint16_t instr2);
// falg getter
void flag_getter(struct comp * c);

#endif