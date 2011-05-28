#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "bf93.h"
#include "stack.h"

extern void (*ops[])(void);

int mode;
struct program_counter pc = { 0, 0, PC_EAST, PC_STAY }; 
char memory[WIDTH][HEIGHT];

static void populate(FILE *stream)
{
    int c, x, y;

    for (y = 0; y < HEIGHT; ++y) {
        for (x = 0; x < WIDTH; ++x) {
            if ((c = fgetc(stream)) == EOF)
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

/* FIXME add actual argument handling
 */
int main(int argc, char **argv)
{
    FILE *fp;

    if (argc != 2)
        return EXIT_FAILURE;

    if (!(fp = fopen(argv[1], "r")))
        return EXIT_FAILURE;

    populate(fp);
    fclose(fp);

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
    return EXIT_FAILURE; /* shouldn't reach */
}
