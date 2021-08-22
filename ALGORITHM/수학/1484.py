import bisect
import math


G = int(input())
v = [i * i for i in range(1, 100000 + 1)]

answer = []

for i in v:
    target = i + G
    idx = bisect.bisect_left(v, target)
    if idx < len(v) and v[idx] == target:
        answer.append(int(math.sqrt(target)))

if len(answer) == 0:
    print(-1)
else:
    for i in answer:
        print(i)
