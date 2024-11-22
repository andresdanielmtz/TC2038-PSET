#include <iostream>
#include <map>
#include <vector>

std::vector<int> graphSets(std::map<int, std::vector<int> > graph) {
  if (graph.size() == 0) {
    return std::vector<int>();
  }

  // If only one node in the graph, return that node
  if (graph.size() == 1) {
    std::vector<int> v;
    for (auto const &[key, val] : graph) {
      v.push_back(key);
    }
    return v;
  }

  int vCurrent = graph.begin()->first;
  std::map<int, std::vector<int> > graph2(graph); // copy of graph

  graph2.erase(vCurrent); // take out the current node
  std::vector<int> res1 = graphSets(graph);

  // After that, we will now check for the neighbors of the current node and so
  // on

  for (auto v : graph.at(vCurrent)) {
    if (graph2.count(v)) {
      graph2.erase(v);
    }
  }

  // This result set contains vCurrent,
  // and the result of recursive call assuming neighbors
  // of vCurrent are not selected
  std::vector<int> res2;
  res2.push_back(vCurrent);
  std::vector<int> res2Sub = graphSets(graph2);
  res2.insert(res2.end(), res2Sub.begin(), res2Sub.end());

  // Our final result is the one which is bigger, return that
  if (res1.size() > res2.size()) {
    return res1;
  }
  return res2;
}
