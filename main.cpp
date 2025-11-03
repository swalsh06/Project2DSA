#include "star.h"
#include "StarGroup.h"
#include "display.h"
using namespace std;



int main() {
    // Set of 100,000 stars roughly in a sphere of radius 100 pc centered on the sun
    ifstream file("1761687300163O-result.csv");


    vector<string> lines;
    string line;
    getline(file, line);
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    std::cout << "Loaded " << lines.size() << " stars\n";
    //int numStars = 400;


    //StarGroup sg1(lines, numStars);


    // sg1.printAdjacencyList();
    // vector<Star> stars = sg1.getStars();

    Display display(lines);

    display.start();
    return 0;
}