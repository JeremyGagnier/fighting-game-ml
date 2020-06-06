import graphics
import physics
import inputs
import logic
import ai
import roster
from player import Player

roster.init()
inputs.init()
graphics.init()

def reset():
	global players, AIs

	local_player_input = inputs.PlayerInputs()
	ai_input = inputs.PlayerInputs()
	players = (Player(200.0, 500.0, local_player_input), Player(600.0, 500.0, ai_input))

	inputs.reset(local_player_input)
	graphics.reset(players)
	physics.init(players)
	logic.init(players)

	AIs = roster.get_next_players()

reset()
iterations = 0
while True:
	iterations += 1

	quit, speed, nographics = inputs.process()
	for i, ai in enumerate(AIs):
		ai.advance(i, players)
	physics.advance()
	logic.advance()

	#if nographics and roster.is_match_important():
	#	graphics.render(0.25)
	if not nographics or (iterations % (30 * 30)) == 0:
		graphics.render(speed)


	for i, p in enumerate(players):
		if p.hitpoints <= 0 or physics.has_fallen(p):
			roster.end_match(players, 1 - i)
			reset()
			iterations = 0

	if iterations > 3 * 60 * 30:
		roster.end_match(players, None)
		reset()
		iterations = 0

	if quit:
		break

roster.save()

graphics.quit()
