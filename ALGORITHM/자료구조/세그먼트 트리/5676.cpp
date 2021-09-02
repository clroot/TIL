#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int compress(int);

struct index_tree
{
  vector<long long> Tree;
  int k = 1;

  index_tree(int n)
  {
    while (k < n)
      k *= 2;
    Tree.resize(3 * k, 1);
  }

  void update(int idx, int value)
  {
    idx += k;
    Tree[idx] = value;
    int node = idx / 2;
    while (node)
    {
      Tree[node] = Tree[node * 2] * Tree[node * 2 + 1];
      node /= 2;
    }
  }

  int range(int left, int right)
  {
    long long ret = 1;
    left += k;
    right += k;
    while (left <= right)
    {
      if (left & 1)
        ret *= Tree[left];
      if (!(right & 1))
        ret *= Tree[right];
      left = (left + 1) / 2;
      right = (right - 1) / 2;
    }
    return compress(ret);
  }
};

int compress(int n)
{
  if (n > 0)
    return 1;
  else if (n < 0)
    return -1;
  else
    return 0;
}

int main()
{
  int n, m;
  while (cin >> n >> m)
  {
    index_tree tr(n);
    for (int i = 0; i < n; i++)
    {
      int t;
      scanf("%d", &t);
      tr.update(i, compress(t));
    }
    for (int i = 0; i < m; i++)
    {
      char command;
      int a, b;
      //cin >> command >> a >> b;
      getchar();
      scanf("%c %d %d", &command, &a, &b);
      if (command == 'C')
        tr.update(a - 1, compress(b));
      else if (command == 'P')
      {
        int res = tr.range(a - 1, b - 1);
        if (res > 0)
          printf("+");
        else if (res < 0)
          printf("-");
        else
          printf("0");
      }
    }
    printf("\n");
  }
  return 0;
}
