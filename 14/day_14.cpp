#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

vector<tuple<int, int, int, int>> read_input()
{
  ifstream file("input.txt");
  vector<tuple<int, int, int, int>> input;
  string line;
  while (getline(file, line))
  {
    int px, py, vx, vy;
    sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
    input.push_back(make_tuple(px, py, vx, vy));
  }
  return input;
}

int max_x = 101;
int max_y = 103;

int mod(int x, int m)
{
  return (x % m + m) % m;
}

int compute_safety_score(vector<tuple<int, int, int, int>> robots)
{
  int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
  for (auto &[px, py, vx, vy] : robots)
  {
    if (px == max_x / 2 || py == max_y / 2)
      continue;
    if (px < max_x / 2 && py < max_y / 2)
      q1++;
    else if (px < max_x / 2 && py > max_y / 2)
      q2++;
    else if (px > max_x / 2 && py < max_y / 2)
      q3++;
    else if (px > max_x / 2 && py > max_y / 2)
      q4++;
  }

  return q1 * q2 * q3 * q4;
}

void part_1()
{
  auto robots = read_input();
  for (int k = 0; k < 100; k++)
  {
    for (int i = 0; i < robots.size(); i++)
    {
      auto [px, py, vx, vy] = robots[i];
      px = mod(px + vx, max_x);
      py = mod(py + vy, max_y);
      robots[i] = make_tuple(px, py, vx, vy);
    }
  }

  cout << compute_safety_score(robots) << endl;
}

void print_grid(vector<tuple<int, int, int, int>> robots)
{
  vector<vector<int>> grid(max_x, vector<int>(max_y, 0));
  for (auto &[px, py, vx, vy] : robots)
  {
    grid[px][py]++;
  }
  for (int y = 0; y < max_y; y++)
  {
    for (int x = 0; x < max_x; x++)
    {
      if (grid[x][y] == 0)
        cout << ' ';
      else
        cout << 'X';
    }
    cout << endl;
  }
  cout << "----------------------------------------------------------------" << endl;
}

void part_2()
{
  auto robots = read_input();
  int best_score = INT_MAX;
  for (int k = 0; k < 100000; k++)
  {
    for (int i = 0; i < robots.size(); i++)
    {
      auto [px, py, vx, vy] = robots[i];
      px = mod(px + vx, max_x);
      py = mod(py + vy, max_y);
      robots[i] = make_tuple(px, py, vx, vy);
    }
    int score = compute_safety_score(robots);
    if (score < best_score)
    {
      best_score = score;
      cout << k << endl;
      print_grid(robots);
    }
  }
}

int main()
{
  part_1();
  part_2();
}
