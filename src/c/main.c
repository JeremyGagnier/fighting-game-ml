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
    for (int frame_number = 0; frame_number < result.states_length; ++frame_number)
    {
        game_state frame = result.states[frame_number];
        printf(
            "Frame %i: p1 hp(%i) x(%.1f) y(%.1f) - p2 hp(%i) x(%.1f) y(%.1f)\n",
            frame_number,
            frame.p1_hp,
            frame.p1_x,
            frame.p1_y,
            frame.p2_hp,
            frame.p2_x,
            frame.p2_y);
    }
    free(result.states);
    return 0;
}
