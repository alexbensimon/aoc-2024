
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <queue>
#include <map>

using namespace std;

// string FILE_NAME = "test.txt";
// int MAX_GRID_SIZE = 6;
// int BYTES_CORRUPTED = 12;

string FILE_NAME = "input.txt";
int MAX_GRID_SIZE = 70;
int BYTES_CORRUPTED = 1024;

vector<pair<int, int>> read_input()
{
  ifstream file(FILE_NAME);
  vector<pair<int, int>> input;
  int a, b;
  string line;
  while (getline(file, line))
  {
    sscanf(line.c_str(), "%d,%d", &a, &b);
    input.push_back({a, b});
  }
  return input;
}

vector<pair<int, int>> directions = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}};

int find_nb_steps(set<pair<int, int>> corrupted)
{
  pair<int, int> start = {0, 0};
  pair<int, int> end = {MAX_GRID_SIZE, MAX_GRID_SIZE};

  queue<pair<int, int>> q;
  set<pair<int, int>> visited;
  map<pair<int, int>, int> dist;

  q.push(start);
  visited.insert(start);
  dist[start] = 0;

  while (!q.empty())
  {
    pair<int, int> current = q.front();
    q.pop();
    int x = current.first;
    int y = current.second;

    if (x == end.first && y == end.second)
    {
      return dist[{x, y}];
    }

    for (auto dir : directions)
    {
      int nx = x + dir.first;
      int ny = y + dir.second;

      if (nx < 0 || nx > MAX_GRID_SIZE || ny < 0 || ny > MAX_GRID_SIZE)
        continue;

      if (corrupted.count({nx, ny}))
        continue;

      if (visited.count({nx, ny}))
        continue;

      visited.insert({nx, ny});
      dist[{nx, ny}] = dist[{x, y}] + 1;
      q.push({nx, ny});
    }
  }

  return -1;
}

void part_1()
{
  auto input = read_input();
  set<pair<int, int>> corrupted;
  for (int i = 0; i < BYTES_CORRUPTED; i++)
    corrupted.insert(input[i]);

  int nb_steps = find_nb_steps(corrupted);
  cout << nb_steps << endl;
}

void part_2()
{
  auto input = read_input();
  set<pair<int, int>> corrupted;
  for (int i = 0; i < BYTES_CORRUPTED; i++)
    corrupted.insert(input[i]);
  for (int i = 0; i < input.size(); i++)
  {
    auto point = input[i];
    corrupted.insert(point);
    int nb_steps = find_nb_steps(corrupted);
    if (nb_steps == -1)
    {
      cout << point.first << "," << point.second << endl;
      return;
    }
  }
}

int main()
{
  part_1();
  part_2();
}
