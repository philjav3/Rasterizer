// Phil Javinsky III
// Vector2D

#include <cmath>
#include <fstream>
#include <vector>
using namespace std;

template<typename vec>
class Vector2D {
public:
    vec x, y;
    Vector2D() : x(vec(0)), y(vec(0)) {}
    Vector2D(vec x2) : x(x2), y(x2) {}
    Vector2D(vec x2, vec y2) : x(x2), y(y2) {}
    Vector2D& normalize() {
      vec nor2 = length2();
      if (nor2 > 0) {
         vec invNor = 1 / sqrt(nor2);
         x *= invNor, y *= invNor;
      }
      return *this;
    }
    Vector2D<vec> operator * (const Vector2D<vec> &v) const {
      return Vector2D<vec>(x * v.x, y * v.y);
    }
    Vector2D<vec> operator - (const Vector2D<vec> &v) const {
      return Vector2D<vec>(x - v.x, y - v.y);
    }
    Vector2D<vec> operator + (const Vector2D<vec> &v) const {
      return Vector2D<vec>(x + v.x, y + v.y);
    }
    Vector2D<vec> operator - () const {
      return Vector2D<vec>(-x, -y);
    }
    vec dot(const Vector2D<vec> &v) const {
      return x * v.x + y * v.y;
    }
    vec length2() const {
      return x * x + y * y;
    }
};

typedef Vector2D<float> Vector2Df;
