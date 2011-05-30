#ifndef STACK_H__
#define STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef STACK_SIZE
    #define STACK_SIZE 14098
#endif
typedef long int stack_data;
#define STACK_DATA_FMT "%ld"

struct stack {
    stack_data data[STACK_SIZE];
    int counter;
} s;

extern const char *prog;

#define stack_pop_body                                          \
    if (s.counter > 0)                                          \
        s.counter--;

#define stack_popret_body(x)                                    \
    *(x) = s.counter == 0 ? 0 : s.data[--s.counter];

#ifndef VROOM
    #define stack_push_body(x)                                  \
        if (STACK_SIZE - s.counter == 0) {                      \
            fprintf(stderr, "\n%s: Stack overflow\n", prog);    \
            exit(EXIT_FAILURE);                                 \
        } else                                                  \
        s.data[s.counter++] = (x);
#else
    #define stack_push_body(x)                                  \
        s.data[s.counter++] = (x);
#endif

#define stack_top_body(x)                                       \
    *(x) = s.data[s.counter - 1];

#define stack_dup_body                                          \
    s.data[s.counter] = s.data[s.counter - 1];                  \
    s.counter++;

#ifndef VROOM
    #define stack_swp_body                                      \
        stack_data tmp;                                         \
        if (s.counter < 2) {                                    \
            fprintf(stderr, "\n%s: Stack underflow\n", prog);   \
            exit(EXIT_FAILURE);                                 \
        }                                                       \
        tmp = s.data[s.counter - 1];                            \
        s.data[s.counter - 1] = s.data[s.counter - 2];          \
        s.data[s.counter - 2] = tmp;
#else
    #define stack_swp_body                                      \
        stack_data tmp = s.data[s.counter - 1];                 \
        s.data[s.counter - 1] = s.data[s.counter - 2];          \
        s.data[s.counter - 2] = tmp;
#endif

#define stack_debug_body                                        \
    int i;                                                      \
    for (i = 0; i < s.counter; ++i)                             \
    fprintf(stdout, "[%c](" STACK_DATA_FMT ") ",                \
        isprint(s.data[i]) ?                                    \
        (int)s.data[i] :                                        \
        ' ',                                                    \
        s.data[i]);                                             \
    fputc('\n', stdout);

#ifdef INLINE
    static inline void stack_pop(void)
    {
        stack_pop_body
    }

    static inline void stack_popret(stack_data *x)
    {
        stack_popret_body(x)
    }

    static inline void stack_push(stack_data x)
    {
        stack_push_body(x)
    }

    static inline void stack_top(stack_data *x)
    {
        stack_top_body(x)
    }

    static inline void stack_dup(void)
    {
        stack_dup_body
    }

    static inline void stack_swp(void)
    {
        stack_swp_body
    }

    static inline void stack_debug(void)
    {
        stack_debug_body
    }
#else
    #define stack_pop()                                         \
        do {                                                    \
            stack_pop_body                                      \
        } while (0)

    #define stack_popret(x)                                     \
        do {                                                    \
            stack_popret_body(x)                                \
        } while (0)

    #define stack_push(x)                                       \
        do {                                                    \
            stack_push_body(x)                                  \
        } while (0)

    #define stack_top(x)                                        \
        do {                                                    \
            stack_top_body(x)                                   \
        } while (0)

    #define stack_dup()                                         \
        do {                                                    \
            stack_dup_body                                      \
        } while (0)

    #define stack_swp()                                         \
        do {                                                    \
            stack_swp_body                                      \
        } while (0)

    #define stack_debug()                                       \
        do {                                                    \
            stack_debug_body                                    \
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
