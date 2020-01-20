#pragma once

#include "stdlib.h"
#include "stdio.h"

#include "constants.h"
#include "game_result.h"
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

typedef player_input input_fn(game_state, int, void*);

extern game_result play_game(
    void* p1_ai,
    void* p2_ai,
    input_fn get_p1_input,
    input_fn get_p2_input);
