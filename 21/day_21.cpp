#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

vector<string> read_input()
{
  ifstream file("input.txt");
  vector<string> lines;
  string line;
  while (getline(file, line))
    lines.push_back(line);
  return lines;
}
map<pair<int, int>, char> num_keys = {
    {{0, 0}, '7'},
    {{0, 1}, '8'},
    {{0, 2}, '9'},
    {{1, 0}, '4'},
    {{1, 1}, '5'},
    {{1, 2}, '6'},
    {{2, 0}, '1'},
    {{2, 1}, '2'},
    {{2, 2}, '3'},
    {{3, 1}, '0'},
    {{3, 2}, 'A'},
};

map<pair<int, int>, char> dir_keys = {
    {{0, 1}, '^'},
    {{0, 2}, 'A'},
    {{1, 0}, '<'},
    {{1, 1}, 'v'},
    {{1, 2}, '>'},
};

vector<pair<int, int>> directions = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

map<pair<int, int>, char> key_for_move = {
    {{-1, 0}, '^'},
    {{0, -1}, '<'},
    {{0, 1}, '>'},
    {{1, 0}, 'v'},
};

pair<int, int> find_char_pos(char c, map<pair<int, int>, char> &keys)
{
  for (auto [pos, key] : keys)
    if (key == c)
      return pos;
  return {-1, -1};
}

vector<string> find_paths(char from, char to, map<pair<int, int>, char> &keys)
{
  auto from_pos = find_char_pos(from, keys);
  struct Node
  {
    pair<int, int> pos;
    string sequence;
  };
  queue<Node> q;
  q.push({from_pos, ""});
  int best_dist = INT_MAX;
  vector<string> best_paths;

  // BFS to find all best paths
  while (!q.empty())
  {
    Node current = q.front();
    q.pop();
    auto [r, c] = current.pos;
    auto sequence = current.sequence;
    if (sequence.size() > best_dist)
      continue;

    if (keys[current.pos] == to)
    {
      sequence += 'A';
      best_paths.push_back(sequence);
      best_dist = sequence.size();
      continue;
    }

    for (auto dir : directions)
    {
      int nr = r + dir.first;
      int nc = c + dir.second;

      if (keys.count({nr, nc}))
      {
        q.push({{nr, nc}, sequence + key_for_move[dir]});
      }
    }
  }
  return best_paths;
}

long long find_best_length(char from, char to, map<pair<int, int>, char> &keys, int level)
{
  auto paths = find_paths(from, to, keys);

  if (level == 1)
    return paths[0].size();

  long long best_length = LLONG_MAX;
  for (auto path : paths)
  {
    path = 'A' + path;
    long long length = 0;
    for (int i = 0; i < path.size() - 1; i++)
    {
      length += find_best_length(path[i], path[i + 1], dir_keys, level - 1);
    }
    best_length = min(best_length, length);
  }
  return best_length;
}

void part_1()
{
  auto codes = read_input();

  long long ans = 0;
  for (auto code : codes)
  {
    string ncode = 'A' + code;

    long long length = 0;
    for (int i = 0; i < ncode.size() - 1; i++)
    {
      length += find_best_length(ncode[i], ncode[i + 1], num_keys, 3);
    }

    long long num_code = stoll(code);
    ans += num_code * length;
  }

  cout << ans << endl;
}

long long find_best_length_memo(char from, char to, map<pair<int, int>, char> &keys, int level, map<tuple<char, char, int>, long long> &memo)
{
  if (memo.count({from, to, level}))
    return memo[{from, to, level}];

  auto paths = find_paths(from, to, keys);

  if (level == 1)
    return paths[0].size();

  long long best_length = LLONG_MAX;
  for (auto path : paths)
  {
    path = 'A' + path;
    long long length = 0;
    for (int i = 0; i < path.size() - 1; i++)
    {
      length += find_best_length_memo(path[i], path[i + 1], dir_keys, level - 1, memo);
    }
    best_length = min(best_length, length);
  }
  memo[{from, to, level}] = best_length;
  return best_length;
}

void part_2()
{
  auto codes = read_input();

  map<tuple<char, char, int>, long long> memo;

  long long ans = 0;
  for (auto code : codes)
  {
    string ncode = 'A' + code;

    long long length = 0;
    for (int i = 0; i < ncode.size() - 1; i++)
    {
      length += find_best_length_memo(ncode[i], ncode[i + 1], num_keys, 26, memo);
    }

    long long num_code = stoll(code);
    ans += num_code * length;
  }

  cout << ans << endl;
}

int main()
{
  part_1();
  part_2();
}
