x_axis = 2
y_axis = 0
jump = 0
attack = 1

print(x_axis, y_axis, jump, attack)

policy = x_axis + 3 * (y_axis + 3 * (jump + 2 * attack))

x_axis = policy % 3
policy = policy // 3
y_axis = policy % 3
policy = policy // 3
jump = policy % 2
policy = policy // 2
attack = policy % 2

print(x_axis, y_axis, jump, attack)
