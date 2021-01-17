/* Main program
 * dependencies: SDL2
 * compilation: gcc main.c opcodes.c `sdl2-config --cflags --libs` -o main
 */

#include "structs.h"
#include "opcodes.h"
#include "main.h"

void initialize_jump_table(struct s_jump *table)
{
    table->mask[0]= 0x0000;  table->id[0]=0x0FFF;           /* 0NNN */
    table->mask[1]= 0xFFFF;  table->id[1]=0x00E0;           /* 00E0 */
    table->mask[2]= 0xFFFF;  table->id[2]=0x00EE;           /* 00EE */
    table->mask[3]= 0xF000;  table->id[3]=0x1000;           /* 1NNN */
    table->mask[4]= 0xF000;  table->id[4]=0x2000;           /* 2NNN */
    table->mask[5]= 0xF000;  table->id[5]=0x3000;           /* 3XNN */
    table->mask[6]= 0xF000;  table->id[6]=0x4000;           /* 4XNN */
    table->mask[7]= 0xF00F;  table->id[7]=0x5000;           /* 5XY0 */
    table->mask[8]= 0xF000;  table->id[8]=0x6000;           /* 6XNN */
    table->mask[9]= 0xF000;  table->id[9]=0x7000;           /* 7XNN */
    table->mask[10]= 0xF00F; table->id[10]=0x8000;          /* 8XY0 */
    table->mask[11]= 0xF00F; table->id[11]=0x8001;          /* 8XY1 */
    table->mask[12]= 0xF00F; table->id[12]=0x8002;          /* 8XY2 */
    table->mask[13]= 0xF00F; table->id[13]=0x8003;          /* 8XY3 */
    table->mask[14]= 0xF00F; table->id[14]=0x8004;          /* 8XY4 */
    table->mask[15]= 0xF00F; table->id[15]=0x8005;          /* 8XY5 */
    table->mask[16]= 0xF00F; table->id[16]=0x8006;          /* 8XY6 */
    table->mask[17]= 0xF00F; table->id[17]=0x8007;          /* 8XY7 */
    table->mask[18]= 0xF00F; table->id[18]=0x800E;          /* 8XYE */
    table->mask[19]= 0xF00F; table->id[19]=0x9000;          /* 9XY0 */
    table->mask[20]= 0xF000; table->id[20]=0xA000;          /* ANNN */
    table->mask[21]= 0xF000; table->id[21]=0xB000;          /* BNNN */
    table->mask[22]= 0xF000; table->id[22]=0xC000;          /* CXNN */
    table->mask[23]= 0xF000; table->id[23]=0xD000;          /* DXYN */
    table->mask[24]= 0xF0FF; table->id[24]=0xE09E;          /* EX9E */
    table->mask[25]= 0xF0FF; table->id[25]=0xE0A1;          /* EXA1 */
    table->mask[26]= 0xF0FF; table->id[26]=0xF007;          /* FX07 */
    table->mask[27]= 0xF0FF; table->id[27]=0xF00A;          /* FX0A */
    table->mask[28]= 0xF0FF; table->id[28]=0xF015;          /* FX15 */
    table->mask[29]= 0xF0FF; table->id[29]=0xF018;          /* FX18 */
    table->mask[30]= 0xF0FF; table->id[30]=0xF01E;          /* FX1E */
    table->mask[31]= 0xF0FF; table->id[31]=0xF029;          /* FX29 */
    table->mask[32]= 0xF0FF; table->id[32]=0xF033;          /* FX33 */
    table->mask[33]= 0xF0FF; table->id[33]=0xF055;          /* FX55 */
    table->mask[34]= 0xF0FF; table->id[34]=0xF065;          /* FX65 */
}

void initialize_memory_fonts(Uint8 *memory)
{
    memory[0]=0xF0;memory[1]=0x90;memory[2]=0x90;memory[3]=0x90; memory[4]=0xF0; // O
    memory[5]=0x20;memory[6]=0x60;memory[7]=0x20;memory[8]=0x20;memory[9]=0x70; // 1
    memory[10]=0xF0;memory[11]=0x10;memory[12]=0xF0;memory[13]=0x80; memory[14]=0xF0; // 2
    memory[15]=0xF0;memory[16]=0x10;memory[17]=0xF0;memory[18]=0x10;memory[19]=0xF0; // 3
    memory[20]=0x90;memory[21]=0x90;memory[22]=0xF0;memory[23]=0x10;memory[24]=0x10; // 4
    memory[25]=0xF0;memory[26]=0x80;memory[27]=0xF0;memory[28]=0x10;memory[29]=0xF0; // 5
    memory[30]=0xF0;memory[31]=0x80;memory[32]=0xF0;memory[33]=0x90;memory[34]=0xF0; // 6
    memory[35]=0xF0;memory[36]=0x10;memory[37]=0x20;memory[38]=0x40;memory[39]=0x40; // 7
    memory[40]=0xF0;memory[41]=0x90;memory[42]=0xF0;memory[43]=0x90;memory[44]=0xF0; // 8
    memory[45]=0xF0;memory[46]=0x90;memory[47]=0xF0;memory[48]=0x10;memory[49]=0xF0; // 9
    memory[50]=0xF0;memory[51]=0x90;memory[52]=0xF0;memory[53]=0x90;memory[54]=0x90; // A
    memory[55]=0xE0;memory[56]=0x90;memory[57]=0xE0;memory[58]=0x90;memory[59]=0xE0; // B
    memory[60]=0xF0;memory[61]=0x80;memory[62]=0x80;memory[63]=0x80;memory[64]=0xF0; // C
    memory[65]=0xE0;memory[66]=0x90;memory[67]=0x90;memory[68]=0x90;memory[69]=0xE0; // D
    memory[70]=0xF0;memory[71]=0x80;memory[72]=0xF0;memory[73]=0x80;memory[74]=0xF0; // E
    memory[75]=0xF0;memory[76]=0x80;memory[77]=0xF0;memory[78]=0x80;memory[79]=0x80; // F
}

