#include "iostream"
#include "vector"
#include "queue"
#include "cmath"

#define endl '\n'

using namespace std;
using node = pair<int, int>;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  auto compare = [](node &p, node &q) -> bool
  {
    return p.first != q.first ? p.first > q.first : p.second > q.second;
  };
  priority_queue<node, vector<node>, decltype(compare)> que(compare);

  int n;
  cin >> n;

  while (n--)
  {
    int x;
    cin >> x;

    if (x == 0)
    {
      if (que.empty())
      {
        cout << 0 << endl;
      }
      else
      {
        cout << que.top().second << endl;
        que.pop();
      }

      continue;
    }

    que.push({abs(x), x});
  }

  return 0;
}