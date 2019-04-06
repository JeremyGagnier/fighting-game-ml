#ifndef FIGHTING_GAME_H
#define FIGHTING_GAME_H

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

extern game_state* play_game(
    player_input get_p1_input(game_state current_state),
    player_input get_p2_input(game_state current_state));

#endif
