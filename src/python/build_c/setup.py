from distutils.core import setup, Extension

def main():
    setup(name="fighting_game",
          version="1.0.0",
          description="",
          author="Jeremy Gagnier",
          author_email="jer.gagnier@gmail.com",
          ext_modules=[Extension("fighting_game", ["../../c/fighting_game_module.c"])])

if __name__ == "__main__":
    main()
