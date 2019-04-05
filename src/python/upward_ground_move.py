from player import Player
from move import Hitbox

class UpwardGroundMove:
	duration = 10
	damage = 10
	hitlag = 16
	knockback = 600
	knockback_angle = 6

	def __init__(self, player):
		self.player = player
		self.frame = 0
		self.hit_enemy = False

		self.player.lag = UpwardGroundMove.duration
		self.player.hitboxes = []

	def advance(self):
		direction = 1
		if not self.player.facing_left:
			direction = -1
		middle_x = self.player.x + direction * Player.w / 2.0

		if self.frame == 2:
			self.player.hitboxes = [_make_hitbox(middle_x, self.player.y, 8)]
		elif self.frame == 3:
			self.player.hitboxes = [_make_hitbox(middle_x - 4 * direction, self.player.y - 14, 8)]
		elif self.frame == 4:
			self.player.hitboxes = [_make_hitbox(self.player.x, self.player.y - 26, 13)]
		elif self.frame == 5:
			self.player.hitboxes = [_make_hitbox(self.player.x, self.player.y - 24, 15)]
		elif self.frame == 6:
			self.player.hitboxes = []
		elif self.frame == 9:
			self.player.current_move = None

		self.frame += 1

def _make_hitbox(px,
	py,
	radius,
	damage = UpwardGroundMove.damage,
	hitlag = UpwardGroundMove.hitlag,
	knockback = UpwardGroundMove.knockback,
	knockback_angle = UpwardGroundMove.knockback_angle):
	return Hitbox(px, py, radius, damage, hitlag, knockback, knockback_angle)
