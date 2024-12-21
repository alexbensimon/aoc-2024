#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <tuple>
#include <optional>

using namespace std;

vector<string> read_input()
{
  ifstream file("input.txt");
  vector<string> input;
  string line;
  while (getline(file, line))
    input.push_back(line);
  return input;
}

pair<int, int> find_start(vector<string> grid)
{
  for (int i = 0; i < grid.size(); i++)
    for (int j = 0; j < grid[i].size(); j++)
      if (grid[i][j] == 'S')
        return {i, j};
  return {-1, -1};
}

vector<pair<int, int>> directions = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}};

map<pair<int, int>, int> find_dist(vector<string> grid)
{
  queue<pair<int, int>> q;
  set<pair<int, int>> visited;
  map<pair<int, int>, int> dist;

  auto start = find_start(grid);
  q.push(start);
  visited.insert(start);
  dist[start] = 0;

  // BFS to find the distance from start of each point on the path
  while (!q.empty())
  {
    pair<int, int> current = q.front();
    q.pop();
    int r = current.first;
    int c = current.second;

    if (grid[r][c] == 'E')
    {
      break;
    }

    for (auto dir : directions)
    {
      int nr = r + dir.first;
      int nc = c + dir.second;

      if (grid[nr][nc] == '#')
        continue;

      if (visited.count({nr, nc}))
        continue;

      visited.insert({nr, nc});
      dist[{nr, nc}] = dist[{r, c}] + 1;
      q.push({nr, nc});
    }
  }

  return dist;
}

void part_1()
{
  auto grid = read_input();
  auto dist = find_dist(grid);

  map<tuple<pair<int, int>, pair<int, int>>, int> cheats;

  for (const auto &[pos, d] : dist)
  {
    int r = pos.first;
    int c = pos.second;
    // check all points we can reach with a cheat
    vector<pair<int, int>> points = {
        {r + 2, c},
        {r - 2, c},
        {r, c + 2},
        {r, c - 2},
        {r + 1, c + 1},
        {r + 1, c - 1},
        {r - 1, c + 1},
        {r - 1, c - 1}};
    for (auto point : points)
    {
      // if the point is on the path and we can save time by cheating
      if (dist.count(point) && (d + 2) < dist[point])
      {
        cheats[{pos, point}] = dist[point] - (d + 2);
      }
    }
  }
  int ans = 0;
  for (const auto &[positions, time_saved] : cheats)
  {
    if (time_saved >= 100)
      ans += 1;
  }
  cout << ans << endl;
}

void part_2()
{
  auto grid = read_input();
  auto dist = find_dist(grid);

  map<tuple<pair<int, int>, pair<int, int>>, int> cheats;

  for (const auto &[pos, d] : dist)
  {
    int r = pos.first;
    int c = pos.second;
    // check all points we can reach with a cheat
    vector<pair<pair<int, int>, int>> points_with_steps;
    for (int steps = 1; steps <= 20; steps++)
    {
      // For each row in the diamond
      for (int row_offset = -steps; row_offset <= steps; row_offset++)
      {
        // Calculate how many cells we can move left/right on this row
        int remaining_steps = steps - abs(row_offset);

        // Add the point to the right
        points_with_steps.push_back({{r + row_offset, c + remaining_steps}, steps});

        // Add the point to the left (if it's not the same as the right point)
        if (remaining_steps > 0)
        {
          points_with_steps.push_back({{r + row_offset, c - remaining_steps}, steps});
        }
      }
    }
    for (auto point : points_with_steps)
    {
      // if the point is on the path and we can save time by cheating
      if (dist.count(point.first) && (d + point.second) < dist[point.first])
      {
        cheats[{pos, point.first}] = dist[point.first] - (d + point.second);
      }
    }
  }
  int ans = 0;
  for (const auto &[positions, time_saved] : cheats)
  {
    if (time_saved >= 100)
      ans += 1;
  }
  cout << ans << endl;
}

int main()
{
  part_1();
  part_2();
}
