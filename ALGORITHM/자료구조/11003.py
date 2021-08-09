import heapq

(n, l) = map(int, input().split())
a = list(map(int, input().split()))

heap = []
result = []

for i in range(0, n):
    heapq.heappush(heap, (a[i], i))

    while True:
        top = heap[0]
        (value, idx) = top
        if i - l + 1 <= idx <= i:
            result.append(value)
            break
        heapq.heappop(heap)

print(" ".join(map(str, result)))
