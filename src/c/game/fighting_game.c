#include "fighting_game.h"

int does_circle_collide_with_player(
    float circle_x,
    float circle_y,
    float circle_rad,
    float box_x,
    float box_y)
{
    box_x -= PLAYER_WIDTH / 2.0f;
    box_y -= PLAYER_HEIGHT / 2.0f;

    // Quick check of 3/6/9/12 ops to avoid doing a ton of ops. If this hits that means we dodged ~32 ops below.
    if (circle_x + circle_rad + PLAYER_WIDTH < box_x ||
        box_x + circle_rad + PLAYER_WIDTH < circle_x ||
        circle_y + circle_rad + PLAYER_HEIGHT < box_y ||
        box_y + circle_rad + PLAYER_HEIGHT < circle_y)
    {
        return 0;
    }

    // There are 6 cases that confirm a collision. Two box checks and four corner checks.
    return (((box_y <= circle_y) & (circle_y <= box_y + PLAYER_HEIGHT)) &&
            ((box_x - circle_rad <= circle_x) & (circle_x <= box_x + PLAYER_WIDTH + circle_rad))) ||
        (((box_x <= circle_x) & (circle_x <= box_x + PLAYER_WIDTH)) &&
            ((box_y - circle_rad <= circle_y) & (circle_y <= box_y + PLAYER_HEIGHT + circle_rad))) ||
        ((box_x - circle_x) * (box_x - circle_x) +
            (box_y - circle_y) * (box_y - circle_y) <= (circle_rad * circle_rad)) ||
        ((box_x + PLAYER_WIDTH - circle_x) * (box_x + PLAYER_WIDTH - circle_x) +
            (box_y - circle_y) * (box_y - circle_y) <= (circle_rad * circle_rad)) ||
        ((box_y + PLAYER_HEIGHT - circle_y) * (box_y + PLAYER_HEIGHT - circle_y) +
            (box_x - circle_x) * (box_x - circle_x) <= (circle_rad * circle_rad)) ||
        ((box_x + PLAYER_WIDTH - circle_x) * (box_x + PLAYER_WIDTH - circle_x) +
            (box_y + PLAYER_HEIGHT - circle_y) * (box_y + PLAYER_HEIGHT - circle_y) <= (circle_rad * circle_rad));
}

static inline int p1_hitbox(game_state state, int direction, float dx, float dy, float size)
{
    return does_circle_collide_with_player(
        state.p1_x + direction * (dx + PLAYER_WIDTH / 2.0),
        state.p1_y + dy,
        size,
        state.p2_x,
        state.p2_y);
}

static inline int p1_center_hitbox(game_state state, int direction, float dx, float dy, float size)
{
    return does_circle_collide_with_player(
        state.p1_x + direction * dx,
        state.p1_y + dy,
        size,
        state.p2_x,
        state.p2_y);
}

static inline int p2_hitbox(game_state state, int direction, float dx, float dy, float size)
{
    return does_circle_collide_with_player(
        state.p2_x + direction * (dx + PLAYER_WIDTH / 2.0),
        state.p2_y + dy,
        size,
        state.p1_x,
        state.p1_y);
}

static inline int p2_center_hitbox(game_state state, int direction, float dx, float dy, float size)
{
    return does_circle_collide_with_player(
        state.p2_x + direction * dx,
        state.p2_y + dy,
        size,
        state.p1_x,
        state.p1_y);
}

