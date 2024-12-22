#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include <set>

using namespace std;

vector<long long> read_input()
{
  vector<long long> input;
  ifstream file("input.txt");
  string line;
  while (getline(file, line))
  {
    input.push_back(stoll(line));
  }
  return input;
}

long long mix(long long num, long long secret)
{
  return num ^ secret;
}

long long prune(long long secret)
{
  return secret % 16777216;
}

long long compute_next_secret(long long secret)
{
  long long next_secret = mix(secret * 64, secret);
  next_secret = prune(next_secret);

  next_secret = mix(next_secret / 32, next_secret);
  next_secret = prune(next_secret);

  next_secret = mix(next_secret * 2048, next_secret);
  next_secret = prune(next_secret);

  return next_secret;
}

void part_1()
{
  auto secrets = read_input();

  long long ans = 0;
  for (auto secret : secrets)
  {
    for (long long i = 0; i < 2000; i++)
    {
      secret = compute_next_secret(secret);
      cout << secret << endl;
    }
    ans += secret;
  }
  cout << ans << endl;
}

void part_2()
{
  auto secrets = read_input();

  map<tuple<int, int, int, int>, int> sequences;

  for (auto secret : secrets)
  {
    vector<int> prices;
    for (long long i = 0; i <= 2000; i++)
    {
      prices.push_back(secret % 10); // Get the last digit
      secret = compute_next_secret(secret);
    }

    set<tuple<int, int, int, int>> seen;
    for (int i = 0; i < prices.size() - 4; i++)
    {
      tuple<int, int, int, int> sequence = {prices[i + 1] - prices[i], prices[i + 2] - prices[i + 1], prices[i + 3] - prices[i + 2], prices[i + 4] - prices[i + 3]};
      if (seen.count(sequence))
        continue;
      seen.insert(sequence);
      sequences[sequence] += prices[i + 4];
    }
  }

  int max_value = 0;
  for (const auto &[sequence, value] : sequences)
  {
    max_value = max(max_value, value);
  }
  cout << max_value << endl;
}

int main()
{
  part_1();
  part_2();
}
