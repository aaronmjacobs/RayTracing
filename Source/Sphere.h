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

   bool hit(const Ray& ray, double& t) const
   {
      Vec3 toOrigin = ray.getOrigin() - center;

      double a = 1.0; // glm::length2(ray.getDirection()); // Ray directions are normalized
      double b = 2.0 * glm::dot(toOrigin, ray.getDirection());
      double c = glm::length2(toOrigin) - radius * radius;
      double discriminant = b * b - 4.0 * a * c;

      if (discriminant < 0.0)
      {
         return false;
      }

      t = (-b - glm::sqrt(discriminant)) / (2.0 * a);
      return true;
   }

private:
   Point3 center;
   double radius = 0.0;
};
