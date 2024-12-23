import sys

def lstep(n, k, m=24):
    return ((n<<k)^n)&((1<<m)-1)

def rstep(n, k, m=24):
    return ((n>>k)^n)&((1<<m)-1)

def gen(n):
    n = lstep(n,6)
    n = rstep(n,5)
    n = lstep(n,11)
    return n

nums = [int(l.strip()) for l in sys.stdin.readlines()]

ans = 0
pricemap = {}
for num in nums:
    price = num % 10
    l = [0, 0, 0, 0]
    enc_seqs = {}
    for i in range(2000):
        new_num = gen(num)
        new_price = new_num % 10
        pdiff = new_price - price
        if i < 4:
            l[i] = pdiff
        else:
            l[:-1] = l[1:]
            l[-1] = pdiff
            pdiffseq = tuple(l)
            if pdiffseq not in enc_seqs:
                enc_seqs[pdiffseq] = new_price
                if pdiffseq not in pricemap:
                    pricemap[pdiffseq] = 0
                pricemap[pdiffseq] += new_price

        num = new_num
        price = new_price

    ans += num

print(ans)
ans_pt2 = -1000
key_pt2 = None
for key, value in pricemap.items():
    if value > ans_pt2:
        ans_pt2 = value
        key_pt2 = key

print(key_pt2, ans_pt2)
