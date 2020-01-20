import pygame

EXIT = 0
SPEED = 1


def process():
    commands = []
    for e in pygame.event.get():
        if e.type == pygame.QUIT:
            commands.append((EXIT, None))
        elif e.type == pygame.KEYUP:
            if e.key == pygame.K_q:
                commands.append((EXIT, None))
            elif e.key == pygame.K_ESCAPE:
                commands.append((EXIT, None))
            elif e.key == pygame.K_1:
                commands.append((SPEED, 0))
            elif e.key == pygame.K_2:
                commands.append((SPEED, 1))
            elif e.key == pygame.K_3:
                commands.append((SPEED, 2))
            elif e.key == pygame.K_4:
                commands.append((SPEED, 3))
            elif e.key == pygame.K_5:
                commands.append((SPEED, 4))

    return commands
