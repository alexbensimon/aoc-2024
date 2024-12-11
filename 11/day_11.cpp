#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <sstream>

using namespace std;

vector<long long> read_input()
{
  ifstream file("input.txt");
  string line;
  getline(file, line);

  vector<long long> numbers;
  istringstream iss(line);
  long long num;
  while (iss >> num)
  {
    numbers.push_back(num);
  }

  return numbers;
}

void part_1()
{
  vector<long long> numbers = read_input();

  for (int i = 0; i < 25; i++)
  {
    vector<long long> new_numbers = numbers;
    for (int i = 0; i < numbers.size(); i++)
    {
      if (numbers[i] == 0)
      {
        new_numbers[i] = 1;
      }
      else if (to_string(numbers[i]).size() % 2 == 0)
      {
        string num_string = to_string(numbers[i]);
        size_t middle = num_string.size() / 2;
        string firstHalf = num_string.substr(0, middle);
        string secondHalf = num_string.substr(middle);
        new_numbers[i] = stoi(firstHalf);
        new_numbers.push_back(stoi(secondHalf));
      }
      else
      {
        new_numbers[i] *= 2024;
      }
    }

    numbers = new_numbers;
  }

  cout << numbers.size() << endl;
}

void part_2()
{
  vector<long long> numbers = read_input();
  unordered_map<long long, long long> counts;

  for (long long num : numbers)
  {
    counts[num]++;
  }

  for (int i = 0; i < 75; i++)
  {
    unordered_map<long long, long long> new_counts = counts;
    for (auto &pair : counts)
    {
      long long num = pair.first;
      long long count = pair.second;
      if (count == 0)
        continue;
      if (num == 0)
      {
        new_counts[1] += count;
      }
      else if (to_string(num).size() % 2 == 0)
      {
        string num_string = to_string(num);
        size_t middle = num_string.size() / 2;
        string firstHalf = num_string.substr(0, middle);
        string secondHalf = num_string.substr(middle);
        new_counts[stoll(firstHalf)] += count;
        new_counts[stoll(secondHalf)] += count;
      }
      else
      {
        new_counts[num * 2024] += count;
      }
      new_counts[num] -= count;
    }

    counts = new_counts;
  }

  long long count = 0;
  for (auto &pair : counts)
  {
    count += pair.second;
  }

  cout << count << endl;
}

int main()
{
  part_1();
  part_2();
}
