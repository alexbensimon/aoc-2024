#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<pair<string, string>> read_input()
{
  vector<pair<string, string>> pairs;
  ifstream file("input.txt");
  string line;

  while (getline(file, line))
  {
    // Find the position of the hyphen
    size_t hyphen_pos = line.find('-');

    // Split the line at the hyphen
    string first = line.substr(0, hyphen_pos);
    string second = line.substr(hyphen_pos + 1);

    // Add the pair to our vector
    pairs.push_back({first, second});
  }

  return pairs;
}

void part_1()
{
  auto pairs = read_input();

  map<string, set<string>> graph;
  for (auto pair : pairs)
  {
    graph[pair.first].insert(pair.second);
    graph[pair.second].insert(pair.first);
  }

  set<tuple<string, string, string>> triplets;
  for (auto &[node, neighbors] : graph)
  {
    for (auto &n1 : neighbors)
    {
      for (auto &n2 : graph[n1])
      {
        if (graph[n2].count(node))
        {
          vector<string> triplet = {node, n1, n2};
          sort(triplet.begin(), triplet.end());
          triplets.insert(make_tuple(triplet[0], triplet[1], triplet[2]));
        }
      }
    }
  }

  int ans = 0;
  for (auto &[a, b, c] : triplets)
  {
    if (a[0] == 't' || b[0] == 't' || c[0] == 't')
      ans++;
  }

  cout << ans << endl;
}

void bronKerbosch(set<string> currentClique, set<string> candidates, set<string> excluded, map<string, set<string>> &graph, set<string> &maxClique)
{
  if (candidates.empty() && excluded.empty())
  {
    // Found a maximal clique
    if (currentClique.size() > maxClique.size())
    {
      maxClique = currentClique;
    }
    return;
  }

  // Iterate through candidates
  for (auto it = candidates.begin(); it != candidates.end();)
  {
    string node = *it;

    // Recurse with node added to currentClique, intersection of neighbors with candidates and excluded
    set<string> newClique = currentClique;
    newClique.insert(node);

    set<string> newCandidates, newExcluded;
    for (string neighbor : graph[node])
    {
      if (candidates.count(neighbor))
        newCandidates.insert(neighbor);
      if (excluded.count(neighbor))
        newExcluded.insert(neighbor);
    }

    bronKerbosch(newClique, newCandidates, newExcluded, graph, maxClique);

    // Move node from candidates to excluded
    it = candidates.erase(it);
    excluded.insert(node);
  }
}

void part_2()
{
  auto pairs = read_input();

  map<string, set<string>> graph;
  for (auto pair : pairs)
  {
    graph[pair.first].insert(pair.second);
    graph[pair.second].insert(pair.first);
  }

  set<string> currentClique, candidates, excluded, maxClique;
  // Initialize candidates with all nodes in the graph
  for (auto &[node, neighbors] : graph)
  {
    candidates.insert(node);
  }
  bronKerbosch(currentClique, candidates, excluded, graph, maxClique);

  for (const string &node : maxClique)
  {
    cout << node << ",";
  }
  cout << endl;
}

int main()
{
  part_1();
  part_2();
}
