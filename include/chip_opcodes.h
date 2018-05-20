#ifndef OPCODES_H
#define OPCODES_H

#include "chip_structs.h"

void decode_execute_opcode(word opcode);

/** Executable opcodes **/

//0x0nnn (ignored)
void SYS(word adrress);
//0x00E0
void CLS();
//0x00EE
void RET();
//0x1nnn
void JP(word address);
//0x2nnn
void CALL(word address);
//0x3xkk
void SE_V_BYTE(byte reg, byte data);
//0x4xkk
void SNE_V_BYTE(byte reg, byte data);
//0x5xy0
void SE_VX_VY(byte reg_x, byte reg_y);
//0x6xkk
void LD_V_BYTE(byte reg, byte data);
//0x7xkk
void ADD_V_BYTE(byte reg, byte data);
//0x8xy0
void LD_VX_VY(byte reg_x, byte reg_y);
//0x8xy1
void OR_VX_VY(byte reg_x, byte reg_y);
//0x8xy2
void AND_VX_VY(byte reg_x, byte reg_y);
//0x8xy3
void XOR_VX_VY(byte reg_x, byte reg_y);
//0x8xy4
void ADD_VX_VY(byte reg_x, byte reg_y);
//0x8xy5
void SUB_VX_VY(byte reg_x, byte reg_y);
//0x8xy6
void SHR_VX_VY(byte reg_x, byte reg_y);
//0x8xy7
void SUBN_VX_VY(byte reg_x, byte reg_y);
//0x8xyE
void SHL_VX_VY(byte reg_x, byte reg_y);
//0x9xy0
void SNE_VX_VY(byte reg_x, byte reg_y);
//0xAnnn
void LD_I_addr(word address);
//0xBnnn
void JP_V0_addr(word address);
//0xCxkk - RND Vx, byte
void RND_V_BYTE(byte reg, byte data);
//0xDxyn - DRW Vx, Vy, nibble
void DRW(byte reg_x, byte reg_y, byte lines);
//0xEx9E - SKP Vx
void SKP_V(byte reg);
//0xEx41
void SKNP_V(byte reg);
//0xFx07
void LD_V_DT(byte reg);
//OxFx0A
void LD_V_K(byte reg);
//0xFx15
void LD_DT_V(byte reg);
//0xFx18
void LD_ST_V(byte reg);
//0xFx1E
void ADD_I_V(byte reg);
//0XFx29
void LD_F_V(byte reg);
//0xFx33
void LD_B_V(byte reg);
//0xFx55
void LD_I_V(byte reg);
//0xFx65
void LD_V_I(byte reg);

#endif