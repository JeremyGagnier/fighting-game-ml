from move import Move
from hitbox import Hitbox

backward_aerial_move = new Move()

downward_aerial_move = new Move()

forward_aerial_move = new Move()

forward_ground_move = new Move(
    duration = 16,
	damage = 15,
	hitlag = 20,
    decreasing_hitlag = False,
	knockback = 600,
	knockback_angle = 2,
    hitboxes = [
        new Hitbox( 3,   7, 7, (5,)),
        new Hitbox(10,  14, 9, (5,)),
        new Hitbox( 8,   5, 7, (6,)),
        new Hitbox(16,  10, 9, (6,)),
        new Hitbox(10,   0, 7, (7,)),
        new Hitbox(20,   0, 9, (7,)),
        new Hitbox( 8,  -5, 7, (8,)),
        new Hitbox(16, -10, 9, (8,)),
        new Hitbox( 3,  -7, 7, (9,)),
        new Hitbox(10, -14, 9, (9,))])

neutral_ground_move = new Move()

upward_ground_move = new Move()
