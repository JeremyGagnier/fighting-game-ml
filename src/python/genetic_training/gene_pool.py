import fighting_game


def init():
    global _p1_ai, _p2_ai
    _p1_ai = fighting_game.get_random_genetic_ai()
    _p2_ai = fighting_game.get_random_genetic_ai()


def reset():
    fighting_game.set_genetic_ai(0, _p1_ai)
    fighting_game.set_genetic_ai(1, _p2_ai)
