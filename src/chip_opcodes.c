#include "chip_opcodes.h"
#include "chip_memory.h"
#include "chip_structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void decode_execute_opcode(word opcode)
{
    switch(opcode & 0xF000) {
        case 0x0000:
            switch(opcode & 0x000F) {
                case 0x0000:
                    CLS();
                    break;
                case 0x000E:
                    RET();
                    break;
                default:
                    fprintf(stderr, "Uknown opcode %04X\n", opcode);
                    break;
            }
            break;
        case 0x1000:
            JP(opcode & 0x0FFF);
            break;
        case 0x2000:
            CALL(opcode & 0x0FFF);
            break;
        case 0x3000:
            SE_V_BYTE((opcode & 0x0F00) >> 8, opcode & 0x00FF);
            break;
        case 0x4000:
            SNE_V_BYTE((opcode & 0x0F00) >> 8, opcode & 0x00FF);
            break;
        case 0x5000:
            switch(opcode & 0x000F) {
                case 0x0000:
                    SE_VX_VY((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    break;
                default:
                    fprintf(stderr, "Uknown opcode %04X\n", opcode);
                    break;
            }
            break;
        case 0x6000:
            LD_V_BYTE((opcode & 0x0F00) >> 8, opcode & 0x00FF);
            break;
        case 0x7000:
            ADD_V_BYTE((opcode & 0x0F00) >> 8, opcode & 0x00FF);
            break;
        case 0x8000:
            switch(opcode & 0x000F) {
                case 0x0000:
                    LD_VX_VY((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    break;
                case 0x0001:
                    OR_VX_VY((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    break;
                case 0x0002:
                    AND_VX_VY((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    break;
                case 0x0003:
                    XOR_VX_VY((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    break;
                case 0x0004:
                    ADD_VX_VY((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    break;
                case 0x0005:
                    SUB_VX_VY((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    break;
                case 0x0006:
                    SHR_VX_VY((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    break;
                case 0x0007:
                    SUBN_VX_VY((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    break;
                case 0x000E:
                    SHL_VX_VY((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    break;
                default:
                    fprintf(stderr, "Uknown opcode %04X\n", opcode);
                    break; 
            }
            break;
        case 0x9000:
            switch(opcode & 0x000F) {
                case 0x0000:
                    SNE_VX_VY((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
                    break;
                default:
                    fprintf(stderr, "Uknown opcode %04X\n", opcode);
                    break; 
            }
            break;
        case 0xA000:
            LD_I_addr(opcode & 0x0FFF);
            break;
        case 0xB000:
            JP_V0_addr(opcode & 0x0FFF);
            break;
        case 0xC000:
            RND_V_BYTE((opcode & 0x0F00) >> 8, opcode & 0x00FF);
            break;
        case 0xD000:
            DRW((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4, opcode & 0x000F);
            break;
        case 0xE000:
            switch(opcode & 0x00FF) {
                case 0x009E:
                    SKP_V((opcode & 0x0F00) >> 8);
                    break;
                case 0x00A1:
                    SKNP_V((opcode & 0x0F00) >> 8);
                    break;
                default:
                    fprintf(stderr, "Uknown opcode %04X\n", opcode);
                    break;
            }
            break;
        case 0xF000:
            switch(opcode & 0x00FF) {
                case 0x0007:
                    LD_V_DT((opcode & 0x0F00) >> 8);
                    break;
                case 0x000A:
                    LD_V_K((opcode & 0x0F00) >> 8);
                    break;
                case 0x0015:
                    LD_DT_V((opcode & 0x0F00) >> 8);
                    break;
                case 0x0018:
                    LD_ST_V((opcode & 0x0F00) >> 8);
                    break;
                case 0x001E:
                    ADD_I_V((opcode & 0x0F00) >> 8);
                    break;
                case 0x0029:
                    LD_F_V((opcode & 0x0F00) >> 8);
                    break;
                case 0x0033:
                    LD_B_V((opcode & 0x0F00) >> 8);
                    break;
                case 0x0055:
                    LD_I_V((opcode & 0x0F00) >> 8);
                    break;
                case 0x0065:
                    LD_V_I((opcode & 0x0F00) >> 8);
                    break;
                default:
                    fprintf(stderr, "Uknown opcode %04X\n", opcode);
                    break;
            }
            break;
        default:
            fprintf(stderr, "Uknown opcode %04X\n", opcode);
            break;
    }
}

void NOOP()
{

}

void SYS(word address)
{
    printf("SYS %04X\n", address);
}

void CLS()
{
    printf("CLS\n");
    memset(screen, 0, 32*64);
    PC += 2;
}

void RET()
{
    printf("RET\n");
    PC = stack[SP];
    SP--;
    PC += 2;
}

void JP(word address)
{
    printf("JP %04X\n", address);
    PC = address;
}

void CALL(word address)
{
    printf("CALL %04X\n", address);
    SP++;
    stack[SP] = PC;
    PC = address;
}

void SE_V_BYTE(byte reg, byte data)
{
    printf("SE V%01X %02X\n", reg, data);
    if(V[reg] == data) {
        PC += 2;
    }
    PC += 2;
}

void SNE_V_BYTE(byte reg, byte data)
{
    printf("SNE V%01X %02X\n", reg, data);
    if(V[reg] != data) {
        PC += 2;
    }
    PC += 2;
}

void SE_VX_VY(byte reg_x, byte reg_y)
{
    printf("SE V%01X V%01X\n", reg_x, reg_y);
    if(V[reg_x] == V[reg_y]) {
        PC += 2;
    }
    PC += 2;
}

void LD_V_BYTE(byte reg, byte data)
{
    printf("LD V%01X %02X\n", reg, data);
    V[reg] = data;
    PC += 2;
}

void ADD_V_BYTE(byte reg, byte data)
{
    printf("ADD V%01X %02X\n", reg, data);
    V[reg] += data;
    PC += 2;
}

void LD_VX_VY(byte reg_x, byte reg_y)
{
    printf("LD V%01X V%01X\n", reg_x, reg_y);
    V[reg_x] = V[reg_y];
    PC += 2;
}

void OR_VX_VY(byte reg_x, byte reg_y)
{
    printf("OR V%01X V%01X\n", reg_x, reg_y);
    V[reg_x] |= V[reg_y];
    PC += 2;
}

void AND_VX_VY(byte reg_x, byte reg_y)
{
    printf("AND V%01X V%01X\n", reg_x, reg_y);
    V[reg_x] &= V[reg_y];
    PC += 2;
}

void XOR_VX_VY(byte reg_x, byte reg_y)
{
    printf("XOR V%01X V%01X\n", reg_x, reg_y);
    V[reg_x] ^= V[reg_y];
    PC += 2;
}

void ADD_VX_VY(byte reg_x, byte reg_y)
{
    printf("ADD V%01X V%01X\n", reg_x, reg_y);
    byte tmp = V[reg_x] + V[reg_y];
    if(tmp < V[reg_x]) {
        V[0xF] = 1;
    }
    V[reg_x] = tmp;
    PC += 2;
}

void SUB_VX_VY(byte reg_x, byte reg_y)
{
    printf("SUB V%01X V%01X\n", reg_x, reg_y);
    if(V[reg_x] > V[reg_y]) {
        V[0xF] = 1;
    } else {
        V[0xF] = 0;
    }
    V[reg_x] -= V[reg_y];
    PC += 2;
}

void SHR_VX_VY(byte reg_x, byte reg_y)
{
    printf("SHR V%01X V%01X\n", reg_x, reg_y);
    if(V[reg_x] & 0x0001) {
        V[0xF] = 1;
    } else {
        V[0xF] = 0;
    }
    V[reg_x] >>= 1;
    PC += 2;
}

void SUBN_VX_VY(byte reg_x, byte reg_y)
{
    printf("SUBN V%01X V%01X\n", reg_x, reg_y);
    if(V[reg_y] > V[reg_x]) {
        V[0xF] = 1;
    } else {
        V[0xF] = 0;
    }
    V[reg_x] = V[reg_y] - V[reg_x];
    PC += 2;
}

void SHL_VX_VY(byte reg_x, byte reg_y)
{
    printf("SHL V%01X V%01X\n", reg_x, reg_y);
    if(V[reg_x] & 0x8000) {
        V[0xF] = 1;
    } else {
        V[0xF] = 0;
    }
    V[reg_x] <<= 1;
    PC += 2;
}

void SNE_VX_VY(byte reg_x, byte reg_y)
{
    printf("SNE V%01X V%01X\n", reg_x, reg_y);
    if(V[reg_x] != V[reg_y]) {
        PC += 2;
    }
    PC += 2;
}

void LD_I_addr(word address)
{
    printf("LD I %04X\n", address);
    I = address;
    PC += 2;
}

void JP_V0_addr(word address)
{
    printf("JP V0 %04X\n", address);
    PC = V[0] + address;
    PC += 2;
}

void RND_V_BYTE(byte reg, byte data)
{
    printf("RND V%01X %02X\n", reg, data);
    srand(time(0));
    byte random = rand() % 256;
    V[reg] = random & data;
    PC += 2;
}

void DRW(byte reg_x, byte reg_y, byte lines)
{
    printf("DRW V%01X V%01X %02X\n", reg_y, reg_x, lines);
    //VF is set to 1 if there is a collision (ie a bit in the sprite changes)
    //otherwise it's zero
    V[0xF] = 0;
    byte pixel;
    int x, y;

    for(y = 0; y < lines; y++) {
        pixel = memory[I + y];
        for(x = 0; x < 8; x++) {
            if((pixel & (0x80 >> x)) != 0) {
                if(screen[V[reg_y] + y][V[reg_x] + x] == 1)
                    V[0xF] = 1;                                 
                screen[V[reg_y] + y][V[reg_x] + x] ^= 1;
            }
        }
    }
    draw_flag = 1;

    PC += 2;
}

void SKP_V(byte reg)
{
    printf("SKP V%01X\n", reg);
    if(key[V[reg]] != 0) {
        PC += 2;
    }
    PC += 2;
}

void SKNP_V(byte reg)
{
    printf("SKNP V%01X\n", reg);
    if(key[V[reg]] == 0) {
        PC += 2;
    }
    PC += 2;
}

void LD_V_DT(byte reg)
{
    printf("LD V%01X DT\n", reg);
    V[reg] = delay_timer;
    PC += 2;
}

void LD_V_K(byte reg)
{
    printf("LD V%01X K\n", reg);
    byte pressed = 0;
    for(byte i = 0; i < 16; i++) {
        if(key[i] != 0)	{
            V[reg] = i;
            pressed = 1;
        }
    }
    if(pressed) {
        PC += 2;
    }
}

void LD_DT_V(byte reg)
{
    printf("LD DT V%01X\n", reg);
    delay_timer = V[reg];
    PC += 2;
}

void LD_ST_V(byte reg)
{
    printf("LD ST V%01X\n", reg);
    sound_timer = V[reg];
    PC += 2;
}

void ADD_I_V(byte reg)
{
    printf("ADD I V%01X\n", reg);
    I += V[reg];
    PC += 2;
}

void LD_F_V(byte reg)
{
    printf("LD F V%01X\n", reg);
    I = V[reg] * 0x5;
    PC += 2;
}

void LD_B_V(byte reg)
{
    printf("LD B V%01X\n", reg);
    byte hundreds, tens, ones;
    hundreds = V[reg] / 100;
    tens = (V[reg] / 10) % 10;
    ones = V[reg] % 10;
    memory[I + 0] = hundreds;
    memory[I + 1] = tens;
    memory[I + 2] = ones;
    PC += 2;
}

void LD_I_V(byte reg)
{
    printf("LD [I] V%01X\n", reg);
    byte i;
    for(i = 0; i <= reg; i++) {
        memory[I + i] = V[i];
    }
    PC += 2;
}

void LD_V_I(byte reg)
{
    printf("LD V%01X [I]\n", reg);
    for(byte i = 0; i <= reg; i++) {
        V[i] = memory[I + i];
    }
    PC += 2;
}
