#ifndef STARGROUP_H
#define STARGROUP_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include "star.h"

class starGroup {
  vector<star> stars;
  public:
    double degToRad(double deg);
    double computeDistance(double parallaxMas);
};


#endif //STARGROUP_H
