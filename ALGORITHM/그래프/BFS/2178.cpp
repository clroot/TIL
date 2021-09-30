#include "cstdio"
#include "vector"
#include "queue"

using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};


int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    vector<vector<int>> gnext(n + 1, vector<int>(m + 1));
    vector<vector<int>> visited(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%1d", &gnext[i][j]);
        }
    }

    queue<pair<int, int>> que;
    que.push({0, 0});
    visited[0][0] = 1;

    while (!que.empty()) {
        int cx = que.front().first;
        int cy = que.front().second;
        que.pop();

        if (cx == m - 1 && cy == n - 1) break;

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (!(0 <= nx && nx < m) || !(0 <= ny && ny < n))
                continue;

            if (gnext[ny][nx] == 1 && visited[ny][nx] == 0) {
                visited[ny][nx] = visited[cy][cx] + 1;
                que.push({nx, ny});
            }
        }
    }

    printf("%d\n", visited[n - 1][m - 1]);
    return 0;
}