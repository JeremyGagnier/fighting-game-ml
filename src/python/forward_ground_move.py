from player import Player
from move import Hitbox

class ForwardGroundMove:
	duration = 16
	damage = 15
	hitlag = 20
	knockback = 600
	knockback_angle = 2
	def __init__(self, player):
		self.player = player
		self.frame = 0
		self.hit_enemy = False

		self.player.lag = ForwardGroundMove.duration
		self.player.hitboxes = []

	def advance(self):
		direction = 1
		if self.player.facing_left:
			direction = -1
		middle_x = self.player.x + direction * Player.w / 2.0

		if self.frame == 5:
			self.player.hitboxes = [
				_make_hitbox(middle_x + direction * 3, self.player.y + 7, 7),
				_make_hitbox(middle_x + direction * 10, self.player.y + 14, 9)]
		elif self.frame == 6:
			self.player.hitboxes = [
				_make_hitbox(middle_x + direction * 8, self.player.y + 5, 7),
				_make_hitbox(middle_x + direction * 16, self.player.y + 10, 9)]
		elif self.frame == 7:
			self.player.hitboxes = [
				_make_hitbox(middle_x + direction * 10, self.player.y + 0, 7),
				_make_hitbox(middle_x + direction * 20, self.player.y + 0, 9)]
		elif self.frame == 8:
			self.player.hitboxes = [
				_make_hitbox(middle_x + direction * 8, self.player.y - 5, 7),
				_make_hitbox(middle_x + direction * 16, self.player.y - 10, 9)]
		elif self.frame == 9:
			self.player.hitboxes = [
				_make_hitbox(middle_x + direction * 3, self.player.y - 7, 7),
				_make_hitbox(middle_x + direction * 10, self.player.y - 14, 9)]
		elif self.frame == 10:
			self.player.hitboxes = []
		elif self.frame == 15:
			self.player.current_move = None

		self.frame += 1

def _make_hitbox(px,
	py,
	radius,
	damage = ForwardGroundMove.damage,
	hitlag = ForwardGroundMove.hitlag,
	knockback = ForwardGroundMove.knockback,
	knockback_angle = ForwardGroundMove.knockback_angle):
	return Hitbox(px, py, radius, damage, hitlag, knockback, knockback_angle)
