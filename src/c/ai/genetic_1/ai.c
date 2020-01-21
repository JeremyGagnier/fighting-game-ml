#include "ai.h"

#define NUM_OF_POLICIES (3 * 3 * 2 * 2)
#define MUTATION_RATE 0.01f

int condense_state(int player_num, game_state state)
{
    int opponent_x_diff, opponent_y_diff, dist_to_left_edge;

    if (player_num == 0)
    {
        opponent_x_diff = state.p2_x - state.p1_x;
        opponent_y_diff = state.p2_y - state.p1_y;
        dist_to_left_edge = state.p1_x;
    }
    else
    {
        opponent_x_diff = state.p1_x - state.p2_x;
        opponent_y_diff = state.p1_y - state.p2_y;
        dist_to_left_edge = state.p2_x;
    }

    int x_diff_state, y_diff_state, left_edge_state;

    if      (opponent_x_diff < -510) x_diff_state = 0;
    else if (opponent_x_diff < -330) x_diff_state = 1;
    else if (opponent_x_diff < -210) x_diff_state = 2;
    else if (opponent_x_diff < -130) x_diff_state = 3;
    else if (opponent_x_diff < -80)  x_diff_state = 4;
    else if (opponent_x_diff < -60)  x_diff_state = 5;
    else if (opponent_x_diff < -49)  x_diff_state = 6;
    else if (opponent_x_diff < -39)  x_diff_state = 7;
    else if (opponent_x_diff < -30)  x_diff_state = 8;
    else if (opponent_x_diff < -22)  x_diff_state = 9;
    else if (opponent_x_diff < -15)  x_diff_state = 10;
    else if (opponent_x_diff < -9)   x_diff_state = 11;
    else if (opponent_x_diff < -4)   x_diff_state = 12;
    else if (opponent_x_diff < 0)    x_diff_state = 13;
    else if (opponent_x_diff < 4)    x_diff_state = 14;
    else if (opponent_x_diff < 9)    x_diff_state = 15;
    else if (opponent_x_diff < 15)   x_diff_state = 16;
    else if (opponent_x_diff < 22)   x_diff_state = 17;
    else if (opponent_x_diff < 30)   x_diff_state = 18;
    else if (opponent_x_diff < 39)   x_diff_state = 19;
    else if (opponent_x_diff < 49)   x_diff_state = 20;
    else if (opponent_x_diff < 60)   x_diff_state = 21;
    else if (opponent_x_diff < 80)   x_diff_state = 22;
    else if (opponent_x_diff < 130)  x_diff_state = 23;
    else if (opponent_x_diff < 210)  x_diff_state = 24;
    else if (opponent_x_diff < 330)  x_diff_state = 25;
    else if (opponent_x_diff < 510)  x_diff_state = 26;
    else                             x_diff_state = 27;

    if      (opponent_y_diff < -510) y_diff_state = 0;
    else if (opponent_y_diff < -330) y_diff_state = 1;
    else if (opponent_y_diff < -210) y_diff_state = 2;
    else if (opponent_y_diff < -130) y_diff_state = 3;
    else if (opponent_y_diff < -80)  y_diff_state = 4;
    else if (opponent_y_diff < -60)  y_diff_state = 5;
    else if (opponent_y_diff < -49)  y_diff_state = 6;
    else if (opponent_y_diff < -39)  y_diff_state = 7;
    else if (opponent_y_diff < -30)  y_diff_state = 8;
    else if (opponent_y_diff < -22)  y_diff_state = 9;
    else if (opponent_y_diff < -15)  y_diff_state = 10;
    else if (opponent_y_diff < -9)   y_diff_state = 11;
    else if (opponent_y_diff < -4)   y_diff_state = 12;
    else if (opponent_y_diff < 0)    y_diff_state = 13;
    else if (opponent_y_diff < 4)    y_diff_state = 14;
    else if (opponent_y_diff < 9)    y_diff_state = 15;
    else if (opponent_y_diff < 15)   y_diff_state = 16;
    else if (opponent_y_diff < 22)   y_diff_state = 17;
    else if (opponent_y_diff < 30)   y_diff_state = 18;
    else if (opponent_y_diff < 39)   y_diff_state = 19;
    else if (opponent_y_diff < 49)   y_diff_state = 20;
    else if (opponent_y_diff < 60)   y_diff_state = 21;
    else if (opponent_y_diff < 80)   y_diff_state = 22;
    else if (opponent_y_diff < 130)  y_diff_state = 23;
    else if (opponent_y_diff < 210)  y_diff_state = 24;
    else if (opponent_y_diff < 330)  y_diff_state = 25;
    else if (opponent_y_diff < 510)  y_diff_state = 26;
    else                             y_diff_state = 27;

    if      (dist_to_left_edge < 50)  left_edge_state = 0;
    else if (dist_to_left_edge < 75)  left_edge_state = 1;
    else if (dist_to_left_edge < 95)  left_edge_state = 2;
    else if (dist_to_left_edge < 100) left_edge_state = 3;
    else if (dist_to_left_edge < 105) left_edge_state = 4;
    else if (dist_to_left_edge < 125) left_edge_state = 5;
    else if (dist_to_left_edge < 200) left_edge_state = 6;
    else if (dist_to_left_edge < 400) left_edge_state = 7;
    else if (dist_to_left_edge < 600) left_edge_state = 8;
    else if (dist_to_left_edge < 675) left_edge_state = 9;
    else if (dist_to_left_edge < 695) left_edge_state = 10;
    else if (dist_to_left_edge < 700) left_edge_state = 11;
    else if (dist_to_left_edge < 705) left_edge_state = 12;
    else if (dist_to_left_edge < 725) left_edge_state = 13;
    else if (dist_to_left_edge < 750) left_edge_state = 14;
    else                              left_edge_state = 15;

    return (x_diff_state + 28 * (y_diff_state + 28 * left_edge_state));
}

