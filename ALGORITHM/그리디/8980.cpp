#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
using delivery = pair<int, int>;

struct package
{
  delivery info;
  int cnt;
};

vector<package> arr;

int main()
{
  int n, c;
  scanf("%d%d", &n, &c);

  int m;
  scanf("%d", &m);

  for (int i = 0; i < m; i++)
  {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);

    package tmp;
    tmp.info = {x, y};
    tmp.cnt = z;

    arr.push_back(tmp);
  }

  sort(arr.begin(), arr.end(), [](const package &aa, const package &bb)
       { return aa.info.second == bb.info.second ? aa.info.first > bb.info.first : aa.info.second < bb.info.second; });

  int check[2001] = {0};
  int ans = 0;

  for (auto &i : arr)
  {
    for (int j = i.info.first; j < i.info.second; j++)
    {
      if (check[j] + i.cnt > c)
        i.cnt = (c - check[j]);

      check[j] += i.cnt;
    }
    ans += i.cnt;
  }

  printf("%d\n", ans);

  return 0;
}