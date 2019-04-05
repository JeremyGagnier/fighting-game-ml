#include "game_state.h"

game_state get_initial_game_state()
{
    game_state initial_game_state = {
        200.0f,
        500.0f,
        0.0f,
        0.0f,
        100,
        0,
        -1,
        7,
        600.0f,
        500.0f,
        0.0f,
        0.0f,
        100,
        0,
        -1,
        15
    };
    return initial_game_state;
}
