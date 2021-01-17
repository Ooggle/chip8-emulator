#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <time.h>

void initialize_jump_table(struct s_jump *table);
void initialize_memory_fonts(Uint8 *memory);
void initialize_cpu(struct s_cpu *cpu);
void count(struct s_cpu *cpu);
int load_rom(struct s_cpu *cpu, const char path[]);
void clear_screen(struct s_screen *screen);
int initialize_screen(struct s_screen *screen);
void destroy_screen(struct s_screen *screen);
void update_screen(struct s_screen *screen);
void update_event(struct s_input *input);
int initialize_SDL(void);
void destroy_SDL(void);
int initialize_emulator(struct s_emulator *emulator);
void destroy_emulator(struct s_emulator *emulator);
void resize_screen(struct s_screen *screen);
uint16_t get_opcode(struct s_cpu *cpu);
Uint8 get_action(struct s_jump *table, Uint16 opcode);
void interpret(struct s_emulator *emulator);
void emulate(struct s_emulator *emulator);
int main(int argc, char *argv[]);

#endif
