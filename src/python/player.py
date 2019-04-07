class Player:
	w = 25
	h = 40
	def __init__(self, startx, starty):
		self.vx = 0.0
		self.vy = 0.0
		self.x = startx
		self.y = starty

		self.hitpoints = 100
		self.lag = 0
		self.current_move = None
        self.has_move_hit = False
		self.grounded = False
		self.double_jump = False
		self.facing_left = False

	def render(self, pygame, surface):
		player_color = (255, 0, 0)
		if self.lag > 0:
			player_color = (128, 0, 128)
		pygame.draw.rect(surface, player_color, (self.x - Player.w / 2.0, self.y - Player.h / 2.0, Player.w, Player.h))

        if (self.current_move != None):
            for hitbox in self.current_move.hitboxes:
                if self.hitlag in hitbox.active_frames:
                    hitbox_x = int(hitbox.dx + self.x)
                    hitbox_y = int(hitbox.dy + self.y)
                    pygame.draw.circle(surface, (0, 0, 255), (hitbox_x, hitbox_y), int(hitbox.radius))
