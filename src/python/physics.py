from game_info import *
from player import Player

GROUND_SPEED = 300.0
AERIAL_MOBILITY = 2400.0
JUMP_SPEED = 650.0
DOUBLE_JUMP_SPEED = 650.0
GRAVITY = 3000.0

def init(players):
	global _players
	_players = players

def advance():
	for player in _players:
		dx = 0
		if player.inputs.right:
			dx += 1
		if player.inputs.left:
			dx -= 1
			
		if player.grounded:
			if player.lag > 0:
				continue

			if player.inputs.right and not player.inputs.left:
				player.facing_left = False
			elif player.inputs.left and not player.inputs.right:
				player.facing_left = True

			player.x += GROUND_SPEED * TIMESTEP * dx

			# Make the player jump
			if player.inputs.jump:
				player.grounded = False
				player.vx = GROUND_SPEED * dx
				player.vy = -JUMP_SPEED
				player.y += player.vy * TIMESTEP
				continue

			# Check if player has walked over the edge
			if not _over_ground(player):
				player.grounded = False
				player.vx = GROUND_SPEED * dx

		else:
			player.vy += GRAVITY * TIMESTEP

			if player.lag <= 0 or player.current_move != None:
				if player.double_jump and player.inputs.jump:
					player.double_jump = False
					player.vy = -DOUBLE_JUMP_SPEED
					player.vx += GROUND_SPEED / 2.0 * dx

				player.vx += AERIAL_MOBILITY * TIMESTEP * dx
				player.vx = max(-GROUND_SPEED, min(player.vx, GROUND_SPEED))

			player.x += player.vx * TIMESTEP
			player.y += player.vy * TIMESTEP

			# Check if player has fallen to their death
			if _has_fallen(player):
				player.dead = True
				continue

			# Check if player landed on the ground and is no longer airbourne
			if _has_landed(player):
				player.grounded = True
				player.double_jump = True
				player.vy = 0
				player.vx = 0
				player.y = 550 - Player.h / 2.0

def _over_ground(player):
	inside_left_edge = player.x + Player.w / 2.0 > 100
	inside_right_edge = player.x - Player.w / 2.0 < 700
	return inside_left_edge and inside_right_edge

def _has_fallen(player):
	left_blastzone = player.x + Player.w / 2.0 < 0
	right_blastzone = player.x - Player.w / 2.0 > 800
	bottom_blastzone = player.y - Player.h / 2.0 > 600
	return left_blastzone or right_blastzone or bottom_blastzone

def _has_landed(player):
	fallen_past_ground = player.y + Player.h / 2.0 > 550
	return fallen_past_ground and _over_ground(player)
