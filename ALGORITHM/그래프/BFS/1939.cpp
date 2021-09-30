#include "iostream"
#include "vector"
#include "queue"
#include "climits"

using namespace std;

using node = pair<int, int>;

int start, finish;
vector<vector<node>> gnext;
vector<bool> visited;

bool BFS(int cost) {
    queue<int> que;
    que.push(start);

    while (!que.empty()) {
        int curIdx = que.front();
        que.pop();

        if (finish == curIdx) return true;

        for (auto &i: gnext[curIdx]) {
            int next = i.first;
            int nextCost = i.second;

            if (!visited[next] && cost <= nextCost) {
                que.push(next);
                visited[next] = true;
            }
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    gnext.resize(n + 1);
    visited.resize(n + 1, false);

    int maxCost = INT_MIN;

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        gnext[a].push_back({b, c});
        gnext[b].push_back({a, c});

        maxCost = max(maxCost, c);
    }

    cin >> start >> finish;

    int low = 0;
    int high = maxCost;

    while (low <= high) {
        visited.clear();
        visited.resize(n + 1, false);

        int mid = (low + high) / 2;

        if (BFS(mid)) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << high << endl;
    return 0;
}