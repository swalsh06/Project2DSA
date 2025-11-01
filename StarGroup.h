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
#include "star.h"
using namespace std;

class StarGroup {
    vector<Star> stars;
    map<int, vector<pair<int, float>>> adjacencyList;
  public:
    StarGroup(vector<Star> s);
    map<int, vector<pair<int, float>>> getAdjacencyList();
    void printAdjacencyList();
    void formAdjacencyList();
    double calcDistance(int i, int j);
};


#endif //STARGROUP_H
