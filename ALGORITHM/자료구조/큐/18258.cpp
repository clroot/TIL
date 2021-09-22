#include "iostream"
#include "string"
#include "queue"

using namespace std;

#define endl '\n'

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  queue<int> que;
  string command;

  while (n--)
  {
    cin >> command;

    if (command == "push")
    {
      int x;
      cin >> x;
      que.push(x);
    }
    else if (command == "pop")
    {
      if (!que.empty())
      {
        cout << que.front() << endl;
        que.pop();
      }
      else
      {
        cout << -1 << endl;
      }
    }
    else if (command == "size")
    {
      cout << que.size() << endl;
    }
    else if (command == "empty")
    {
      cout << (que.empty() ? 1 : 0) << endl;
    }
    else if (command == "front")
    {
      cout << (!que.empty() ? que.front() : -1) << endl;
    }
    else if (command == "back")
    {
      cout << (!que.empty() ? que.back() : -1) << endl;
    }
  }

  return 0;
}