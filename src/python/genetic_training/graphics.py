import pygame

TIMESTEP = 1.0 / 30.0
PLAYER_W = 25.0
PLAYER_H = 40.0

def init():
    global _screen, _font
    pygame.init()
    _screen = pygame.display.set_mode((800, 600))
    _font = pygame.font.Font(pygame.font.get_default_font(), 26)


def reset():
    pass


def _draw_text(x, y, color, text):
    global _font, _screen

    surf = _font.render(text, True, color)
    _screen.blit(surf, (x, y))


def _render_players(game_state):
    p1_color = (255, 0, 0)
    if game_state.p1_lag > 0:
        p1_color = (128, 0, 128)
    pygame.draw.rect(_screen, p1_color, (game_state.p1_x - PLAYER_W / 2.0, game_state.p1_y - PLAYER_H / 2.0, PLAYER_W, PLAYER_H))

    p2_color = (255, 0, 0)
    if game_state.p2_lag > 0:
        p2_color = (128, 0, 128)
    pygame.draw.rect(_screen, p2_color, (game_state.p2_x - PLAYER_W / 2.0, game_state.p2_y - PLAYER_H / 2.0, PLAYER_W, PLAYER_H))
"""
    if game_state.current_move != None:
        for hitbox in game_state.current_move.hitboxes:
            if game_state.current_move.duration - game_state.lag in hitbox.active_frames:
                hitbox_x = int(hitbox.dx + game_state.x)
                hitbox_y = int(hitbox.dy + game_state.y)
                pygame.draw.circle(surface, (0, 0, 255), (hitbox_x, hitbox_y), int(hitbox.radius))
"""

def render(game_state, wait_pct):
    global _screen

    pygame.time.wait(int(TIMESTEP * 1000 * wait_pct))

    _screen.fill((0, 0, 0))
    pygame.draw.rect(_screen, (0, 180, 0), (100, 550, 600, 50))
    _render_players(game_state)
    pygame.display.update()
