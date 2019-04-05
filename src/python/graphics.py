from game_info import *
import pygame


def init():
	global _screen, _leaders, _font
	pygame.init()
	_screen = pygame.display.set_mode((800, 600))
	_leaders = ()
	_font = pygame.font.Font(pygame.font.get_default_font(), 26)

def reset(players):
	global _players
	_players = players

def set_leaderboard(leaders):
	global _leaders

	_leaders = leaders[:10]

def _draw_text(x, y, color, text):
	global _font, _screen

	surf = _font.render(text, True, color)
	_screen.blit(surf, (x, y))

def render_ui():
	global _leaders

	for i, leader in enumerate(_leaders):
		name = leader[1].name
		score = str(leader[0])
		color = (max(255 - 10 * leader[1].top_10s, 0), max(255 - 10 * leader[1].ancestral_top_10s, 0), 255)
		_draw_text(10, 10 + i * 30, color, str(i + 1) + ": Player " + name + " - Score " + score)

def render(wait_pct):
	global _screen, _players

	_screen.fill((0, 0, 0))

	pygame.draw.rect(_screen, (0, 180, 0), (100, 550, 600, 50))

	for player in _players:
		player.render(pygame, _screen)

	render_ui()
	pygame.display.update()
	pygame.time.wait(int(TIMESTEP * 1000 * wait_pct))


def quit():
	pygame.display.quit()
	pygame.quit()