void initialize_cpu(struct s_cpu *cpu)
{
    memset(cpu, 0, sizeof(*cpu));
    initialize_memory_fonts(cpu->memory);
    initialize_jump_table(&cpu->jump_table);
    cpu->pc = START_ADDRESS;
}

void count(struct s_cpu *cpu)
{
    if(cpu->sys_counter > 0)
        cpu->sys_counter--;
    if(cpu->sound_counter > 0)
        cpu->sound_counter--;
}

int load_rom(struct s_cpu *cpu, const char path[])
{
    FILE *rom = fopen(path, "rb");
    if(!rom)
    {
        perror("Error fopen:");
        return -1;
    }
    fread(&cpu->memory[START_ADDRESS], sizeof(uint8_t) * (MEMORY_SIZE - START_ADDRESS), 1, rom);
    fclose(rom);
    return 0;
}

void clear_screen(struct s_screen *screen)
{
    memset(screen->pixels, BLACK, sizeof(screen->pixels));
}

int initialize_screen(struct s_screen *screen)
{
    screen->w = SDL_CreateWindow("Emulateur", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(NULL == screen->w)
    {
        fprintf(stderr, "Error SDL_CreateWindow: %s.\n", SDL_GetError());
        return -1;
    }
    screen->r = SDL_CreateRenderer(screen->w, -1, SDL_RENDERER_ACCELERATED);
    if(NULL == screen->r)
    {
        fprintf(stderr, "Error SDL_CreateRenderer: %s.\n", SDL_GetError());
        SDL_DestroyWindow(screen->w);
        return -2;
    }
    clear_screen(screen);
    screen->pixel_height = PIXEL_DIM;
    screen->pixel_width = PIXEL_DIM;
    return 0;
}

void destroy_screen(struct s_screen *screen)
{
    SDL_DestroyRenderer(screen->r);
    SDL_DestroyWindow(screen->w);
}

void update_screen(struct s_screen *screen)
{
    SDL_SetRenderDrawColor(screen->r, 0, 0, 0, 255);
    SDL_RenderClear(screen->r);
    SDL_SetRenderDrawColor(screen->r, 255, 255, 255, 255);
    for(size_t i = 0; i < PIXEL_BY_WIDTH; i++)
    {
        for(size_t j = 0; j < PIXEL_BY_HEIGHT; j++)
        {
            if(screen->pixels[i][j] == WHITE)
            {
                SDL_Rect pixel_rect = {
                    screen->pixel_width * i, screen->pixel_height * j,
                    screen->pixel_width, screen->pixel_height
                };
                SDL_RenderFillRect(screen->r, &pixel_rect);
            }
        }
    }
    SDL_RenderPresent(screen->r);
}

void update_event(struct s_input *input)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            input->quit = SDL_TRUE;
        else if(event.type == SDL_KEYDOWN)
            input->key[event.key.keysym.scancode] = SDL_TRUE;
        else if(event.type == SDL_KEYUP)
            input->key[event.key.keysym.scancode] = SDL_FALSE;
        else if(event.type == SDL_MOUSEMOTION)
        {
            input->x = event.motion.x;
            input->y = event.motion.y;
            input->xrel = event.motion.xrel;
            input->yrel = event.motion.yrel;
        }
        else if(event.type == SDL_MOUSEWHEEL)
        {
            input->xwheel = event.wheel.x;
            input->ywheel = event.wheel.y;
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN)
              input->mouse[event.button.button] = SDL_TRUE;
        else if(event.type == SDL_MOUSEBUTTONUP)
            input->mouse[event.button.button] = SDL_FALSE;
        else if(event.type == SDL_WINDOWEVENT)
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                input->resize = SDL_TRUE;
    }
}

