#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <stack>

using namespace std;

vector<pair<int, int>> directions = {
    {-1, 0}, // up
    {0, 1},  // right
    {1, 0},  // down
    {0, -1}  // left
};

vector<vector<char>> read_input()
{
  ifstream file("input.txt");
  vector<vector<char>> input;
  string line;
  while (getline(file, line))
  {
    input.push_back(vector<char>(line.begin(), line.end()));
  }
  return input;
}

vector<set<pair<int, int>>> find_regions()
{
  auto input = read_input();
  vector<set<pair<int, int>>> regions;
  set<pair<int, int>> visited;
  for (int i = 0; i < input.size(); i++)
  {
    for (int j = 0; j < input[i].size(); j++)
    {
      if (visited.find({i, j}) != visited.end())
        continue;
      set<pair<int, int>> region;
      char letter = input[i][j];
      region.insert({i, j});

      // DFS to find all points in the same region
      stack<pair<int, int>> s;
      s.push({i, j});
      while (!s.empty())
      {
        auto [r, c] = s.top();
        s.pop();
        for (auto &direction : directions)
        {
          int nr = r + direction.first;
          int nc = c + direction.second;
          if (nr < 0 || nr >= input.size() || nc < 0 || nc >= input[nr].size())
            continue;
          if (visited.find({nr, nc}) != visited.end())
            continue;
          if (input[nr][nc] == letter)
          {
            s.push({nr, nc});
            visited.insert({nr, nc});
            region.insert({nr, nc});
          }
        }
      }
      regions.push_back(region);
    }
  }
  return regions;
}

int compute_perimeter(set<pair<int, int>> region)
{
  int perimeter = 0;
  for (auto &point : region)
  {
    for (auto &direction : directions)
    {
      int nr = point.first + direction.first;
      int nc = point.second + direction.second;
      if (region.find({nr, nc}) == region.end())
        perimeter++;
    }
  }
  return perimeter;
}

void part_1()
{
  auto regions = find_regions();
  int res = 0;
  for (auto &region : regions)
  {
    res += region.size() * compute_perimeter(region);
  }
  cout << res << endl;
}

int compute_nb_sides(set<pair<int, int>> region)
{
  // An edge is {direction, point}
  set<pair<pair<int, int>, pair<float, float>>> edges;
  for (auto &point : region)
  {
    for (auto &direction : directions)
    {
      int nr = point.first + direction.first;
      int nc = point.second + direction.second;
      if (region.find({nr, nc}) == region.end())
        edges.insert({direction, {nr, nc}});
    }
  }

  int sides = 0;
  set<pair<pair<int, int>, pair<float, float>>> visited;
  for (auto &edge : edges)
  {
    if (visited.find(edge) != visited.end())
      continue;
    visited.insert(edge);
    sides++;

    // DFS to find all edges that belong to the same side
    stack<pair<pair<int, int>, pair<float, float>>> s;
    s.push(edge);
    while (!s.empty())
    {
      auto [direction, point] = s.top();
      s.pop();

      vector<pair<pair<int, int>, pair<float, float>>> edges_to_check;

      if (direction.second == 0)
      {
        // If left or right is an edge, it belongs to the same side
        pair<pair<int, int>, pair<float, float>> left = {direction, {point.first, point.second - 1}};
        pair<pair<int, int>, pair<float, float>> right = {direction, {point.first, point.second + 1}};
        edges_to_check.push_back(left);
        edges_to_check.push_back(right);
      }
      else
      {
        pair<pair<int, int>, pair<float, float>> up = {direction, {point.first - 1, point.second}};
        pair<pair<int, int>, pair<float, float>> down = {direction, {point.first + 1, point.second}};
        edges_to_check.push_back(up);
        edges_to_check.push_back(down);
      }

      for (auto &edge_to_check : edges_to_check)
      {
        if (visited.find(edge_to_check) != visited.end())
          continue;
        if (edges.find(edge_to_check) != edges.end())
        {
          s.push(edge_to_check);
          visited.insert(edge_to_check);
        }
      }
    }
  }
  return sides;
}

void part_2()
{
  auto regions = find_regions();
  int res = 0;
  for (auto &region : regions)
  {
    res += region.size() * compute_nb_sides(region);
  }
  cout << res << endl;
}

int main()
{
  part_1();
  part_2();
}
