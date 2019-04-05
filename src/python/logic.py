from player import Player
from forward_ground_move import ForwardGroundMove
from neutral_ground_move import NeutralGroundMove
from upward_ground_move import UpwardGroundMove
from forward_aerial_move import ForwardAerialMove
from backward_aerial_move import BackwardAerialMove
from downward_aerial_move import DownwardAerialMove
import math

def init(players):
	global _players
	_players = players

def advance():
	for player in _players:
		if player.lag == 0 and player.inputs.attack:
			if player.grounded:
				if player.inputs.left or player.inputs.right:
					player.current_move = ForwardGroundMove(player)
				elif player.inputs.up:
					player.current_move = UpwardGroundMove(player)
				else:
					player.current_move = NeutralGroundMove(player)
			else:
				if player.inputs.left and player.facing_left or player.inputs.right and not player.facing_left:
					player.current_move = ForwardAerialMove(player)
				elif player.inputs.left and not player.facing_left or player.inputs.right and player.facing_left:
					player.current_move = BackwardAerialMove(player)
				elif player.inputs.down:
					player.current_move = DownwardAerialMove(player)

		elif player.lag > 0:
			player.lag -= 1

		if player.current_move != None:
			player.current_move.advance()

	# Check for players being hit by moves
	for player in _players:
		if player.current_move == None:
			continue

		# Can't hit your opponent multiple times with the same move
		if player.current_move.hit_enemy:
			continue

		for opponent in _players:
			# You aren't your own opponent
			if player == opponent:
				continue

			for hitbox in player.hitboxes:
				if _circle_to_rect(hitbox.x, hitbox.y, hitbox.radius, opponent.x, opponent.y, Player.w, Player.h):
					_hit_enemy(player, opponent, hitbox)

def _hit_enemy(player, opponent, hitbox):
	# Apply damage, knockback, lag, and cancel their move
	opponent.hitpoints -= hitbox.damage
	if opponent.hitpoints <= 0:
		opponent.dead = True
	opponent.lag = hitbox.hitlag
	opponent.grounded = False
	opponent.current_move = None
	opponent.hitboxes = []
	player.current_move.hit_enemy = True

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
