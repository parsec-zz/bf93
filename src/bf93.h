#ifndef BF93_H__
#define BF93_H__

#define WIDTH       80
#define HEIGHT      25

struct program_counter {
    int x;
    int y;
    int x_dir;
    int y_dir;
};

extern struct program_counter pc;

#define PC_NORTH    (-1)
#define PC_SOUTH    1
#define PC_EAST     1
#define PC_WEST     (-1)
#define PC_STAY     0

#if 0
static inline pc_advance(void)
{
    pc.x = (pc.x + pc.x_dir + WIDTH) % WIDTH;
    pc.y = (pc.y + pc.y_dir + HEIGHT) % HEIGHT;
}

static inline pc_set_north(void)
{
    pc.x_dir = PC_STAY;
    pc.y_dir = PC_NORTH;
}

static inline pc_set_south(void)
{
    pc.x_dir = PC_STAY;
    pc.y_dir = PC_SOUTH;
}

static inline pc_set_east(void)
{
    pc.x_dir = PC_EAST;
    pc.y_dir = PC_STAY;
}

static inline pc_set_west(void)
{
    pc.x_dir = PC_WEST;
    pc.y_dir = PC_STAY;
}
#endif

#define pc_advance()                                            \
    do {                                                        \
        pc.x = (pc.x + pc.x_dir + WIDTH) % WIDTH;               \
        pc.y = (pc.y + pc.y_dir + HEIGHT) % HEIGHT;             \
    } while (0)

#define pc_set_north()                                          \
    do {                                                        \
        pc.x_dir = PC_STAY;                                     \
        pc.y_dir = PC_NORTH;                                    \
    } while (0)                                                 \

#define pc_set_south()                                          \
    do {                                                        \
        pc.x_dir = PC_STAY;                                     \
        pc.y_dir = PC_SOUTH;                                    \
    } while (0)

#define pc_set_east()                                           \
    do {                                                        \
        pc.x_dir = PC_EAST;                                     \
        pc.y_dir = PC_STAY;                                     \
    } while (0)

#define pc_set_west()                                           \
    do {                                                        \
        pc.x_dir = PC_WEST;                                     \
        pc.y_dir = PC_STAY;                                     \
    } while (0)

#endif /* BF93_H__ */
