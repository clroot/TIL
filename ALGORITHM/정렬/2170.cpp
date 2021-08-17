#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
using line = pair<int, int>;

int main()
{
  int n;
  scanf("%d", &n);
  vector<line> vec(n);

  for (int i = 0; i < n; ++i)
    scanf("%d%d", &vec[i].first, &vec[i].second);

  sort(vec.begin(), vec.end());

  int end = vec[0].second;
  long long ans = vec[0].second - vec[0].first;

  for (int i = 1; i < vec.size(); ++i)
  {
    if (vec[i].first < end && end < vec[i].second)
    {
      ans += vec[i].second - end;
      end = vec[i].second;
    }
    else if (vec[i].first > end)
    {
      end = vec[i].second;
      ans += vec[i].second - vec[i].first;
    }
  }

  printf("%lld\n", ans);
  return 0;
}