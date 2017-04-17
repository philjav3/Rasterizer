// Phil Javinsky III
// Vector3D

#include <cmath>
#include <fstream>
#include <vector>
using namespace std;

template<typename vec>
class Vector3D {
public:
    vec x, y, z;
    Vector3D() : x(vec(0)), y(vec(0)), z(vec(0)) {}
    Vector3D(vec x2) : x(x2), y(x2), z(x2) {}
    Vector3D(vec x2, vec y2, vec z2) : x(x2), y(y2), z(z2) {}
    Vector3D& normalize() {
      vec nor2 = length2();
      if (nor2 > 0) {
         vec invNor = 1 / sqrt(nor2);
         x *= invNor, y *= invNor, z *= invNor;
      }
      return *this;
    }
    Vector3D<vec> operator * (const Vector3D<vec> &v) const {
      return Vector3D<vec>(x * v.x, y * v.y, z * v.z);
    }
    Vector3D<vec> operator - (const Vector3D<vec> &v) const {
      return Vector3D<vec>(x - v.x, y - v.y, z - v.z);
    }
    Vector3D<vec> operator + (const Vector3D<vec> &v) const {
      return Vector3D<vec>(x + v.x, y + v.y, z + v.z);
    }
    Vector3D<vec> operator - () const {
      return Vector3D<vec>(-x, -y, -z);
    }
    vec dot(const Vector3D<vec> &v) const {
      return x * v.x + y * v.y + z * v.z;
    }
    vec length2() const {
      return x * x + y * y + z * z;
    }
};

typedef Vector3D<float> Vector3Df;
