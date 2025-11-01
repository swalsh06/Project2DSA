#include "dijkstra.h"
#include <vector>
#include <unordered_map>
#include <limits>
#include <queue>
#include <algorithm>
#include <iostream>

//
// Created by srwal on 10/28/2025.
//
using namespace std;

// Returns shortest distances from start node to target node
vector<int> dijkstra(const unordered_map<int, vector<pair<int,float>>>& graph, int start, int target){

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

        if (u == target) break;  // early stopping

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
