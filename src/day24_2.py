import sys
import re
from typing import Optional

nets = {}

lines = [l.strip() for l in sys.stdin.readlines()]
parsing_gates = False
net_rgx = re.compile(r"([a-z0-9]{3}): ([01])")
gate_rgx = re.compile(r"([a-z0-9]{3}) (AND|OR|XOR) ([a-z0-9]{3}) -> ([a-z0-9]{3})")

gates = []
nets = {}

wires = {}

def get_half_adder(a, b) -> tuple[Optional[str], Optional[str]]:
    s = None
    c = None
    for in1, op, in2, out in gates:
        if s is not None and c is not None:
            break
        if set((in1, in2)) == set((a, b)):
            match op:
                case 'AND': c = out
                case 'XOR': s = out

    return (s, c)

def is_half_adder(a, b, s) -> Optional[str]:
    s_out, c_out = get_half_adder(a, b)
    if s_out == s:
        return c_out
    return None

def get_full_adder(a, b, c) -> tuple[Optional[str], Optional[str]]:
    p = [c, a, b]
    for _ in range(3):
        p = p[1:] + p[:1]
        s0, c0 = get_half_adder(p[0], p[1])
        if s0 is None or c0 is None:
            continue
        s1, c1 = get_half_adder(s0, p[2])
        if s1 is None or c1 is None:
            continue

        c_out = None
        for in1, op, in2, out in gates:
            if c_out is not None:
                break
            if set((in1, in2)) == set((c0, c1)):
                match op:
                    case 'OR': c_out = out

        if c_out:
            return (s1, c_out)
        
    return (None, None)

def print_full_adder(a, b, c) -> tuple[Optional[str], Optional[str]]:
    p = [c, a, b]
    for _ in range(3):
        p = p[1:] + p[:1]
        s0, c0 = get_half_adder(p[0], p[1])
        if s0 is None or c0 is None:
            continue
        s1, c1 = get_half_adder(s0, p[2])
        if s1 is None or c1 is None:
            continue

        c_out = None
        for in1, op, in2, out in gates:
            if c_out is not None:
                break
            if set((in1, in2)) == set((c0, c1)):
                match op:
                    case 'OR': c_out = out

        if c_out:
            return (s1, c_out)
        
    return (None, None)

def is_full_adder(a, b, c_in, s) -> Optional[str]:
    s_out, c_out = get_full_adder(a, b, c_in)
    if s_out == s:
        return c_out

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

c = None
for i in range(45):
    old_c = c
    x, y, z = f"x{i:02}", f"y{i:02}", f"z{i:02}"
    print(x, y, c, z)
    if i == 0:
        c = is_half_adder(x, y, z)
    else:
        c = is_full_adder(x, y, c, z)

    # semi-automatic: on finding errors, override here.

    if not c:
        s1, c1 = get_half_adder(x, y)
        # s2, c2 = get_half_adder(s1, old_c)
        for in1, op, in2, out in gates:
            s1 = set((in1, in2, out))
            s2 = set((x, y, old_c, z, str(s1), str(c1)))
            if s1.intersection(s2):
                print("  ", in1, op, in2, "=>", out)

        if not c:
            break

