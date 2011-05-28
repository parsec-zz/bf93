#ifndef STACK_H__
#define STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef STACK_SIZE
    #define STACK_SIZE 4098
#endif
typedef long int stack_data;
#define STACK_DATA_FMT "%ld"

struct stack {
    stack_data data[STACK_SIZE];
    int counter;
} s;

extern const char *prog;

#ifdef INLINE
    static inline void stack_pop(void)
    {
    }

    static inline void stack_popret(int *x)
    {
    }

    static inline void stack_push(int x)
    {
    }

    static inline void stack_top(int *x)
    {
    }

    static inline void stack_dup(void)
    {
    }

    static inline void stack_swp(void)
    {
    }

    static inline void stack_debug(void)
    {
    }
#else
    #define stack_pop()                                         \
        do {                                                    \
            if (s.counter > 0)                                  \
                s.counter--;                                    \
        } while (0)

    #define stack_popret(x)                                     \
        do {                                                    \
            *(x) = s.counter == 0 ? 0 : s.data[--s.counter];    \
        } while (0)

    #define stack_push(x)                                       \
        do {                                                    \
            if (STACK_SIZE - s.counter == 0) {                  \
                fprintf(stderr, "%s: Stack overflow\n", prog);  \
                exit(EXIT_FAILURE);                             \
            } else                                              \
                s.data[s.counter++] = (x);                      \
        } while (0)

    #define stack_top(x)                                        \
        do {                                                    \
            *(x) = s.data[s.counter - 1];                       \
        } while (0)

    #define stack_dup()                                         \
        do {                                                    \
            s.data[s.counter] = s.data[s.counter - 1];          \
            s.counter++;                                        \
        } while (0)

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

    #define stack_debug()                                       \
        do {                                                    \
            int i;                                              \
            for (i = 0; i < s.counter; ++i)                     \
                fprintf(stderr, "[%c](" STACK_DATA_FMT ") ",    \
                        isprint(s.data[i]) ?                    \
                            (int)s.data[i] :                    \
                            ' ',                                \
                        s.data[i]);                             \
            fputc('\n', stderr);                                \
        } while (0)
#endif /* INLINE */

/* FIXME optimize!
 */
#define stack_op(op)                                            \
    do {                                                        \
        stack_data a, b;                                        \
        stack_popret(&b);                                       \
        stack_popret(&a);                                       \
        stack_push(a op b);                                     \
    } while (0)

#endif /* STACK_H__ */
