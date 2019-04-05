#include "fighting_game.h"
#include "player_input.h"
#include "game_state.h"

player_input do_nothing(game_state current_state) {
    return 0;
}

int main()
{
    play_game(do_nothing, do_nothing);
    return 0;
}
