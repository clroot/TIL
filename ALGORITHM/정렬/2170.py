import sys
input = sys.stdin.readline

n = int(input())
l = [tuple(map(int, input().split())) for _ in range(0, n)]
l.sort()

(p, q) = l[0]

end = q
answer = q - p

for (p, q) in l[1:]:
    if p < end < q:
        answer += q - end
        end = q
    elif end < p:
        end = q
        answer += q - p

print(answer)
