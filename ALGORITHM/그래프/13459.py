import heapq
import sys
from collections import deque

input = sys.stdin.readline


def go(m, y, x, dy, dx, isBlue: bool = False):
    global y_limit
    global x_limit

    flag = False
    while 0 < y + dy < y_limit \
            and 0 < x + dx < x_limit \
            and m[y + dy][x + dx] != '#' \
            and m[y][x] != 'O':
        y += dy
        x += dx
        if m[y][x] == ('R' if isBlue else 'B'):
            flag = True
    return y, x, flag


que = []
history = []

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]

[y_limit, x_limit] = map(int, input().split(" "))
m = [list(input().strip()) for _ in range(y_limit)]

rx, ry = 0, 0
bx, by = 0, 0

for i, s in enumerate(m):
    if 'R' in s:
        rx = s.index('R')
        ry = i
    if 'B' in s:
        bx = s.index('B')
        by = i

history.append(((ry, rx), (by, bx)))
heapq.heappush(que, (1, (ry, rx), (by, bx)))

while bool(que):
    (t, (ry, rx), (by, bx)) = heapq.heappop(que)
    m[ry][rx] = 'R'
    m[by][bx] = 'B'

    for i in range(4):
        (try_ry, try_rx, fr) = go(m, ry, rx, dy[i], dx[i])
        (try_by, try_bx, fb) = go(m, by, bx, dy[i], dx[i], isBlue=True)

        if t > 10:
            continue
        if m[try_by][try_bx] == 'O':
            continue

        if m[try_ry][try_rx] == 'O':
            print(1)
            quit(0)

        if fr:
            try_ry, try_rx = try_by - dy[i], try_bx - dx[i]
        elif fb:
            try_by, try_bx = try_ry - dy[i], try_rx - dx[i]

        if ((try_ry, try_rx), (try_by, try_bx)) not in history:
            heapq.heappush(que, (t + 1, (try_ry, try_rx), (try_by, try_bx)))
            history.append(((try_ry, try_rx), (try_by, try_bx)))

    m[ry][rx] = '.'
    m[by][bx] = '.'

print(0)
