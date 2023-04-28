#pragma once

#include "Ray.h"
#include "VecTypes.h"

class Camera
{
public:
   static constexpr const double kAspectRatio = 16.0 / 9.0;

   Camera()
   {
      double viewportHeight = 2.0;
      double viewportWidth = viewportHeight * kAspectRatio;
      double focalLength = 1.0;

      location = Point3(0.0, 0.0, 0.0);
      horizontal = Vec3(viewportWidth, 0.0, 0.0);
      vertical = Vec3(0.0, viewportHeight, 0.0);
      lowerLeftCorner = location - horizontal / 2.0 - vertical / 2.0 + Vec3(0.0, 0.0, focalLength);
   }

   Ray getRay(double u, double v) const
   {
      return Ray(location, lowerLeftCorner + u * horizontal + v * vertical - location);
   }

private:
   Point3 location;
   Vec3 horizontal;
   Vec3 vertical;
   Point3 lowerLeftCorner;
};
