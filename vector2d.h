#ifndef VECTOR2D_H
#define VECTOR2D_H


#include <math.h>
template<class T>
class Vector2d
{
public:
  T x,y;
  Vector2d(T,T);
  Vector2d();

  double norma();
  void zero();
};




#endif
