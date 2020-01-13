#pragma once

#include "../../game/game_state.h"
#include "../../game/player_input.h"

typedef struct
{
    int* dna;
} genetic_ai;

int condense_state(int player_num, game_state state);
player_input uncondense_input(int condensed_input);

extern genetic_ai* load_genetic_ai(char* filename);
extern void save_genetic_ai(genetic_ai* ai, char* filename);
extern player_input get_genetic_ai_input(game_state state, int player_num, void* ai_struct);
