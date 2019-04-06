#ifndef GAME_STATE_H
#define GAME_STATE_H

extern int GROUNDED;
extern int DOUBLE_JUMP;
extern int AIR_DASH;
extern int FACING_LEFT;
extern int MOVE_HAS_HIT;

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
/*
extern int is_grounded(int flags);
extern int has_double_jump(int flags);
extern int has_air_dash(int flags);
extern int is_facing_left(int flags);
extern int has_move_hit(int flags);
*/
extern game_state get_initial_game_state();

#endif
