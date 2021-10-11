#include "cstdio"
#include "vector"

using namespace std;

int main() {
    int n, k;

    scanf("%d%d", &n, &k);

    vector<int> sequence(n);

    for (int i = 0; i < n; i++) {
        scanf("%1d", &sequence[i]);
    }

    vector<int> stack;
    int eraseCount = 0;

    for (auto &i: sequence) {
        while (!stack.empty() && stack.back() < i && eraseCount < k) {
            stack.pop_back();
            eraseCount += 1;
        }
        if (stack.size() + 1 <= n - k) {
            stack.push_back(i);
        }
    }

    for (auto &i: stack)
        printf("%d", i);

    return 0;
}