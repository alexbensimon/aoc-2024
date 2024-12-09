#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> read_input()
{
  ifstream file("input.txt");
  string line;
  getline(file, line);
  vector<int> input;
  for (char c : line)
  {
    // Convert char to int
    input.push_back(c - '0');
  }
  return input;
}

vector<int> uncompress(vector<int> input)
{
  vector<int> output;
  int id = 0;
  bool space = false;
  for (int num : input)
  {
    for (int i = 0; i < num; i++)
    {
      output.push_back(space ? -1 : id);
    }
    if (!space)
      id++;
    space = !space;
  }
  return output;
}

void display(vector<int> uncompressed)
{
  for (int num : uncompressed)
  {
    cout << (num == -1 ? "." : to_string(num));
  }
  cout << endl;
}

void part_1()
{
  auto input = read_input();
  auto uncompressed = uncompress(input);

  while (true)
  {
    auto it = find(uncompressed.begin(), uncompressed.end(), -1);
    if (it == uncompressed.end())
      break;
    int index = it - uncompressed.begin();

    int num = uncompressed.back();
    uncompressed.pop_back();
    uncompressed[index] = num;
  }

  long long ans = 0;
  for (int i = 0; i < uncompressed.size(); i++)
  {
    ans += uncompressed[i] * i;
  }
  cout << ans << endl;
}

void part_2()
{
  auto input = read_input();

  // Store data in a map where keys are nums and values are:
  // - position
  // - size

  // -> how to store space? -> another data structure -> list of positions and sizes ?

  map<int, pair<int, int>> data;
  vector<pair<int, int>> spaces;
  int id = 0;
  bool space = false;
  int position = 0;
  for (int num : input)
  {
    if (space)
    {
      spaces.push_back({position, num});
    }
    else
    {
      data[id] = {position, num};
      id++;
    }
    position += num;
    space = !space;
  }

  for (auto it = data.rbegin(); it != data.rend(); ++it)
  {
    int data_position = it->second.first;
    int data_size = it->second.second;

    for (int i = 0; i < spaces.size(); i++)
    {
      int space_position = spaces[i].first;
      int space_size = spaces[i].second;

      if ((space_position < data_position) && (space_size >= data_size))
      {
        it->second.first = space_position;

        spaces[i].first += data_size;
        spaces[i].second -= data_size;

        break;
      }
    }
  }

  long long ans = 0;

  for (const auto &[id, value] : data)
  {
    int position = value.first;
    int size = value.second;

    for (int i = 0; i < size; i++)
    {
      ans += (position + i) * id;
    }
  }

  cout << ans << endl;
}

int main()
{
  part_1();
  part_2();
}
