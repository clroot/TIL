#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
using segment = pair<long long, long long>; //first : value, second : lazy

struct segment_tree
{
  int k = 1;
  vector<segment> tree;

  long long init(vector<long long> &a, int node, int start, int end)
  {
    if (start == end)
      return tree[node].first = a[start];
    else
      return tree[node].first = init(a, node * 2, start, (start + end) / 2) +
                                init(a, node * 2 + 1, (start + end) / 2 + 1, end);
  }

  segment_tree(int n, vector<long long> &a)
  {
    while (k <= n)
      k *= 2;
    tree.resize(k * 3, {0, 0});
    init(a, 1, 1, n);
  }

  void update_lazy(int node, int start, int end)
  {
    if (tree[node].second)
    {
      tree[node].first += (end - start + 1) * tree[node].second;
      if (start != end)
      {
        tree[node * 2].second += tree[node].second;
        tree[node * 2 + 1].second += tree[node].second;
      }
      tree[node].second = 0;
    }
  }

  void update_range(int node, int start, int end, int left, int right, long long diff)
  {
    update_lazy(node, start, end);
    if (left > end || right < start)
      return;
    if (left <= start && right >= end)
    {
      tree[node].first += (end - start + 1) * diff;
      if (start != end)
      {
        tree[node * 2].second += diff;
        tree[node * 2 + 1].second += diff;
      }
      return;
    }
    update_range(node * 2, start, (start + end) / 2, left, right, diff);
    update_range(node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
    tree[node].first = tree[node * 2].first + tree[node * 2 + 1].first;
  }

  long long sum(int node, int start, int end, int left, int right)
  {
    update_lazy(node, start, end);
    if (left > end || right < start)
      return 0;
    if (left <= start && right >= end)
      return tree[node].first;
    return (sum(node * 2, start, (start + end) / 2, left, right) +
            sum(node * 2 + 1, (start + end) / 2 + 1, end, left, right));
  }
};

int main()
{
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  vector<long long> arr;
  arr.resize(n + 2, 0);
  for (int i = 1; i <= n; i++)
    scanf("%d", &arr[i]);
  segment_tree tree(n, arr);
  for (int i = 0; i < m + k; i++)
  {
    long long a, b, c, d;
    scanf("%lld", &a);
    if (a == 1)
    {
      scanf("%lld%lld%lld", &b, &c, &d);
      tree.update_range(1, 1, n, b, c, d);
    }
    if (a == 2)
    {
      scanf("%lld%lld", &b, &c);
      printf("%lld\n", tree.sum(1, 1, n, b, c));
    }
  }
  return 0;
}
