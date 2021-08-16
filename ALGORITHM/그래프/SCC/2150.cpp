#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

struct SCC
{
  vector<vector<int> > gnext, gnext_rev, ans;
  vector<bool> check;
  stack<int> vertex_stack;
  vector<vector<int> > scc_group;
  int number_of_vertex = 0;

  SCC(int n)
  {
    check.resize(n + 2, false);
    gnext.resize(n + 2);
    gnext_rev.resize(n + 2);
    number_of_vertex = n;
  }

  void add_edge(const int from, const int to)
  {
    gnext[from].push_back(to);
    gnext_rev[to].push_back(from);
  }

  void DFS(int vertex)
  {
    check[vertex] = true;
    for (auto &i : gnext[vertex])
      if (!check[i])
        DFS(i);
    vertex_stack.push(vertex);
  }

  void count_vertex()
  {
    for (int i = 1; i <= number_of_vertex; i++)
      if (!check[i])
        DFS(i);
  }

  void find_scc()
  {
    check.clear();
    check.resize(number_of_vertex + 2, false);
    while (!vertex_stack.empty())
    {
      int idx = vertex_stack.top();
      vertex_stack.pop();

      if (check[idx])
        continue;

      check[idx] = true;

      stack<int> vertex_to_visit;
      for (auto &i : gnext_rev[idx])
        vertex_to_visit.push(i);

      vector<int> tmp;
      tmp.push_back(idx);

      while (!vertex_to_visit.empty())
      {
        int idx2 = vertex_to_visit.top();

        vertex_to_visit.pop();
        if (check[idx2])
          continue;

        tmp.push_back(idx2);
        check[idx2] = true;

        for (auto &i : gnext_rev[idx2])
          vertex_to_visit.push(i);
      }

      sort(tmp.begin(), tmp.end());

      tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
      ans.resize(ans.size() + 1);

      for (auto &i : tmp)
        ans[ans.size() - 1].push_back(i);
    }
    sort(ans.begin(), ans.end());
  }
};

int main()
{
  int v, e;
  cin >> v >> e;
  SCC scc(v);

  for (int i = 0; i < e; i++)
  {
    int a, b;
    scanf("%d%d", &a, &b);
    scc.add_edge(a, b);
  }

  scc.count_vertex();
  scc.find_scc();
  cout << scc.ans.size() << endl;

  for (auto &i : scc.ans)
  {
    for (auto &j : i)
      cout << j << " ";
    cout << -1;
    cout << endl;
  }
}