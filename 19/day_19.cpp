#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

tuple<vector<string>, vector<string>> read_input()
{
  ifstream file("input.txt");
  vector<string> patterns;
  vector<string> designs;
  string line;
  bool read_patterns = true;
  while (getline(file, line))
  {
    if (line.empty())
    {
      read_patterns = false;
      continue;
    }
    if (read_patterns)
    {
      string pattern;
      stringstream ss(line);
      while (getline(ss >> ws, pattern, ','))
      {
        patterns.push_back(pattern);
      }
    }
    else
      designs.push_back(line);
  }
  return {patterns, designs};
}

bool is_design_possible(string design, vector<string> patterns)
{
  if (design == "")
    return true;

  for (auto pattern : patterns)
  {
    if (design.substr(0, pattern.length()) == pattern)
    {
      if (is_design_possible(design.substr(pattern.length()), patterns))
        return true;
    }
  }
  return false;
}

void part_1()
{
  auto [patterns, designs] = read_input();
  int count = 0;
  for (auto design : designs)
  {
    if (is_design_possible(design, patterns))
      count++;
  }
  cout << count << endl;
}

// Pass parameters by reference to improve performance
long long find_nb_arrangements(const string &design, const vector<string> &patterns, map<string, long long> &memo)
{
  if (design == "")
    return 1;

  if (memo.count(design))
    return memo[design];

  long long count = 0;
  for (const auto &pattern : patterns)
  {
    if (design.substr(0, pattern.length()) == pattern)
      count += find_nb_arrangements(design.substr(pattern.length()), patterns, memo);
  }
  memo[design] = count;
  return count;
}

void part_2()
{
  auto [patterns, designs] = read_input();
  map<string, long long> memo;
  long long count = 0;
  for (const auto &design : designs)
  {
    count += find_nb_arrangements(design, patterns, memo);
  }
  cout << count << endl;
}

int main()
{
  part_1();
  part_2();
}
