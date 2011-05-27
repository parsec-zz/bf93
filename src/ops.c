#include <stdio.h>
#include <stdlib.h>

#include "bf93.h"
#include "stack.h"

//struct program_counter pc;
//struct stack s;

extern int mode;

static void bf_nop(void) { }


static void bf_add(void)
{
    stack_op(+);
} 

static void bf_substract(void)
{
    stack_op(-);
} 

static void bf_multiply(void)
{
    stack_op(*);
} 

static void bf_divide(void)
{
    stack_op(/);
} 

static void bf_modulo(void)
{
    stack_op(%);
} 

static void bf_not(void) { } 

static void bf_greater(void)
{
    stack_op(>);
} 

static void bf_right(void)
{
    pc_set_east();
} 

static void bf_left(void)
{
    pc_set_west();
} 

static void bf_up(void)
{
    pc_set_north();
} 

static void bf_down(void)
{
    pc_set_south();
} 

static void bf_random(void) { } 

static void bf_horizontal_if(void)
{
    int x;
    stack_popret(x);
    if (x)
        pc_set_west();
    else
        pc_set_east();
} 

static void bf_vertical_if(void) { } 

static void bf_stringmode(void)
{
    mode = !mode;
} 

static void bf_dup(void)
{
    stack_dup();
} 

static void bf_swap(void)
{
    stack_swp();
} 

static void bf_pop(void)
{
    stack_pop();
} 

static void bf_pop_int(void)
{
    int x;
    stack_popret(x);
    printf("%d", x);
} 

static void bf_pop_char(void)
{
    int x;
    stack_popret(x);
    putchar(x);
} 

static void bf_bridge(void)
{
    pc_advance();
} 

static void bf_get(void) { } 

static void bf_put(void) { } 

static void bf_input_value(void) { } 

static void bf_input_character(void) { } 

static void bf_push0(void)
{
    stack_push(0);
}

static void bf_push1(void) { }

static void bf_push2(void) { }

static void bf_push3(void) { }

static void bf_push4(void) { }

static void bf_push5(void) { }

static void bf_push6(void) { }

static void bf_push7(void) { }

static void bf_push8(void) { }

static void bf_push9(void) { }

static void bf_end(void)
{
    putchar('\n');
    exit(EXIT_SUCCESS);
} 

void (*ops[])(void) = {
#define A &bf_nop
#define B A, A, A, A,  A, A, A, A
#define C B, B, B, B,  B, B, B, B
    C, C,
#undef C
#undef B
#undef A
    ['+'] = &bf_add,
    ['-'] = &bf_substract,
    ['*'] = &bf_multiply,
    ['/'] = &bf_divide,
    ['%'] = &bf_modulo,
    ['!'] = &bf_not,
    ['`'] = &bf_greater,
    ['>'] = &bf_right,
    ['<'] = &bf_left,
    ['^'] = &bf_up,
    ['v'] = &bf_down,
    ['?'] = &bf_random,
    ['_'] = &bf_horizontal_if,
    ['|'] = &bf_vertical_if,
    ['"'] = &bf_stringmode,
    [':'] = &bf_dup,
    ['\\'] = &bf_swap,
    ['$'] = &bf_pop,
    ['.'] = &bf_pop_int,
    [','] = &bf_pop_char,
    ['#'] = &bf_bridge,
    ['g'] = &bf_get,
    ['p'] = &bf_put,
    ['&'] = &bf_input_value,
    ['~'] = &bf_input_character,
    ['0'] = &bf_push0,
    ['1'] = &bf_push1,
    ['2'] = &bf_push2,
    ['3'] = &bf_push3,
    ['4'] = &bf_push4,
    ['5'] = &bf_push5,
    ['6'] = &bf_push6,
    ['7'] = &bf_push7,
    ['8'] = &bf_push8,
    ['9'] = &bf_push9,
    ['@'] = &bf_end
};
