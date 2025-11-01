#ifndef STARGROUP_H
#define STARGROUP_H
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include "star.h"
using namespace std;

class StarGroup {
  vector<Star> stars;
  public:
    StarGroup(vector<Star> s);
    double calcDistance(int i, int j);
};


#endif //STARGROUP_H
