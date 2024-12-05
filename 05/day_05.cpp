#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

tuple<unordered_map<int, pair<unordered_set<int>, unordered_set<int>>>, vector<vector<int>>> read_input()
{
  ifstream file("input.txt");
  // key is the number, value is a pair of sets of numbers that are before and after
  unordered_map<int, pair<unordered_set<int>, unordered_set<int>>> rules;
  vector<vector<int>> updates;
  string line;
  bool is_first_part = true;
  while (getline(file, line))
  {
    if (line.empty())
    {
      is_first_part = false;
      continue;
    }

    if (is_first_part)
    {
      istringstream iss(line);
      int a, b;
      sscanf(line.c_str(), "%d|%d", &a, &b);
      rules[a].second.insert(b);
      rules[b].first.insert(a);
    }
    else
    {
      vector<int> update;
      istringstream iss(line);
      string num;
      while (getline(iss, num, ','))
      {
        update.push_back(stoi(num));
      }
      updates.push_back(update);
    }
  }

  return {rules, updates};
}

tuple<vector<vector<int>>, vector<vector<int>>, unordered_map<int, pair<unordered_set<int>, unordered_set<int>>>> get_valid_invalid_updates()
{
  auto [rules, updates] = read_input();

  vector<vector<int>> valid_updates;
  vector<vector<int>> invalid_updates;

  // for each update, check before and after if rule is violated
  for (const auto &update : updates)
  {
    bool is_update_valid = true;
    for (int i = 0; i < update.size(); i++)
    {
      // Check if numbers before current position are in the after rules for this number
      for (int j = 0; j < i; j++)
      {
        if (rules[update[i]].second.find(update[j]) != rules[update[i]].second.end())
        {
          is_update_valid = false;
          break;
        }
      }
      // Check after
      for (int j = i + 1; j < update.size(); j++)
      {
        if (rules[update[i]].first.find(update[j]) != rules[update[i]].first.end())
        {
          is_update_valid = false;
          break;
        }
      }
      if (!is_update_valid)
        break;
    }

    if (is_update_valid)
    {
      valid_updates.push_back(update);
    }
    else
    {
      invalid_updates.push_back(update);
    }
  }

  return {valid_updates, invalid_updates, rules};
}

void part_1()
{
  auto [valid_updates, invalid_updates, rules] = get_valid_invalid_updates();

  int ans = 0;

  for (const auto &update : valid_updates)
  {
    ans += update[update.size() / 2];
  }

  cout << ans << endl;
}

struct CompareWithRules
{
  const unordered_map<int, pair<unordered_set<int>, unordered_set<int>>> &rules;

  CompareWithRules(const unordered_map<int, pair<unordered_set<int>, unordered_set<int>>> &r) : rules(r) {}

  bool operator()(int a, int b) const
  {
    return (rules.at(a).second.find(b) != rules.at(a).second.end()) || (rules.at(b).first.find(a) != rules.at(b).first.end());
  }
};

void part_2()
{
  auto [valid_updates, invalid_updates, rules] = get_valid_invalid_updates();
  auto mutable_updates = invalid_updates;

  for (auto &update : mutable_updates)
  {
    sort(update.begin(), update.end(), CompareWithRules(rules));
  }

  int ans = 0;
  for (const auto &update : mutable_updates)
  {
    ans += update[update.size() / 2];
  }

  cout << ans << endl;
}

int main()
{
  part_1();
  part_2();
}
