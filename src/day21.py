from functools import lru_cache
import sys

dpad = (" ^A"
        "<v>")

numpad = ("789"
          "456"
          "123"
          " 0A")

dpad_key_pos = {}
numpad_key_pos = {}
move_len = {}

for i, ch in enumerate(dpad):
    dpad_key_pos[ch] = (i//3, i%3)

for i, ch in enumerate(numpad):
    numpad_key_pos[ch] = (i//3, i%3)

def numpad2dpad(seq):
    # start from A
    seq = 'A' + seq
    dpadseq = []
    for (st,ed) in zip(seq[:-1], seq[1:]):
        (sty, stx) = numpad_key_pos[st]
        (edy, edx) = numpad_key_pos[ed]
        dx = edx - stx
        dy = edy - sty
        if (edx == 0 and sty == 3):
            # up then left
            dpadseq += ['^']*abs(dy) + ['<']*abs(dx)
        elif (stx == 0 and edy == 3):
            # right then down
            dpadseq += ['>']*abs(dx) + ['v']*abs(dy)
        else:
            if dx < 0:
                dpadseq += ['<']*abs(dx)
            if dy > 0:
                dpadseq += ['v']*abs(dy)
            if dy < 0:
                dpadseq += ['^']*abs(dy)
            if dx > 0:
                dpadseq += ['>']*abs(dx)
        dpadseq += ['A']

    return ''.join(dpadseq)

@lru_cache
def dpad2dpad(st, ed):
    dpadseq = []
    (sty, stx) = dpad_key_pos[st]
    (edy, edx) = dpad_key_pos[ed]
    dx = edx - stx
    dy = edy - sty

    if (edx == 0 and sty == 0):
        # down then left
        dpadseq += ['v']*abs(dy) + ['<']*abs(dx)
    elif (stx == 0 and edy == 0):
        # right then up
        dpadseq += ['>']*abs(dx) + ['^']*abs(dy)
    else:
        if dx < 0:
            dpadseq += ['<']*abs(dx)
        if dy > 0:
            dpadseq += ['v']*abs(dy)
        if dy < 0:
            dpadseq += ['^']*abs(dy)
        if dx > 0:
            dpadseq += ['>']*abs(dx)

    dpadseq += ['A']
    return ''.join(dpadseq)

@lru_cache
def dpad2len(st, ed, depth):
    if depth == 1:
        return len(dpad2dpad(st, ed))
    ans = 0
    seq = 'A' + dpad2dpad(st, ed)
    for (st,ed) in zip(seq[:-1], seq[1:]):
        ans += dpad2len(st, ed, depth-1)

    return ans

def numpad2len(seq, depth):
    seq = 'A' + numpad2dpad(seq)
    ans = 0
    for (st,ed) in zip(seq[:-1], seq[1:]):
        ans += dpad2len(st, ed, depth)
    return ans

codes = [l.strip() for l in sys.stdin.readlines()]

for depth in [2, 25]:
    ans = 0
    for code in codes:
        length = numpad2len(code, depth) 
        complexity = length*int(code[:-1])
        ans += complexity

    print(ans)
