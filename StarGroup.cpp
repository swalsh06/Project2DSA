#include <cmath>
#include "StarGroup.h"
using namespace std;

StarGroup::StarGroup(vector<Star> s){
  stars = s;
}

double StarGroup::calcDistance(int i, int j){
  double dx = stars[i].getX() - stars[j].getX();
  double dy = stars[i].getY() - stars[j].getY();
  double dz = stars[i].getZ() - stars[j].getZ();
  return sqrt(dx*dx + dy*dy + dz*dz);
}

