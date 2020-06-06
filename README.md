# fighting-game-ml
This project is for exploring the application of machine learning to fighting games to create non-human players. Fighting games are well known for having poorly programmed AI that have superhuman reaction times but are easily exploited. The most common practice in the gaming industry for making these AI's is to combine hueristics with a behavior FSM. Machine learning techniques provide the possibility of having a more intelligent human-like AI which can significantly improve the fun of the game when playing alone.

This problem space is fundamentally different from well researched games like Chess and Go due to its real-time nature. This makes searches like alpha-beta pruning significantly less effective.

## Training checklist:
- Progressively stronger heuristic based AI
- Self-learning/adverserial

## Technique checklist:
- Genetic algorithm
  - Simple state discretization (done)
  - Neural net state discretization
- Neural net
  - Hill climbing parameter tuning
  - Genetic parameter tuning
  - Normal distributed temporal reinforcement


### State Discretization

The idea here is to convert a very large state space (800 pixels wide, 600 pixels tall map, up to 800 pixels delta x between fighters, etc.) into a smaller state space that is still sensitive to important differences. For example if your opponent is 500 pixels away it's not much different from them being 400 pixels away. However the difference between 20 pixels and 15 pixels can be very large since it can determine whether or not some attacks hit. This is easy to hard code but a neural net can provide better performance by learning which details matter and which do not.


## Runbook

To run the original python fighting game cd to src/python/old/ and run python3 game.py. You will need pygame and numpy installed. The evaluation speed can be modified with numbers 1 to 5.
