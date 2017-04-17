// Phil Javinsky III
// Triangle.cpp

class Triangle {
public:
   Vector2Df point0, point1, point2;
   Vector3Df color0, color1, color2;

   Triangle(const Vector2Df &p0, const Vector2Df &p1, const Vector2Df &p2,
               const Vector3Df &c0, const Vector3Df &c1, const Vector3Df &c2) {
      point0 = p0;
      point1 = p1;
      point2 = p2;
      color0 = c0;
      color1 = c1;
      color2 = c2;
   }
};
