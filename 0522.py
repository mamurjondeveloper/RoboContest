n = int(input())
a = list(map(int, input().split()))
if 0 in a:
    print("Yes")
    quit()
neg = 0
for x in a:
    if x < 0:
        neg += 1
if neg % 2:
    print("No")
    quit()
m = 10 ** 6
s = list(range(m + 1))
i = 2
while i * i <= m:
    if s[i] == i:
        j = i * i
        while j <= m:
            if s[j] == j:
                s[j] = i
            j += i
    i += 1
d = {}
for x in a:
    x = abs(x)
    while x > 1:
        p = s[x]
        c = 0
        while x % p == 0:
            c += 1
            x //= p
        d[p] = (d.get(p, 0) + c) % 2
for v in d.values():
    if v:
        print("No")
        quit()
print("Yes")
