from functools import reduce

n, k = map(int, input().split())
multiply = (lambda p, q: p * q)

answer = reduce(multiply, range(1, n + 1), 1) / (
    reduce(multiply, range(1, (n - k) + 1), 1) *
    reduce(multiply, range(1, k + 1), 1)
)

print(int(answer))
