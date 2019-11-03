#include "vector2d.h"


template <class T>
bool operator !=(const Vector2d<T> &p1,const Vector2d<T> &p2)
{
    return ( p1.x != p2.x and p1.y != p2.y);
}


template <class T>
Vector2d<T> operator +(const Vector2d<T> &p1,const Vector2d<T> &p2)
{
    Vector2d<T> res( p1.x + p2.x, p1.y + p2.y );
    return res;
}

template <class T>
Vector2d<T> operator -(const Vector2d<T> &p1,const Vector2d<T> &p2)
{
    Vector2d<T> res( p1.x - p2.x, p1.y - p2.y );
    return res;
}

template <class T>
Vector2d<T> operator / (const Vector2d<T> &p1,const double &p2)
{
    Vector2d<T> res( p1.x / p2, p1.y / p2 );
    return res;
}

template <class T>
Vector2d<T> operator * (const Vector2d<T> &p1,const double &p2)
{
    Vector2d<T> res( p1.x * p2, p1.y * p2 );
    return res;
}



template<class T>
Vector2d<T>::Vector2d(T x, T y)
{
  this->x = x;
  this->y = y;
}


template<class T>
Vector2d<T>::Vector2d()
{
  this->x=0;
  this->y=0;
}


template<class T>
double  Vector2d<T>::norma()
{
  return (sqrt( pow(x,2) + pow(y,2) ));
}

template<class T>
void  Vector2d<T>::zero()
{
  this->x = 0;
  this->y = 0;
}
