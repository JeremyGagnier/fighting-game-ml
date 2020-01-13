#include "stdio.h"

#include "game/fighting_game.h"
#include "ai/genetic_1/ai.h"

player_input do_nothing(game_state current_state, int player_num, void* ai_struct)
{
    return 0;
}

int main()
{
    game_result result = play_game(NULL, NULL, do_nothing, do_nothing);
    for (int frame = 0; frame < result.states_length; ++frame)
    {
        printf("Frame %i:\n", frame);
    }
    free(result.states);
    return 0;
}
