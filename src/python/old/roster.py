import ai
import graphics
import threading
import numpy
import os
import glob
import copy
import random

PATH_TO_GENETICS = "../../../genetics/"

def init():
	global _roster, _rating, _i, _j, _k

	names = []
	ai_num = 25
	try:
		fin = open(PATH_TO_GENETICS + "info", "r")
		data = fin.read()
		fin.close()
		data = data.split(",")
		ai_num = int(data[0])
		names = data[1:]
	except:
		pass

	_roster = [ai.AI(n) for n in names]
	ai.AI.num = ai_num - (25 - len(names))
	_roster += [ai.AI(str(ai.AI.num)) for i in range(25 - len(names))]

	_rating = [0 for i in range(25)]
	for player in _roster:
		try:
			player.setup_policy(PATH_TO_GENETICS)
		except:
			player.randomize()

	_i = 0
	_j = 1
	_k = random.randint(0, 1)

def save():
	print("Saving " + str(len(_roster)) + " players")
	map(os.remove, glob.glob(PATH_TO_GENETICS + "*"))

	state = str(ai.AI.num) + ","
	pnames = ""
	for player in _roster:
		print("Saving player " + player.name)
		player.save(PATH_TO_GENETICS)
		pnames += player.name + ","

	state += pnames[:-1]

	fout = open(PATH_TO_GENETICS + "info", "w")
	fout.write(state)
	fout.close()

def get_next_players():
	global _i, _j, _k

	if (_k == 0):
		return (_roster[_i], _roster[_j])
	return (_roster[_j], _roster[_i])

def is_match_important():
	global _i, _j

	return (_i == 0 and _j < 5)

def end_round():
	global _roster, _rating

	print("Ending round.")

	score_roster = zip(_rating, _roster)
	score_roster = sorted(score_roster, key=lambda x: x[0], reverse=True)
	graphics.set_leaderboard(score_roster)
	_rating, _roster = zip(*score_roster)
	_roster = list(_roster)
	_rating = [0 for i in range(25)]

	for rating, player in score_roster:
		player.score = rating

	_roster[20] = ai.AI(str(ai.AI.num))
	_roster[21] = ai.AI(str(ai.AI.num))

	_roster[20].randomize()
	_roster[21].randomize()

	_roster[22] = ai.breed(_roster[0], _roster[1])
	_roster[23] = ai.breed(_roster[2], _roster[3])
	_roster[24] = ai.breed(_roster[4], _roster[5])

	truth = _roster[0].policies == _roster[1].policies
	for i in range(2, 10):
		truth = numpy.logical_and(truth, _roster[0].policies == _roster[i].policies)

	diff = sum(numpy.ones(ai.NUM_OF_STATES, numpy.int8)[truth])
	similarity_pct = float(diff) / float(ai.NUM_OF_STATES)

	print("Genetic difference among top 10 is: " + str(round(1 - similarity_pct, 4)))

	for i in range(10):
		_roster[i].top_10s += 1

	return score_roster

def end_match(players, winner):
	global _i, _j, _k, _rating

	if winner == 0:
		if _k == 0:
			_rating[_i] += min(100 - players[1].hitpoints, 100) + 25
			if players[1].hitpoints > 0 and (players[1].current_move != None or players[1].lag == 0):
				# Player 1 jumped to their death, penalize them
				_rating[_j] -= 25
		else:
			_rating[_j] += min(100 - players[1].hitpoints, 100) + 25
			if players[1].hitpoints > 0 and (players[1].current_move != None or players[1].lag == 0):
				# Player 1 jumped to their death, penalize them
				_rating[_i] -= 25
	elif winner == 1:
		if _k == 0:
			_rating[_j] += min(100 - players[0].hitpoints, 100) + 25
			if players[0].hitpoints > 0 and (players[0].current_move != None or players[0].lag == 0):
				# Player 0 jumped to their death, penalize them
				_rating[_i] -= 25
		else:
			_rating[_i] += min(100 - players[0].hitpoints, 100) + 25
			if players[0].hitpoints > 0 and (players[0].current_move != None or players[0].lag == 0):
				# Player 0 jumped to their death, penalize them
				_rating[_j] -= 25


	_k = random.randint(0, 1)
	_j += 1

	if _j >= 25:
		_i += 1
		_j = _i + 1

	if _i >= 24:
		end_round()
		_i = 0
		_j = 1
