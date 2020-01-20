#pragma once

#include "stdio.h"
#include "stdlib.h"

#include "../../game/game_state.h"
#include "../../game/player_input.h"
#include "../../common/acorn.h"

#define NUM_OF_STATES (28 * 28 * 16)

typedef struct
{
    char dna[NUM_OF_STATES];
} genetic_ai;

int condense_state(int player_num, game_state state);
player_input uncondense_input(char condensed_input);

extern genetic_ai* make_random_genetic_ai(void);
extern genetic_ai* load_genetic_ai(char* filename);
extern void save_genetic_ai(genetic_ai* ai, char* filename);
extern genetic_ai* breed_genetic_ai(genetic_ai* parent1, genetic_ai* parent2);
extern player_input get_genetic_ai_input(game_state state, int player_num, void* ai_struct);
