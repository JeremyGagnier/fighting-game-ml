from player import Player
from move import Hitbox

class NeutralGroundMove:
	duration = 6
	damage = 8
	hitlag = 10
	knockback = 400
	knockback_angle = 0.5

	def __init__(self, player):
		self.player = player
		self.frame = 0
		self.hit_enemy = False

		self.player.lag = NeutralGroundMove.duration
		self.player.hitboxes = []

	def advance(self):
		if self.frame == 0:
			self.player.hitboxes = [_make_hitbox(self.player.x, self.player.y, 25)]
		elif self.frame == 1:
			self.player.hitboxes = [_make_hitbox(self.player.x, self.player.y, 22, hitlag = NeutralGroundMove.hitlag - 1)]
		elif self.frame == 2:
			self.player.hitboxes = [_make_hitbox(self.player.x, self.player.y, 20, hitlag = NeutralGroundMove.hitlag - 2)]
		elif self.frame == 3:
			self.player.hitboxes = []
		elif self.frame == 5:
			self.player.current_move = None

		self.frame += 1

def _make_hitbox(px,
	py,
	radius,
	damage = NeutralGroundMove.damage,
	hitlag = NeutralGroundMove.hitlag,
	knockback = NeutralGroundMove.knockback,
	knockback_angle = NeutralGroundMove.knockback_angle):
	return Hitbox(px, py, radius, damage, hitlag, knockback, knockback_angle)
