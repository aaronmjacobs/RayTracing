#pragma once

#include "VecTypes.h"

class Ray
{
public:
   Ray() = default;

   Ray(const Point3& rayOrigin, const Vec3& rayDirection)
      : origin(rayOrigin)
      , direction(rayDirection)
   {
   }

   const Point3& getOrigin() const
   {
      return origin;
   }

   const Vec3& getDirection() const
   {
      return direction;
   }

   Point3 at(double t) const
   {
      return origin + direction * t;
   }

private:
   Point3 origin;
   Vec3 direction;
};
