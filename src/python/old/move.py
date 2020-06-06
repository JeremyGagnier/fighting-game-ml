class Move:
    def __init__(self, duration, damage, hitlag, decreasing_hitlag, knockback, knockback_angle, hitboxes):
        self.duration = duration
        self.damage = damage
        self.hitlag = hitlag
        self.decreasing_hitlag = decreasing_hitlag
        self.knockback = knockback
        self.knockback_angle = knockback_angle
        self.hitboxes = hitboxes
