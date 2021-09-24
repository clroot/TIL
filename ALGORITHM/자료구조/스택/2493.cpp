#include "iostream"
#include "vector"

using namespace std;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  vector<pair<int, int>> tower;

  for (int i = 0; i < n; ++i)
  {
    int h;
    cin >> h;

    while (!tower.empty() && tower.back().second < h)
    {
      tower.pop_back();
    }

    cout << (tower.empty() ? 0 : tower.back().first) << " ";
    tower.push_back({i + 1, h});
  }

  return 0;
}