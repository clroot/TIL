#include <cstdio>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

int main()
{
  int n, k;
  scanf("%d%d", &n, &k);

  int work[101] = {0};
  for (int i = 0; i < k; i++)
    scanf("%d", &work[i]);

  set<int> working;
  int r = 0;

  for (int i = 0; i < k; i++)
  {
    if (working.find(work[i]) != working.end())
      continue;

    if (working.size() + 1 <= n)
      working.insert(work[i]);
    else
    {
      r++;
      priority_queue<pair<int, int> > que;
      for (int j : working)
      {
        int how_far = 0;

        for (int f = i + 1; f < k; f++, how_far++)
          if (work[f] == j)
            break;

        que.push({how_far, j});
      }

      int idx = que.top().second;

      working.erase(idx);
      working.insert(work[i]);

      while (!que.empty())
        que.pop();
    }
  }

  printf("%d\n", r);
  return 0;
}
