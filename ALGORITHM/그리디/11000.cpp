#include "iostream"
#include "vector"
#include "queue"
#include "functional"
#include "algorithm"

#define endl "\n"

using namespace std;
using lesson = pair<int, int>;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    priority_queue<lesson, vector<lesson>, greater<>> lessons;

    for (int i = 0; i < n; i++) {
        int s, t;
        cin >> s >> t;
        lessons.push({s, t});
    }

    int answer = 0;
    priority_queue<int, vector<int>, greater<>> classRoom;

    while (!lessons.empty()) {
        auto top = lessons.top();
        lessons.pop();

        if (classRoom.empty()) {
            classRoom.push(top.second);
            continue;
        }

        if (classRoom.top() <= top.first) {
            classRoom.pop();
        }
        classRoom.push(top.second);

        answer = max(answer, (int) classRoom.size());
    }

    cout << answer << endl;

    return 0;
}