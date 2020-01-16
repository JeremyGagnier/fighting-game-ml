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

extern game_result play_game(
    void* p1_ai,
    void* p2_ai,
    player_input get_p1_input(game_state current_state, int player_num, void* ai_struct),
    player_input get_p2_input(game_state current_state, int player_num, void* ai_struct));
