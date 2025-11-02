#ifndef STARGROUP_H
#define STARGROUP_H
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <unordered_map>
#include "star.h"
using namespace std;

class StarGroup {
    vector<Star> stars;
    map<int, vector<pair<int, float>>> adjacencyList;
    int nodesExplored;
  public:
    StarGroup(vector<Star> s);
    map<int, vector<pair<int, float>>> getAdjacencyList();
    void printAdjacencyList();
    void formAdjacencyList();
    double calcDistance(int i, int j);
    vector<int> dijkstra(const unordered_map<int, vector<pair<int,float>>>& graph, int start, int target);
    float heuristic(int from, int to, const unordered_map<int, pair<float,float>>& starPos);
    vector<int> a_star(const unordered_map<int, vector<pair<int,float>>>& graph, const unordered_map<int, pair<float,float>>& starPos, int start, int end);
};



#endif //STARGROUP_H
