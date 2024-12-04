#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

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

void part_1()
{
  auto grid = read_input();
  int ans = 0;

  vector<pair<int, int>> directions = {
      {0, 1},   // right
      {0, -1},  // left
      {1, 0},   // down
      {-1, 0},  // up
      {1, 1},   // down-right
      {-1, -1}, // up-left
      {1, -1},  // down-left
      {-1, 1}   // up-right
  };

  for (int i = 0; i < grid.size(); i++)
  {
    for (int j = 0; j < grid[i].size(); j++)
    {
      if (grid[i][j] != 'X')
        continue;

      for (const auto &[di, dj] : directions)
      {
        // Check if the word "XMAS" fits in this direction
        if (i + di * 3 >= 0 && i + di * 3 < grid.size() &&
            j + dj * 3 >= 0 && j + dj * 3 < grid[i].size() &&
            grid[i + di][j + dj] == 'M' &&
            grid[i + di * 2][j + dj * 2] == 'A' &&
            grid[i + di * 3][j + dj * 3] == 'S')
        {
          ans++;
        }
      }
    }
  }

  cout << ans << endl;
}

void part_2()
{
  auto grid = read_input();
  int ans = 0;

  // We don't have to check the borders because the center of the X can't be there
  for (int i = 1; i < grid.size() - 1; i++)
  {
    for (int j = 1; j < grid[i].size() - 1; j++)
    {
      if (grid[i][j] != 'A')
        continue;

      bool first_line = (grid[i - 1][j + 1] == 'S' && grid[i + 1][j - 1] == 'M') ||
                        (grid[i - 1][j + 1] == 'M' && grid[i + 1][j - 1] == 'S');

      bool second_line = (grid[i - 1][j - 1] == 'S' && grid[i + 1][j + 1] == 'M') ||
                         (grid[i - 1][j - 1] == 'M' && grid[i + 1][j + 1] == 'S');

      if (first_line && second_line)
        ans++;
    }
  }

  cout << ans << endl;
}

int main()
{
  part_1();
  part_2();
}
