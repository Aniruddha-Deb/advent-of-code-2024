from functools import lru_cache

@lru_cache(maxsize=None)
def f(n):
    if n == 0:
        return [1]
    elif len(str(n)) % 2 == 0:
        strn = str(n)
        ln = len(strn)
        return [int(strn[:ln//2]), int(strn[ln//2:])]
    else:
        return [n*2024]

def g(n, k):
    l = { n: 1}
    for _ in range(k):
        new_l = {}
        for n, freq in l.items():
            ret = f(n)
            for num in ret:
                new_l[num] = new_l.get(num,0)+freq
        l = new_l
    return sum(l.values())

l = [int(x) for x in input().split(" ")]
ans_1 = 0
ans_2 = 0
for num in l:
    ans_1 += g(num, 25)
    ans_2 += g(num, 75)
print(ans_1)
print(ans_2)
