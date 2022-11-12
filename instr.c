#include "instr.h"

void n1(struct comp * c, uint16_t instr){
    uint16_t opcode = (instr & 0xf000) >> 12;
    uint16_t nibble2 = (instr & 0x0f00) >> 8;
    uint16_t nibble3 = (instr & 0x00f0) >> 4;
    uint16_t nibble4 = (instr & 0x000f);
    // switch case statment for opcode 16 cases plus default
    switch (opcode){
        case 0x0:
            // send lower three nibbles to n2 decode function
            n2(c, nibble2, nibble3, nibble4);
            break;
        case 0x1:   //add
            // test and set c flag
            if ((((int)c->gpr[nibble3]) + ((int)c->gpr[nibble4])) > 0xffff) c->spr[2] &= 0x4000;
            // add two registers, store in n2; note that overflow will be treated as uints are
            c->gpr[nibble2] = c->gpr[nibble3] + c->gpr[nibble4];
            // test and set the z flag
            if (c->gpr[nibble2] == 0) c->spr[2] &= 0x8000;
            break;

        case 0x2:   // sub
            // test and set c and n flag
            if ((((int)c->gpr[nibble3]) - ((int)c->gpr[nibble4])) < 0) c->spr[2] &= 0x6000;
            // subtract two registers, store in reg[n2]
            c->gpr[nibble2] = c->gpr[nibble3] - c->gpr[nibble4];
            // test and set the z flag
            if (c->gpr[nibble2] == 0) c->spr[2] &= 0x8000;
            break;

        case 0x3:   // mul
            // test and set c flag
            if ((((int)c->gpr[nibble3]) * ((int)c->gpr[nibble4])) < 0) c->spr[2] &= 0x4000;
            // multiply two registers, store in reg[n2]
            c->gpr[nibble2] = c->gpr[nibble3] * c->gpr[nibble4];
            // test and set the z flag
            if (c->gpr[nibble2] == 0) c->spr[2] &= 0x8000;
            break;

        case 0x4:   // div
            // divide two registers, store in reg[n2]
            c->gpr[nibble2] = c->gpr[nibble3] / c->gpr[nibble4];
            // test and set the z flag
            if (c->gpr[nibble2] == 0) c->spr[2] &= 0x8000;
            break;

        case 0x5:   // rem
            // get remainder between two registers, store in reg[n2]
            c->gpr[nibble2] = c->gpr[nibble3] % c->gpr[nibble4];
            // test and set the z flag
            if (c->gpr[nibble2] == 0) c->spr[2] &= 0x8000;
            break;

        case 0x6:
            // and two registers, store in reg[n2]
            c->gpr[nibble2] = c->gpr[nibble3] & c->gpr[nibble4];
            // test and set the z flag aftwrwards. less calculations needed
            if (c->gpr[nibble2] == 0) c->spr[2] &= 0x8000;
            break;

        case 0x7:
            // nand two registers, store in reg[n2]
            c->gpr[nibble2] = ~(c->gpr[nibble3] & c->gpr[nibble4]);
            // test and set the z flag aftwrwards
            if (c->gpr[nibble2] == 0) c->spr[2] &= 0x8000;
            break;

        case 0x8:
            // or two registers, store in reg[n2]
            c->gpr[nibble2] = c->gpr[nibble3] | c->gpr[nibble4];
            // test and set the z flag aftwrwards
            if (c->gpr[nibble2] == 0) c->spr[2] &= 0x8000;  
            break;

        case 0x9:
            // nor two registers, store in reg[n2]
            c->gpr[nibble2] = ~(c->gpr[nibble3] | c->gpr[nibble4]);
            // test and set the z flag
            if (c->gpr[nibble2] == 0) c->spr[2] &= 0x8000;
            break;

        case 0xa:
            // xor two registers, store in reg[n2]
            c->gpr[nibble2] = c->gpr[nibble3] ^ c->gpr[nibble4];
            // test and set the z flag
            if (c->gpr[nibble2] == 0) c->spr[2] &= 0x8000;
            break;
        case 0xb:
            // xnor two registers, store in reg[n2]
            c->gpr[nibble2] = ~(c->gpr[nibble3] ^ c->gpr[nibble4]);
            // test and set the z flag
            if (c->gpr[nibble2] == 0) c->spr[2] &= 0x8000;
            break;

        case 0xc:
            // load low byte of instr into reg[n2]
            c->gpr[nibble2] = (instr & 0x00ff);
            // test and set the z flag
            if (c->gpr[nibble2] == 0) c->spr[2] &= 0x8000;
            break;

        case 0xd:
            // load high byte into reg[n2]
            c->gpr[nibble2] = ((instr & 0x00ff) << 8);
            // test and set the z flag
            if (c->gpr[nibble2] == 0) c->spr[2] &= 0x8000;
            break;

        case 0xe:
            // load indirect to reg[n2] from mem[(reg[n3] << 16) + reg[n4]]
            if ((((uint32_t)(c->gpr[nibble3] << 16)) + ((uint32_t)(c->gpr[nibble4]))) < 0x80000000){
                c->gpr[instr & 0x0f00 >> 8] = (((uint32_t)(c->gpr[nibble3] << 16)) + ((uint32_t)(c->gpr[nibble4])));
            } else {
                perror("lod, memory location specified is too large");
            }
            break;
        case 0xf:
            // store indirect from reg[n2] to mem[reg[n3] << 16 + reg[n4]]
            if ((((uint32_t)(c->gpr[nibble3] << 16)) + ((uint32_t)(c->gpr[nibble4]))) < 0x80000000){
                c->mem[(((uint32_t)(c->gpr[nibble3] << 16)) + ((uint32_t)(c->gpr[nibble4])))] = nibble2;
            } else {
                perror("str, memory location specified is too large");
            }
            break;
        default:
            // error out
            perror("invalid opcode in n1 switch case");
            break;
    }
}

void n2(struct comp * c, uint16_t instr, uint16_t nibble3, uint16_t nibble4){
    switch (instr){
        case 0x0:
            // escape to n3 opcodes
            n3(c, c->gpr[nibble3], c->gpr[nibble4]);
            break;
        case 0x1:
            // move from one register to another
            c->gpr[c->gpr[nibble3]] = c->gpr[nibble4];
            break;
        case 0x2:
            // swap two registers
            uint16_t temp = c->gpr[nibble3];
            c->gpr[nibble3] = c->gpr[nibble4];
            c->gpr[nibble4] = temp;
            break;
        case 0x3:
            // not reg[n4] and store in reg[n3]
            c->gpr[nibble3] = ~(c->gpr[nibble4]);
            if (c->gpr[nibble4] == 0){
                c->spr[2] = c->spr[2] & 0x8000;
            }
            break;
        case 0x4:
            // compare registers and activate jump mode
    }
        
}

void n3(struct comp * c, uint16_t instr, uint16_t nibble4{
    uint16_t opcode = (instr & 0x00f0) >> 4;

            
}

void n4(struct comp * c, uint16_t instr){
    uint16_t opcode = (instr & 0x000f);
    // switch case statment for opcode 16 cases plus default

            
}

void flag_setter(struct comp * c, uint16_t instr1, uint16_t instr2){
    int result = ((int)instr1 - (int)instr2);
    if (((int)instr1 - (int)instr2) == 0){
        c->spr[2] &= 0x8000;
    }
    if (((int)instr1 - (int)instr2) < 0){
        c->spr[2] &= 0x4000;
    }
    if (((int)instr1 + (int)instr2) > 0xffff){
        c->spr[2] &= 0x2000;
    }
}


void flag_getter(struct comp * c){

}