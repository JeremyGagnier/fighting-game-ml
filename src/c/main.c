#include "stdio.h"

#include "game/fighting_game.h"
#include "ai/genetic_1/ai.h"

void* p1_ai;
void* p2_ai;

int main()
{
    p1_ai = (void*)make_random_genetic_ai();
    p2_ai = (void*)make_random_genetic_ai();
    game_result result = play_game(p1_ai, p2_ai, get_genetic_ai_input, get_genetic_ai_input);
    for (int frame = 0; frame < result.states_length; ++frame)
    {
        printf("Frame %i:\n", frame);
    }
    free(result.states);
    return 0;
}
