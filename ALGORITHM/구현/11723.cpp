#include "iostream"
#include "string"
#include "cmath"

#define endl "\n"

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    unsigned int all = 0;
    for (int i = 1; i <= 20; i++) {
        all |= (int) pow(2, i);
    }

    int m;
    cin >> m;

    unsigned int s = 0;

    while (m--) {
        string command;
        cin >> command;

        int x;

        if (command == "add") {
            cin >> x;
            s |= (int) pow(2, x);
        } else if (command == "remove") {
            cin >> x;
            s &= all - (int) pow(2, x);
        } else if (command == "check") {
            cin >> x;
            int check = s & (int) pow(2, x);
            cout << (check ? 1 : 0) << endl;
        } else if (command == "toggle") {
            cin >> x;
            s ^= (int) pow(2, x);
        } else if (command == "all") {
            s = all;
        } else {
            s = 0;
        }
    }

    return 0;
}