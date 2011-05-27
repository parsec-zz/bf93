#ifndef STACK_H__
#define STACK_H__

#define STACK_SIZE 1024

struct stack {
    int data[STACK_SIZE];
    int counter;
};

extern struct stack s;

#define stack_pop()                                             \
    do {                                                        \
        if (s.counter > 0)                                      \
            s.counter--;                                        \
    } while (0)

#define stack_popret(x)                                         \
    do {                                                        \
        (x) = s.counter == 0 ? 0 : s.data[--s.counter];         \
    } while (0)

#define stack_push(x)                                           \
    do {                                                        \
        if (STACK_SIZE - s.counter == 0)                        \
            exit(EXIT_FAILURE);                                 \
        else                                                    \
            s.data[s.counter++] = (x);                          \
    } while (0)

#define stack_top(x)                                            \
    do {                                                        \
        (x) = s.data[s.counter - 1];                            \
    } while (0)

#define stack_dup()                                             \
    do {                                                        \
        s.data[s.counter] = s.data[s.counter - 1];              \
        s.counter++;                                            \
    } while (0)

#define stack_swp()                                             \
    do {                                                        \
        ;                                                       \
    } while (0)

#define stack_op(o)                                             \
    do {                                                        \
        ;                                                       \
    } while (0)

#define stack_debug()                                           \
    do {                                                        \
        int i;                                                  \
        for (i = 0; i < s.counter; ++i)                         \
            printf("%d(%c) ", i, s.data[i]);                    \
        putchar('\n');                                          \
    } while (0)

#endif /* STACK_H__ */
