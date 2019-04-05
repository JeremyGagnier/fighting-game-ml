class Player:
	w = 25
	h = 40
	def __init__(self, inputs, startx, starty):
		self.hitpoints = 100
		self.lag = 0
		self.current_move = None
		self.hitboxes = []
		self.inputs = inputs
		self.grounded = False
		self.double_jump = False
		self.dead = False
		self.facing_left = False
		self.vx = 0.0
		self.vy = 0.0
		self.x = startx
		self.y = starty

	def render(self, pygame, surface):
		player_color = (255, 0, 0)
		if self.dead:
			player_color = (50, 0, 0)
		elif self.lag > 0:
			player_color = (128, 0, 128)
		pygame.draw.rect(surface, player_color, (self.x - Player.w / 2.0, self.y - Player.h / 2.0, Player.w, Player.h))
		for hitbox in self.hitboxes:
			pygame.draw.circle(surface, (0, 0, 255), (int(hitbox.x), int(hitbox.y)), int(hitbox.radius))
			