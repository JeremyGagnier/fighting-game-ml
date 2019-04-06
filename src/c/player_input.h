#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

typedef int player_input;   // left, right, up, down, jump, attack

extern int LEFT;
extern int RIGHT;
extern int UP;
extern int DOWN;
extern int JUMP;
extern int ATTACK;

extern int input_left(player_input input);
extern int input_right(player_input input);
extern int input_up(player_input input);
extern int input_down(player_input input);
extern int input_jump(player_input input);
extern int input_attack(player_input input);

#endif
