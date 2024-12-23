import numpy as np 
import sys

edges = [l.strip().split('-') for l in sys.stdin.readlines()]
verts = []
for (a,b) in edges:
    verts += [a, b]
verts = {key: i for i, key in enumerate(list(set(verts)))}
verts_no_t = {}
ctr = 0
for key in verts:
    if not key[0] == 't':
        verts_no_t[key] = ctr
        ctr += 1

n = len(verts)
m = len(verts_no_t)

mat = np.zeros((n, n))
mat_no_t = np.zeros((m,m))

for (a,b) in edges:
    mat[verts[a]][verts[b]] = 1
    mat[verts[b]][verts[a]] = 1
    if not (a[0] == 't' or b[0] == 't'):
        mat_no_t[verts_no_t[a]][verts_no_t[b]] = 1
        mat_no_t[verts_no_t[b]][verts_no_t[a]] = 1

mat_cube = mat @ mat @ mat
mat_no_t_cube = mat_no_t @ mat_no_t @ mat_no_t

ans = 0
ans_no_t = 0
for vert, idx in verts.items():
    ans += mat_cube[idx][idx]
for vert, idx in verts_no_t.items():
    ans_no_t += mat_no_t_cube[idx][idx]

print((ans-ans_no_t)//6)

