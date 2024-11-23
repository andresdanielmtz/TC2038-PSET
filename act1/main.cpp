#include <iostream>
#include <vector>
#include <map>
#include <cmath>

struct Tower {
    int x, y;
    Tower(int x_, int y_) : x(x_), y(y_) {}
};

double getDistance(const Tower& t1, const Tower& t2) {
    return sqrt(pow(t1.x - t2.x, 2) + pow(t1.y - t2.y, 2));
}

// Create adjacency list representation of interference graph

std::map<int, std::vector<int> > buildInterferenceGraph(const std::vector<Tower>& towers, double d) {
    std::map<int, std::vector<int> > graph;
    
    for (int i = 0; i < towers.size(); i++) {
        graph[i] = std::vector<int>();
    }
    
    // Add edges 
    for (int i = 0; i < towers.size(); i++) {
        for (int j = i + 1; j < towers.size(); j++) {
            if (getDistance(towers[i], towers[j]) == d) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }
    
    return graph;
}

void printGraph(const std::map<int, std::vector<int> >& graph) {
    for (auto const &[key, val] : graph) {
        std::cout << key << ": ";
        for (auto v : val) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<int> graphSets(std::map<int, std::vector<int> > graph) {
    if (graph.size() == 0) {
        return std::vector<int>();
    }
    
    if (graph.size() == 1) {
        std::vector<int> v;
        for (auto const &[key, val] : graph) {
            v.push_back(key);
        }
        return v;
    }
    
    int vCurrent = graph.begin()->first;
    std::map<int, std::vector<int> > graph2(graph); // Copy of graph
    graph2.erase(vCurrent); // Remove vCurrent from graph
    
    std::vector<int> res1 = graphSets(graph2); // get independent set without vCurrent
    
    for (auto v : graph.at(vCurrent)) {
        if (graph2.count(v)) {
            graph2.erase(v);
        }
    }
    
    std::vector<int> res2;
    res2.push_back(vCurrent);
    std::vector<int> res2Sub = graphSets(graph2);
    res2.insert(res2.end(), res2Sub.begin(), res2Sub.end());
    
    if (res1.size() > res2.size()) {
        return res1;
    }
    return res2;
}

int main() {
    int n, d;
    std::cin >> n >> d;
    
    std::vector<Tower> towers;
    for (int i = 0; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        towers.push_back(Tower(x, y));
    }
 
    
    // Build interference graph
    auto interferenceGraph = buildInterferenceGraph(towers, d);
    printGraph(interferenceGraph);

    // Find maximum independent set
    auto remainingTowers = graphSets(interferenceGraph);
    std::cout << "Remaining towers: " << remainingTowers.size() << std::endl;
    // Calculate minimum number of towers to destroy
    int towersToDestroy = n - remainingTowers.size();
    
    std::cout << towersToDestroy << std::endl;
    
    return 0;
}