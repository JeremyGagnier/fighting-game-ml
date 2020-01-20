import fighting_game


def init():
    global NUM_OF_STATES, _p1_ai, _p2_ai
    (_p1_ai, NUM_OF_STATES) = fighting_game.get_random_genetic_ai()
    (_p2_ai, NUM_OF_STATES) = fighting_game.get_random_genetic_ai()


def reset():
    fighting_game.set_genetic_ai(_p1_ai, NUM_OF_STATES, 0)
    fighting_game.set_genetic_ai(_p2_ai, NUM_OF_STATES, 1)
