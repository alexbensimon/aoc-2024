#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

tuple<int, int, int, vector<int>> read_input()
{
  ifstream file("input.txt");
  int a, b, c;
  vector<int> program;
  string line;

  getline(file, line);
  sscanf(line.c_str(), "Register A: %d", &a);
  getline(file, line);
  sscanf(line.c_str(), "Register B: %d", &b);
  getline(file, line);
  sscanf(line.c_str(), "Register C: %d", &c);

  // Skip empty line
  getline(file, line);

  getline(file, line);
  string program_str = line.substr(line.find(":") + 2); // Skip "Program: "

  stringstream ss(program_str);
  string number;
  while (getline(ss, number, ','))
  {
    program.push_back(stoi(number));
  }

  return {a, b, c, program};
}

int combo_op(int value, int a, int b, int c)
{
  if (value == 4)
    return a;
  if (value == 5)
    return b;
  if (value == 6)
    return c;
  return value;
}

string compute_output(int a, int b, int c, vector<int> program)
{
  int pc = 0;
  string output = "";
  while (pc < program.size())
  {
    int opcode = program[pc];
    int operand = program[pc + 1];

    switch (opcode)
    {
    case 0:
    {
      int num = a;
      int denom = pow(2, combo_op(operand, a, b, c));
      a = num / denom;
      break;
    }
    case 1:
    {
      b = b ^ operand;
      break;
    }
    case 2:
    {
      b = combo_op(operand, a, b, c) % 8;
      break;
    }
    case 3:
    {
      if (a == 0)
        break;
      pc = operand;
      continue;
    }
    case 4:
    {
      b = b ^ c;
      break;
    }
    case 5:
    {
      if (output != "")
        output += ",";
      output += to_string(combo_op(operand, a, b, c) % 8);
      break;
    }
    case 6:
    {
      int num = a;
      int denom = pow(2, combo_op(operand, a, b, c));
      b = num / denom;
      break;
    }
    case 7:
    {
      int num = a;
      int denom = pow(2, combo_op(operand, a, b, c));
      c = num / denom;
      break;
    }
    }

    pc += 2;
  }

  return output;
}

void part_1()
{
  auto [a, b, c, program] = read_input();
  string output = compute_output(a, b, c, program);
  cout << output << endl;
}

long long find(vector<int> program, long long ans)
{
  if (program.size() == 0)
    return ans;
  int last_output = program.back();
  program.pop_back();
  for (int i = 0; i < 8; i++)
  {
    long long a = (ans * 8) | i;
    long long b = a % 8;
    b = b ^ 5;
    long long c = a / pow(2, b);
    b = b ^ 6;
    b = b ^ c;
    if (b % 8 == last_output)
    {
      long long result = find(program, a);
      if (result != -1)
        return result;
    }
  }
  return -1;
}

void part_2()
{
  /*

  Program: 2,4,1,5,7,5,1,6,4,1,5,5,0,3,3,0

  2 4 -> b = a % 8
  1 5 -> b = b ^ 5
  7 5 -> c = a / 2^b
  1 6 -> b = b ^ 6
  4 1 -> b = b ^ c
  5 5 -> output b % 8
  0 3 -> a = a / 8
  3 0 -> if a != 0, jump 0

  */

  auto [a, b, c, program] = read_input();

  cout << find(program, 0) << endl;
}

int main()
{
  part_1();
  part_2();
}
