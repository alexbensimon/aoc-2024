#include <fstream>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<vector<char>> read_input()
{
  ifstream file("input.txt");
  vector<vector<char>> grid;

  string line;
  while (getline(file, line))
  {
    grid.push_back(vector<char>(line.begin(), line.end()));
  }

  return grid;
}

pair<int, int> find_initial_position(const vector<vector<char>> &grid)
{
  for (int i = 0; i < grid.size(); i++)
  {
    for (int j = 0; j < grid[i].size(); j++)
    {
      if (grid[i][j] == '^')
        return {i, j};
    }
  }

  return {-1, -1};
}

void part_1()
{
  auto grid = read_input();
  auto position = find_initial_position(grid);
  set<pair<int, int>> visited;
  vector<pair<int, int>> directions = {
      {-1, 0}, // up
      {0, 1},  // right
      {1, 0},  // down
      {0, -1}  // left
  };
  int d = 0;

  while (true)
  {
    visited.insert(position);

    pair<int, int> next_position = {position.first + directions[d].first, position.second + directions[d].second};

    // if out of grid, break
    if (next_position.first < 0 || next_position.first >= grid.size() || next_position.second < 0 || next_position.second >= grid[0].size())
      break;
    // if # change direction
    if (grid[next_position.first][next_position.second] == '#')
    {
      d = (d + 1) % 4;
    }
    // else change position
    else
      position = next_position;
  }

  cout << visited.size() << endl;
}

void part_2()
{
  auto grid = read_input();
  auto initial_position = find_initial_position(grid);
  set<pair<int, int>> obstructions;
  vector<pair<int, int>> directions = {
      {-1, 0}, // up
      {0, 1},  // right
      {1, 0},  // down
      {0, -1}  // left
  };

  for (int i = 0; i < grid.size(); i++)
  {
    for (int j = 0; j < grid[i].size(); j++)
    {
      if (grid[i][j] != '.')
        continue;
      grid[i][j] = '#';
      auto position = initial_position;
      int d = 0;
      int loops = 0;
      bool out = false;

      // A bit of a hack, but it works
      while (loops < 10000)
      {
        pair<int, int> next_position = {position.first + directions[d].first, position.second + directions[d].second};

        if (next_position.first < 0 || next_position.first >= grid.size() ||
            next_position.second < 0 || next_position.second >= grid[0].size())
        {
          out = true;
          break;
        }

        if (grid[next_position.first][next_position.second] == '#')
        {
          d = (d + 1) % 4;
        }
        else
        {
          position = next_position;
        }

        loops++;
      }

      // Reset grid for next iteration
      grid[i][j] = '.';

      // If it didn't get out after 10000 loops, it's an obstruction
      if (!out)
        obstructions.insert({i, j});
    }
  }

  cout << obstructions.size() << endl;
}

int main()
{
  part_1();
  part_2();
}
