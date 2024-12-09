#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<vector<long long>> read_input()
{
  ifstream file("input.txt");
  vector<vector<long long>> result;
  string line;
  while (getline(file, line))
  {
    vector<long long> row;
    stringstream ss(line);
    string number;

    // Read the first number before the colon
    getline(ss, number, ':');
    row.push_back(stoll(number));

    // Read the remaining numbers
    long long num;
    while (ss >> num)
    { // This automatically skips whitespace
      row.push_back(num);
    }

    result.push_back(row);
  }
  return result;
}

vector<vector<char>> generatePermutations(int size)
{
  vector<char> characters = {'+', '*'};
  int totalPermutations = 1 << size; // 2^n permutations
  vector<vector<char>> result;
  for (int i = 0; i < totalPermutations; ++i)
  {
    vector<char> permutation;
    for (int j = 0; j < size; ++j)
    {
      if (i & (1 << j))
      {
        permutation.push_back('*');
      }
      else
      {
        permutation.push_back('+');
      }
    }
    result.push_back(permutation);
  }
  return result;
}

void part_1()
{
  auto equations = read_input();
  long long ans = 0;
  for (auto &equation : equations)
  {
    long long correct_result = equation[0];
    int slots = equation.size() - 2;
    auto permutations = generatePermutations(slots);
    bool valid_equation = false;
    for (auto &permutation : permutations)
    {
      long long result = equation[1];
      for (int i = 2; i < equation.size(); i++)
      {
        if (permutation[i - 2] == '+')
        {
          result += equation[i];
        }
        else
        {
          result *= equation[i];
        }
      }
      if (result == correct_result)
      {
        valid_equation = true;
        break;
      }
    }
    if (valid_equation)
    {
      ans += correct_result;
    }
  }
  cout << ans << endl;
}

vector<vector<char>> generatePermutations2(int size)
{
  vector<char> characters = {'+', '*', '|'}; // Added third character
  int totalPermutations = pow(3, size);      // 3^n permutations
  vector<vector<char>> result;

  for (int i = 0; i < totalPermutations; ++i)
  {
    vector<char> permutation;
    int num = i;

    // Convert to base-3 representation
    for (int j = 0; j < size; ++j)
    {
      int remainder = num % 3;
      permutation.push_back(characters[remainder]);
      num /= 3;
    }

    result.push_back(permutation);
  }

  return result;
}

void part_2()
{
  auto equations = read_input();
  long long ans = 0;
  for (auto &equation : equations)
  {
    long long correct_result = equation[0];
    int slots = equation.size() - 2;
    auto permutations = generatePermutations2(slots);
    bool valid_equation = false;
    for (auto &permutation : permutations)
    {
      long long result = equation[1];
      for (int i = 2; i < equation.size(); i++)
      {
        if (permutation[i - 2] == '+')
        {
          result += equation[i];
        }
        else if (permutation[i - 2] == '*')
        {
          result *= equation[i];
        }
        else
        {
          // Convert to strings
          string res = to_string(result);
          string num = to_string(equation[i]);

          // Concatenate strings
          string concatenatedStr = res + num;

          // Convert back to a number
          result = stoll(concatenatedStr);
        }
      }
      if (result == correct_result)
      {
        valid_equation = true;
        break;
      }
    }
    if (valid_equation)
    {
      ans += correct_result;
    }
  }
  cout << ans << endl;
}

int main()
{
  part_1();
  part_2();
}
