// Phil Javinsky III
// FrameBuffer.h

#include <iostream>
#include <cmath>
#include "Vector3D.cpp"
#include "Vector2D.cpp"
#include "Line.cpp"
#include "Triangle.cpp"
using namespace std;

class FrameBuffer {
public:
   FrameBuffer(int w, int h, string f);
   void setWidth(int w);
   int getWidth();
   void setHeight(int h);
   int getHeight();
   void setFile(string f);
   void drawLines(const vector<Line> &lines);
   void drawTriangles(const vector<Triangle> &triangles);
   void outputImage(const Vector3Df *image);
   void clear();

private:
   int width;
   int height;
   string outputFile;
   bool randomColor;
};
