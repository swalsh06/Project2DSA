#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include "starGroup.h"

double starGroup::degToRad(double deg){
    return deg * M_PI / 180.0;
}

double starGroup::computeDistance(double parallaxMas){
    return 1000.0 / parallaxMas;
}
