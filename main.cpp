#include "Star.h"
#include "StarGroup.h"
#include "dijkstra.h"
#include "display.h"
#pragma once
using namespace std;

double degToRad(double deg){
    return deg * M_PI / 180.0;
}

int main() {
  	/*  Drawing edges between stars
		for(int i = 0; i < stars.size; i++){
			for(int j = i + 1; j < stars.size(); j++){
				// sg1 = whatever instance of StarGroup is being used
				double distance = sg1.calcDistance(i,j);
				if(distance < 5.0){
					draw edge here
				}
			}
		}
  	 */
	// Set of 100,000 stars roughly in a sphere of radius 100 pc centered on the sun
	// ifstream file("1761687300163O-result.csv");
	// string line;
 //    vector<Star> stars;
 //
 //    int numStars = 400;
 //    int counter = 0;
 //    // Pull star data and make objects that are then pushed to the vector
 //    while (getline(file, line) && count < numStars) {
 //    	stringstream ss(line);
 //      	Star s;
 //      	string token;
 //      	getline(ss, token, ',');
 //      	s.setId(stoll(token));
 //      	getline(ss, token, ',');
 //      	s.setRa(stod(token));
 //      	getline(ss, token, ',');
 //      	s.setDec(stod(token));
 //      	getline(ss, token, ',');
 //      	s.setParallax(stod(token));
 //
 //      	double distance = s.computeDistance();
 //      	double raRad = degToRad(s.getRa());
 //      	double decRad = degToRad(s.getDec());
 //
 //      	s.setX(distance * cos(decRad) * cos(raRad));
 //      	s.setY(distance * cos(decRad) * sin(raRad));
 //      	s.setZ(distance * sin(decRad));
 //
 //        s.setNumId(counter);
 //      	stars.push_back(s);
 //
 //      	counter++;
 //    }


    // StarGroup sg1(stars);


    Display display;

    // Temporary simulated Dijkstra result
    std::vector<int> testPath = {2, 45, 77, 120, 300};
    display.setPath(testPath);

    display.start();
    return 0;
}

