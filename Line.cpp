// Phil Javinsky III
// Line.cpp

class Line {
public:
   Vector2Df point0, point1;
   Vector3Df color;

   Line(const Vector2Df &p0, const Vector2Df &p1, const Vector3Df &c) {
      point0 = p0;
      point1 = p1;
      color = c;
   }
};
