#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL2/SDL.h>

#define MEMORY_SIZE 4096
#define START_ADDRESS 512

#define BLACK SDL_FALSE
#define WHITE SDL_TRUE
#define PIXEL_BY_WIDTH 64
#define PIXEL_BY_HEIGHT 32
#define PIXEL_DIM 8
#define WIDTH  PIXEL_BY_WIDTH*PIXEL_DIM 
#define HEIGHT PIXEL_BY_HEIGHT*PIXEL_DIM

#define FPS 16
#define OPCODE_NB 35
#define MAX_JUMP 15

typedef SDL_bool s_pixel;

struct s_jump
{
    Uint16 mask[OPCODE_NB];
    Uint16 id[OPCODE_NB];
    /* int pointer[OPCODE_NB]; */
};

struct s_cpu
{
    uint8_t memory[MEMORY_SIZE];
    uint8_t V[16];
    uint16_t I;
    uint16_t jump[16];
    uint8_t jump_nb;
    uint8_t sys_counter;
    uint8_t sound_counter;
    uint16_t pc;
    struct s_jump jump_table;
};

struct s_screen
{
    SDL_Window *w;
    SDL_Renderer *r;
    s_pixel pixels[PIXEL_BY_WIDTH][PIXEL_BY_HEIGHT];
    Uint32 pixel_height;
    Uint32 pixel_width;
};

struct s_input
{
    SDL_bool key[SDL_NUM_SCANCODES];
    SDL_bool quit;
    int x, y, xrel, yrel;
    int xwheel, ywheel;
    SDL_bool mouse[6];
    SDL_bool resize;
};

struct s_emulator
{
    struct s_cpu cpu;
    struct s_screen screen;
    struct s_input in;
};

#endif
