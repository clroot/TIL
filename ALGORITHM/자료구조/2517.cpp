#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct index_tree
{
  vector<int> Tree;
  int k = 1;

  index_tree(int n)
  {
    while (k < n)
      k *= 2;
    Tree.resize(k * 3, 0);
  }

  void update(int idx, int value)
  {
    idx += k;
    Tree[idx] = value;

    int node = idx / 2;

    while (node)
    {
      Tree[node] = Tree[node * 2] + Tree[node * 2 + 1];
      node /= 2;
    }
  }

  int range(int left, int right)
  {
    left += k;
    right += k;

    int ret = 0;

    while (left <= right)
    {
      if (left & 1)
        ret += Tree[left];
      if (!(right & 1))
        ret += Tree[right];
      left = (left + 1) / 2;
      right = (right - 1) / 2;
    }

    return ret;
  }
};

int main()
{
  int n;
  vector<int> vec;
  vector<int> arr;

  scanf("%d", &n);

  for (int i = 0; i < n; i++)
  {
    int input;
    scanf("%d", &input);
    arr.push_back(input);
    vec.push_back(input);
  }

  sort(vec.begin(), vec.end());
  vec.erase(unique(vec.begin(), vec.end()), vec.end());
  index_tree tr(n);

  for (auto &i : arr)
  {
    int idx = lower_bound(vec.begin(), vec.end(), i) - vec.begin();
    tr.update(idx, 1);
    printf("%d\n", tr.range(idx + 1, vec.size()) + 1);
  }
}