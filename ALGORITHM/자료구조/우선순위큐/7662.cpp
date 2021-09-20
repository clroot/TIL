#include <set>
#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
  int Test_case;
  cin >> Test_case;
  while (Test_case--)
  {
    int T;
    cin >> T;
    multiset<int> que;
    for (int i = 0; i < T; i++)
    {
      char command;
      int n;
      getchar();
      scanf("%c %d", &command, &n);
      if (command == 'I')
        que.insert(n);
      else
      {
        if (que.size() != 0 && n == 1)
        {
          auto iter = que.end();
          iter--;
          que.erase(iter);
        }
        else if (que.size() != 0)
          que.erase(que.begin());
      }
    }
    if (que.size() == 0)
    {
      printf("EMPTY\n");
      continue;
    }
    auto iter = que.end();
    iter--;
    printf("%d %d\n", *(iter), *(que.begin()));
  }
}