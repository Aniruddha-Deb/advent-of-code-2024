import re, sys
import numpy as np

def render(robots, frame, w=101, h=103):
    x_coords = []
    y_coords = []
    for x, y, vx, vy in robots:
        xf = (x + frame*vx) % w
        yf = (y + frame*vy) % h

        x_coords.append(xf)
        y_coords.append(yf)

    return x_coords, y_coords

re_rbt = re.compile(r"p=(\d+),(\d+) v=(-?\d+),(-?\d+)")

input = [l.strip() for l in sys.stdin.readlines()]
robots = []
for inp in input:
    m = re_rbt.match(inp)
    assert m
    robots.append((int(m.group(1)), int(m.group(2)), int(m.group(3)), int(m.group(4))))

x_vars = []
y_vars = []
for i in range(104):
    x_coords, y_coords = render(robots, i)
    x_vars.append(np.var(x_coords))
    y_vars.append(np.var(y_coords))

tx = np.argmin(x_vars) # = t mod 101
ty = np.argmin(y_vars) # = t mod 103

# t = tx + K*101 = ty mod 103
# K = (inv(101) * (ty - tx)) mod 103

t = tx + ((pow(101, -1, 103)*(ty-tx))%103)*101

print(t)
