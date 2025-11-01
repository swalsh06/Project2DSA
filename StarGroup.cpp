#include <cmath>
#include <map>
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

