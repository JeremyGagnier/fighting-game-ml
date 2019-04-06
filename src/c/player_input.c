#include "player_input.h"

int LEFT = (1 << 0);
int RIGHT = (1 << 1);
int UP = (1 << 2);
int DOWN = (1 << 3);
int JUMP = (1 << 4);
int ATTACK = (1 << 4);

int input_left(player_input input)
{
    return input % 2;
}

int input_right(player_input input)
{
    return (input >> 1) % 2;
}

int input_up(player_input input)
{
    return (input >> 2) % 2;
}

int input_down(player_input input)
{
    return (input >> 3) % 2;
}

int input_jump(player_input input)
{
    return (input >> 4) % 2;
}

int input_attack(player_input input)
{
    return input >> 5;
}
