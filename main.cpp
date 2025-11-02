#include "star.h"
#include "StarGroup.h"
#include "display.h"
using namespace std;

double degToRad(double deg){
    return deg * M_PI / 180.0;
}

int main() {
    // Set of 100,000 stars roughly in a sphere of radius 100 pc centered on the sun
    ifstream file("1761687300163O-result.csv");
    // if (!file.is_open()) {
    //     cerr << "Failed to open star dataset file!" << endl;
    //     return 1;
    // }
    string line;
    vector<Star> stars;
    int numStars = 400;
    int counter = 0;
    getline(file, line);
    // Pull star data and make objects that are then pushed to the vector
    while (getline(file, line) && counter < numStars) {
        //cout << line << endl;
        stringstream ss(line);
        Star s;
        string token;
        getline(ss, token, ',');
        s.setId(stoll(token));
        getline(ss, token, ',');
        s.setRa(stod(token));
        getline(ss, token, ',');
        s.setDec(stod(token));
        getline(ss, token, ',');
        s.setParallax(stod(token));

        double distance = s.computeDistance();
        double raRad = degToRad(s.getRa());
        double decRad = degToRad(s.getDec());

        s.setX(distance * cos(decRad) * cos(raRad));
        s.setY(distance * cos(decRad) * sin(raRad));
        s.setZ(distance * sin(decRad));
        stars.push_back(s);

        counter++;
    }


    StarGroup sg1(stars);
    //sg1.formAdjacencyList();

    //sg1.printAdjacencyList();

    Display display(stars);
    std::cout << "Loaded " << stars.size() << " stars\n";


    // Temporary simulated Dijkstra result
    std::vector<int> testPath = {2, 45, 77, 120, 300};
    display.setPath(testPath);

    display.start();
    return 0;
}
