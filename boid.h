
#ifndef BOID_H
#define BOID_H

#include <vector>
#include <GL/glut.h>
#include "vector2d.h"
#include "vector2d.cpp"
#include <random>
using namespace std;

class Boid{
public:
  //
  Vector2d<double> position;
  Vector2d<double> velocity;
  Vector2d<double> acceleration;

  double max_force,max_speed,perception,width,height;

  Boid(double, double, double, double);
  void draw();
  void update();
  void edges();
  void behaviour(vector<Boid *>);
  Vector2d<double> align(vector<Boid *> );
  Vector2d<double> cohesion(vector<Boid *>);
  Vector2d<double> separation(vector<Boid *>);

};


#endif
