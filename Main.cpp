// Phil Javinsky III
// Main.cpp

#include <cstdlib>
using namespace std;

#include "FrameBuffer.h"

int main() {
   FrameBuffer buffer (800, 600, "lines1.ppm");
   vector<Triangle> triangles;
   vector<Line> lines;

   // First line image
   int numLines = 36;
   int midX = buffer.getWidth()/2;
   int midY = buffer.getHeight()/2;
   for (int i = 1; i <= numLines; i++) {
      int angle = (360/numLines) * i;
      int x = midX + 225 * cos(angle * M_PI/180); // x point on edge of circle
      int y = midY + 225 * sin(angle * M_PI/180); // y point on edge of circle
      lines.push_back(Line(Vector2Df(midX,midY), Vector2Df(x,y), Vector3Df(-1,0,0)));
   }
   buffer.drawLines(lines);

   // Second line image
   lines.clear();
   buffer.setFile("lines2.ppm");
   buffer.setWidth(641);
   buffer.setHeight(641);
   int w = buffer.getWidth() - 1;
   int h = buffer.getHeight() - 1;
   int a = 0, b = 0;
   int a1 = h, b1 = w;

   for (int i = 0; i <= 80; i++) {
      // lower left corner
      lines.push_back(Line(Vector2Df(0,a), Vector2Df(b,h), Vector3Df(-1,0,0)));
      // upper right corner
      lines.push_back(Line(Vector2Df(b,0), Vector2Df(w,a), Vector3Df(-1,0,0)));
      // upper left corner
      lines.push_back(Line(Vector2Df(b,0), Vector2Df(0,a1), Vector3Df(-1,0,0)));
      // lower right corner
      lines.push_back(Line(Vector2Df(w,a), Vector2Df(b1,h), Vector3Df(-1,0,0)));
      a += 8;
      b += 8;
      a1 -= 8;
      b1 -= 8;

   }
   buffer.drawLines(lines);

   /////////////////////////////////
   buffer.setWidth(800);
   buffer.setHeight(600);
   // First triangle image
   buffer.setFile("triangles1.ppm");
   triangles.push_back(Triangle(Vector2Df(0,0), Vector2Df(799,0), Vector2Df(799,599),
                        Vector3Df(0,0,0), Vector3Df(125,125,125), Vector3Df(255,255,255)));
   triangles.push_back(Triangle(Vector2Df(799,599), Vector2Df(0,599), Vector2Df(0,0),
                         Vector3Df(255,0,0), Vector3Df(0,255,0), Vector3Df(0,0,255)));
   buffer.drawTriangles(triangles);

   // Second triangle image
   triangles.clear();
   buffer.setFile("triangles2.ppm");
   triangles.push_back(Triangle(Vector2Df(200,0), Vector2Df(200,200), Vector2Df(0,200),
                        Vector3Df(255,255,0), Vector3Df(0,255,255), Vector3Df(255,0,255)));
   triangles.push_back(Triangle(Vector2Df(200,0), Vector2Df(799,200), Vector2Df(200,200),
                        Vector3Df(255,0,0), Vector3Df(255,0,0), Vector3Df(0,0,255)));
   triangles.push_back(Triangle(Vector2Df(200,599), Vector2Df(200,200), Vector2Df(799,200),
                        Vector3Df(0,255,0), Vector3Df(0,0,0), Vector3Df(0,0,255)));
   triangles.push_back(Triangle(Vector2Df(200,200), Vector2Df(200,599), Vector2Df(0,200),
                        Vector3Df(0,255,0), Vector3Df(255,255,0), Vector3Df(255,255,255)));
   buffer.drawTriangles(triangles);

   // Third triangle image
   triangles.clear();
   buffer.setFile("triangles3.ppm");
   triangles.push_back(Triangle(Vector2Df(300,50), Vector2Df(200,150), Vector2Df(600,50),
                        Vector3Df(255,100,100), Vector3Df(255,100,100), Vector3Df(255,100,100)));
   triangles.push_back(Triangle(Vector2Df(200,150), Vector2Df(600,50), Vector2Df(500,150),
                        Vector3Df(255,100,100), Vector3Df(255,100,100), Vector3Df(255,100,100)));
   triangles.push_back(Triangle(Vector2Df(200,150), Vector2Df(500,150), Vector2Df(200,450),
                        Vector3Df(255,255,100), Vector3Df(255,255,100), Vector3Df(255,255,100)));
   triangles.push_back(Triangle(Vector2Df(200,450), Vector2Df(500,150), Vector2Df(500,450),
                        Vector3Df(255,255,100), Vector3Df(255,255,100), Vector3Df(255,255,100)));
   triangles.push_back(Triangle(Vector2Df(600,50), Vector2Df(500,150), Vector2Df(500,450),
                        Vector3Df(100,100,255), Vector3Df(100,100,255), Vector3Df(100,100,255)));
   triangles.push_back(Triangle(Vector2Df(600,50), Vector2Df(500,450), Vector2Df(600,350),
                        Vector3Df(100,100,255), Vector3Df(100,100,255), Vector3Df(100,100,255)));
   buffer.drawTriangles(triangles);

}
