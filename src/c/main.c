#include "stdio.h"

#include "fighting_game.h"

player_input do_nothing(game_state current_state)
{
    return 0;
}

int main()
{
    game_result result = play_game(do_nothing, do_nothing);
    for (int frame = 0; frame < result.states_length; ++frame)
    {
        printf("Frame %i:\n", frame);
    }
    free(result.states);
    return 0;
}
