#ifndef STARGROUP_H
#define STARGROUP_H
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>
#include "star.h"
using namespace std;

class StarGroup {
    vector<Star> stars;
    unordered_map<int, vector<pair<int, float>>> adjacencyList;
    unordered_map<int, pair<double, double>> starPositions;
    int nodesExplored;
  public:
    StarGroup(vector<Star> s);
    unordered_map<int, vector<pair<int, float>>> getAdjacencyList();
    void printAdjacencyList();
    void formAdjacencyList();
    unordered_map<int, pair<double, double>> getStarPositions();
    void printStarPositions();
    void formStarPositions();
    double calcDistance(int i, int j);
    vector<int> dijkstra(int start, int target);
    float heuristic(int from, int to);
    vector<int> a_star(int start, int end);
};



#endif //STARGROUP_H
