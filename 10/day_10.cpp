#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <stack>

using namespace std;

vector<string> read_input()
{
  ifstream file("input.txt");
  vector<string> input;
  string line;
  while (getline(file, line))
  {
    input.push_back(line);
  }
  return input;
}

vector<pair<int, int>> directions = {
    {-1, 0}, // up
    {0, 1},  // right
    {1, 0},  // down
    {0, -1}  // left
};

int find_score(vector<string> grid, pair<int, int> position)
{
  set<pair<int, int>> arrivals;
  stack<pair<int, int>> s;
  s.push(position);
  while (!s.empty())
  {
    auto [r, c] = s.top();
    s.pop();
    int val = grid[r][c] - '0';
    if (val == 9)
    {
      arrivals.insert({r, c});
      continue;
    }
    for (auto [dr, dc] : directions)
    {
      int nr = r + dr;
      int nc = c + dc;
      if (nr < 0 || nr >= grid.size() || nc < 0 || nc >= grid[0].size())
        continue;
      if (grid[nr][nc] - '0' == val + 1)
        s.push({nr, nc});
    }
  }
  return arrivals.size();
}

void part_1()
{
  auto grid = read_input();
  int score = 0;
  for (int i = 0; i < grid.size(); i++)
  {
    for (int j = 0; j < grid[i].size(); j++)
    {
      if (grid[i][j] == '0')
        score += find_score(grid, {i, j});
    }
  }

  cout << score << endl;
}

int find_rating(vector<string> grid, pair<int, int> position)
{
  set<vector<pair<int, int>>> paths;
  stack<vector<pair<int, int>>> s;
  s.push({position});
  while (!s.empty())
  {
    auto path = s.top();
    s.pop();
    auto [r, c] = path.back();
    int val = grid[r][c] - '0';
    if (val == 9)
    {
      paths.insert(path);
      continue;
    }
    for (auto [dr, dc] : directions)
    {
      int nr = r + dr;
      int nc = c + dc;
      if (nr < 0 || nr >= grid.size() || nc < 0 || nc >= grid[0].size())
        continue;
      if (grid[nr][nc] - '0' == val + 1)
      {
        path.push_back({nr, nc});
        s.push(path);
      }
    }
  }

  return paths.size();
}

void part_2()
{
  auto grid = read_input();
  int rating = 0;
  for (int i = 0; i < grid.size(); i++)
  {
    for (int j = 0; j < grid[i].size(); j++)
    {
      if (grid[i][j] == '0')
        rating += find_rating(grid, {i, j});
    }
  }

  cout << rating << endl;
}

int main()
{
  part_1();
  part_2();
}
