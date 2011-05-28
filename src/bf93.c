#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "bf93.h"
#include "stack.h"

extern void (*ops[])(void);

int mode;
struct program_counter pc = { 0, 0, PC_EAST, PC_STAY }; 
char memory[WIDTH][HEIGHT];

static void populate(void)
{
    int c, x, y;

    for (y = 0; y < HEIGHT; ++y) {
        for (x = 0; x < WIDTH; ++x) {
            if ((c = getchar()) == EOF)
                return;
            if (c == '\n')
                break;
            memory[x][y] = c;
        }
        if (x == WIDTH)
            while ((c = getchar()) != '\n' && c != EOF)
                ;
    }
}

static void show(void)
{
    int x, y;

    for (x = 0; x < WIDTH; ++x)
        putchar('=');
    putchar('\n');
    
    for (y = 0; y < HEIGHT; ++y) {
        for (x = 0; x < WIDTH; ++x) {
            putchar(isprint(memory[x][y]) ? memory[x][y] : ' ');
        }
        putchar('\n');
    }
    
    for (x = 0; x < WIDTH; ++x)
        putchar('=');
    putchar('\n');
}

int main(void)
{
    populate();
    show();

    for (;;) {
        int op = memory[pc.x][pc.y];

        if (mode && op != '"')  /* text mode */
            stack_push(op);
        else                    /* code mode */
            if (op < 128 && op > 0)
                ops[op]();
        pc_advance();
    }
    puts("oh noes");
    return EXIT_FAILURE; /* shouldn't reach */
}
