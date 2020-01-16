from move import Move
from hitbox import Hitbox

backward_aerial_move = Move(
    duration = 10,
    damage = 12,
    hitlag = 10,
    decreasing_hitlag = False,
    knockback = 450,
    knockback_angle = 0.5,
    hitboxes = [
        Hitbox( 7.5, 8, 8, (1,)),
        Hitbox(12.5, 8, 8, (2,)),
        Hitbox(17.5, 8, 8, (2, 3)),
        Hitbox(  30, 8, 8, (3,)),
        Hitbox(  20, 8, 8, (4, 5)),
        Hitbox(32.5, 8, 8, (4, 5))])

downward_aerial_move = Move(
    duration = 16,
    damage = 13,
    hitlag = 24,
    decreasing_hitlag = False,
    knockback = 500,
    knockback_angle = -1,
    hitboxes = [
        Hitbox( 20, 22, 9, (1,)),
        Hitbox( 20, 22, 7, (2,)),
        Hitbox( 20, 22, 6, (3,)),
        Hitbox( 20, 22, 5, (4,)),
        Hitbox( 20, 22, 4, (5,)),
        Hitbox( 10, 27, 9, (2,)),
        Hitbox( 10, 27, 7, (3,)),
        Hitbox( 10, 27, 6, (4,)),
        Hitbox( 10, 27, 5, (5,)),
        Hitbox(  0, 29, 9, (3,)),
        Hitbox(  0, 29, 7, (4,)),
        Hitbox(  0, 29, 6, (5,)),
        Hitbox(-10, 27, 9, (4,)),
        Hitbox(-10, 27, 7, (5,)),
        Hitbox(-20, 22, 9, (5,))])

forward_aerial_move = Move(
    duration = 16,
    damage = 15,
    hitlag = 20,
    decreasing_hitlag = False,
    knockback = 600,
    knockback_angle = 2,
    hitboxes = [
        Hitbox(15.5,  -7, 7, (5,)),
        Hitbox(22.5, -14, 9, (5,)),
        Hitbox(20.5,  -5, 7, (6,)),
        Hitbox(28.5, -10, 9, (6,)),
        Hitbox(22.5,   0, 7, (7,)),
        Hitbox(32.5,   0, 9, (7,)),
        Hitbox(20.5,   5, 7, (8,)),
        Hitbox(28.5,  10, 9, (8,)),
        Hitbox(15.5,   7, 7, (9,)),
        Hitbox(22.5,  14, 9, (9,))])

forward_ground_move = Move(
    duration = 16,
	damage = 15,
	hitlag = 20,
    decreasing_hitlag = False,
	knockback = 600,
	knockback_angle = 2,
    hitboxes = [
        Hitbox(15.5,   7, 7, (5,)),
        Hitbox(22.5,  14, 9, (5,)),
        Hitbox(20.5,   5, 7, (6,)),
        Hitbox(28.5,  10, 9, (6,)),
        Hitbox(22.5,   0, 7, (7,)),
        Hitbox(32.5,   0, 9, (7,)),
        Hitbox(20.5,  -5, 7, (8,)),
        Hitbox(28.5, -10, 9, (8,)),
        Hitbox(15.5,  -7, 7, (9,)),
        Hitbox(22.5, -14, 9, (9,))])

neutral_ground_move = Move(
    duration = 6,
    damage = 8,
    hitlag = 10,
    decreasing_hitlag = True,
    knockback = 400,
    knockback_angle = 0.5,
    hitboxes = [
        Hitbox(0, 0, 25, (0,)),
        Hitbox(0, 0, 22, (1,)),
        Hitbox(0, 0, 20, (2,))])

upward_ground_move = Move(
    duration = 10,
    damage = 10,
    hitlag = 16,
    decreasing_hitlag = False,
    knockback = 600,
    knockback_angle = 6,
    hitboxes = [
        Hitbox(12.5,   0, 8, (2,)),
        Hitbox( 8.5, -14, 8, (3,)),
        Hitbox(   0, -26, 13, (4,)),
        Hitbox(   0, -24, 15, (5,))])