game_state step(
    game_state previous_state,
    player_input p1_inputs,
    player_input p2_inputs)
{
    game_state new_state;
    new_state.p1_hp = previous_state.p1_hp;
    new_state.p2_hp = previous_state.p2_hp;

    // Update physics values for player 1
    if (previous_state.p1_flags & GROUNDED)
    {
        if (previous_state.p1_lag == 0)
        {
            int p1_dx = (p1_inputs % 2) - ((p1_inputs >> 1) % 2);

            // Set facing left, double jump, and air dash
            int p1_left = p1_inputs % 2;
            int not_p1_right = !((p1_inputs >> 1) % 2);
            int only_left = p1_left & not_p1_right;
            int not_only_right = p1_left | not_p1_right;
            int facing_left = (previous_state.p1_flags >> 3) % 2;
            int now_facing_left = (facing_left | only_left) & not_only_right;
            new_state.p1_flags = (now_facing_left << 3) +
                (previous_state.p1_flags & MOVE_HAS_HIT) +
                DOUBLE_JUMP +
                AIR_DASH;
            // Set x position
            new_state.p1_x = previous_state.p1_x + GROUND_SPEED * TIMESTEP * p1_dx;

            if ((p1_inputs >> 4) % 2)
            {
                new_state.p1_y = previous_state.p1_y - JUMP_SPEED * TIMESTEP;
                new_state.p1_vx = GROUND_SPEED * p1_dx;
                new_state.p1_vy = -JUMP_SPEED;
            }
            else
            {
                new_state.p1_y = previous_state.p1_y;
                // Check if the player has walked over the edge
                if ((previous_state.p1_x + PLAYER_WIDTH / 2.0f < 100.0f) |
                    (previous_state.p1_x - PLAYER_WIDTH / 2.0f > 700.0f))
                {
                    new_state.p1_vx = GROUND_SPEED * p1_dx;
                    new_state.p1_vy = 0;
                } else {
                    // Set grounded
                    new_state.p1_flags += GROUNDED;
                }
            }
        }
        else
        {
            new_state.p1_x = previous_state.p1_x;
            new_state.p1_y = previous_state.p1_y;
            new_state.p1_flags = previous_state.p1_flags;
        }
    }
    else
    {
        new_state.p1_vy = previous_state.p1_vy + GRAVITY * TIMESTEP;

        if ((previous_state.p1_lag <= 0) | (previous_state.p1_current_move >= 0))
        {
            int p1_dx = (p1_inputs % 2) - ((p1_inputs >> 1) % 2);
            if (((previous_state.p1_flags >> 1) % 2) & ((p1_inputs >> 4) % 2))
            {
                // Remove double jump
                new_state.p1_flags = previous_state.p1_flags - DOUBLE_JUMP;
                new_state.p1_vy = -DOUBLE_JUMP_SPEED;
                new_state.p1_vx = previous_state.p1_vx + GROUND_SPEED / 2.0f * p1_dx;
            }
            else
            {
                new_state.p1_flags = previous_state.p1_flags;
                new_state.p1_vx = previous_state.p1_vx;
            }
            new_state.p1_vx += AERIAL_MOBILITY * TIMESTEP * p1_dx;
            if (new_state.p1_vx < -GROUND_SPEED)
            {
                new_state.p1_vx = -GROUND_SPEED;
            }
            else if (new_state.p1_vx > GROUND_SPEED)
            {
                new_state.p1_vx = GROUND_SPEED;
            }
        }
        else
        {
            new_state.p1_flags = previous_state.p1_flags;
            new_state.p1_vx = previous_state.p1_vx;
        }

        new_state.p1_x = previous_state.p1_x + new_state.p1_vx * TIMESTEP;
        new_state.p1_y = previous_state.p1_y + new_state.p1_vy * TIMESTEP;
        if (((new_state.p1_x + PLAYER_WIDTH / 2.0f < 100.0f) |
            (new_state.p1_x - PLAYER_WIDTH / 2.0f > 700.0f)) &
            (new_state.p1_y + PLAYER_HEIGHT / 2.0f > 550.0f))
        {
            // Set grounded and double jump
            new_state.p1_flags |= GROUNDED + DOUBLE_JUMP;
        }
    }
    if ((new_state.p1_y - PLAYER_HEIGHT / 2.0f > 600.0f) |
        (new_state.p1_x - PLAYER_WIDTH / 2.0f > 800.0f) |
        (new_state.p1_x + PLAYER_WIDTH / 2.0f < 0.0f))
    {
        new_state.p1_hp = 0;
    }

    // Update physics values for player 2
    if (previous_state.p2_flags & GROUNDED)
    {
        if (previous_state.p2_lag == 0)
        {
            int p2_dx = (p2_inputs % 2) - ((p2_inputs >> 1) % 2);

            // Set facing left, double jump, and air dash
            int p2_left = p2_inputs % 2;
            int not_p2_right = !((p2_inputs >> 1) % 2);
            int only_left = p2_left & not_p2_right;
            int not_only_right = p2_left | not_p2_right;
            int facing_left = (previous_state.p2_flags >> 3) % 2;
            int now_facing_left = (facing_left | only_left) & not_only_right;
            new_state.p2_flags = (now_facing_left << 3) +
                (previous_state.p2_flags & MOVE_HAS_HIT) +
                DOUBLE_JUMP +
                AIR_DASH;
            // Set x position
            new_state.p2_x = previous_state.p2_x + GROUND_SPEED * TIMESTEP * p2_dx;

            if ((p2_inputs >> 4) % 2)
            {
                new_state.p2_y = previous_state.p2_y - JUMP_SPEED * TIMESTEP;
                new_state.p2_vx = GROUND_SPEED * p2_dx;
                new_state.p2_vy = -JUMP_SPEED;
            }
            else
            {
                new_state.p2_y = previous_state.p2_y;
                // Check if the player has walked over the edge
                if ((previous_state.p2_x + PLAYER_WIDTH / 2.0f < 100.0f) |
                    (previous_state.p2_x - PLAYER_WIDTH / 2.0f > 700.0f))
                {
                    new_state.p2_vx = GROUND_SPEED * p2_dx;
                    new_state.p2_vy = 0;
                } else {
                    // Set grounded
                    new_state.p2_flags += GROUNDED;
                }
            }
        }
        else
        {
            new_state.p2_x = previous_state.p2_x;
            new_state.p2_y = previous_state.p2_y;
            new_state.p2_flags = previous_state.p2_flags;
        }
    }
    else
    {
        new_state.p2_vy = previous_state.p2_vy + GRAVITY * TIMESTEP;

        if ((previous_state.p2_lag <= 0) | (previous_state.p2_current_move >= 0))
        {
            int p2_dx = (p2_inputs % 2) - ((p2_inputs >> 1) % 2);
            if (((previous_state.p2_flags >> 1) % 2) & ((p2_inputs >> 4) % 2))
            {
                // Remove double jump
                new_state.p2_flags = previous_state.p2_flags - DOUBLE_JUMP;
                new_state.p2_vy = -DOUBLE_JUMP_SPEED;
                new_state.p2_vx = previous_state.p2_vx + GROUND_SPEED / 2.0f * p2_dx;
            }
            else
            {
                new_state.p2_flags = previous_state.p2_flags;
                new_state.p2_vx = previous_state.p2_vx;
            }
            new_state.p1_vx += AERIAL_MOBILITY * TIMESTEP * p2_dx;
            if (new_state.p2_vx < -GROUND_SPEED)
            {
                new_state.p2_vx = -GROUND_SPEED;
            }
            else if (new_state.p2_vx > GROUND_SPEED)
            {
                new_state.p2_vx = GROUND_SPEED;
            }
        }
        else
        {
            new_state.p2_flags = previous_state.p2_flags;
            new_state.p2_vx = previous_state.p2_vx;
        }

        new_state.p2_x = previous_state.p2_x + new_state.p2_vx * TIMESTEP;
        new_state.p2_y = previous_state.p2_y + new_state.p2_vy * TIMESTEP;
        if (((new_state.p2_x + PLAYER_WIDTH / 2.0f < 100.0f) |
            (new_state.p2_x - PLAYER_WIDTH / 2.0f > 700.0f)) &
            (new_state.p2_y + PLAYER_HEIGHT / 2.0f > 550.0f))
        {
            // Set grounded and double jump
            new_state.p2_flags |= GROUNDED + DOUBLE_JUMP;
        }
    }
    if ((new_state.p2_y - PLAYER_HEIGHT / 2.0f > 600.0f) |
        (new_state.p2_x - PLAYER_WIDTH / 2.0f > 800.0f) |
        (new_state.p2_x + PLAYER_WIDTH / 2.0f < 0.0f))
    {
        new_state.p2_hp = 0;
    }

    // Update p1 lag and moves
    if (previous_state.p1_lag <= 0)
    {
        if (((p1_inputs >> 5)) % 2)
        {
            if (new_state.p1_flags % 2)
            {
                if ((p1_inputs % 2) | ((p1_inputs >> 1) % 2))
                {
                    new_state.p1_current_move = FORWARD_GROUND;
                    new_state.p1_lag = FORWARD_GROUND_DURATION;
                }
                else if (p1_inputs & (1 << 2))
                {
                    new_state.p1_current_move = UP_GROUND;
                    new_state.p1_lag = UP_GROUND_DURATION;
                }
                else
                {
                    new_state.p1_current_move = NEUTRAL_GROUND;
                    new_state.p1_lag = NEUTRAL_GROUND_DURATION;
                }
            }
            else
            {
                int facing_left = (new_state.p1_flags >> 3) % 2;
                if (((p1_inputs % 2) & facing_left) | (((p1_inputs >> 1) % 2) & !facing_left))
                {
                    new_state.p1_current_move = FORWARD_AIR;
                    new_state.p1_lag = FORWARD_AIR_DURATION;
                }
                else if (((p1_inputs % 2) & !facing_left) | (((p1_inputs >> 1) % 2) & facing_left))
                {
                    new_state.p1_current_move = BACK_AIR;
                    new_state.p1_lag = BACK_AIR_DURATION;
                }
                else if (p1_inputs & (1 << 3))
                {
                    new_state.p1_current_move = DOWN_AIR;
                    new_state.p1_lag = DOWN_AIR_DURATION;
                }
                else
                {
                    new_state.p1_current_move = -1;
                    new_state.p1_lag = 0;
                }
            }
        }
        else
        {
            new_state.p1_current_move = -1;
            new_state.p1_lag = 0;
        }
    }
    else
    {
        new_state.p1_lag = previous_state.p1_lag - 1;
        if (new_state.p1_lag <= 0)
        {
            new_state.p1_current_move = -1;
        }
        else
        {
            new_state.p1_current_move = previous_state.p1_current_move;
        }
    }

    // Update p2 lag and moves
    if (previous_state.p2_lag <= 0)
    {
        if (((p2_inputs >> 5)) % 2)
        {
            if (new_state.p2_flags % 2)
            {
                if ((p2_inputs % 2) | ((p2_inputs >> 1) % 2))
                {
                    new_state.p2_current_move = FORWARD_GROUND;
                    new_state.p2_lag = FORWARD_GROUND_DURATION;
                }
                else if (p2_inputs & (1 << 2))
                {
                    new_state.p2_current_move = UP_GROUND;
                    new_state.p2_lag = UP_GROUND_DURATION;
                }
                else
                {
                    new_state.p2_current_move = NEUTRAL_GROUND;
                    new_state.p2_lag = NEUTRAL_GROUND_DURATION;
                }
            }
            else
            {
                int facing_left = (new_state.p2_flags >> 3) % 2;
                if (((p2_inputs % 2) & facing_left) | (((p2_inputs >> 1) % 2) & !facing_left))
                {
                    new_state.p2_current_move = FORWARD_AIR;
                    new_state.p2_lag = FORWARD_AIR_DURATION;
                }
                else if (((p2_inputs % 2) & !facing_left) | (((p2_inputs >> 1) % 2) & facing_left))
                {
                    new_state.p2_current_move = BACK_AIR;
                    new_state.p2_lag = BACK_AIR_DURATION;
                }
                else if (p2_inputs & (1 << 3))
                {
                    new_state.p2_current_move = DOWN_AIR;
                    new_state.p2_lag = DOWN_AIR_DURATION;
                }
                else
                {
                    new_state.p2_current_move = -1;
                    new_state.p2_lag = 0;
                }
            }
        }
        else
        {
            new_state.p2_current_move = -1;
            new_state.p2_lag = 0;
        }
    }
    else
    {
        new_state.p2_lag = previous_state.p2_lag - 1;
        if (new_state.p2_lag <= 0)
        {
            new_state.p2_current_move = -1;
        }
        else
        {
            new_state.p2_current_move = previous_state.p2_current_move;
        }
    }

    // Hits is a bitflag for tracking which players were hit. This is done because if both players are hit they must
    // both have their moves cancelled instead of priority going to player 1.
    int hits = 0;

    // Check p1 attack for hits
    if (!(new_state.p1_flags & MOVE_HAS_HIT) & (new_state.p1_current_move >= 0))
    {
        int direction = ((new_state.p1_flags >> 3) % 2) * 2 - 1;
        int hit;
        switch (new_state.p1_current_move)
        {
            case FORWARD_GROUND:
                if (new_state.p1_lag == 15)
                {
                    hit = p1_hitbox(new_state, direction, 3.0f, 7.0f, 7.0f) ||
                        p1_hitbox(new_state, direction, 10.0f, 14.0f, 9.0f);
                }
                else if (new_state.p1_lag == 14)
                {
                    hit = p1_hitbox(new_state, direction, 8.0f, 5.0f, 7.0f) ||
                        p1_hitbox(new_state, direction, 16.0f, 10.0f, 9.0f);
                }
                else if (new_state.p1_lag == 13)
                {
                    hit = p1_hitbox(new_state, direction, 10.0f, 0.0f, 7.0f) ||
                        p1_hitbox(new_state, direction, 20.0f, 0.0f, 9.0f);
                }
                else if (new_state.p1_lag == 12)
                {
                    hit = p1_hitbox(new_state, direction, 8.0f, -5.0f, 7.0f) ||
                        p1_hitbox(new_state, direction, 16.0f, -10.0f, 9.0f);
                }
                else if (new_state.p1_lag == 11)
                {
                    hit = p1_hitbox(new_state, direction, 3.0f, -7.0f, 7.0f) ||
                        p1_hitbox(new_state, direction, 10.0f, -14.0f, 9.0f);
                }
                else
                {
                    hit = 0;
                }
                if (hit)
                {
                    hits += 1;
                    new_state.p2_hp -= FORWARD_GROUND_DAMAGE;
                    new_state.p2_lag = FORWARD_GROUND_HITLAG;
                    new_state.p2_vx += direction * FORWARD_GROUND_KNOCKBACK_X * FORWARD_GROUND_KNOCKBACK;
                    new_state.p2_vy += FORWARD_GROUND_KNOCKBACK_Y * FORWARD_GROUND_KNOCKBACK;
                }
                break;
            case UP_GROUND:
                if (new_state.p1_lag == 8)
                {
                    hit = p1_hitbox(new_state, direction, 0.0f, 0.0f, 8.0f);
                }
                else if (new_state.p1_lag == 7)
                {
                    hit = p1_hitbox(new_state, direction, -4.0f, -14.0f, 8.0f);
                }
                else if (new_state.p1_lag == 6)
                {
                    hit = p1_center_hitbox(new_state, direction, 0.0f, -26.0f, 13.0f);
                }
                else if (new_state.p1_lag == 5)
                {
                    hit = p1_center_hitbox(new_state, direction, 0.0f, -24.0f, 15.0f);
                }
                else
                {
                    hit = 0;
                }
                if (hit)
                {
                    hits += 1;
                    new_state.p2_hp -= UP_GROUND_DAMAGE;
                    new_state.p2_lag = UP_GROUND_HITLAG;
                    new_state.p2_vx += direction * UP_GROUND_KNOCKBACK_X * UP_GROUND_KNOCKBACK;
                    new_state.p2_vy += UP_GROUND_KNOCKBACK_Y * UP_GROUND_KNOCKBACK;
                }
                break;
            case NEUTRAL_GROUND:
                if (new_state.p1_lag == 6)
                {
                    hit = p1_center_hitbox(new_state, direction, 0.0f, 0.0f, 25.0f);
                }
                else if (new_state.p1_lag == 5)
                {
                    hit = p1_center_hitbox(new_state, direction, 0.0f, 0.0f, 22.0f);
                }
                else if (new_state.p1_lag == 4)
                {
                    hit = p1_center_hitbox(new_state, direction, 0.0f, 0.0f, 20.0f);
                }
                else
                {
                    hit = 0;
                }
                if (hit)
                {
                    hits += 1;
                    new_state.p2_hp -= NEUTRAL_GROUND_DAMAGE;
                    new_state.p2_lag = NEUTRAL_GROUND_HITLAG - NEUTRAL_GROUND_DURATION + new_state.p1_lag;
                    new_state.p2_vx += direction * NEUTRAL_GROUND_KNOCKBACK_X * NEUTRAL_GROUND_KNOCKBACK;
                    new_state.p2_vy += NEUTRAL_GROUND_KNOCKBACK_Y * NEUTRAL_GROUND_KNOCKBACK;
                }
                break;
            case FORWARD_AIR:
                if (new_state.p1_lag == 15)
                {
                    hit = p1_hitbox(new_state, direction, 3.0f, -7.0f, 7.0f) ||
                        p1_hitbox(new_state, direction, 10.0f, -14.0f, 9.0f);
                }
                else if (new_state.p1_lag == 14)
                {
                    hit = p1_hitbox(new_state, direction, 8.0f, -5.0f, 7.0f) ||
                        p1_hitbox(new_state, direction, 16.0f, -10.0f, 9.0f);
                }
                else if (new_state.p1_lag == 13)
                {
                    hit = p1_hitbox(new_state, direction, 10.0f, 0.0f, 7.0f) ||
                        p1_hitbox(new_state, direction, 20.0f, 0.0f, 9.0f);
                }
                else if (new_state.p1_lag == 12)
                {
                    hit = p1_hitbox(new_state, direction, 8.0f, 5.0f, 7.0f) ||
                        p1_hitbox(new_state, direction, 16.0f, 10.0f, 9.0f);
                }
                else if (new_state.p1_lag == 11)
                {
                    hit = p1_hitbox(new_state, direction, 3.0f, 7.0f, 7.0f) ||
                        p1_hitbox(new_state, direction, 10.0f, 14.0f, 9.0f);
                }
                else
                {
                    hit = 0;
                }
                if (hit)
                {
                    hits += 1;
                    new_state.p2_hp -= FORWARD_AIR_DAMAGE;
                    new_state.p2_lag = FORWARD_AIR_HITLAG;
                    new_state.p2_vx += direction * FORWARD_AIR_KNOCKBACK_X * FORWARD_AIR_KNOCKBACK;
                    new_state.p2_vy += FORWARD_AIR_KNOCKBACK_Y * FORWARD_AIR_KNOCKBACK;
                }
                break;
            case DOWN_AIR:
                if (new_state.p1_lag == 12)
                {
                    hit = p1_hitbox(new_state, direction, 20.0f, 2.0f, 9.0f);
                }
                else if (new_state.p1_lag == 11)
                {
                    hit = p1_hitbox(new_state, direction, 20.0f, 2.0f, 7.0f) ||
                        p1_hitbox(new_state, direction, 10.0f, 7.0f, 9.0f);
                }
                else if (new_state.p1_lag == 10)
                {
                    hit = p1_hitbox(new_state, direction, 20.0f, 2.0f, 5.0f) ||
                        p1_hitbox(new_state, direction, 10.0f, 7.0f, 7.0f) ||
                        p1_hitbox(new_state, direction, 0.0f, 9.0f, 9.0f);
                }
                else if (new_state.p1_lag == 9)
                {
                    hit = p1_hitbox(new_state, direction, 20.0f, 2.0f, 5.0f) ||
                        p1_hitbox(new_state, direction, 10.0f, 7.0f, 6.0f) ||
                        p1_hitbox(new_state, direction, 0.0f, 9.0f, 7.0f) ||
                        p1_hitbox(new_state, direction, -10.0f, 7.0f, 9.0f);
                }
                else if (new_state.p1_lag == 8)
                {
                    hit = p1_hitbox(new_state, direction, 20.0f, 2.0f, 4.0f) ||
                        p1_hitbox(new_state, direction, 10.0f, 7.0f, 5.0f) ||
                        p1_hitbox(new_state, direction, 0.0f, 9.0f, 6.0f) ||
                        p1_hitbox(new_state, direction, -10.0f, 7.0f, 7.0f) ||
                        p1_hitbox(new_state, direction, -20.0f, 2.0f, 9.0f);
                }
                else
                {
                    hit = 0;
                }
                if (hit)
                {
                    hits += 1;
                    new_state.p2_hp -= DOWN_AIR_DAMAGE;
                    new_state.p2_lag = DOWN_AIR_HITLAG;
                    new_state.p2_vx += direction * DOWN_AIR_KNOCKBACK_X * DOWN_AIR_KNOCKBACK;
                    new_state.p2_vy += DOWN_AIR_KNOCKBACK_Y * DOWN_AIR_KNOCKBACK;
                }
                break;
            case BACK_AIR:
                if (new_state.p1_lag == 9)
                {
                    hit = p1_hitbox(new_state, direction, -5.0f, 8.0f, 8.0f);
                }
                else if (new_state.p1_lag == 8)
                {
                    hit = p1_hitbox(new_state, direction, 0.0f, 8.0f, 8.0f) ||
                        p1_hitbox(new_state, direction, 5.0f, 8.0f, 8.0f);
                }
                else if (new_state.p1_lag == 7)
                {
                    hit = p1_hitbox(new_state, direction, 5.0f, 8.0f, 8.0f) ||
                        p1_hitbox(new_state, direction, 17.5f, 8.0f, 8.0f);
                }
                else if ((new_state.p1_lag == 6) | (new_state.p1_lag == 5))
                {
                    hit = p1_hitbox(new_state, direction, 7.5f, 8.0f, 8.0f) ||
                        p1_hitbox(new_state, direction, 20.0f, 8.0f, 8.0f);
                }
                else
                {
                    hit = 0;
                }
                if (hit)
                {
                    hits += 1;
                    new_state.p2_hp -= BACK_AIR_DAMAGE;
                    new_state.p2_lag = BACK_AIR_HITLAG;
                    new_state.p2_vx += direction * BACK_AIR_KNOCKBACK_X * BACK_AIR_KNOCKBACK;
                    new_state.p2_vy += BACK_AIR_KNOCKBACK_Y * BACK_AIR_KNOCKBACK;
                }
                break;
        }
    }

    // Check p2 attack for hits
    if (!(new_state.p2_flags & MOVE_HAS_HIT) & (new_state.p2_current_move >= 0))
    {
        int direction = ((new_state.p2_flags >> 3) % 2) * 2 - 1;
        int hit;
        switch (new_state.p2_current_move)
        {
            case FORWARD_GROUND:
                if (new_state.p2_lag == 15)
                {
                    hit = p2_hitbox(new_state, direction, 3.0f, 7.0f, 7.0f) ||
                        p2_hitbox(new_state, direction, 10.0f, 14.0f, 9.0f);
                }
                else if (new_state.p2_lag == 14)
                {
                    hit = p2_hitbox(new_state, direction, 8.0f, 5.0f, 7.0f) ||
                        p2_hitbox(new_state, direction, 16.0f, 10.0f, 9.0f);
                }
                else if (new_state.p2_lag == 13)
                {
                    hit = p2_hitbox(new_state, direction, 10.0f, 0.0f, 7.0f) ||
                        p2_hitbox(new_state, direction, 20.0f, 0.0f, 9.0f);
                }
                else if (new_state.p2_lag == 12)
                {
                    hit = p2_hitbox(new_state, direction, 8.0f, -5.0f, 7.0f) ||
                        p2_hitbox(new_state, direction, 16.0f, -10.0f, 9.0f);
                }
                else if (new_state.p2_lag == 11)
                {
                    hit = p2_hitbox(new_state, direction, 3.0f, -7.0f, 7.0f) ||
                        p2_hitbox(new_state, direction, 10.0f, -14.0f, 9.0f);
                }
                else
                {
                    hit = 0;
                }
                if (hit)
                {
                    hits += 2;
                    new_state.p1_hp -= FORWARD_GROUND_DAMAGE;
                    new_state.p1_lag = FORWARD_GROUND_HITLAG;
                    new_state.p1_vx += direction * FORWARD_GROUND_KNOCKBACK_X * FORWARD_GROUND_KNOCKBACK;
                    new_state.p1_vy += FORWARD_GROUND_KNOCKBACK_Y * FORWARD_GROUND_KNOCKBACK;
                }
                break;
            case UP_GROUND:
                if (new_state.p2_lag == 8)
                {
                    hit = p2_hitbox(new_state, direction, 0.0f, 0.0f, 8.0f);
                }
                else if (new_state.p2_lag == 7)
                {
                    hit = p2_hitbox(new_state, direction, -4.0f, -14.0f, 8.0f);
                }
                else if (new_state.p2_lag == 6)
                {
                    hit = p2_center_hitbox(new_state, direction, 0.0f, -26.0f, 13.0f);
                }
                else if (new_state.p2_lag == 5)
                {
                    hit = p2_center_hitbox(new_state, direction, 0.0f, -24.0f, 15.0f);
                }
                else
                {
                    hit = 0;
                }
                if (hit)
                {
                    hits += 2;
                    new_state.p1_hp -= UP_GROUND_DAMAGE;
                    new_state.p1_lag = UP_GROUND_HITLAG;
                    new_state.p1_vx += direction * UP_GROUND_KNOCKBACK_X * UP_GROUND_KNOCKBACK;
                    new_state.p1_vy += UP_GROUND_KNOCKBACK_Y * UP_GROUND_KNOCKBACK;
                }
                break;
            case NEUTRAL_GROUND:
                if (new_state.p2_lag == 6)
                {
                    hit = p2_center_hitbox(new_state, direction, 0.0f, 0.0f, 25.0f);
                }
                else if (new_state.p2_lag == 5)
                {
                    hit = p2_center_hitbox(new_state, direction, 0.0f, 0.0f, 22.0f);
                }
                else if (new_state.p2_lag == 4)
                {
                    hit = p2_center_hitbox(new_state, direction, 0.0f, 0.0f, 20.0f);
                }
                else
                {
                    hit = 0;
                }
                if (hit)
                {
                    hits += 2;
                    new_state.p1_hp -= NEUTRAL_GROUND_DAMAGE;
                    new_state.p1_lag = NEUTRAL_GROUND_HITLAG - NEUTRAL_GROUND_DURATION + new_state.p2_lag;
                    new_state.p1_vx += direction * NEUTRAL_GROUND_KNOCKBACK_X * NEUTRAL_GROUND_KNOCKBACK;
                    new_state.p1_vy += NEUTRAL_GROUND_KNOCKBACK_Y * NEUTRAL_GROUND_KNOCKBACK;
                }
                break;
            case FORWARD_AIR:
                if (new_state.p2_lag == 15)
                {
                    hit = p2_hitbox(new_state, direction, 3.0f, -7.0f, 7.0f) ||
                        p2_hitbox(new_state, direction, 10.0f, -14.0f, 9.0f);
                }
                else if (new_state.p2_lag == 14)
                {
                    hit = p2_hitbox(new_state, direction, 8.0f, -5.0f, 7.0f) ||
                        p2_hitbox(new_state, direction, 16.0f, -10.0f, 9.0f);
                }
                else if (new_state.p2_lag == 13)
                {
                    hit = p2_hitbox(new_state, direction, 10.0f, 0.0f, 7.0f) ||
                        p2_hitbox(new_state, direction, 20.0f, 0.0f, 9.0f);
                }
                else if (new_state.p2_lag == 12)
                {
                    hit = p2_hitbox(new_state, direction, 8.0f, 5.0f, 7.0f) ||
                        p2_hitbox(new_state, direction, 16.0f, 10.0f, 9.0f);
                }
                else if (new_state.p2_lag == 11)
                {
                    hit = p2_hitbox(new_state, direction, 3.0f, 7.0f, 7.0f) ||
                        p2_hitbox(new_state, direction, 10.0f, 14.0f, 9.0f);
                }
                else
                {
                    hit = 0;
                }
                if (hit)
                {
                    hits += 2;
                    new_state.p1_hp -= FORWARD_AIR_DAMAGE;
                    new_state.p1_lag = FORWARD_AIR_HITLAG;
                    new_state.p1_vx += direction * FORWARD_AIR_KNOCKBACK_X * FORWARD_AIR_KNOCKBACK;
                    new_state.p1_vy += FORWARD_AIR_KNOCKBACK_Y * FORWARD_AIR_KNOCKBACK;
                }
                break;
            case DOWN_AIR:
                if (new_state.p2_lag == 12)
                {
                    hit = p2_hitbox(new_state, direction, 20.0f, 2.0f, 9.0f);
                }
                else if (new_state.p2_lag == 11)
                {
                    hit = p2_hitbox(new_state, direction, 20.0f, 2.0f, 7.0f) ||
                        p2_hitbox(new_state, direction, 10.0f, 7.0f, 9.0f);
                }
                else if (new_state.p2_lag == 10)
                {
                    hit = p2_hitbox(new_state, direction, 20.0f, 2.0f, 5.0f) ||
                        p2_hitbox(new_state, direction, 10.0f, 7.0f, 7.0f) ||
                        p2_hitbox(new_state, direction, 0.0f, 9.0f, 9.0f);
                }
                else if (new_state.p2_lag == 9)
                {
                    hit = p2_hitbox(new_state, direction, 20.0f, 2.0f, 5.0f) ||
                        p2_hitbox(new_state, direction, 10.0f, 7.0f, 6.0f) ||
                        p2_hitbox(new_state, direction, 0.0f, 9.0f, 7.0f) ||
                        p2_hitbox(new_state, direction, -10.0f, 7.0f, 9.0f);
                }
                else if (new_state.p2_lag == 8)
                {
                    hit = p2_hitbox(new_state, direction, 20.0f, 2.0f, 4.0f) ||
                        p2_hitbox(new_state, direction, 10.0f, 7.0f, 5.0f) ||
                        p2_hitbox(new_state, direction, 0.0f, 9.0f, 6.0f) ||
                        p2_hitbox(new_state, direction, -10.0f, 7.0f, 7.0f) ||
                        p2_hitbox(new_state, direction, -20.0f, 2.0f, 9.0f);
                }
                else
                {
                    hit = 0;
                }
                if (hit)
                {
                    hits += 2;
                    new_state.p1_hp -= DOWN_AIR_DAMAGE;
                    new_state.p1_lag = DOWN_AIR_HITLAG;
                    new_state.p1_vx += direction * DOWN_AIR_KNOCKBACK_X * DOWN_AIR_KNOCKBACK;
                    new_state.p1_vy += DOWN_AIR_KNOCKBACK_Y * DOWN_AIR_KNOCKBACK;
                }
                break;
            case BACK_AIR:
                if (new_state.p2_lag == 9)
                {
                    hit = p2_hitbox(new_state, direction, -5.0f, 8.0f, 8.0f);
                }
                else if (new_state.p2_lag == 8)
                {
                    hit = p2_hitbox(new_state, direction, 0.0f, 8.0f, 8.0f) ||
                        p2_hitbox(new_state, direction, 5.0f, 8.0f, 8.0f);
                }
                else if (new_state.p2_lag == 7)
                {
                    hit = p2_hitbox(new_state, direction, 5.0f, 8.0f, 8.0f) ||
                        p2_hitbox(new_state, direction, 17.5f, 8.0f, 8.0f);
                }
                else if ((new_state.p2_lag == 6) | (new_state.p2_lag == 5))
                {
                    hit = p2_hitbox(new_state, direction, 7.5f, 8.0f, 8.0f) ||
                        p2_hitbox(new_state, direction, 20.0f, 8.0f, 8.0f);
                }
                else
                {
                    hit = 0;
                }
                if (hit)
                {
                    hits += 2;
                    new_state.p1_hp -= BACK_AIR_DAMAGE;
                    new_state.p1_lag = BACK_AIR_HITLAG;
                    new_state.p1_vx += direction * BACK_AIR_KNOCKBACK_X * BACK_AIR_KNOCKBACK;
                    new_state.p1_vy += BACK_AIR_KNOCKBACK_Y * BACK_AIR_KNOCKBACK;
                }
                break;
        }
    }

    if (hits % 2)
    {
        new_state.p1_flags |= MOVE_HAS_HIT; // Set move has hit
        new_state.p2_flags &= ~GROUNDED;    // Unset grounded
        new_state.p2_current_move = -1;
    }
    if (hits / 2)
    {
        new_state.p2_flags |= MOVE_HAS_HIT; // Set move has hit
        new_state.p1_flags &= ~GROUNDED;    // Unset grounded
        new_state.p1_current_move = -1;
    }

    return new_state;
}

game_result play_game(
    void* p1_ai,
    void* p2_ai,
    input_fn get_p1_input,
    input_fn get_p2_input)
{
    // 3600 frames at 30fps means a maximum of 2 minute games.
    game_state* states = (game_state*)malloc(3601 * sizeof(game_state));
    states[0] = get_initial_game_state();
    int frame;
    for (frame = 0; frame < 3600; ++frame)
    {
        game_state current_state = states[frame];
        if ((current_state.p1_hp <= 0) | (current_state.p2_hp <= 0))
        {
            frame += 1;
            break;
        }
        player_input p1_input = get_p1_input(current_state, 0, p1_ai);
        player_input p2_input = get_p2_input(current_state, 1, p2_ai);
        states[frame + 1] = step(current_state, p1_input, p2_input);
    }
    game_result result = {states, frame};
    return result;
}
