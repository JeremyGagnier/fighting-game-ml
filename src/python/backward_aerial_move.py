from player import Player
from move import Hitbox

class BackwardAerialMove:
	duration = 10
	damage = 12
	hitlag = 10
	knockback = 450
	knockback_angle = 0.5
	def __init__(self, player):
		self.player = player
		self.frame = 0
		self.hit_enemy = False

		self.player.lag = BackwardAerialMove.duration
		self.player.hitboxes = []

	def advance(self):
		direction = 1
		if not self.player.facing_left:
			direction = -1
		middle_x = self.player.x + direction * Player.w / 2.0

		if self.frame == 1:
			self.player.hitboxes = [
				_make_hitbox(middle_x - direction * 5, self.player.y + 8, 8),
				_make_hitbox(middle_x - direction * 5, self.player.y + 8, 8)]
		elif self.frame == 2:
			self.player.hitboxes = [
				_make_hitbox(middle_x + direction * 0, self.player.y + 8, 8),
				_make_hitbox(middle_x + direction * 5, self.player.y + 8, 8)]
		elif self.frame == 3:
			self.player.hitboxes = [
				_make_hitbox(middle_x + direction * 5, self.player.y + 8, 8),
				_make_hitbox(middle_x + direction * 17.5, self.player.y + 8, 8)]
		elif self.frame == 4:
			self.player.hitboxes = [
				_make_hitbox(middle_x + direction * 7.5, self.player.y + 8, 8),
				_make_hitbox(middle_x + direction * 20, self.player.y + 8, 8)]
		elif self.frame == 5:
			self.player.hitboxes = [
				_make_hitbox(middle_x + direction * 7.5, self.player.y + 8, 8),
				_make_hitbox(middle_x + direction * 20, self.player.y + 8, 8)]
		elif self.frame == 6:
			self.player.hitboxes = []
		elif self.frame == 9:
			self.player.current_move = None

		self.frame += 1

def _make_hitbox(
    px,
	py,
	radius,
	damage = BackwardAerialMove.damage,
	hitlag = BackwardAerialMove.hitlag,
	knockback = BackwardAerialMove.knockback,
	knockback_angle = BackwardAerialMove.knockback_angle):
	return Hitbox(px, py, radius, damage, hitlag, knockback, knockback_angle)
