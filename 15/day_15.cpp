#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <map>

using namespace std;

tuple<vector<string>, vector<char>> read_input()
{
  ifstream file("input.txt");
  vector<string> grid;
  vector<char> moves;
  string line;
  while (getline(file, line) && line != "")
  {
    grid.push_back(line);
  }
  while (getline(file, line))
  {
    for (char c : line)
    {
      moves.push_back(c);
    }
  }

  return {grid, moves};
}

map<char, tuple<int, int>> directions = {
    {'^', {-1, 0}},
    {'>', {0, 1}},
    {'v', {1, 0}},
    {'<', {0, -1}}};

tuple<int, int> find_starting_position(vector<string> grid)
{
  for (int i = 0; i < grid.size(); i++)
  {
    for (int j = 0; j < grid[i].size(); j++)
    {
      if (grid[i][j] == '@')
        return {i, j};
    }
  }
  return {-1, -1};
}

void part_1()
{
  auto [grid, moves] = read_input();
  auto [r, c] = find_starting_position(grid);

  for (char move : moves)
  {
    auto [dr, dc] = directions[move];
    int nr = r;
    int nc = c;
    while (grid[nr][nc] != '#')
    {
      nr += dr;
      nc += dc;

      if (grid[nr][nc] == '.')
      {
        while (nr != r || nc != c)
        {
          grid[nr][nc] = grid[nr - dr][nc - dc];
          nr -= dr;
          nc -= dc;
        }

        grid[r][c] = '.';
        r = r + dr;
        c = c + dc;
        break;
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < grid.size(); i++)
  {
    for (int j = 0; j < grid[i].size(); j++)
    {
      if (grid[i][j] == 'O')
        ans += i * 100 + j;
    }
  }
  cout << ans << endl;
}

vector<string> build_wider_grid(vector<string> grid)
{
  vector<string> wider_grid;
  for (string row : grid)
  {
    string wider_row = "";
    for (char c : row)
    {
      if (c == '#')
        wider_row += "##";
      else if (c == 'O')
        wider_row += "[]";
      else if (c == '.')
        wider_row += "..";
      else
        wider_row += "@.";
    }
    wider_grid.push_back(wider_row);
  }
  return wider_grid;
}

bool move_if_valid(vector<string> &grid, int r, int c, int dr, int dc)
{
  int nr = r + dr;
  int nc = c + dc;
  bool can_move = false;

  if (grid[nr][nc] == '#')
    return false;
  if (grid[nr][nc] == '.')
    can_move = true;
  if (grid[nr][nc] == '[' || grid[nr][nc] == ']')
  {
    // up or down -> need to check both parts of the box
    if (dc == 0)
    {
      int box_complement_col = grid[nr][nc] == '[' ? nc + 1 : nc - 1;
      if (move_if_valid(grid, nr, box_complement_col, dr, dc) && move_if_valid(grid, nr, nc, dr, dc))
        can_move = true;
    }
    else
    {
      if (move_if_valid(grid, nr, nc, dr, dc))
        can_move = true;
    }
  }

  if (can_move)
  {
    grid[nr][nc] = grid[r][c];
    grid[r][c] = '.';
    return true;
  }

  return false;
}

void part_2()
{
  auto [grid, moves] = read_input();
  grid = build_wider_grid(grid);

  auto [r, c] = find_starting_position(grid);

  for (char move : moves)
  {
    vector<string> new_grid = grid;
    auto [dr, dc] = directions[move];
    if (move_if_valid(new_grid, r, c, dr, dc))
    {
      r += dr;
      c += dc;
      grid = new_grid;
    }
  }

  int ans = 0;
  for (int i = 0; i < grid.size(); i++)
  {
    for (int j = 0; j < grid[i].size(); j++)
    {
      if (grid[i][j] == '[')
        ans += i * 100 + j;
    }
  }
  cout << ans << endl;
}

int main()
{
  part_1();
  part_2();
}
