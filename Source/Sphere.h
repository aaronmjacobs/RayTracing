#pragma once

#include "Ray.h"
#include "VecTypes.h"

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

class Sphere
{
public:
   Sphere() = default;

   Sphere(const Point3& sphereCenter, double sphereRadius)
      : center(sphereCenter)
      , radius(glm::max(0.0, sphereRadius))
   {
   }

   const Point3& getCenter() const
   {
      return center;
   }

   void setCenter(const Point3& newCenter)
   {
      center = newCenter;
   }

   double getRadius() const
   {
      return radius;
   }

   void setRadius(double newRadius)
   {
      radius = glm::max(0.0, newRadius);
   }

   bool hit(const Ray& ray) const
   {
      Vec3 toCenter = center - ray.getOrigin();

      double a = glm::length2(ray.getDirection());
      double b = 2.0 * glm::dot(toCenter, ray.getDirection());
      double c = glm::length2(toCenter) - radius * radius;
      double discriminant = b * b - 4.0 * a * c;

      return discriminant > 0.0;
   }

private:
   Point3 center;
   double radius = 0.0;
};
