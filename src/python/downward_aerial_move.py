from player import Player
from move import Hitbox

class DownwardAerialMove:
	duration = 16
	damage = 13
	hitlag = 24
	knockback = 500
	knockback_angle = -1
	def __init__(self, player):
		self.player = player
		self.frame = 0
		self.hit_enemy = False

		self.player.lag = DownwardAerialMove.duration
		self.player.hitboxes = []

	def advance(self):
		direction = 1
		if self.player.facing_left:
			direction = -1
		middle_y = self.player.y + Player.h / 2.0

		if self.frame == 4:
			self.player.hitboxes = [
				_make_hitbox(self.player.x + direction * 20, middle_y + 2, 9)]
		elif self.frame == 5:
			self.player.hitboxes = [
				_make_hitbox(self.player.x + direction * 20, middle_y + 2, 7),
				_make_hitbox(self.player.x + direction * 10, middle_y + 7, 9)]
		elif self.frame == 6:
			self.player.hitboxes = [
				_make_hitbox(self.player.x + direction * 20, middle_y + 2, 6),
				_make_hitbox(self.player.x + direction * 10, middle_y + 7, 7),
				_make_hitbox(self.player.x + direction * 0, middle_y + 9, 9)]
		elif self.frame == 7:
			self.player.hitboxes = [
				_make_hitbox(self.player.x + direction * 20, middle_y + 2, 5),
				_make_hitbox(self.player.x + direction * 10, middle_y + 7, 6),
				_make_hitbox(self.player.x + direction * 0, middle_y + 9, 7),
				_make_hitbox(self.player.x - direction * 10, middle_y + 7, 9)]
		elif self.frame == 8:
			self.player.hitboxes = [
				_make_hitbox(self.player.x + direction * 20, middle_y + 2, 4),
				_make_hitbox(self.player.x + direction * 10, middle_y + 7, 5),
				_make_hitbox(self.player.x + direction * 0, middle_y + 9, 6),
				_make_hitbox(self.player.x - direction * 10, middle_y + 7, 7),
				_make_hitbox(self.player.x - direction * 20, middle_y + 2, 9)]
		elif self.frame == 9:
			self.player.hitboxes = []
		elif self.frame == 15:
			self.player.current_move = None

		self.frame += 1

def _make_hitbox(px,
	py,
	radius,
	damage = DownwardAerialMove.damage,
	hitlag = DownwardAerialMove.hitlag,
	knockback = DownwardAerialMove.knockback,
	knockback_angle = DownwardAerialMove.knockback_angle):
	return Hitbox(px, py, radius, damage, hitlag, knockback, knockback_angle)
