#ifndef FIGHTING_GAME
#define FIGHTING_GAME

#include <stdlib.h>

#include "constants.h"
#include "game_state.h"
#include "player_input.h"

enum move
{
    FORWARD_GROUND,
    UP_GROUND,
    NEUTRAL_GROUND,
    FORWARD_AIR,
    DOWN_AIR,
    BACK_AIR
};

game_state* play_game(
    player_input get_p1_input(game_state current_state),
    player_input get_p2_input(game_state current_state));

#endif
