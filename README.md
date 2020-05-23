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

The idea here is to convert a very large state space (800 pixels wide, 600 pixels tall map, up to 800 pixels delta x between fighters, etc.) into a smaller state space that is still sensitive to important differences. For example if your opponent is 500 pixels away it's not much different from them being 400 pixels away. However the difference between 20 pixels and 15 pixels can be very large since it can determine whether or not some attacks hit. This is easy to hard code but a neural net could learn what details about the state space are important in order to enhance other techniques.
