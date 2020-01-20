from distutils.core import setup, Extension


def main():
    setup(name="fighting_game",
          version="1.0.0",
          description="",
          author="Jeremy Gagnier",
          author_email="jer.gagnier@gmail.com",
          ext_modules=[Extension("fighting_game", ["fighting_game_module.c", "game/fighting_game.c", "game/game_state.c", "game/constants.c", "game/player_input.c", "ai/genetic_1/ai.c", "common/acorn.c"])])


if __name__ == "__main__":
    main()
