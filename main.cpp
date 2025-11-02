#include "star.h"
#include "StarGroup.h"
#include "display.h"
using namespace std;



int main() {
    // Set of 100,000 stars roughly in a sphere of radius 100 pc centered on the sun
    ifstream file("1761687300163O-result.csv");
    // if (!file.is_open()) {
    //     cerr << "Failed to open star dataset file!" << endl;
    //     return 1;
    // }

    vector<Star> stars;

    vector<string> lines;
    string line;
    getline(file, line);
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    int numStars = 400;


    StarGroup sg1(lines, numStars);

    //sg1.printAdjacencyList();

    Display display(stars);
    std::cout << "Loaded " << stars.size() << " stars\n";


    // Temporary simulated Dijkstra result
    std::vector<int> testPath = {2, 45, 77, 120, 300};
    display.setPath(testPath);

    display.start();
    return 0;
}
