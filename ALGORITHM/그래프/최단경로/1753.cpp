#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
using node = pair<int, int>;

vector<node> gnext[20001];
int dist[20001];
bool check[20001];

int main()
{
  int v, e, k;
  scanf("%d %d %d", &v, &e, &k);

  memset(dist, 0x7F, sizeof(dist));
  dist[k] = 0;

  for (int i = 0; i < e; i++)
  {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    gnext[a].push_back({b, c});
  }

  priority_queue<node, vector<node>, greater<node>> heap;
  heap.push({0, k});

  while (!heap.empty())
  {
    int idx = heap.top().second;
    heap.pop();

    if (check[idx])
      continue;
    check[idx] = true;

    for (auto i : gnext[idx])
    {
      if (dist[i.first] > dist[idx] + i.second)
      {
        dist[i.first] = dist[idx] + i.second;
        heap.push({dist[i.first], i.first});
      }
    }
  }

  for (int i = 1; i <= v; i++)
  {
    if (!check[i])
      printf("INF \n");
    else
      printf("%d \n", dist[i]);
  }

  return 0;
}