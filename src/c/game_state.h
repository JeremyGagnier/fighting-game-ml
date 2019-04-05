#ifndef GAME_STATE
#define GAME_STATE

typedef struct
{
    float p1_x;
    float p1_y;
    float p1_vx;
    float p1_vy;
    int p1_hp;
    int p1_lag;
    int p1_current_move;
    int p1_flags;  // grounded, double jump, air dash, facing left, move has hit

    float p2_x;
    float p2_y;
    float p2_vx;
    float p2_vy;
    int p2_hp;
    int p2_lag;
    int p2_current_move;
    int p2_flags;  // grounded, double jump, air dash, facing left, move has hit
} game_state;

int GROUNDED = (1 << 0);
int DOUBLE_JUMP = (1 << 1);
int AIR_DASH = (1 << 2);
int FACING_LEFT = (1 << 3);
int MOVE_HAS_HIT = (1 << 4);

inline int is_grounded(int flags)
{
    return flags % 2;
}

inline int has_double_jump(int flags)
{
    return (flags >> 1) % 2;
}

inline int has_air_dash(int flags)
{
    return (flags >> 2) % 2;
}

inline int is_facing_left(int flags)
{
    return (flags >> 3) % 2;
}

inline int has_move_hit(int flags)
{
    return flags >> 4;
}

game_state get_initial_game_state();

#endif
