#include <iostream>
#include <list>
#include <string>

using namespace std;

int main()
{
  list<char> data;
  string input;
  cin >> input;

  for (auto &i : input)
    data.push_back(i);

  int N;
  cin >> N;

  auto cursor = data.end();

  while (N--)
  {
    char order;
    cin >> order;

    if (order == 'L' && cursor != data.begin())
    {
      cursor--;
    }
    else if (order == 'D' && cursor != data.end())
    {
      cursor++;
    }
    else if (order == 'B' && cursor != data.begin())
    {
      cursor = data.erase(--cursor);
    }
    else if (order == 'P')
    {
      char c;
      cin >> c;
      data.insert(cursor, c);
    }
  }

  for (auto &i : data)
    cout << i;

  cout << endl;
}