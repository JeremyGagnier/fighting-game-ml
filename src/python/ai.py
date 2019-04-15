import pickle
import random
import numpy

NUM_OF_STATES = 28 * 28 * 16
MUTATION = 0.0005

class State:
	def __init__(self,
		opponent_x_diff,		# 800 unique spaces
		opponent_y_diff,		# 600 unique spaces
		dist_to_left_edge):		# 800 unique spaces

		self.opponent_x_diff = opponent_x_diff
		self.opponent_y_diff = opponent_y_diff
		self.dist_to_left_edge = dist_to_left_edge

	def get_id(self):
		if (self.opponent_x_diff < -510): x_diff_state = 0
		elif (self.opponent_x_diff < -330): x_diff_state = 1
		elif (self.opponent_x_diff < -210): x_diff_state = 2
		elif (self.opponent_x_diff < -130): x_diff_state = 3
		elif (self.opponent_x_diff < -80): x_diff_state = 4
		elif (self.opponent_x_diff < -60): x_diff_state = 5
		elif (self.opponent_x_diff < -49): x_diff_state = 6
		elif (self.opponent_x_diff < -39): x_diff_state = 7
		elif (self.opponent_x_diff < -30): x_diff_state = 8
		elif (self.opponent_x_diff < -22): x_diff_state = 9
		elif (self.opponent_x_diff < -15): x_diff_state = 10
		elif (self.opponent_x_diff < -9): x_diff_state = 11
		elif (self.opponent_x_diff < -4): x_diff_state = 12
		elif (self.opponent_x_diff < 0): x_diff_state = 13
		elif (self.opponent_x_diff < 4): x_diff_state = 14
		elif (self.opponent_x_diff < 9): x_diff_state = 15
		elif (self.opponent_x_diff < 15): x_diff_state = 16
		elif (self.opponent_x_diff < 22): x_diff_state = 17
		elif (self.opponent_x_diff < 30): x_diff_state = 18
		elif (self.opponent_x_diff < 39): x_diff_state = 19
		elif (self.opponent_x_diff < 49): x_diff_state = 20
		elif (self.opponent_x_diff < 60): x_diff_state = 21
		elif (self.opponent_x_diff < 80): x_diff_state = 22
		elif (self.opponent_x_diff < 130): x_diff_state = 23
		elif (self.opponent_x_diff < 210): x_diff_state = 24
		elif (self.opponent_x_diff < 330): x_diff_state = 25
		elif (self.opponent_x_diff < 510): x_diff_state = 26
		else: x_diff_state = 27

		if (self.opponent_y_diff < -510): y_diff_state = 0
		elif (self.opponent_y_diff < -330): y_diff_state = 1
		elif (self.opponent_y_diff < -210): y_diff_state = 2
		elif (self.opponent_y_diff < -130): y_diff_state = 3
		elif (self.opponent_y_diff < -80): y_diff_state = 4
		elif (self.opponent_y_diff < -60): y_diff_state = 5
		elif (self.opponent_y_diff < -49): y_diff_state = 6
		elif (self.opponent_y_diff < -39): y_diff_state = 7
		elif (self.opponent_y_diff < -30): y_diff_state = 8
		elif (self.opponent_y_diff < -22): y_diff_state = 9
		elif (self.opponent_y_diff < -15): y_diff_state = 10
		elif (self.opponent_y_diff < -9): y_diff_state = 11
		elif (self.opponent_y_diff < -4): y_diff_state = 12
		elif (self.opponent_y_diff < 0): y_diff_state = 13
		elif (self.opponent_y_diff < 4): y_diff_state = 14
		elif (self.opponent_y_diff < 9): y_diff_state = 15
		elif (self.opponent_y_diff < 15): y_diff_state = 16
		elif (self.opponent_y_diff < 22): y_diff_state = 17
		elif (self.opponent_y_diff < 30): y_diff_state = 18
		elif (self.opponent_y_diff < 39): y_diff_state = 19
		elif (self.opponent_y_diff < 49): y_diff_state = 20
		elif (self.opponent_y_diff < 60): y_diff_state = 21
		elif (self.opponent_y_diff < 80): y_diff_state = 22
		elif (self.opponent_y_diff < 130): y_diff_state = 23
		elif (self.opponent_y_diff < 210): y_diff_state = 24
		elif (self.opponent_y_diff < 330): y_diff_state = 25
		elif (self.opponent_y_diff < 510): y_diff_state = 26
		else: y_diff_state = 27

		if (self.dist_to_left_edge < 50): left_edge_state = 0
		elif (self.dist_to_left_edge < 75): left_edge_state = 1
		elif (self.dist_to_left_edge < 95): left_edge_state = 2
		elif (self.dist_to_left_edge < 100): left_edge_state = 3
		elif (self.dist_to_left_edge < 105): left_edge_state = 4
		elif (self.dist_to_left_edge < 125): left_edge_state = 5
		elif (self.dist_to_left_edge < 200): left_edge_state = 6
		elif (self.dist_to_left_edge < 400): left_edge_state = 7
		elif (self.dist_to_left_edge < 600): left_edge_state = 8
		elif (self.dist_to_left_edge < 675): left_edge_state = 9
		elif (self.dist_to_left_edge < 695): left_edge_state = 10
		elif (self.dist_to_left_edge < 700): left_edge_state = 11
		elif (self.dist_to_left_edge < 705): left_edge_state = 12
		elif (self.dist_to_left_edge < 725): left_edge_state = 13
		elif (self.dist_to_left_edge < 750): left_edge_state = 14
		else: left_edge_state = 15

		return (x_diff_state + 28 * (y_diff_state + 28 * left_edge_state))

