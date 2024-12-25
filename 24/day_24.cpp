#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>

using namespace std;

struct Op
{
  string gate;
  string input1;
  string input2;
  string output;
};

tuple<map<string, bool>, vector<Op>> read_input()
{
  map<string, bool> values;
  vector<Op> ops;

  ifstream file("input.txt");
  string line;

  // Parse initial values
  while (getline(file, line) && !line.empty())
  {
    char var[4];
    int value;
    sscanf(line.c_str(), "%[^:]: %d", var, &value);
    values[var] = (value == 1);
  }

  // Parse operations
  while (getline(file, line))
  {
    if (line.empty())
      continue;

    char input1[4], input2[4], output[4];
    if (sscanf(line.c_str(), "%3s AND %3s -> %3s", input1, input2, output) == 3)
      ops.push_back({"AND", input1, input2, output});
    else if (sscanf(line.c_str(), "%3s OR %3s -> %3s", input1, input2, output) == 3)
      ops.push_back({"OR", input1, input2, output});
    else if (sscanf(line.c_str(), "%3s XOR %3s -> %3s", input1, input2, output) == 3)
      ops.push_back({"XOR", input1, input2, output});
  }

  return {values, ops};
}

bool execute_op(string gate, bool input1, bool input2)
{
  if (gate == "AND")
    return input1 && input2;
  else if (gate == "OR")
    return input1 || input2;
  else if (gate == "XOR")
    return input1 != input2;
  else
    throw invalid_argument("Invalid gate: " + gate);
}

void part_1()
{
  auto [values, ops] = read_input();
  set<string> inputs_ready;

  for (const auto &[var, val] : values)
    inputs_ready.insert(var);

  while (ops.size() > 0)
  {
    for (int i = 0; i < ops.size(); i++)
    {
      const auto &op = ops[i];
      if (inputs_ready.count(op.input1) && inputs_ready.count(op.input2))
      {
        values[op.output] = execute_op(op.gate, values[op.input1], values[op.input2]);
        inputs_ready.insert(op.output);
        ops.erase(ops.begin() + i);
      }
    }
  }

  string z = "";
  for (const auto &[var, val] : values)
  {
    if (var[0] == 'z')
    {
      char bit = val ? '1' : '0';
      z = bit + z;
    }
  }

  cout << stoll(z, nullptr, 2) << endl;
}

void display_op(const Op &op)
{
  cout << op.input1 << " " << op.input2 << " " << op.gate << " -> " << op.output << endl;
}

void find_ops(const vector<Op> &ops, const string &output)
{
  for (const auto &op : ops)
  {
    if (op.output == output)
    {
      display_op(op);
      if (op.input1[0] != 'x')
        find_ops(ops, op.input1);
      if (op.input2[0] != 'x')
        find_ops(ops, op.input2);
      return;
    }
  }
}

Op find_op_with_output(const vector<Op> &ops, const string &output)
{
  for (const auto &op : ops)
    if (op.output == output)
      return op;

  cout << "No op found for " << output << endl;
  return Op();
}

Op find_op_with_inputs(const vector<Op> &ops, const string &input1, const string &input2, const string &gate)
{
  for (const auto &op : ops)
    if (op.gate == gate && ((op.input1 == input1 && op.input2 == input2) || (op.input1 == input2 && op.input2 == input1)))
      return op;

  cout << "No op found for " << input1 << " " << input2 << " " << gate << endl;
  return Op();
}

void part_2()
{
  auto [values, ops] = read_input();

  string carry_in = find_op_with_inputs(ops, "x00", "y00", "AND").output;
  for (int i = 1; i < 45; i++)
  {
    string num = (i < 10 ? "0" + to_string(i) : to_string(i));
    string x = "x" + num;
    string y = "y" + num;
    string z = "z" + num;

    Op x_xor_y = find_op_with_inputs(ops, x, y, "XOR");

    Op sum = find_op_with_inputs(ops, x_xor_y.output, carry_in, "XOR");
    if (sum.output != z)
      cout << "Op with " << x_xor_y.output << " " << carry_in << " " << "XOR" << " is not " << z << endl;

    Op x_and_y = find_op_with_inputs(ops, x, y, "AND");

    Op temp = find_op_with_inputs(ops, x_xor_y.output, carry_in, "AND");

    Op carry_out = find_op_with_inputs(ops, x_and_y.output, temp.output, "OR");

    carry_in = carry_out.output;
  }
  // jgb,rkf,rrs,rvc,vcg,z09,z20,z24
}

int main()
{
  part_1();
  part_2();
}
