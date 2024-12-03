#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>

using namespace std;

void part_1()
{
  ifstream file("input.txt");
  stringstream buffer;
  buffer << file.rdbuf();
  string file_content = buffer.str();

  regex pattern("mul\\((\\d{1,3},\\d{1,3})\\)");
  smatch matches;
  int ans = 0;
  while (regex_search(file_content, matches, pattern))
  {
    stringstream ss(matches[1].str());
    int a, b;
    char comma;
    ss >> a >> comma >> b;
    ans += a * b;

    file_content = matches.suffix().str();
  }

  cout << ans << endl;
}

void part_2()
{
  ifstream file("input.txt");
  stringstream buffer;
  buffer << file.rdbuf();
  string file_content = buffer.str();

  regex pattern("mul\\((\\d{1,3},\\d{1,3})\\)|(don't\\(\\))|(do\\(\\))");
  smatch matches;
  int ans = 0;
  bool enabled = true;

  while (regex_search(file_content, matches, pattern))
  {
    for (size_t i = 0; i < matches.size(); ++i)
    {
      string match = matches[i].str();
      cout << match << endl;
      if (match == "don't()")
      {
        enabled = false;
        break;
      }
      else if (match == "do()")
      {
        enabled = true;
        break;
      }
      else if (enabled)
      {
        int a, b;
        sscanf(match.c_str(), "mul(%d,%d)", &a, &b);
        cout << a << " " << b << endl;
        ans += a * b;
        break;
      }
    }
    file_content = matches.suffix().str();
  }

  cout << ans << endl;
}

int main()
{
  part_1();
  part_2();
}
