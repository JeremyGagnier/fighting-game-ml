import pygame

class PlayerInputs:
	def __init__(self):
		self.left = False
		self.right = False
		self.jump = False
		self.up = False
		self.down = False
		self.attack = False

def init():
	global _speed, _nographics

	_speed = 1
	_nographics = False

def reset(local_player_input):
	global _local_player_input

	_local_player_input = local_player_input

def process():
	global _local_player_input, _speed, _nographics

	_local_player_input.jump = False
	_local_player_input.attack = False

	quit = False
	for e in pygame.event.get():
		if e.type == pygame.QUIT:
			quit = True
		elif e.type == pygame.KEYUP:
			if e.key == pygame.K_q:
				quit = True
			elif e.key == pygame.K_ESCAPE:
				quit = True
			elif e.key == pygame.K_1:
				_speed = 1
				_nographics = False
			elif e.key == pygame.K_2:
				_speed = 0.5
				_nographics = False
			elif e.key == pygame.K_3:
				_speed = 0.25
				_nographics = False
			elif e.key == pygame.K_4:
				_speed = 0.1
				_nographics = False
			elif e.key == pygame.K_5:
				_speed = 0
				_nographics = True
			"""elif e.key == pygame.K_w:
				_local_player_input.up = False
			elif e.key == pygame.K_a:
				_local_player_input.left = False
			elif e.key == pygame.K_s:
				_local_player_input.down = False
			elif e.key == pygame.K_d:
				_local_player_input.right = False"""

		elif e.type == pygame.KEYDOWN:
			"""if e.key == pygame.K_w:
				_local_player_input.up = True
			elif e.key == pygame.K_a:
				_local_player_input.left = True
			elif e.key == pygame.K_s:
				_local_player_input.down = True
			elif e.key == pygame.K_d:
				_local_player_input.right = True
			elif e.key == pygame.K_SPACE:
				_local_player_input.jump = True
			elif e.key == pygame.K_f:
				_local_player_input.attack = True"""


	return (quit, _speed, _nographics)
