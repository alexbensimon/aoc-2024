#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

vector<vector<int>> read_input()
{
  ifstream file("input.txt");
  vector<vector<int>> reports;

  string line;
  while (getline(file, line))
  {
    istringstream iss(line);
    vector<int> report;
    int level;
    while (iss >> level)
    {
      report.push_back(level);
    }
    reports.push_back(report);
  }

  return reports;
}

bool is_report_safe(const vector<int> &report)
{
  bool is_inc = report[0] < report[1];
  for (int i = 1; i < report.size(); i++)
  {
    bool wrong_trend = (is_inc && report[i] < report[i - 1]) || (!is_inc && report[i] > report[i - 1]);
    bool not_gradual = (abs(report[i] - report[i - 1]) < 1) || (abs(report[i] - report[i - 1]) > 3);
    if (wrong_trend || not_gradual)
      return false;
  }
  return true;
}

void part_1()
{
  auto reports = read_input();
  int safe_reports = 0;
  for (const auto &report : reports)
  {
    if (is_report_safe(report))
      safe_reports++;
  }
  cout << safe_reports << endl;
}

bool is_report_safe_one_error(const vector<int> &report)
{
  // Generate all variants of the report with each element removed
  vector<vector<int>> variants;
  for (size_t i = 0; i < report.size(); ++i)
  {
    vector<int> temp = report;
    temp.erase(temp.begin() + i);
    variants.push_back(temp);
  }

  for (const auto &variant : variants)
  {
    if (is_report_safe(variant))
      return true;
  }

  return false;
}

void part_2()
{
  auto reports = read_input();
  int safe_reports = 0;
  for (const auto &report : reports)
  {
    if (is_report_safe(report) || is_report_safe_one_error(report))
      safe_reports++;
  }
  cout << safe_reports << endl;
}

int main()
{
  part_1();
  part_2();
}