player_input uncondense_input(char condensed_input)
{
    char x_axis = condensed_input % 3;
    condensed_input = condensed_input / 3;
    char y_axis = condensed_input % 3;
    condensed_input = condensed_input / 3;
    char jump = condensed_input % 2;
    condensed_input = condensed_input / 2;
    char attack = condensed_input % 21;
    
    return (x_axis == 0) * LEFT +
        (x_axis == 2) * RIGHT +
        (y_axis == 0) * DOWN +
        (y_axis == 2) * UP +
        (jump == 1) * JUMP +
        (attack == 1) * ATTACK;
}

genetic_ai* make_random_genetic_ai(void)
{
    genetic_ai* ai = (genetic_ai*)malloc(sizeof(genetic_ai));
    for (int i = 0; i < NUM_OF_STATES; ++i)
    {
        ai->dna[i] = acorn_randint(0, NUM_OF_POLICIES);
    }
    return ai;
}

genetic_ai* load_genetic_ai(char* filename)
{
    genetic_ai* ai = (genetic_ai*)malloc(sizeof(genetic_ai));
    FILE* f_in = fopen(filename, "r");
    fread((void*)ai->dna, NUM_OF_STATES, NUM_OF_STATES, f_in);
    return ai;
}

void save_genetic_ai(genetic_ai* ai, char* filename)
{
    FILE* f_out = fopen(filename, "w");
    fwrite((void*)ai->dna, NUM_OF_STATES, NUM_OF_STATES, f_out);
}

extern genetic_ai* breed_genetic_ai(genetic_ai* parent1, genetic_ai* parent2)
{
    /**
     * Some improvements can be had with breeding. Randomly chosing every single policy from the
     * parents is too much randomness. In actual DNA only chromosomes are randomly chosen. This can
     * be emulated by finding some groupings; for example grouping by a physical grid mapped to the
     * x/y differences.
     */
    genetic_ai* new_ai = (genetic_ai*)malloc(sizeof(genetic_ai));
    for (int i = 0; i < NUM_OF_STATES; ++i)
    {
        if (acorn_rand() <= MUTATION_RATE)
        {
            new_ai->dna[i] = (char)acorn_randint(0, NUM_OF_POLICIES + 1);
        }
        else
        {
            if (acorn_randint(0, 2))
            {
                new_ai->dna[i] = parent2->dna[i];
            }
            else
            {
                new_ai->dna[i] = parent1->dna[i];
            }
        }
    }
    return new_ai;
}

player_input get_genetic_ai_input(game_state state, int player_num, void* ai_struct)
{
    genetic_ai* ai = (genetic_ai*)ai_struct;
    int condensed_state = condense_state(player_num, state);
    return uncondense_input(ai->dna[condensed_state]);
}
