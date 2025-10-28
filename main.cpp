#include "star.h"
#include "starGroup.h"
#include "dijkstra.h"
#include "display.h"
#pragma once

int main() {
    Display display;

    // Temporary simulated Dijkstra result
    std::vector<int> testPath = {2, 45, 77, 120, 300};
    display.setPath(testPath);

    display.start();
    return 0;
}

