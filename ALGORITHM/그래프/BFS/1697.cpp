#include "iostream"
#include "vector"
#include "queue"

using namespace std;

int main() {
    const int MAX = 100000;
    int n, k;
    cin >> n >> k;

    queue<pair<int, int>> que;
    vector<bool> visited(MAX, false);

    que.push({0, n});

    while (!que.empty()) {
        int depth = que.front().first;
        int cur = que.front().second;

        que.pop();

        if (cur == k) {
            cout << depth << endl;
            return 0;
        }

        if (0 <= cur - 1 && !visited[cur - 1]) {
            que.push({depth + 1, cur - 1});
            visited[cur - 1] = true;
        }
        if (cur + 1 <= MAX && !visited[cur + 1]) {
            que.push({depth + 1, cur + 1});
            visited[cur + 1] = true;
        }
        if (cur * 2 <= MAX && !visited[cur * 2]) {
            que.push({depth + 1, cur * 2});
            visited[cur * 2] = true;
        }
    }
}