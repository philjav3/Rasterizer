// Phil Javinsky III
// FrameBuffer.cpp

#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int w, int h, string f) {
   width = w;
   height = h;
   outputFile = f;
}

void FrameBuffer::setWidth(int w) {
   width = w;
}
int FrameBuffer::getWidth() {
   return width;
}

void FrameBuffer::setHeight(int h) {
   height = h;
}
int FrameBuffer::getHeight() {
   return height;
}

void FrameBuffer::setFile(string f) {
   outputFile = f;
}

// line rasterization using Bresenham's line algorithm
void FrameBuffer::drawLines(const vector<Line> &lines) {
   Vector3Df *image = new Vector3Df[width * height];

   for (int i = 0; i < lines.size(); i++) {
      Vector2Df p0 = lines[i].point0;
      Vector2Df p1 = lines[i].point1;
      Vector3Df c = lines[i].color;
      if (c.x == -1) {
         c = Vector3Df(rand() % 255, rand() % 255, rand() % 255);
      }
      int x1 = p0.x; int y1 = p0.y;
      int x2 = p1.x; int y2 = p1.y;

      int x, y, xe, ye;
      int dx = x2 - x1, dy = y2 - y1;
      int dx1 = abs(dx), dy1 = abs(dy);
      int px = 2*dy1 - dx1, py = 2*dx1 - dy1;

      if (dy1 <= dx1) {
         if (dx >= 0) {
            x = x1;
            y = y1;
            xe = x2;
         }
         else {
            x = x2;
            y = y2;
            xe = x1;
         }
         image[x + y*width] = c;
         for (int i = 0; x < xe; i++) {
            x = x + 1;
            if (px < 0) {
               px = px + 2*dy1;
            }
            else {
               if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                  y = y + 1;
               }
               else {
                  y = y - 1;
               }
               px = px + 2*(dy1-dx1);
            }
            image[x + y*width] = c;
         }
      }
      else {
         if (dy >= 0) {
            x = x1;
            y = y1;
            ye = y2;
         }
         else {
            x = x2;
            y = y2;
            ye = y1;
         }
         image[x + y*width] = c;
         for (int i = 0; y < ye; i++) {
            y = y + 1;
            if (py <= 0) {
               py = py + 2*dx1;
            }
            else {
               if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                  x = x + 1;
               }
               else {
                  x = x - 1;
               }
               py = py + 2*(dx1-dy1);
            }
            image[x + y*width] = c;
         }
      }
   }
   outputImage(image);
   delete[] image;
}

// triangle rasterization using barycentric coordinates
void FrameBuffer::drawTriangles(const vector<Triangle> &triangles) {
   Vector3Df *image = new Vector3Df[width * height];

   for (int i = 0; i < triangles.size(); i++) {
      Vector2Df p0 = triangles[i].point0;
      Vector2Df p1 = triangles[i].point1;
      Vector2Df p2 = triangles[i].point2;
      Vector3Df c0 = triangles[i].color0;
      Vector3Df c1 = triangles[i].color1;
      Vector3Df c2 = triangles[i].color2;

      // get the bounding box of the triangle
      float maxX = fmax(p0.x, fmax(p1.x, p2.x));
      float minX = fmin(p0.x, fmin(p1.x, p2.x));
      float maxY = fmax(p0.y, fmax(p1.y, p2.y));
      float minY = fmin(p0.y, fmin(p1.y, p2.y));

      Vector2Df v = Vector2Df();
      float f_a = (p1.y - p2.y)*p0.x + (p2.x - p1.x)*p0.y + p1.x*p2.y - p2.x*p1.y;
      float f_b = (p2.y - p0.y)*p1.x + (p0.x - p2.x)*p1.y + p2.x*p0.y - p0.x*p2.y;
      float f_g = (p0.y - p1.y)*p2.x + (p1.x - p0.x)*p2.y + p0.x*p1.y - p1.x*p0.y;

      for (v.y = minY; v.y <= maxY; v.y++) {
         for (v.x = minX; v.x <= maxX; v.x++) {
            // get barycentric coordinates
            float alpha = ((p1.y - p2.y)*v.x + (p2.x - p1.x)*v.y + p1.x*p2.y - p2.x*p1.y) / f_a;
            float beta  = ((p2.y - p0.y)*v.x + (p0.x - p2.x)*v.y + p2.x*p0.y - p0.x*p2.y) / f_b;
            float gamma = ((p0.y - p1.y)*v.x + (p1.x - p0.x)*v.y + p0.x*p1.y - p1.x*p0.y) / f_g;

            // inside triangle
            if (alpha >= 0 && beta >= 0 && gamma >= 0) {
               if ((alpha > 0 || (f_a * ((p1.y - p2.y)*(-1) + (p2.x - p1.x)*(-1) + p1.x*p2.y - p2.x*p1.y)) > 0) &&
                   (beta  > 0 || (f_b * ((p2.y - p0.y)*(-1) + (p0.x - p2.x)*(-1) + p2.x*p0.y - p0.x*p2.y)) > 0) &&
                   (gamma > 0 || (f_g * ((p0.y - p1.y)*(-1) + (p1.x - p0.x)*(-1) + p0.x*p1.y - p1.x*p0.y)) > 0)) {
                  //c = a*c0 + b*c1 + g*c2
                  int x = alpha*c0.x + beta*c1.x + gamma*c2.x;
                  int y = alpha*c0.y + beta*c1.y + gamma*c2.y;
                  int z = alpha*c0.z + beta*c1.z + gamma*c2.z;
                  image[int(v.x + v.y*width)] = Vector3Df(x,y,z);
               }
               else { // white border
                  image[int(v.x + v.y*width)] = Vector3Df(255,255,255);
               }
          }
        }
      }
   }
   outputImage(image);
   delete[] image;
}

// output shapes to ppm file
void FrameBuffer::outputImage(const Vector3Df *image) {
   ofstream output;
   output.open(outputFile);
   // magic number, P6 or P3 (plain)
   output << "P3\n";
   // width and height
   output << width << " " << height << endl;
   // max color value
   output << 255;
   for (int y = 0; y < height; y++) {
      output << endl;
       for (int x = 0; x < width; x++) {
          output << image[x + y*width].x << " "
                 << image[x + y*width].y << " "
                 << image[x + y*width].z << " ";
       }
    }
   output.close();
}

// clear frame buffer
void FrameBuffer::clear() {
   Vector3Df *image = new Vector3Df[width * height];

   for (int y = 0; y < height; y++) {
       for (int x = 0; x < width; x++) {
          image[x + y*width] = Vector3Df(0,0,0);
       }
    }
   outputImage(image);
   delete[] image;
}
