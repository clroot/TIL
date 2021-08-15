(n, l) = list(map(int, input().split()))
p = list(map(int, input().split()))

p.sort()

ans = 1
now = p[0]

for i in range(1, n):
    if now + l - 1 < p[i]:
        now = p[i]
        ans += 1

print(ans)
