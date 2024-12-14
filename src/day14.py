import re, sys

def safety_score(robots, iters, w=101, h=103):
    q1, q2, q3, q4 = 0,0,0,0
    wm, hm = w//2, h//2
    for x, y, vx, vy in robots:
        xf = (x + iters*vx) % w
        yf = (y + iters*vy) % h

        if (xf < wm and yf < hm): q1 += 1
        elif (xf < wm and yf > hm): q2 += 1
        elif (xf > wm and yf < hm): q3 += 1
        elif (xf > wm and yf > hm): q4 += 1

    return q1*q2*q3*q4
        

re_rbt = re.compile(r"p=(\d+),(\d+) v=(-?\d+),(-?\d+)")

input = [l.strip() for l in sys.stdin.readlines()]
robots = []
for inp in input:
    m = re_rbt.match(inp)
    assert m
    robots.append((int(m.group(1)), int(m.group(2)), int(m.group(3)), int(m.group(4))))

ans = 0
steps = [100]

for step in steps:
    print(safety_score(robots, step))
