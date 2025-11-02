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

long long Star::getId(){
  return id;
}

int Star::getNumId(){
  return numId;
}

double Star::getX(){
  return x;
}

double Star::getY(){
  return y;
}

double Star::getZ(){
  return z;
}

double Star::getRa(){
  return ra;
}

double Star::getDec(){
  return dec;
}

double Star::getParallax(){
  return parallax;
}

double Star::computeDistance(){
    return 1000.0 / parallax;
}