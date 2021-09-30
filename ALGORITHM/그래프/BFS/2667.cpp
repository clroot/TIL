#include "cstdio"
#include "vector"
#include "queue"

using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};


int main() {
    int n, m;
    scanf("%d", &n);

    vector<vector<int>> gnext(n + 1, vector<int>(n + 1));
    vector<pair<int, int>> candidate;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%1d", &gnext[i][j]);

            if (gnext[i][j] == 1) {
                candidate.push_back({j, i});
            }
        }
    }

    vector<int> answer;
    while (!candidate.empty()) {
        int tx = candidate.back().first;
        int ty = candidate.back().second;
        candidate.pop_back();

        if (gnext[ty][tx] == 0)
            continue;

        int houseCounter = 1;

        queue<pair<int, int>> que;
        que.push({tx, ty});

        while (!que.empty()) {
            int cx = que.front().first;
            int cy = que.front().second;
            que.pop();

            gnext[cy][cx] = 0;

            for (int i = 0; i < 4; i++) {
                int nx = cx + dx[i];
                int ny = cy + dy[i];

                if (!(0 <= nx && nx < n) || !(0 <= ny && ny < n))
                    continue;

                if (gnext[ny][nx] == 1) {
                    que.push({nx, ny});
                    gnext[ny][nx] = 0;
                    houseCounter++;
                }
            }
        }

        answer.push_back(houseCounter);
    }

    sort(answer.begin(), answer.end());

    printf("%d\n", answer.size());
    for (auto &i: answer)
        printf("%d\n", i);

    return 0;
}