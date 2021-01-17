#include "structs.h"
#include "opcodes.h"
#include "main.h"

void opcode_DXYN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 23
{
    struct s_cpu *cpu = &emulator->cpu;
    cpu->V[0xF] = 0;

    printf("-- display --\n");    

    for(size_t i = 0; i < b1; i++)
    {
        Uint8 codage = cpu->memory[cpu->I + i];
        Uint8 y = cpu->V[b2] + i;

        for(size_t j = 0; j < 8; j++)
        {
            Uint8 x = cpu->V[b3] + j;
            printf("x=%d, y=%d\n", x, y);
            if(y < PIXEL_BY_HEIGHT && x < PIXEL_BY_WIDTH && ((codage << j) & 0b10000000))
            {
                if((emulator->screen.pixels[x][y] == WHITE))
                    cpu->V[0xF] = 1;
                emulator->screen.pixels[x][y] = !emulator->screen.pixels[x][y]; /* change bit color. */
            }
        }
    }
}

void opcode_1NNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 3
{
    emulator->cpu.pc = (b3 << 8) + (b2 << 4) + b1 - 2;
}

void opcode_2NNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 4
{
    struct s_cpu *cpu = &emulator->cpu; 
    cpu->jump[cpu->jump_nb] = cpu->pc;
    if(cpu->jump_nb < MAX_JUMP)
        cpu->jump_nb++;

    cpu->pc = (b3 << 8) + (b2 << 4) + b1 - 2;
}

void opcode_00EE(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 2
{
    struct s_cpu *cpu = &emulator->cpu;
    if(cpu->jump_nb > 0)
    {
        cpu->jump_nb--;
        cpu->pc = cpu->jump[cpu->jump_nb];
    }
}

void opcode_3XNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 5
{
    struct s_cpu *cpu = &emulator->cpu;
    if(cpu->V[b3] == (b2 << 4) + b1)
        cpu->pc += 2;
}

void opcode_8XY4(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 14
{
    struct s_cpu *cpu = &emulator->cpu;
    cpu->V[0xF] = cpu->V[b2] > 0xFF - cpu->V[b3];
    cpu->V[b3] += cpu->V[b2];
}

void opcode_8XY7(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 17
{
    struct s_cpu *cpu = &emulator->cpu;
    cpu->V[0xF] = cpu->V[b3] <= cpu->V[b2];
    cpu->V[b3] = cpu->V[b2] - cpu->V[b3];
}

int rand_int(int min, int max)
{
    return (rand() / (RAND_MAX + 1.)) * (max - min + 1) + min;
}

void opcode_CXNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 22
{
    emulator->cpu.V[b3] = rand_int(0, 0xFF) & ((b2 << 4) + b1);
}

void opcode_FX33(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 32
{
    struct s_cpu *cpu = &emulator->cpu;
    Uint8 nb = cpu->V[b3];
    cpu->memory[cpu->I + 2] = nb % 10;
    cpu->memory[cpu->I + 1] = (nb/10) % 10;
    cpu->memory[cpu->I] = nb / 100;
}

void opcode_00E0(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 1
{
    clear_screen(&emulator->screen);
}

void opcode_FX29(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 31
{
    struct s_cpu *cpu = &emulator->cpu;
    cpu->I = 5 * cpu->V[b3];
}

void opcode_4XNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 6
{
    struct s_cpu *cpu = &emulator->cpu;
    if(cpu->V[b3] != ((b2 << 4) + b1))
        cpu->pc += 2;
}
void opcode_5XY0(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 7
{
    struct s_cpu *cpu = &emulator->cpu;
    if(cpu->V[b3] == cpu->V[b2])
        cpu->pc += 2;
}
void opcode_6XNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 8
{
    struct s_cpu *cpu = &emulator->cpu;
    cpu->V[b3] = ((b2 << 4) + b1);
}
void opcode_7XNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 9
{
    struct s_cpu *cpu = &emulator->cpu;
    cpu->V[b3] += ((b2 << 4) + b1);
}
void opcode_8XY0(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3){} // 10
void opcode_8XY1(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 11
{
    struct s_cpu *cpu = &emulator->cpu;
    cpu->V[b3] |= cpu->V[b2];
}
void opcode_8XY2(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 12
{
    struct s_cpu *cpu = &emulator->cpu;
    cpu->V[b3] &= cpu->V[b2];
}
void opcode_8XY3(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 13
{
    struct s_cpu *cpu = &emulator->cpu;
    cpu->V[b3] ^= cpu->V[b2];
}
void opcode_8XY5(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3){}
void opcode_8XY6(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3){}
void opcode_8XYE(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3){}
void opcode_9XY0(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3){}
void opcode_ANNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 20
{
    struct s_cpu *cpu = &emulator->cpu;
    cpu->I = ((b3 << 8) + (b2 << 4) + b1);
}
void opcode_BNNN(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3){}
void opcode_EX9E(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3){}
void opcode_EXA1(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3){}
void opcode_FX07(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3){}
void opcode_FX0A(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3) // 27
{
    getchar();
    //TODO
}
void opcode_FX15(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3){}
void opcode_FX18(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3){}
void opcode_FX1E(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3){}
void opcode_FX55(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3){}
void opcode_FX65(struct s_emulator *emulator, Uint8 b1, Uint8 b2, Uint8 b3){}
