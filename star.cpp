#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include "Star.h"
using namespace std;

Star::Star(int c) {
  numId = c;
}


void Star::setId(long long id){
  this->id = id;
}

void Star::setNumId(int numId){
  this->numId = numId;
}

void Star::setX(double x){
  this->x = x;
}

void Star::setY(double y){
  this->y = y;
}

void Star::setZ(double z){
  this->z = z;
}

void Star::setRa(double ra){
  this->ra = ra;
}

void Star::setDec(double dec){
  this->dec = dec;
}

void Star::setParallax(double parallax){
  this->parallax = parallax;
}

long long Star::getId() const{
  return id;
}

int Star::getNumId() const{
  return numId;
}

double Star::getX() const{
  return x;
}

double Star::getY() const {
  return y;
}

double Star::getZ() const {
  return z;
}

double Star::getRa() const{
  return ra;
}

double Star::getDec() const{
  return dec;
}

double Star::getParallax() const{
  return parallax;
}

double Star::computeDistance() const{
    return 1000.0 / parallax;
}