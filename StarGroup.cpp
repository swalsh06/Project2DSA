#include <cmath>
#include <map>
#include "StarGroup.h"
#include <vector>
#include <unordered_map>
#include <limits>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

StarGroup::StarGroup(vector<Star> s){
  stars = s;
    nodesExplored = 0;
}

double StarGroup::calcDistance(int i, int j){
  double dx = stars[i].getX() - stars[j].getX();
  double dy = stars[i].getY() - stars[j].getY();
  double dz = stars[i].getZ() - stars[j].getZ();
  return sqrt(dx*dx + dy*dy + dz*dz);
}

map<int, vector<pair<int, float>>> StarGroup::getAdjacencyList() {
  return adjacencyList;
}

void StarGroup::printAdjacencyList() {
  for (const auto& [f, tv] : adjacencyList) {
    cout << "from " << f << " has connections to: \n";
    for (const auto& [tn, w] : tv) {
      cout << " -> to " << tn << " w " << w << "\n";
    }
  }
}
void StarGroup::formAdjacencyList() {
  for(int i = 0; i < stars.size(); i++){
    for(int j = 0; j < stars.size(); j++){
      // sg1 = whatever instance of StarGroup is being used
      if (i != j){
        float distance = calcDistance(i,j);
        if(distance < 5.0){
          adjacencyList[i].push_back({j, distance});
        }
      }
    }
  }
}

// Dijkstra's algorithm
// Returns shortest distances from start node to target node
vector<int> StarGroup::dijkstra(const unordered_map<int, vector<pair<int,float>>>& graph, int start, int target){

    unordered_map<int, float> dist;
    unordered_map<int, int> prev;

    int infinity = numeric_limits<float>::infinity();;

    //set all distances to infinity
    for (auto& pair : graph) {
        dist[pair.first] = infinity;
    }
    dist[start] = 0;

    // Priority queue <current_distance, starID>
    priority_queue<pair<float,int>, vector<pair<float,int>>, greater<pair<float,int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        nodesExplored++;

        if (u == target) {
            break;
        }// early stopping

        for (auto neighbor: graph.at(u)) {
            int v = neighbor.first;
            float weight = neighbor.second;
            float alt = d + weight;

            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                pq.push({alt, v});
            }
        }
    }

    // Reconstruct path
    vector<int> path;
    if (dist[target] == infinity) {
        return path;  // no path
    }
    int current = target;
    while (current != start) {
        path.push_back(current);
        current = prev[current];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
};

//heuristic for A*
float StarGroup::heuristic(int from, int to, const unordered_map<int, pair<float,float>>& starPos) {
    auto [x1,y1] = starPos.at(from);
    auto [x2,y2] = starPos.at(to);
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

// A* algorithm
// Returns shortest distances from start node to target node using heuristic
vector<int> StarGroup::a_star(const unordered_map<int, vector<pair<int,float>>>& graph, const unordered_map<int, pair<float,float>>& starPos, int start, int end) {

    //gScore : dist from start so far
    //fScore : gScore + heuristic estimate to goal

    unordered_map<int,float> gScore;
    unordered_map<int,int> prev;

    int infinity = numeric_limits<float>::infinity();;

    for (auto& pair : graph) gScore[pair.first] = infinity;
    gScore[start] = 0;

    // Priority queue: {fScore, starID}
    priority_queue<pair<float,int>, vector<pair<float,int>>, greater<pair<float,int>>> pq;
    pq.push({heuristic(start, end, starPos), start});

    while (!pq.empty()) {
        auto [f, u] = pq.top();
        pq.pop();
        nodesExplored++;

        if (u == end) {
            break; // goal reached
        }
        for (auto [v, weight] : graph.at(u)) {
            float tentative_g = gScore[u] + weight;
            if (tentative_g < gScore[v]) {
                gScore[v] = tentative_g;
                prev[v] = u;
                float fScore = tentative_g + heuristic(v, end, starPos);
                pq.push({fScore, v});
            }
        }
    }

    // Reconstruct path
    vector<int> path;
    if (gScore[end] == numeric_limits<float>::infinity()) return path;
    for (int current = end; current != start; current = prev[current]) path.push_back(current);
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;

}
