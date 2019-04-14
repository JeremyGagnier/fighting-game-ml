from player import Player
import math
import moves


def init(players):
	global _players
	_players = players


def advance():
	for player in _players:
		if player.lag == 0 and player.inputs.attack:
			if player.grounded:
				if player.inputs.left or player.inputs.right:
					player.current_move = moves.forward_ground_move
				elif player.inputs.up:
					player.current_move = moves.upward_ground_move
				else:
					player.current_move = moves.neutral_ground_move
			else:
				if player.inputs.left and player.facing_left or player.inputs.right and not player.facing_left:
					player.current_move = moves.forward_aerial_move
				elif player.inputs.left and not player.facing_left or player.inputs.right and player.facing_left:
					player.current_move = moves.backward_aerial_move
				elif player.inputs.down:
					player.current_move = moves.downward_aerial_move

		elif player.lag > 0:
			player.lag -= 1

	# Check for players being hit by moves
	for player in _players:
		if player.current_move == None or player.has_move_hit:
			continue

		for opponent in _players:
			# You aren't your own opponent
			if player == opponent:
				continue

			for hitbox in player.current_move.hitboxes:
				if player.current_move.duration - player.lag in hitbox.active_frames and\
					_circle_to_rect(hitbox.x, hitbox.y, hitbox.radius, opponent.x, opponent.y, Player.w, Player.h):
					_hit_enemy(player, opponent, hitbox)


def _hit_enemy(player, opponent, hitbox):
	# Apply damage, knockback, lag, and cancel their move
	opponent.hitpoints -= hitbox.damage
	opponent.lag = hitbox.hitlag
	opponent.grounded = False
	opponent.current_move = None
	player.has_move_hit = True

	# Calculate knockback
	direction = 1
	if player.x > opponent.x:
		direction = -1

	angle = math.atan(hitbox.knockback_angle)
	opponent.vx =  math.cos(angle) * direction * hitbox.knockback
	opponent.vy = -math.sin(angle) * hitbox.knockback


def _circle_to_rect(cx, cy, cr, bx, by, bw, bh):
	# Adjust input
	bx -= bw / 2.0
	by -= bh / 2.0

	# Check cases
	if(((bx - cr <= cx and cx <= bx + bw + cr) and
	    (by <= cy and cy <= by + bh)) or
	   ((by - cr <= cy and cy <= by + bh + cr) and
	    (bx <= cx and cx <= bx + bw)) or
	   (bx - cx) * (bx - cx) + (by - cy) * (by - cy) <= (cr * cr) or
	   (bx + bw - cx) * (bx + bw - cx) + (by - cy) * (by - cy) <= (cr * cr) or
	   (bx - cx) * (bx - cx) + (by + bh - cy) * (by + bh - cy) <= (cr * cr) or
	   (bx + bw - cx) * (bx + bw - cx) + (by + bh - cy) * (by + bh - cy) <= (cr * cr)):
		return True;

	return False;
