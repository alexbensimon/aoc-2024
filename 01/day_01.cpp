#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

tuple<vector<int>, vector<int>> read_input()
{
  ifstream file("input.txt");
  vector<int> v1, v2;

  string line;
  while (getline(file, line))
  {
    istringstream iss(line);
    int a, b;
    iss >> a >> b;
    v1.push_back(a);
    v2.push_back(b);
  }

  return {v1, v2};
}

void part_1()
{
  auto [v1, v2] = read_input();

  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end());

  int ans = 0;
  for (int i = 0; i < v1.size(); i++)
  {
    ans += abs(v1[i] - v2[i]);
  }

  cout << ans << endl;
}

void part_2()
{
  auto [v1, v2] = read_input();

  unordered_map<int, int> v2_map;
  for (int val : v2)
  {
    if (v2_map.find(val) != v2_map.end())
    {
      v2_map[val]++;
    }
    else
    {
      v2_map[val] = 1;
    }
  }

  int ans = 0;
  for (int val : v1)
  {
    ans += val * v2_map[val];
  }

  cout << ans << endl;
}

int main()
{
  part_1();
  part_2();
}
