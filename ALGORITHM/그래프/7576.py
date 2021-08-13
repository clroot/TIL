from collections import deque
import sys
input = sys.stdin.readline

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]

[M, N] = map(int, input().split())

tomato = [list(map(int, input().split())) for _ in range(N)]

que = deque()

for i, t in enumerate(tomato):
    for j, k in enumerate(t):
        if k == 1:
            que.append((i, j))

r = 1
while bool(que):
    (y, x) = que.popleft()

    for i in range(4):
        try_y = y + dy[i]
        try_x = x + dx[i]

        if not (0 <= try_x < M) \
                or not (0 <= try_y < N):
            continue

        if tomato[try_y][try_x] == -1 or tomato[try_y][try_x] >= 1:
            continue

        tomato[try_y][try_x] = tomato[y][x] + 1
        r = max(r, tomato[try_y][try_x])
        que.append((try_y, try_x))

for t in tomato:
    if 0 in t:
        print(-1)
        quit(0)

print(r - 1)
