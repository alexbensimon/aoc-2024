#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

// Key is a vector of the number of slots to occupy in each column
vector<int> grid_to_key(vector<string> grid)
{
  vector<int> key(grid[0].size(), 0);
  for (int i = grid.size() - 1; i >= 0; i--)
  {
    for (int j = 0; j < grid[i].size(); j++)
    {
      if (grid[i][j] == '#')
        key[j] += 1;
    }
  }
  return key;
}

// Lock is a vector of the number of slots available in each column
vector<int> grid_to_lock(vector<string> grid)
{
  vector<int> lock(grid[0].size(), 0);
  for (int i = 0; i < grid.size(); i++)
  {
    for (int j = 0; j < grid[i].size(); j++)
    {
      if (grid[i][j] == '#')
        lock[j] += 1;
    }
  }
  for (int i = 0; i < lock.size(); i++)
  {
    lock[i] = grid.size() - lock[i];
  }
  return lock;
}

void process_grid(const vector<string> &grid, vector<vector<int>> &locks, vector<vector<int>> &keys)
{
  if (grid.empty())
    return;

  if (grid[0][0] == '#')
    locks.push_back(grid_to_lock(grid));
  else
    keys.push_back(grid_to_key(grid));
}

tuple<vector<vector<int>>, vector<vector<int>>> read_input()
{
  vector<vector<int>> locks;
  vector<vector<int>> keys;
  vector<string> grid;

  ifstream file("input.txt");
  string line;
  while (getline(file, line))
  {
    if (line.empty())
    {
      process_grid(grid, locks, keys);
      grid.clear();
    }
    else
    {
      grid.push_back(line);
    }
  }

  process_grid(grid, locks, keys);
  return {locks, keys};
}

void part_1()
{
  auto [locks, keys] = read_input();
  int ans = 0;
  for (auto key : keys)
  {
    for (auto lock : locks)
    {
      bool can_fit = true;
      for (int i = 0; i < key.size(); i++)
      {
        if (key[i] > lock[i])
        {
          can_fit = false;
          break;
        }
      }
      if (can_fit)
        ans += 1;
    }
  }
  cout << ans << endl;
}

int main()
{
  part_1();
}
