#ifndef STACK_H__
#define STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#ifndef STACK_SIZE
    #define STACK_SIZE 8192
#endif
typedef long int stack_data;
#define STACK_DATA_FMT "%ld"

struct stack {
    stack_data data[STACK_SIZE];
    int counter;
} s;

extern const char *prog;

#define stack_pop()                                             \
    do {                                                        \
        if (s.counter > 0)                                      \
        s.counter--;                                            \
    } while (0)

#define stack_popret(x)                                         \
    do {                                                        \
        *(x) = s.counter == 0 ? 0 : s.data[--s.counter];        \
    } while (0)

#ifndef VROOM
    #define stack_push(x)                                       \
        do {                                                    \
            if (STACK_SIZE - s.counter == 0) {                  \
                fprintf(stderr, "%s: Stack overflow\n", prog);  \
                exit(EXIT_FAILURE);                             \
            } else                                              \
            s.data[s.counter++] = (x);                          \
        } while (0)
#else
    #define stack_push(x)                                       \
        do {                                                    \
            s.data[s.counter++] = (x);                          \
        } while (0)
#endif

#define stack_top(x)                                            \
    do {                                                        \
        *(x) = s.data[s.counter - 1];                           \
    } while (0)

#ifndef VROOM
    #define stack_dup()                                         \
        do {                                                    \
            if (STACK_SIZE - s.counter == 0) {                  \
                fprintf(stderr, "%s: Stack overflow\n", prog);  \
                exit(EXIT_FAILURE);                             \
            }                                                   \
            s.data[s.counter] = s.data[s.counter - 1];          \
            s.counter++;                                        \
        } while (0)
#else
    #define stack_dup()                                         \
        do {                                                    \
            s.data[s.counter] = s.data[s.counter-1];            \
            s.counter++;                                        \
        } while (0)
#endif

#ifndef VROOM
    #define stack_swp()                                         \
        do {                                                    \
            stack_data tmp;                                     \
            if (s.counter < 2) {                                \
                fprintf(stderr, "%s: Stack underflow\n", prog); \
                exit(EXIT_FAILURE);                             \
            }                                                   \
            tmp = s.data[s.counter - 1];                        \
            s.data[s.counter - 1] = s.data[s.counter - 2];      \
            s.data[s.counter - 2] = tmp;                        \
        } while (0)
#else
    #define stack_swp()                                         \
        do {                                                    \
            stack_data tmp = s.data[s.counter - 1];             \
            s.data[s.counter - 1] = s.data[s.counter - 2];      \
            s.data[s.counter - 2] = tmp;                        \
        } while (0)
#endif

#define stack_debug()                                           \
    do {                                                        \
        int i;                                                  \
        for (i = 0; i < s.counter; ++i)                         \
            fprintf(stderr, "[%c](" STACK_DATA_FMT ") ",        \
                    isprint((unsigned char)s.data[i]) ?         \
                    (int)s.data[i] :                            \
                    ' ',                                        \
                    s.data[i]);                                 \
        fputc('\n', stdout);                                    \
    } while (0)

#ifndef VROOM
    #define stack_op(op)                                        \
        do {                                                    \
            if (s.counter < 2) {                                \
                fprintf(stderr, "%s: Stack underflow\n", prog); \
                exit(EXIT_FAILURE);                             \
            }                                                   \
            s.data[s.counter - 2] = s.data[s.counter - 2] op    \
                                    s.data[s.counter - 1];      \
            s.counter--;                                        \
        } while (0)
#else
    #define stack_op(op)                                        \
        do {                                                    \
            s.data[s.counter - 2] = s.data[s.counter - 2] op    \
                                    s.data[s.counter - 1];      \
            s.counter--;                                        \
        } while (0)
#endif

#endif /* STACK_H__ */
