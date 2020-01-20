#include "game_state.h"

int GROUNDED = (1 << 0);
int DOUBLE_JUMP = (1 << 1);
int AIR_DASH = (1 << 2);
int FACING_LEFT = (1 << 3);
int MOVE_HAS_HIT = (1 << 4);

game_state get_initial_game_state(void)
{
    game_state initial_game_state = {
        200.0f,
        500.0f,
        0.0f,
        0.0f,
        100,
        0,
        -1,
        6,
        600.0f,
        500.0f,
        0.0f,
        0.0f,
        100,
        0,
        -1,
        14
    };
    return initial_game_state;
}
