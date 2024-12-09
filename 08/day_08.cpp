#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

struct GridData
{
  map<char, set<pair<int, int>>> coord_map;
  int rows;
  int cols;
};

GridData read_input()
{
  ifstream file("input.txt");
  string line;
  GridData data;
  data.rows = 0;
  data.cols = 0;

  while (getline(file, line))
  {
    if (data.cols == 0)
    {
      data.cols = line.length();
    }
    for (int col = 0; col < line.length(); col++)
    {
      char c = line[col];
      if (c != '.')
      {
        data.coord_map[c].insert({data.rows, col});
      }
    }
    data.rows++;
  }

  return data;
}

void part_1()
{
  auto grid_data = read_input();

  for (auto &[c, coords] : grid_data.coord_map)
  {
    for (auto &coord1 : coords)
    {
      for (auto &coord2 : coords)
      {
        if (coord1.first == coord2.first && coord1.second == coord2.second)
        {
          continue;
        }
        int antinode_r = coord2.first + coord2.first - coord1.first;
        int antinode_c = coord2.second + coord2.second - coord1.second;
        if (antinode_r < 0 || antinode_r >= grid_data.rows || antinode_c < 0 || antinode_c >= grid_data.cols)
        {
          continue;
        }
        grid_data.coord_map['#'].insert({antinode_r, antinode_c});
      }
    }
  }

  cout << grid_data.coord_map['#'].size() << endl;
}

void part_2()
{
  auto grid_data = read_input();

  for (auto &[c, coords] : grid_data.coord_map)
  {
    for (auto &coord1 : coords)
    {
      for (auto &coord2 : coords)
      {
        if (coord1.first == coord2.first && coord1.second == coord2.second)
        {
          continue;
        }

        grid_data.coord_map['#'].insert(coord2);

        int i = 1;
        while (true)
        {
          int antinode_r = coord2.first + i * (coord2.first - coord1.first);
          int antinode_c = coord2.second + i * (coord2.second - coord1.second);
          if (antinode_r < 0 || antinode_r >= grid_data.rows || antinode_c < 0 || antinode_c >= grid_data.cols)
          {
            break;
          }
          grid_data.coord_map['#'].insert({antinode_r, antinode_c});
          i++;
        }
      }
    }
  }

  cout << grid_data.coord_map['#'].size() << endl;
}

int main()
{
  // part_1();
  part_2();
}
