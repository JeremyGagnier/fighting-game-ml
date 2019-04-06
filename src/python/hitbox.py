class Hitbox:
    def __init__(self, dx, dy, radius, active_frames, is_centered = False):
        self.dx = dx
        self.dy = dy
        self.radius = radius
        self.active_frames = active_frames
        self.is_centered = is_centered