int initialize_SDL(void)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Error SDL_Init: %s.\n", SDL_GetError());
        return -1;
    }
    return 0;
}

void destroy_SDL(void)
{
    SDL_Quit();
}

int initialize_emulator(struct s_emulator *emulator)
{
    int status = -1;
    initialize_cpu(&emulator->cpu);
    memset(&emulator->in, 0, sizeof(emulator->in));
    if(0 == initialize_SDL())
    {
        int status = initialize_screen(&emulator->screen);
        if(0 > status)
            destroy_SDL();        
    }
    return status;
}

void destroy_emulator(struct s_emulator *emulator)
{
    destroy_screen(&emulator->screen);
    destroy_SDL();
}

/* void set_pixels(struct s_screen *screen)
{
    for(size_t i = 0; i < PIXEL_BY_WIDTH; i++)
        for(size_t j = 0; j < PIXEL_BY_HEIGHT; j++)
            screen->pixels[i][j] = (i % (j + 8)) != 0;
} */

void resize_screen(struct s_screen *screen)
{
    int w, h;
    SDL_GetWindowSize(screen->w, &w, &h);
    screen->pixel_height = h / PIXEL_BY_HEIGHT;
    screen->pixel_width = w / PIXEL_BY_WIDTH;
}

uint16_t get_opcode(struct s_cpu *cpu)
{
    return (cpu->memory[cpu->pc] << 8) + cpu->memory[cpu->pc + 1];
}

Uint8 get_action(struct s_jump *table, Uint16 opcode)
{
    for(size_t i = 0; i < OPCODE_NB; i++)
    {
        if((table->mask[i] & opcode) == table->id[i])
            return i;
    }
    fprintf(stderr, "Bad action, unknown opcode %s.\n", opcode);
    return 0;
}

void interpret(struct s_emulator *emulator)
{
    Uint16 opcode = get_opcode(&emulator->cpu);
    Uint8 b3, b2, b1;
    b3 = (opcode & (0x0F00)) >> 8;
    b2 = (opcode & (0x00F0)) >> 4;
    b1 = (opcode & (0x000F));
    Uint8 action = get_action(&emulator->cpu.jump_table, opcode);

    printf("opcode: %X, %d, %X\n", opcode, action, (opcode & 0x0FFF));

    switch(action)
    {
        case 1:
            opcode_00E0(emulator, b1, b2, b3);
            break;
        case 2:
            opcode_00EE(emulator, b1, b2, b3);
            break;
        case 3:
            opcode_1NNN(emulator, b1, b2, b3);
            break;
        case 4:
            opcode_2NNN(emulator, b1, b2, b3);
            break;
        case 5:
            opcode_3XNN(emulator, b1, b2, b3);
            break;
        case 6:
            opcode_4XNN(emulator, b1, b2, b3);
            break;
        case 7:
            opcode_5XY0(emulator, b1, b2, b3);
            break;
        case 8:
            opcode_6XNN(emulator, b1, b2, b3);
            break;
        case 9:
            opcode_7XNN(emulator, b1, b2, b3);
            break;
        case 11:
            opcode_8XY1(emulator, b1, b2, b3);
            break;
        case 12:
            opcode_8XY2(emulator, b1, b2, b3);
            break;
        case 13:
            opcode_8XY3(emulator, b1, b2, b3);
            break;
        case 14:
            opcode_8XY4(emulator, b1, b2, b3);
            break;
        case 17:
            opcode_8XY7(emulator, b1, b2, b3);
            break;
        case 20:
            opcode_ANNN(emulator, b1, b2, b3);
            break;
        case 22:
            opcode_CXNN(emulator, b1, b2, b3);
            break;
        case 23:
            opcode_DXYN(emulator, b1, b2, b3);
            break;
        case 27:
            opcode_FX0A(emulator, b1, b2, b3);
            break;
        case 31:
            opcode_FX29(emulator, b1, b2, b3);
            break;
        case 32:
            opcode_FX33(emulator, b1, b2, b3);
            break;
        
        default:
            break;
    }
    
    emulator->cpu.pc += 2;
}



void emulate(struct s_emulator *emulator)
{
    //set_pixels(&emulator->screen);
    while(!emulator->in.quit)
    {
        update_event(&emulator->in);
        if(emulator->in.resize)
            resize_screen(&emulator->screen); 

        /* 4 cycles */
        for(size_t i = 0; i < 3; i++)
        {
            interpret(emulator);
        }
        update_screen(&emulator->screen);
        SDL_Delay(FPS);
    }
}

int main(int argc, char *argv[])
{
    struct s_emulator emulator = {0};
    int status = -1;
    srand(time(NULL));
    if(initialize_emulator(&emulator))
    {
        if(0 == load_rom(&emulator.cpu, "IBM Logo.ch8"))
        {
            status = 0;
            emulate(&emulator);
        }
        destroy_emulator(&emulator);
    }
    return status;
}



