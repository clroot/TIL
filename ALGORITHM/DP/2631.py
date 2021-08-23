# LIS
import bisect

n = int(input())
children = [int(input()) for _ in range(0, n)]

LIS = [children[0]]

for i in children[1:]:
    if i > LIS[-1]:
        LIS.append(i)
    else:
        idx = bisect.bisect_left(LIS, i)
        LIS[idx] = i

print(n - len(LIS))
