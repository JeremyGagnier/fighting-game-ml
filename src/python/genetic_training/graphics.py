import pygame

TIMESTEP = 1.0 / 30.0


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
    player_color = (255, 0, 0)
    if self.lag > 0:
        player_color = (128, 0, 128)
    pygame.draw.rect(surface, player_color, (self.x - Player.w / 2.0, self.y - Player.h / 2.0, Player.w, Player.h))

    if self.current_move != None:
        for hitbox in self.current_move.hitboxes:
            if self.current_move.duration - self.lag in hitbox.active_frames:
                hitbox_x = int(hitbox.dx + self.x)
                hitbox_y = int(hitbox.dy + self.y)
                pygame.draw.circle(surface, (0, 0, 255), (hitbox_x, hitbox_y), int(hitbox.radius))


def render(game_state, wait_pct):
    global _screen

    pygame.time.wait(int(TIMESTEP * 1000 * wait_pct))

    _screen.fill((0, 0, 0))
    pygame.draw.rect(_screen, (0, 180, 0), (100, 550, 600, 50))
    _render_players(game_state)
    pygame.display.update()
