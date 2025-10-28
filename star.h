#ifndef STAR_H
#define STAR_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>

struct Star {
    long long id;
    double x, y, z;
    // ra: right ascension (sky longitude degrees)
    // dec: declination (sky latitude degrees)
    // parallax: apparent shift in position (milliarcseconds) - used to estimate distance
    double ra, dec, parallax;
};




#endif //STAR_H
