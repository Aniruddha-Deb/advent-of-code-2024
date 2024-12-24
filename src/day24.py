from functools import reduce
import sys
import re

nets = {}

lines = [l.strip() for l in sys.stdin.readlines()]
parsing_gates = False
net_rgx = re.compile(r"([a-z0-9]{3}): ([01])")
gate_rgx = re.compile(r"([a-z0-9]{3}) (AND|OR|XOR) ([a-z0-9]{3}) -> ([a-z0-9]{3})")

gates = []
nets = {}

for line in lines:
    if line == "":
        parsing_gates = True
        continue

    if parsing_gates:
        groups = gate_rgx.match(line)
        assert groups is not None
        in1, in2 = groups[1], groups[3]
        op = groups[2]
        out = groups[4]
        gates.append((in1, op, in2, out))
        for net in [in1, in2, out]:
            if net not in nets:
                nets[net] = None

    else:
        groups = net_rgx.match(line)
        assert groups is not None
        net, value = groups[1], int(groups[2])
        nets[net] = value

while True:
    for in1, op, in2, out in gates:
        if nets[in1] is not None and nets[in2] is not None:
            out_value = None
            match op:
                case "AND": out_value = nets[in1] & nets[in2]
                case "OR": out_value = nets[in1] | nets[in2]
                case "XOR": out_value = nets[in1] ^ nets[in2]
            assert out_value is not None
            if nets[out] is None:
                nets[out] = out_value
            else:
                assert out_value == nets[out]  # inconsistency check

    if all([(value is not None) for value in nets.values()]):
        break

z_keys = [key for key in nets if key.startswith('z')]
z_keys.sort()
z_values = [nets[key]<<i for i, key in enumerate(z_keys)]
ans = reduce(lambda a,b: a|b, z_values)
print(ans)



