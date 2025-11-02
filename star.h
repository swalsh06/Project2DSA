#ifndef STAR_H
#define STAR_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>

class Star {
    long long id;
    int numId;
    double x, y, z;
    // ra: right ascension (sky longitude degrees)
    // dec: declination (sky latitude degrees)
    // parallax: apparent shift in position (milliarcseconds) - used to estimate distance
    double ra, dec, parallax;
    public:
		Star(int c);
        void setId(long long id);
        void setNumId(int numId);
        void setX(double x);
        void setY(double y);
        void setZ(double z);
        void setRa(double ra);
        void setDec(double dec);
        void setParallax(double parallax);
        long long getId() const;
        int getNumId() const;
        double getX() const;
        double getY() const;
        double getZ() const;
        double getRa() const;
        double getDec() const;
        double getParallax() const;

    	double computeDistance() const;
};




#endif //STAR_H
