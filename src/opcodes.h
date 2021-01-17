#ifndef OPCODES_H
#define OPCODES_H

#include <SDL2/SDL.h>
#include <time.h>

#include <stdint.h>
#include <stdio.h>

void opcode_DXYN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_1NNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_2NNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_00EE(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_3XNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_8XY4(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_8XY7(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
int rand_int();
void opcode_CXNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_FX33(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_00E0(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_FX29(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_4XNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_5XY0(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_6XNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_7XNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_7XNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_8XY1(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_8XY2(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_8XY3(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_8XY5(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_8XY6(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_8XYE(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_9XY0(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_ANNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_BNNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_EX9E(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_EXA1(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_FX07(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_FX0A(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_FX15(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_FX18(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_FX1E(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_FX55(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);
void opcode_FX65(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3);

#endif
