#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <queue>
#include <map>
#include <set>

using namespace std;

vector<string> read_input()
{
  ifstream file("input.txt");
  vector<string> grid;
  string line;
  while (getline(file, line))
  {
    grid.push_back(line);
  }
  return grid;
}

pair<int, int> find_start_position(vector<string> grid)
{
  for (int i = 0; i < grid.size(); i++)
  {
    for (int j = 0; j < grid[i].size(); j++)
    {
      if (grid[i][j] == 'S')
        return {i, j};
    }
  }
  return {-1, -1};
}

// Custom comparator to prioritize the lowest cost
struct Compare
{
  bool operator()(const tuple<pair<int, int>, pair<int, int>, int> &a, const tuple<pair<int, int>, pair<int, int>, int> &b)
  {
    return get<2>(a) > get<2>(b);
  }
};

void part_1()
{
  auto grid = read_input();
  auto start = find_start_position(grid);
  pair<int, int> start_dir = {0, 1};

  // Queue is a tuple of (position, direction, cost)
  priority_queue<tuple<pair<int, int>, pair<int, int>, int>, vector<tuple<pair<int, int>, pair<int, int>, int>>, Compare> q;
  set<tuple<pair<int, int>, pair<int, int>>> processed;

  q.push({start, start_dir, 0});

  // Dijkstra's algorithm to find the best path
  while (!q.empty())
  {
    auto [position, direction, cost] = q.top();
    q.pop();

    if (processed.find({position, direction}) != processed.end())
      continue;
    processed.insert({position, direction});

    if (grid[position.first][position.second] == 'E')
    {
      cout << cost << endl;
      return;
    }

    // Move forward
    pair<int, int> new_position = {position.first + direction.first, position.second + direction.second};
    if (grid[new_position.first][new_position.second] != '#')
    {
      q.push({new_position, direction, cost + 1});
    }

    // Rotate clockwise
    pair<int, int> clockwise = {direction.second, -direction.first};
    q.push({position, clockwise, cost + 1000});

    // Rotate counterclockwise
    pair<int, int> counterclockwise = {-direction.second, direction.first};
    q.push({position, counterclockwise, cost + 1000});
  }
}

// Custom comparator to prioritize the lowest cost
struct Compare2
{
  bool operator()(const tuple<pair<int, int>, pair<int, int>, vector<pair<int, int>>, int> &a, const tuple<pair<int, int>, pair<int, int>, vector<pair<int, int>>, int> &b)
  {
    return get<3>(a) > get<3>(b);
  }
};

void part_2()
{
  auto grid = read_input();
  auto start = find_start_position(grid);
  pair<int, int> start_dir = {0, 1};

  // Queue is a tuple of (position, direction, path, cost)
  priority_queue<tuple<pair<int, int>, pair<int, int>, vector<pair<int, int>>, int>, vector<tuple<pair<int, int>, pair<int, int>, vector<pair<int, int>>, int>>, Compare2> q;

  // We track the best cost for each state (position, direction)
  map<tuple<pair<int, int>, pair<int, int>>, int> best_costs;
  set<pair<int, int>> best_paths;

  q.push({start, start_dir, {start}, 0});

  // Dijkstra's algorithm to find the best path
  while (!q.empty())
  {
    auto [position, direction, path, cost] = q.top();
    q.pop();

    // Skip if we've found this state with a better cost
    auto state = make_tuple(position, direction);
    if (best_costs.count(state) && best_costs[state] < cost)
      continue;
    best_costs[state] = cost;

    if (grid[position.first][position.second] == 'E')
    {
      // Each time we find the end, we add the path to the set of best paths
      best_paths.insert(path.begin(), path.end());
      continue;
    }

    // Move forward
    pair<int, int> new_position = {position.first + direction.first, position.second + direction.second};
    if (grid[new_position.first][new_position.second] != '#')
    {
      vector<pair<int, int>> new_path = path;
      new_path.push_back(new_position);
      q.push({new_position, direction, new_path, cost + 1});
    }

    // Rotate clockwise
    pair<int, int> clockwise = {direction.second, -direction.first};
    q.push({position, clockwise, path, cost + 1000});

    // Rotate counterclockwise
    pair<int, int> counterclockwise = {-direction.second, direction.first};
    q.push({position, counterclockwise, path, cost + 1000});
  }

  cout << best_paths.size() << endl;
}

int main()
{
  part_1();
  part_2();
}
