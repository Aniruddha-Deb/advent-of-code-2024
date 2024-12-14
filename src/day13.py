import re, sys

re_btn = re.compile(r"Button [AB]: X\+(\d+), Y\+(\d+)")
re_prize = re.compile(r"Prize: X=(\d+), Y=(\d+)")

input = [l.strip() for l in sys.stdin.readlines()]
ans = 0
ans_pt2 = 0

i = 0
add = 10000000000000
while i < len(input):
    subarr = input[i:i+4]
    i += 4
    m1 = re_btn.match(subarr[0])
    m2 = re_btn.match(subarr[1])
    m3 = re_prize.match(subarr[2])
    assert m1 and m2 and m3
    x1 = int(m1.group(1))
    y1 = int(m1.group(2))
    x2 = int(m2.group(1))
    y2 = int(m2.group(2))
    x = int(m3.group(1))
    y = int(m3.group(2))
    x_pt2 = x + add
    y_pt2 = y + add


    d = x1*y2 - x2*y1
    a = (x*y2 - x2*y)//d
    b = -(x*y1 - x1*y)//d

    a_pt2 = (x_pt2*y2 - x2*y_pt2)//d
    b_pt2 = -(x_pt2*y1 - x1*y_pt2)//d

    if (a*x1 + b*x2 == x and a*y1 + b*y2 == y):
        ans += 3*a + b
    if (a_pt2*x1 + b_pt2*x2 == x_pt2 and a_pt2*y1 + b_pt2*y2 == y_pt2):
        ans_pt2 += 3*a_pt2 + b_pt2


print(ans)
print(ans_pt2)
