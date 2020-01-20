import struct


class GameState:
    def __init__(self, binary):
        (p1_x,
            p1_y,
            p1_vx,
            p1_vy,
            p1_hp,
            p1_lag,
            p1_current_move,
            p1_flags,
            p2_x,
            p2_y,
            p2_vx,
            p2_vy,
            p2_hp,
            p2_lag,
            p2_current_move,
            p2_flags) = struct.unpack("ffffiiiiffffiiii", binary)
        self.p1_x = p1_x
        self.p1_y = p1_y
        self.p1_vx = p1_vx
        self.p1_vy = p1_vy
        self.p1_hp = p1_hp
        self.p1_lag = p1_lag
        self.p1_current_move = p1_current_move
        self.p1_flags = p1_flags
        self.p2_x = p2_x
        self.p2_y = p2_y
        self.p2_vx = p2_vx
        self.p2_vy = p2_vy
        self.p2_hp = p2_hp
        self.p2_lag = p2_lag
        self.p2_current_move = p2_current_move
        self.p2_flags = p2_flags
