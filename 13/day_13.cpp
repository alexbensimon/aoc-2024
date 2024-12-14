#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

vector<tuple<int, int, int, int, int, int>> read_input()
{
  ifstream file("input.txt");
  vector<vector<string>> input;
  string line;
  vector<string> group;
  while (getline(file, line))
  {
    if (line.empty())
    {
      input.push_back(group);
      group.clear();
    }
    else
    {
      group.push_back(line);
    }
  }

  vector<tuple<int, int, int, int, int, int>> machines;
  for (auto &group : input)
  {
    int ax, ay, bx, by, px, py;
    sscanf(group[0].c_str(), "Button A: X+%d, Y+%d", &ax, &ay);
    sscanf(group[1].c_str(), "Button B: X+%d, Y+%d", &bx, &by);
    sscanf(group[2].c_str(), "Prize: X=%d, Y=%d", &px, &py);
    machines.push_back({ax, ay, bx, by, px, py});
  }

  return machines;
}

void part_1()
{
  auto machines = read_input();
  int tokens = 0;
  for (auto &machine : machines)
  {
    auto [ax, ay, bx, by, px, py] = machine;

    double determinant = ax * by - ay * bx;
    if (determinant == 0)
      continue;
    double x = (px * by - py * bx) / determinant;
    double y = (py * ax - px * ay) / determinant;

    if (x != floor(x) || y != floor(y))
      continue;

    tokens += x * 3 + y;
  }
  cout << tokens << endl;
}

ostream &operator<<(ostream &os, __int128 num)
{
  if (num < 0)
  {
    os << "-";
    num = -num;
  }
  if (num > 9)
    os << (__int128)(num / 10);
  os << (int)(num % 10);
  return os;
}

void part_2()
{
  auto machines = read_input();
  __int128 tokens = 0;
  for (auto &machine : machines)
  {
    auto [ax, ay, bx, by, px, py] = machine;
    __int128 npx = px + 10000000000000LL;
    __int128 npy = py + 10000000000000LL;

    __int128 determinant = ax * by - ay * bx;
    if (determinant == 0)
      continue;

    __int128 num_x = npx * by - npy * bx;
    __int128 num_y = npy * ax - npx * ay;

    __int128 x = num_x / determinant;
    __int128 y = num_y / determinant;

    if (num_x % determinant != 0 || num_y % determinant != 0)
      continue;

    tokens += x * 3 + y;
  }
  cout << tokens << endl;
}

int main()
{
  part_1();
  part_2();
}
