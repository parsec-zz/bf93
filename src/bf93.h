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

#define pc_advance_body                                         \
    pc.x = (pc.x + pc.x_dir + WIDTH) % WIDTH;                   \
    pc.y = (pc.y + pc.y_dir + HEIGHT) % HEIGHT;

#define pc_set_north_body                                       \
    pc.x_dir = PC_STAY;                                         \
    pc.y_dir = PC_NORTH;

#define pc_set_south_body                                       \
    pc.x_dir = PC_STAY;                                         \
    pc.y_dir = PC_SOUTH;

#define pc_set_east_body                                        \
    pc.x_dir = PC_EAST;                                         \
    pc.y_dir = PC_STAY;

#define pc_set_west_body                                        \
    pc.x_dir = PC_WEST;                                         \
    pc.y_dir = PC_STAY;

#ifdef INLINE
    static inline void pc_advance(void)
    {
        pc_advance_body
    }

    static inline void pc_set_north(void)
    {
        pc_set_north_body
    }

    static inline void pc_set_south(void)
    {
        pc_set_south_body
    }

    static inline void pc_set_east(void)
    {
        pc_set_east_body
    }

    static inline void pc_set_west(void)
    {
        pc_set_west_body
    }
#else
    #define pc_advance()                                        \
        do {                                                    \
            pc_advance_body                                     \
        } while (0)

    #define pc_set_north()                                      \
        do {                                                    \
            pc_set_north_body                                   \
        } while (0)                                             \

    #define pc_set_south()                                      \
        do {                                                    \
            pc_set_south_body                                   \
        } while (0)

    #define pc_set_east()                                       \
        do {                                                    \
            pc_set_east_body                                    \
        } while (0)

    #define pc_set_west()                                       \
        do {                                                    \
            pc_set_west_body                                    \
        } while (0)
#endif /* INLINE */

#endif /* BF93_H__ */