def get_state(pnum, players):
	player = players[pnum]
	opponent = players[1 - pnum]

	return State(
		opponent.x - player.x,
		opponent.y - player.y,
		player.x)

def apply_policy(policy, inputs):
	x_axis = policy % 3
	policy = policy // 3
	y_axis = policy % 3
	policy = policy // 3
	jump = policy % 2
	policy = policy // 2
	attack = policy % 21

	if x_axis == 1 and random.random() < 0.05:
		x_axis = random.randint(0, 1) * 2

	inputs.left = x_axis == 0
	inputs.right = x_axis == 2
	inputs.down = y_axis == 0
	inputs.up = y_axis == 2
	inputs.jump = jump == 1
	inputs.attack = attack == 1

def breed(ai0, ai1):
	new_ai = AI(str(AI.num))
	new_ai.ancestral_top_10s = (ai0.ancestral_top_10s + ai0.top_10s + ai1.ancestral_top_10s + ai1.top_10s) / 2

	choices = numpy.random.randint(2, size=NUM_OF_STATES, dtype=numpy.int8)
	new_ai.policies = numpy.zeros(NUM_OF_STATES, numpy.int8)
	new_ai.policies += numpy.multiply(ai0.policies, choices)
	new_ai.policies += numpy.multiply(ai1.policies, 1 - choices)

	chance = numpy.random.randint(int(round(1 / MUTATION)) + 1, size=NUM_OF_STATES, dtype=numpy.int32)
	mutations = numpy.random.randint(36, size=NUM_OF_STATES, dtype=numpy.int8)
	new_ai.policies[chance == 0] = mutations[chance == 0]

	return new_ai

class AI:
	num = 0
	def __init__(self, name):
		AI.num += 1
		self.name = name
		self.top_10s = 0
		self.ancestral_top_10s = 0
		self.score = None

	def randomize(self):
		self.policies = numpy.random.randint(36, size=NUM_OF_STATES, dtype=numpy.int8)
		print("Randomizing player " + self.name)

	def setup_policy(self):
		fin = open("genetics/" + self.name + ".ai", "rb")
		self.policies = pickle.load(fin)
		fin.close()
		print("Loading player " + self.name)

	def save(self):
		fout = open("genetics/" + self.name + ".ai", "wb")
		pickle.dump(self.policies, fout)
		fout.close()
		print("Saving player " + self.name)

	def advance(self, pnum, players):
		state = get_state(pnum, players)
		state_id = state.get_id()
		policy = self.policies[state_id]
		apply_policy(policy, players[pnum].inputs)

