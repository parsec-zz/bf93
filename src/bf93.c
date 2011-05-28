#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include <getopt.h>

#include "bf93.h"
#include "stack.h"

const char *prog = "bf93";

extern void (*ops[])(void);

int mode;
struct program_counter pc = { 0, 0, PC_EAST, PC_STAY }; 

typedef int mem_data;
mem_data memory[WIDTH][HEIGHT];

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
            while ((c = fgetc(stream)) != '\n' && c != EOF)
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
            putchar(isprint(memory[x][y]) ? (int)memory[x][y] : ' ');
        }
        putchar('\n');
    }
    
    for (x = 0; x < WIDTH; ++x)
        putchar('=');
    putchar('\n');
}

static void usage(FILE *stream)
{
    fprintf(stream,
            "usage: %s [option] <filename>\n"
            " -h    display this message\n"
            " -s    show populated memory\n",
            prog);
}

int main(int argc, char **argv)
{
    if (argv[0] && argv[0][0])
        prog = argv[0];
    
    {
        FILE *fp;
        int c, do_show = 0;
        
        while ((c = getopt(argc, argv, "hs")) != -1) {
            switch (c) {
                case 'h':
                    usage(stdout);
                    return EXIT_SUCCESS;

                case 's':
                    do_show = 1;
                    break;

                default:
                    usage(stderr);
                    return EXIT_FAILURE;
            }    
        }

        if (optind != argc - 1) {
            usage(stderr);
            return EXIT_FAILURE;
        }
        if (!(fp = fopen(argv[optind], "r"))) {
            fprintf(stderr, "%s: %s: %s\n", prog, argv[optind], strerror(errno));
            return EXIT_FAILURE;
        }
        populate(fp);
        fclose(fp);

        if (do_show)
            show();
    }

    for (;;) {
        mem_data c = memory[pc.x][pc.y];

        if (mode && c != '"')  /* text mode */
            stack_push(c);
        else                    /* code mode */
            if (c < 128 && c > 0)
                ops[c]();
        pc_advance();
    }
    return EXIT_FAILURE; /* shouldn't reach */
}
