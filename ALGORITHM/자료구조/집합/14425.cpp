#include "iostream"
#include "string"
#include "unordered_set"

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    unordered_set<string> set;
    int answer = 0;

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        set.insert(s);
    }

    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        auto iter = set.find(s);

        if (iter != set.end()) {
            answer += 1;
        }
    }

    cout << answer << endl;

    return 0;
}