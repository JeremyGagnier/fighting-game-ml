import fighting_game
import gene_pool
import graphics
import inputs

from game_state import GameState

gene_pool.init()
graphics.init()

_speed = 0


class Exit(Exception):
    pass


def _reset():
    graphics.reset()
    gene_pool.reset()


def _handle_input(commands):
    global _speed
    for (command, value) in commands:
        if command == inputs.EXIT:
            raise Exit()
        elif command == inputs.SPEED:
            _speed = value
        else:
            print("Unrecognized command " + command)


if __name__ == "__main__":
    try:
        _reset()
        raw_states = fighting_game.run("genetic", "genetic")
        for i in range(len(raw_states) / 64):
            state = GameState(raw_states[(i * 64):((i + 1) * 64)])
            _handle_input(inputs.process())
            if _speed == 0:
                wait_pct = 1.0
            elif _speed == 1:
                wait_pct = 0.5
            elif _speed == 2:
                wait_pct = 0.25
            elif _speed == 3:
                wait_pct = 0.1
            elif _speed == 4:
                wait_pct = 0.0
            graphics.render(state, wait_pct)

    except Exit:
        pass
