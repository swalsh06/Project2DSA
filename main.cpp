#include "star.h"

#include "display.h"

int main() {
    Display display;

    // Temporary simulated Dijkstra result
    std::vector<int> testPath = {2, 45, 77, 120, 300};
    display.setPath(testPath);

    display.start();
    return 0;
}

