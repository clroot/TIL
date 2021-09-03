#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

int dist[10001];
bool check[10001];
using data1 = pair<int, int>;

int main()
{
  int v, e;
  long long r = 0;
  vector<data1> arr[10001];
  data1 input;
  cin >> v >> e;
  memset(dist, 0x7F, sizeof(dist));
  for (int i = 0; i < e; i++)
  {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    arr[a].push_back({b, c});
    arr[b].push_back({a, c});
  }
  priority_queue<data1, vector<data1>, greater<data1>> heap;
  dist[1] = 0;
  heap.push({0, 1});
  while (!heap.empty())
  {
    int idx = heap.top().second;
    heap.pop();
    if (check[idx])
      continue;
    check[idx] = true;
    for (auto i : arr[idx])
    {
      if (!check[i.first] && dist[i.first] > i.second)
      {
        dist[i.first] = i.second;
        heap.push({dist[i.first], i.first});
      }
    }
  }
  for (int i = 1; i <= v; i++)
    r += dist[i];
  printf("%lld \n", r);

  return 0;
}